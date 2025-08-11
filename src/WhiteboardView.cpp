#include "WhiteboardView.hpp"

#include <QWheelEvent>

#include "WhiteboardScene.hpp"

WhiteboardView::WhiteboardView(QWidget* parent)
	: base_t(parent), m_isViewRectDragging(false)
{
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	auto* scene = new WhiteboardScene;
	setScene(scene);

	connect(scene, &QGraphicsScene::sceneRectChanged, this, [this](QRectF const& rect)
	{
		m_sceneRect = rect;
		syncViewRectWithScene();

		update();
	});
}

void WhiteboardView::syncViewRectWithScene()
{
	QRectF viewBoundingRect = mapFromScene(sceneRect()).boundingRect();
	QRectF sceneBoundingRect = mapFromScene(m_sceneRect).boundingRect();

	QPointF topLeft =
	{
		std::min(viewBoundingRect.left(), sceneBoundingRect.left()),
		std::min(viewBoundingRect.top(), sceneBoundingRect.top())
	};

	QPointF bottomRight =
	{
		std::max(viewBoundingRect.right(), sceneBoundingRect.right()),
		std::max(viewBoundingRect.bottom(), sceneBoundingRect.bottom())
	};

	topLeft = mapToScene(topLeft.toPoint());
	bottomRight = mapToScene(bottomRight.toPoint());

	QRectF syncRect = { topLeft, bottomRight };
	setSceneRect(syncRect);
}

void WhiteboardView::syncViewRectWithScreen()
{
	QRectF const viewRect = sceneRect();

	QSize const wndSize = size();
	QRectF const wndRect =
	{
		mapToScene(0.0, 0.0),
		mapToScene(QPoint(wndSize.width(), wndSize.height()))
	};

	QPointF topLeft =
	{
		std::max(viewRect.left(), m_sceneRect.left()),
		std::max(viewRect.top(), m_sceneRect.top())
	};
	topLeft.setX(std::min(topLeft.x(), wndRect.left()));
	topLeft.setY(std::min(topLeft.y(), wndRect.top()));

	QPointF bottomRight =
	{
		std::min(viewRect.right(), m_sceneRect.right()),
		std::min(viewRect.bottom(), m_sceneRect.bottom())
	};
	bottomRight.setX(std::max(bottomRight.x(), wndRect.right()));
	bottomRight.setY(std::max(bottomRight.y(), wndRect.bottom()));

	setSceneRect({ topLeft, bottomRight });
}

void WhiteboardView::paintEvent(QPaintEvent* event)
{
	base_t::paintEvent(event);

	QPainter painter(viewport());

	painter.setPen(Qt::red);
	painter.drawPolygon(mapFromScene(m_sceneRect));

	painter.setPen(Qt::green);
	painter.drawPolygon(mapFromScene(sceneRect()));
}

void WhiteboardView::resizeEvent(QResizeEvent* event)
{
	syncViewRectWithScreen();
	base_t::resizeEvent(event);
}

void WhiteboardView::wheelEvent(QWheelEvent* event)
{
	if (event->modifiers().testFlag(Qt::ControlModifier))
	{
		setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

		double const scaleFactor = (event->angleDelta().y() > 0.0 ? 1.25 : 0.8);
		scale(scaleFactor, scaleFactor);

		syncViewRectWithScreen();
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
	if (event->button() == Qt::MiddleButton)
	{
		m_lastMousePos = event->pos();
		m_isViewRectDragging = true;
		return;
	}

	QGraphicsView::mousePressEvent(event);
}

void WhiteboardView::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::MiddleButton)
		m_isViewRectDragging = false;

	QGraphicsView::mouseReleaseEvent(event);
}

void WhiteboardView::mouseMoveEvent(QMouseEvent* event)
{
	if (m_isViewRectDragging)
	{
		setTransformationAnchor(QGraphicsView::NoAnchor);

		QPoint const mousePos = event->pos();
		QPointF const mappedMousePos = mapToScene(mousePos);
		QPointF const mappedLastMousePos = mapToScene(m_lastMousePos);

		QPointF const offset = mappedMousePos - mappedLastMousePos;
		translate(offset.x(), offset.y());

		m_lastMousePos = mousePos;
		return;
	}

	base_t::mouseMoveEvent(event);
}
