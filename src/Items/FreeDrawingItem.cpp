#include "FreeDrawingItem.hpp"

#include <QGraphicsScene>
#include <QPainter>

std::unique_ptr<ToolItemBase> FreeDrawingItem::clone() const
{ return std::make_unique<SelectedConstructionImpl<this_t>>(); }

ToolItemBase::id_t FreeDrawingItem::getId() const
{ return ToolItemBase::getIdFromHolder<this_t>(); }

QString FreeDrawingItem::getName() const
{ return "Free drawing"; }

void FreeDrawingItem::onPathStart()
{ m_path.moveTo(getStartPathPt()); }

void FreeDrawingItem::onPathUpdate()
{ m_path.lineTo(getCurrentPathPt()); }

QRectF FreeDrawingItem::getLimitRect() const
{ return m_path.boundingRect(); }

void FreeDrawingItem::onPaint(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget)
{ painter->drawPath(m_path); }