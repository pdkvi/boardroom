#include "FreeDrawingItem.hpp"

#include <QGraphicsScene>
#include <QPainter>

QString FreeDrawingItem::getName() const
{
	return "Free drawing";
}

void FreeDrawingItem::startPath(QPointF const& pos)
{
	m_path.moveTo(pos);
	update();
}

void FreeDrawingItem::updatePath(QPointF const& pos)
{
	m_path.lineTo(pos);
	update();
}

void FreeDrawingItem::endPath(QPointF const& pos)
{
	m_path.lineTo(pos);
	base_t::endPath(pos);
}

QRectF FreeDrawingItem::boundingRect() const
{
	return m_path.boundingRect();
}

void FreeDrawingItem::paint(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget)
{
	painter->drawPath(m_path);
}
