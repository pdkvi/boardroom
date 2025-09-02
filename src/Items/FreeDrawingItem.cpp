#include "FreeDrawingItem.hpp"

#include <QGraphicsScene>
#include <QPainter>

QString FreeDrawingItem::getName() const
{
	return "Free drawing";
}

void FreeDrawingItem::onPathStart()
{
	m_path.moveTo(getStartPathPt());
}

void FreeDrawingItem::onPathUpdate()
{
	m_path.lineTo(getCurrentPathPt());
}

QRectF FreeDrawingItem::getLimitRect() const
{
	return m_path.boundingRect();
}

void FreeDrawingItem::onPaint(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget)
{
	painter->drawPath(m_path);
}