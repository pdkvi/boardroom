#include "EllipseItem.hpp"

#include <QPainter>

ToolItemBase::id_t EllipseItem::getId() const
{ return ToolItemBase::getIdFromHolder<this_t>(); }

QString EllipseItem::getName() const
{ return "Ellipse"; }

std::unique_ptr<ToolItemBase> EllipseItem::getThisCopy() const
{ return getThisCopyImpl<this_t>(); }

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