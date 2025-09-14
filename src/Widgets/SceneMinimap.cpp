#include "SceneMinimap.hpp"

#include <QGraphicsView>
#include <QMouseEvent>

SceneMinimap::SceneMinimap(QWidget* parent)
	: base_t(parent), m_targetView(nullptr), m_viewRectColor(Qt::blue)
{
	setFrameShape(QFrame::Box);
}

bool SceneMinimap::eventFilter(QObject* watched, QEvent* event)
{
	if (event->type() == QEvent::Paint && watched == m_targetView->viewport())
		update();

	return base_t::eventFilter(watched, event);
}

QGraphicsScene* SceneMinimap::getTargetScene() const
{ return (m_targetView == nullptr ? nullptr : m_targetView->scene()); }

QGraphicsView* SceneMinimap::getTargetView() const
{ return m_targetView; }

void SceneMinimap::setTargetView(QGraphicsView* targetView)
{
	if (m_targetView)
		m_targetView->viewport()->removeEventFilter(this);

	m_targetView = targetView;
	m_targetView->viewport()->installEventFilter(this);

	update();
}

std::optional<QPoint> SceneMinimap::mapFromScene(QPointF const& pt) const
{
	std::optional<QPointF> const alignedSceneTopLeft = getAlignedSceneTopLeftPt();
	std::optional<qreal> unitsInPx = getSceneUnitsInPx();

	if (alignedSceneTopLeft == std::nullopt || unitsInPx == std::nullopt)
		return std::nullopt;

	return QPoint(
		(alignedSceneTopLeft->x() + pt.x()) / (*unitsInPx),
		(alignedSceneTopLeft->y() + pt.y()) / (*unitsInPx)
	);
}

std::optional<QRect> SceneMinimap::mapFromScene(QRectF const& rect) const
{
	std::optional<QPoint> const topLeft = mapFromScene(rect.topLeft());
	std::optional<QPoint> const bottomRight = mapFromScene(rect.bottomRight());

	if (topLeft == std::nullopt || bottomRight == std::nullopt)
		return std::nullopt;

	return QRect(*topLeft, *bottomRight);
}

std::optional<QPointF> SceneMinimap::mapToScene(QPoint const& pt)
{
	std::optional<QPointF> const alignedSceneTopLeft = getAlignedSceneTopLeftPt();
	std::optional<qreal> const unitsInPx = getSceneUnitsInPx();

	if (alignedSceneTopLeft == std::nullopt || unitsInPx == std::nullopt)
		return std::nullopt;

	return QPoint(
		pt.x() * (*unitsInPx) - alignedSceneTopLeft->x(),
		pt.y() * (*unitsInPx) - alignedSceneTopLeft->y()
	);
}

void SceneMinimap::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);

	paintTargetView(painter);
	paintTargetViewRect(painter);

	base_t::paintEvent(event);
}

void SceneMinimap::mouseMoveEvent(QMouseEvent* event)
{
	QGraphicsScene const* scene = getTargetScene();
	if (scene == nullptr)
		return;

	QRectF const targetViewRect = m_targetView->mapToScene(m_targetView->viewport()->geometry()).boundingRect();
	if (targetViewRect.contains(scene->sceneRect()))
		return;

	mapToScene(event->pos()).and_then([this](QPointF const& centerPt)
	{
		m_targetView->centerOn(centerPt);
		return std::make_optional(centerPt);
	});
}

void SceneMinimap::paintTargetView(QPainter& painter)
{
	QGraphicsScene* scene = getTargetScene();
	if (scene == nullptr)
		return;

	// drawing aligned area background
	painter.save();

	QBrush alignBrush = m_targetView->backgroundBrush();

	float h, s, v;
	alignBrush.color().getHsvF(&h, &s, &v);
	v += (v > 0.5f ? -0.1f : 0.1f);

	alignBrush.setColor(QColor::fromHsvF(h, s, v));
	painter.setBrush(alignBrush);

	painter.drawRect(0, 0, width(), height());
	painter.restore();

	// drawing target view background
	painter.save();

	painter.setBrush(m_targetView->backgroundBrush());
	mapFromScene(scene->sceneRect()).and_then([scene, &painter](QRect const& rect)
	{
		painter.drawRect(rect);
		return std::make_optional(rect);
	});

	painter.restore();

	// drawing scene
	painter.save();

	mapFromScene(scene->sceneRect()).and_then([scene, &painter](QRect const& rect)
	{
		scene->render(&painter, rect);
		return std::make_optional(rect);
	});

	painter.restore();
}

void SceneMinimap::paintTargetViewRect(QPainter& painter)
{
	QGraphicsScene const* scene = getTargetScene();
	if (scene == nullptr)
		return;

	QRectF const targetViewRect = m_targetView->mapToScene(m_targetView->viewport()->geometry()).boundingRect();
	if (targetViewRect.contains(scene->sceneRect()))
		return;

	painter.save();

	QColor penColor = m_viewRectColor;
	penColor.setAlpha(128);
	painter.setPen(penColor);

	QColor brushColor = m_viewRectColor;
	brushColor.setAlpha(64);
	painter.setBrush(brushColor);

	mapFromScene(targetViewRect).and_then([&painter](QRect const& rect)
	{
		painter.drawRect(rect);
		return std::make_optional(rect);
	});

	painter.restore();
}

std::optional<qreal> SceneMinimap::getSceneUnitsInPx() const
{
	QGraphicsScene const* scene = getTargetScene();
	if (scene == nullptr)
		return std::nullopt;

	qreal const sceneWidth = scene->sceneRect().width();
	qreal const sceneHeight = scene->sceneRect().height();

	qreal const horizUnitsInPx = sceneWidth / width();
	qreal const vertUnitsInPx = sceneHeight / height();

	return std::max(horizUnitsInPx, vertUnitsInPx);
}

std::optional<Qt::Orientation> SceneMinimap::getSceneOrientationInMinimap() const
{
	QGraphicsScene const* scene = getTargetScene();
	if (scene == nullptr)
		return std::nullopt;

	qreal const sceneWidth = scene->sceneRect().width();
	qreal const sceneHeight = scene->sceneRect().height();

	qreal const horizUnitsInPx = sceneWidth / width();
	qreal const vertUnitsInPx = sceneHeight / height();

	return horizUnitsInPx > vertUnitsInPx ? Qt::Horizontal : Qt::Vertical;
}

std::optional<QPointF> SceneMinimap::getAlignedSceneTopLeftPt() const
{
	QGraphicsScene const* scene = getTargetScene();
	if (scene == nullptr)
		return std::nullopt;

	qreal const sceneWidth = scene->sceneRect().width();
	qreal const sceneHeight = scene->sceneRect().height();

	// Align the beginning of the scene with the coordinates (0, 0)
	// (because the coordinates of the view start from zero)
	QPointF value = { -scene->sceneRect().left(), -scene->sceneRect().top() };

	qreal const unitsInPx = *getSceneUnitsInPx().or_else([]()
	{
		Q_ASSERT(false);
		return std::make_optional<qreal>();
	});

	// For a smaller dimension, it is necessary to calculate the offset,
	// because in this dimension the scene inside the minimap is aligned.
	Qt::Orientation orientation = *getSceneOrientationInMinimap().or_else([]
	{
		Q_ASSERT(false);
		return std::make_optional<Qt::Orientation>();
	});

	if (orientation == Qt::Horizontal)
		value.ry() += (height() * unitsInPx - sceneHeight) / 2;
	else
		value.rx() += (width() * unitsInPx - sceneWidth) / 2;

	return value;
}
