#include "RectangleItem.hpp"

#include <QPainter>

QString RectangleItem::getName() const
{
	return "Rectangle";
}

void RectangleItem::startPathImpl(QPointF const& pos)
{
	m_startPt = pos;
	m_endPt = pos;
}

void RectangleItem::updatePathImpl(QPointF const& pos)
{
	m_endPt = pos;
}

void RectangleItem::endPathImpl(QPointF const& pos)
{
	updatePathImpl(pos);
}

QRectF RectangleItem::boundingRectImpl() const
{
	auto const [x1, y1] = m_startPt;
	auto const [x2, y2] = m_endPt;

	QPointF const topLeft = { std::min(x1, x2), std::min(y1, y2) };
	QPointF const bottomRight = { std::max(x1, x2), std::max(y1, y2) };

	return QRectF(topLeft, bottomRight);
}

void RectangleItem::paintImpl(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget)
{
	painter->drawRect(boundingRectImpl());
}