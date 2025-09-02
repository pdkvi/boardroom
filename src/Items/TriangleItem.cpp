#include "TriangleItem.hpp"

#include <QVector2D>
#include <QPainter>

QString TriangleItem::getName() const
{
	return "Triangle";
}

void TriangleItem::startPathImpl(QPointF const& pos)
{
	m_startPt = pos;
	m_endPt = pos;
}

void TriangleItem::updatePathImpl(QPointF const& pos)
{
	m_endPt = pos;
}

void TriangleItem::endPathImpl(QPointF const& pos)
{
	updatePathImpl(pos);
}

QRectF TriangleItem::boundingRectImpl() const
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

void TriangleItem::paintImpl(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget)
{
	QRectF const& rect = boundingRectImpl();

	QPainterPath path;
	path.moveTo(rect.bottomLeft());
	path.lineTo(rect.left() + rect.width() / 2, rect.top());
	path.lineTo(rect.bottomRight());
	path.lineTo(rect.bottomLeft());

	painter->drawPath(path);
}
