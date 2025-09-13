#include "SceneMinimap.hpp"

#include <QGraphicsView>
#include <QMouseEvent>

SceneMinimap::SceneMinimap(QWidget* parent)
	: base_t(parent), m_targetView(nullptr)
{
	setFrameShape(QFrame::Box);
}

QGraphicsView const* SceneMinimap::getTargetView() const { return m_targetView; }
void SceneMinimap::setTargetView(QGraphicsView* targetView)
{
	m_targetView = targetView;
	connect(m_targetView->scene(), &QGraphicsScene::changed, [this]()
	{
		update();
	});
}

QPoint SceneMinimap::mapFromScene(QPointF const& pt) const
{
	if (m_targetView == nullptr || m_targetView->scene() == nullptr)
		return QPoint{};

	QGraphicsScene const* scene = m_targetView->scene();
	qreal const sceneWidth = scene->sceneRect().width();
	qreal const sceneHeight = scene->sceneRect().height();

	qreal const unitsInPx = std::max(sceneWidth / width(), sceneHeight / height());

	// In general, there are two possible scenarios:
	//     - scene fills the entire horizontal space of the minimap
	//     - scene fills the entire vertical one.
	// During this check, both the aspect ratio of the scene and the
	// aspect ratio of the minimap itself must be taken into account.
	Qt::Orientation const sceneOrientationInMinimap = (sceneWidth / width() > sceneHeight / height() ?
		Qt::Horizontal : Qt::Vertical);

	// Calculate the necessary base offset for the point (0, 0) in the coordinates
	// of the scene so that its projection in the coordinates of the view coincides
	// with the beginning of the scene that the minimap displays
	QSizeF const offset = [&]
	{
		// Align the beginning of the scene with the coordinates (0, 0)
		// (because the coordinates of the view start from zero)
		QSizeF value = { -scene->sceneRect().left(), -scene->sceneRect().top() };

		// For a smaller dimension, it is necessary to calculate the offset,
		// because in this dimension the scene inside the minimap is aligned.
		if (sceneOrientationInMinimap == Qt::Horizontal)
			value.rheight() += (height() * unitsInPx - sceneHeight) / 2;
		else
			value.rwidth() += (width() * unitsInPx - sceneWidth) / 2;

		return value;
	}();

	return QPoint(
		(offset.width() + pt.x()) / unitsInPx,
		(offset.height() + pt.y()) / unitsInPx
	);
}

QRect SceneMinimap::mapFromScene(QRectF const& rect) const
{
	if (m_targetView == nullptr || m_targetView->scene() == nullptr)
		return QRect{};

	return QRect(mapFromScene(rect.topLeft()), mapFromScene(rect.bottomRight()));
}

QPointF SceneMinimap::mapToScene(QPoint const& pt)
{
	// All formulas (except the endpoint) are similar to
	// those in SceneMinimap::mapFromScene()
	// TODO: separate common parts into own methods

	if (m_targetView == nullptr || m_targetView->scene() == nullptr)
		return QPoint{};

	QGraphicsScene const* scene = m_targetView->scene();
	qreal const sceneWidth = scene->sceneRect().width();
	qreal const sceneHeight = scene->sceneRect().height();

	qreal const unitsInPx = std::max(sceneWidth / width(), sceneHeight / height());

	Qt::Orientation const sceneOrientationInMinimap = (sceneWidth / width() > sceneHeight / height() ?
		Qt::Horizontal : Qt::Vertical);


	QSizeF const offset = [&]
	{
		QSizeF value = { -scene->sceneRect().left(), -scene->sceneRect().top() };

		if (sceneOrientationInMinimap == Qt::Horizontal)
			value.rheight() += (height() * unitsInPx - sceneHeight) / 2;
		else
			value.rwidth() += (width() * unitsInPx - sceneWidth) / 2;

		return value;
	}();

	return QPoint(
		pt.x() * unitsInPx - offset.width(),
		pt.y() * unitsInPx - offset.height()
	);
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
	QRectF const targetViewRect = m_targetView->mapToScene(m_targetView->viewport()->geometry()).boundingRect();
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
	QGraphicsScene* scene = (m_targetView == nullptr ? nullptr : m_targetView->scene());
	if (scene == nullptr)
		return;

	QRectF const targetViewRect = m_targetView->mapToScene(m_targetView->viewport()->geometry()).boundingRect();
	if (targetViewRect.contains(scene->sceneRect()))
		return;

	m_targetView->centerOn(mapToScene(event->pos()));
}
