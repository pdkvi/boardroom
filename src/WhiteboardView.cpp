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

	QRectF const viewRect = sceneRect();
	auto const viewRectStr = QString("view rect: LEFT = %1, TOP = %2, BOTTOM = %3, RIGHT = %4")
		.arg(viewRect.left())
		.arg(viewRect.top())
		.arg(viewRect.bottom())
		.arg(viewRect.right());

	QRectF const screenRect = mapToScene(QRect{0, 0, width(), height()}).boundingRect();
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

		QRectF const viewRect = sceneRect();
		QRectF const screenRect = mapToScene(QRect{ 0, 0, width(), height() }).boundingRect();

		if (event->modifiers().testFlag(Qt::ShiftModifier))
		{
			double const leftOffset = -std::max(offset.x(), 0.0);
			double const rightOffset = -std::min(offset.x(), 0.0);

			if (screenRect.left() + leftOffset < viewRect.left() ||
				screenRect.right() + rightOffset > viewRect.right())
			{
				setSceneRect(viewRect.adjusted(leftOffset, 0.0, rightOffset, 0.0));
			}

			translate(offset.x(), 0.0);
		}
		else
		{
			double const topOffset = -std::max(offset.y(), 0.0);
			double const bottomOffset = -std::min(offset.y(), 0.0);

			if (screenRect.top() + topOffset < viewRect.top() ||
				screenRect.bottom() + bottomOffset > viewRect.bottom())
			{
				setSceneRect(viewRect.adjusted(0.0, topOffset, 0.0, bottomOffset));
			}

			translate(0.0, offset.y());
		}
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
	{
		m_isViewRectDragging = false;
		return;
	}

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

		QRectF const viewRect = sceneRect();
		QRectF const screenRect = mapToScene(QRect{ 0, 0, width(), height() }).boundingRect();

		double const leftOffset = -std::max(offset.x(), 0.0);
		double const rightOffset = -std::min(offset.x(), 0.0);

		double const topOffset = -std::max(offset.y(), 0.0);
		double const bottomOffset = -std::min(offset.y(), 0.0);

		if (screenRect.left() + leftOffset < viewRect.left() ||
			screenRect.right() + rightOffset > viewRect.right() ||
			screenRect.top() + topOffset < viewRect.top() ||
			screenRect.bottom() + bottomOffset > viewRect.bottom())
		{
			setSceneRect(viewRect.adjusted(leftOffset, topOffset, rightOffset, bottomOffset));
		}

		translate(offset.x(), offset.y());

		m_lastMousePos = mousePos;
		return;
	}

	base_t::mouseMoveEvent(event);
}
