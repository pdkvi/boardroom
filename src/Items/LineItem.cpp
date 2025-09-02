#include "LineItem.hpp"

#include <QPainter>

QString LineItem::getName() const
{
	return "Line";
}

void LineItem::startPathImpl(QPointF const& pos)
{
	m_startPt = pos;
	m_endPt = pos;
}

void LineItem::updatePathImpl(QPointF const& pos)
{
	m_endPt = pos;
}

void LineItem::endPathImpl(QPointF const& pos)
{
	updatePathImpl(pos);
}

QRectF LineItem::boundingRectImpl() const
{
	QPointF const topLeft =
	{
		std::min(m_startPt.x(), m_endPt.x()),
		std::min(m_startPt.y(), m_endPt.y())
	};

	QPointF const bottomRight =
	{
		std::max(m_startPt.x(), m_endPt.x()),
		std::max(m_startPt.y(), m_endPt.y())
	};

	return QRectF(topLeft, bottomRight);
}

void LineItem::paintImpl(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget)
{
	painter->drawLine(m_startPt, m_endPt);
}
