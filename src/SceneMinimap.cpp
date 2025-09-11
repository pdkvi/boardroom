#include "SceneMinimap.hpp"

#include <QGraphicsView>
#include <QMouseEvent>

SceneMinimap::SceneMinimap(QWidget* parent)
	: base_t(parent), m_targetView(nullptr)
{
	setFrameShape(QFrame::Box);
}

QGraphicsView const* SceneMinimap::getTargetView() const { return m_targetView; }
void SceneMinimap::setTargetView(QGraphicsView const* targetView) { m_targetView = targetView; }

QPoint SceneMinimap::mapFromScene(QPointF const& pt) const
{
	if (m_targetView == nullptr || m_targetView->scene() == nullptr)
		return QPoint{};

	// FIXME: incorrect algorithm

	QGraphicsScene const* scene = m_targetView->scene();
	qreal const sceneWidth = scene->sceneRect().width();
	qreal const sceneHeight = scene->sceneRect().height();
	qreal const sceneMaxDim = std::max(sceneWidth, sceneHeight);

	qreal const horizSceneOffset = (sceneMaxDim - sceneWidth) / 2 - scene->sceneRect().left();
	qreal const vertSceneOffset = (sceneMaxDim - sceneHeight) / 2 - scene->sceneRect().top();

	return QPoint(
		(horizSceneOffset + pt.x()) * width() / sceneMaxDim,
		(vertSceneOffset + pt.y()) * height() / sceneMaxDim
	);
}

QRect SceneMinimap::mapFromScene(QRectF const& rect) const
{
	if (m_targetView == nullptr || m_targetView->scene() == nullptr)
		return QRect{};

	return QRect(mapFromScene(rect.topLeft()), mapFromScene(rect.bottomRight()));
}

void SceneMinimap::paintEvent(QPaintEvent* event)
{
	// TODO: separate substeps into private methods for early return support

	QPainter painter(this);

	QGraphicsScene* scene = (m_targetView == nullptr ? nullptr : m_targetView->scene());

	// nothing to render, TODO: add base fill color
	if (scene == nullptr)
		return;


	// drawing aligned area background
	painter.save();
	painter.setBrush(Qt::red);
	painter.drawRect(0, 0, width(), height());
	painter.restore();

	// drawing target view background
	painter.save();
	painter.setBrush(m_targetView->backgroundBrush());
	painter.drawRect(mapFromScene(scene->sceneRect()));
	painter.restore();

	// drawing scene
	scene->render(&painter, mapFromScene(scene->sceneRect()));


	// drawing target view rect
	QRectF const targetViewRect = m_targetView->mapToScene(m_targetView->geometry()).boundingRect();
	if (targetViewRect.contains(scene->sceneRect()))
	{
		base_t::paintEvent(event);
		return;
	}

	painter.save();
	painter.setPen(QColor(0, 0, 255, 128));
	painter.setBrush(QColor(0, 0, 255, 64));
	painter.drawRect(mapFromScene(targetViewRect));
	painter.restore();

	base_t::paintEvent(event);
}

void SceneMinimap::mouseMoveEvent(QMouseEvent* event)
{
	// TODO: implement (after paintEvent)

	// QRectF const screenSceneRect = mapToScene(QRect{ 0, 0, width(), height() }).boundingRect();
	//
	// QRectF const targetScreenSceneRect = m_targetView->mapToScene(m_targetView->viewport()->geometry()).boundingRect();
	// if (targetScreenSceneRect.contains(screenSceneRect))
	// 	return;
	//
	// QPointF const newCenterPt = mapToScene(event->pos());
	// m_targetView->centerOn(newCenterPt);

	base_t::mouseMoveEvent(event);
}
