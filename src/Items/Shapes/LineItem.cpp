#include "LineItem.hpp"

ToolItemBase::id_t LineItem::getId() const
{ return ToolItemBase::getIdFromHolder<this_t>(); }

QString LineItem::getName() const
{ return "Line"; }

std::unique_ptr<ToolItemBase> LineItem::getThisCopy() const
{ return getThisCopyImpl<this_t>(); }

QPainterPath LineItem::shape() const
{
	QPainterPath path;
	path.moveTo(getStartPathPt());
	path.lineTo(getCurrentPathPt());
	return path;
}