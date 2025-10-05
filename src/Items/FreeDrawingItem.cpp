#include "FreeDrawingItem.hpp"

#include <QGraphicsScene>
#include <QPainter>

void FreeDrawingItem::copyTo(ToolItemBase* target) const
{
	base_t::copyTo(target);
	if (auto casted = dynamic_cast<this_t*>(target))
		casted->m_path = m_path;
}

ToolItemBase::id_t FreeDrawingItem::getId() const
{ return ToolItemBase::getIdFromHolder<this_t>(); }

QString FreeDrawingItem::getName() const
{ return "Free drawing"; }

std::unique_ptr<ToolItemBase> FreeDrawingItem::getThisCopy() const
{ return getThisCopyImpl<this_t>(); }

QPainterPath FreeDrawingItem::shape() const
{ return m_path; }

void FreeDrawingItem::onPathStart()
{ m_path.moveTo(getStartPathPt()); }

void FreeDrawingItem::onPathUpdate()
{ m_path.lineTo(getCurrentPathPt()); }
