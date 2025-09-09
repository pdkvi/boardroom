#include "RectangleItem.hpp"

#include <QPainter>

QString RectangleItem::getName() const
{
	return "Rectangle";
}

QPainterPath RectangleItem::shape() const
{
	auto const [x1, y1] = getStartPathPt();
	auto const [x2, y2] = getCurrentPathPt();

	QPointF const topLeft = { std::min(x1, x2), std::min(y1, y2) };
	QPointF const bottomRight = { std::max(x1, x2), std::max(y1, y2) };

	QPainterPath path;
	path.addRect(QRectF{ topLeft, bottomRight });

	return path;
}