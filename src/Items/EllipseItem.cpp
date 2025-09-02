#include "EllipseItem.hpp"

#include <QPainter>

QString EllipseItem::getName() const
{
	return "Ellipse";
}

void EllipseItem::startPathImpl(QPointF const& pos)
{
	m_startPt = pos;
	m_endPt = pos;
}

void EllipseItem::updatePathImpl(QPointF const& pos)
{
	m_endPt = pos;
}

void EllipseItem::endPathImpl(QPointF const& pos)
{
	updatePathImpl(pos);
}

QRectF EllipseItem::boundingRectImpl() const
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

void EllipseItem::paintImpl(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget)
{
	painter->setPen(QPen(Qt::black, 1));

	QRectF const ellipseRect = [&]
	{
		qreal const halfPenWidth = painter->pen().widthF() / 2;
		return boundingRectImpl().adjusted(halfPenWidth, halfPenWidth, -halfPenWidth, -halfPenWidth);
	}();

	painter->setClipRect(boundingRectImpl());
	painter->drawEllipse(ellipseRect);
}