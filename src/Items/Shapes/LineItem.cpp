#include "LineItem.hpp"

QString LineItem::getName() const
{
	return "Line";
}

QPainterPath LineItem::shape() const
{
	QPainterPath path;
	path.moveTo(getStartPathPt());
	path.lineTo(getCurrentPathPt());
	return path;
}