#include "FreeHandDrawingItem.hpp"

#include <QPainter>

FreeHandDrawingItem::FreeHandDrawingItem(QPointF const& startPt, QGraphicsItem* parent)
	: base_t(parent)
{
	m_path.moveTo(startPt);
}

QRectF FreeHandDrawingItem::boundingRect() const
{
	return m_path.boundingRect();
}

void FreeHandDrawingItem::paint(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget)
{
	painter->drawPath(m_path);
}

void FreeHandDrawingItem::moveTo(QPointF const& pt)
{
	m_path.lineTo(pt);
}