#include "TriangleItem.hpp"

#include <QVector2D>
#include <QPainter>

ToolItemBase::id_t TriangleItem::getId() const
{ return ToolItemBase::getIdFromHolder<this_t>(); }

QString TriangleItem::getName() const
{ return "Triangle"; }

std::unique_ptr<ToolItemBase> TriangleItem::getThisCopy() const
{ return getThisCopyImpl<this_t>(); }

QPainterPath TriangleItem::shape() const
{
	auto const [x1, y1] = getStartPathPt();
	auto const [x2, y2] = getCurrentPathPt();

	auto const [left, right] = std::tie(std::min(x1, x2), std::max(x1, x2));
	auto const [top, bottom] = std::tie(std::min(y1, y2), std::max(y1, y2));

	QPainterPath path;
	path.moveTo(left, bottom);
	path.lineTo(left + (right - left) / 2, top);
	path.lineTo(right, bottom);
	path.lineTo(left, bottom);

	return path;
}