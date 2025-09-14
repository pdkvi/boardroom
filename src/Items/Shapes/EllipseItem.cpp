#include "EllipseItem.hpp"

#include <QPainter>

QString EllipseItem::getName() const
{
	return "Ellipse";
}

QPainterPath EllipseItem::shape() const
{
	auto const [x1, y1] = getStartPathPt();
	auto const [x2, y2] = getCurrentPathPt();

	auto const [left, right] = std::tie(std::min(x1, x2), std::max(x1, x2));
	auto const [top, bottom] = std::tie(std::min(y1, y2), std::max(y1, y2));

	QPainterPath path;
	path.addEllipse(left, top, right - left, bottom - top);

	return path;
}