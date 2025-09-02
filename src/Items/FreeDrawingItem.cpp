#include "FreeDrawingItem.hpp"

#include <QGraphicsScene>
#include <QPainter>

QString FreeDrawingItem::getName() const
{
	return "Free drawing";
}

void FreeDrawingItem::startPathImpl(QPointF const& pos)
{
	m_path.moveTo(pos);
}

void FreeDrawingItem::updatePathImpl(QPointF const& pos)
{
	m_path.lineTo(pos);
}

void FreeDrawingItem::endPathImpl(QPointF const& pos)
{
	updatePathImpl(pos);
}

QRectF FreeDrawingItem::boundingRectImpl() const
{
	return m_path.boundingRect();
}

void FreeDrawingItem::paintImpl(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget)
{
	painter->drawPath(m_path);
}