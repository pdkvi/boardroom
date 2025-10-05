#include "WhiteboardView.hpp"

#include <QActionGroup>
#include <QWheelEvent>
#include <QBoxLayout>
#include <QMenu>

#include "WhiteboardScene.hpp"

WhiteboardView::WhiteboardView(QWidget* parent)
	: base_t(parent), m_state(CurrentState::Nothing), m_hasDebugRendering(false)
{
	auto* scene = new WhiteboardScene;
	setScene(scene);

	setBackgroundBrush(Qt::white);

	scene->addRect(-1, -1, 2, 2, QPen{}, QBrush{Qt::red});

	m_minimap = new SceneMinimap(this);
	m_minimap->setTargetView(this);

	double const maxDim = std::clamp(std::max(width(), height()) / 10, 120, 220);
	m_minimap->setMinimumSize(120, 120);
	m_minimap->setMaximumSize(maxDim, maxDim);
}

void WhiteboardView::setCurrentTool(std::unique_ptr<ToolBase>&& tool)
{ m_currentTool = std::move(tool); }

std::unique_ptr<ToolBase> const& WhiteboardView::getCurrentTool() const
{ return m_currentTool; }

QRectF WhiteboardView::targetSceneRect() const
{
	if (QGraphicsScene const* scene = this->scene())
		return scene->sceneRect();

	return QRectF{};
}

void WhiteboardView::setDebugRenderingEnabled(bool value)
{ m_hasDebugRendering = value; }

void WhiteboardView::renderDebugInformation(QPainter& painter) const
{
	if (m_hasDebugRendering == false)
		return;

	painter.setPen(Qt::red);
	painter.drawPolygon(mapFromScene(targetSceneRect()));

	painter.setPen(Qt::green);
	painter.drawPolygon(mapFromScene(sceneRect()));

	QRectF const viewRect = sceneRect();
	auto const viewRectStr = QString("view rect: LEFT = %1, TOP = %2, BOTTOM = %3, RIGHT = %4")
		.arg(viewRect.left())
		.arg(viewRect.top())
		.arg(viewRect.bottom())
		.arg(viewRect.right());

	QRectF const screenRect = mapToScene(QRect{ 0, 0, width(), height() }).boundingRect();
	auto const screenRectStr = QString("screen rect: LEFT = %1, TOP = %2, BOTTOM = %3, RIGHT = %4")
		.arg(screenRect.left())
		.arg(screenRect.top())
		.arg(screenRect.bottom())
		.arg(screenRect.right());

	QFont const monospace("Monospace", 10);
	QFontMetricsF const fm(monospace);

	painter.setPen(Qt::black);
	painter.setFont(monospace);

	QRect const viewStrRect = fm.boundingRect(viewRectStr).toRect();
	painter.drawText((width() - viewStrRect.width()) / 2, viewStrRect.height(), viewRectStr);

	painter.setPen(Qt::lightGray);
	QRect const screenStrRect = fm.boundingRect(screenRectStr).toRect();
	painter.drawText((width() - screenStrRect.width()) / 2, viewStrRect.height() + screenStrRect.height(), screenRectStr);
}

void WhiteboardView::paintEvent(QPaintEvent* event)
{
	m_minimap->setVisible(
		m_minimap->getInteractionState() == SceneMinimap::InteractionState::MovingViewport ||
		!m_minimap->isTargetSceneFitInTargetView()
	);

	base_t::paintEvent(event);

	QPainter painter(viewport());
	renderDebugInformation(painter);
}

void WhiteboardView::resizeEvent(QResizeEvent* event)
{
	m_minimap->move(width() - m_minimap->width(), 0);
	base_t::resizeEvent(event);
}

void WhiteboardView::wheelEvent(QWheelEvent* event)
{
	if (event->modifiers().testFlag(Qt::ControlModifier))
	{
		setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

		double const scaleFactor = (event->angleDelta().y() > 0.0 ? 1.25 : 0.8);
		scale(scaleFactor, scaleFactor);
	}
	else
	{
		setTransformationAnchor(QGraphicsView::NoAnchor);

		QSize const wndSize = this->size();
		QPoint const wndSceneCenter = mapFromScene(0.0, 0.0);

		QPointF offset(wndSize.width(), wndSize.height());
		offset *= (event->angleDelta().y() > 0.0 ? 0.1 : -0.1);
		offset = mapToScene(wndSceneCenter + offset.toPoint());

		if (event->modifiers().testFlag(Qt::ShiftModifier))
			translate(offset.x(), 0.0);
		else
			translate(0.0, offset.y());
	}
}

void WhiteboardView::mousePressEvent(QMouseEvent* event)
{
	switch (event->button())
	{
	case Qt::LeftButton:
	{
		if (m_currentTool == nullptr)
			break;

		m_state = CurrentState::Drawing;
		m_currentItem = m_currentTool->createItem();
		m_currentItem->startPath(mapToScene(event->pos()));
		scene()->addItem(m_currentItem->getSceneItem());
		break;
	}

	case Qt::RightButton:
	{
		if (event->modifiers().testFlag(Qt::ShiftModifier))
		{
			m_state = CurrentState::Selection;
			setDragMode(RubberBandDrag);
			base_t::mousePressEvent(event);
			break;
		}

		m_state = CurrentState::Nothing;

		auto* popup = new QMenu(this);
		popup->setAttribute(Qt::WA_DeleteOnClose);

		for (ToolItemBase::id_t id : m_currentTool->getSupportedItemsId())
		{
			std::shared_ptr<ToolItemBase const> item = ToolItemRegistry::getItem(id);

			auto* action = new QAction(item->getName());
			action->setCheckable(true);
			action->setChecked(item->getId() == m_currentTool->getCurrentItemId());

			connect(action, &QAction::triggered, [this, id]() { m_currentTool->setCurrentItemId(id); });

			popup->addAction(action);
		}

		popup->setGeometry(QRect(mapToGlobal(event->pos()), popup->sizeHint()));
		popup->show();

		break;
	}

	case Qt::MiddleButton:
	{
		m_state = CurrentState::Moving;
		break;
	}

	default:
	{
		m_state = CurrentState::Nothing;
		break;
	}
	}

	m_lastMousePos = event->pos();
}

void WhiteboardView::mouseReleaseEvent(QMouseEvent* event)
{
	switch (event->button())
	{
	case Qt::LeftButton:
	{
		if (m_currentItem == nullptr)
			break;

		m_currentItem->endPath(mapToScene(event->pos()));
		m_currentItem.release();

		break;
	}

	case Qt::RightButton:
	{
		setDragMode(NoDrag);
		break;
	}

	default:
		break;
	}

	m_state = CurrentState::Nothing;
	QGraphicsView::mouseReleaseEvent(event);
}

void WhiteboardView::mouseMoveEvent(QMouseEvent* event)
{
	switch (m_state)
	{
	case CurrentState::Drawing:
	{
		m_currentItem->updatePath(mapToScene(event->pos()));
		break;
	}

	case CurrentState::Moving:
	{
		setTransformationAnchor(QGraphicsView::NoAnchor);

		QPoint const mousePos = event->pos();
		QPointF const mappedMousePos = mapToScene(mousePos);
		QPointF const mappedLastMousePos = mapToScene(m_lastMousePos);

		QPointF const offset = mappedMousePos - mappedLastMousePos;
		translate(offset.x(), offset.y());

		m_lastMousePos = mousePos;
		break;
	}

	default:
		break;
	}

	base_t::mouseMoveEvent(event);
}
