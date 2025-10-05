#include "RectangleItem.hpp"

#include <QPainter>

ToolItemBase::id_t RectangleItem::getId() const
{ return ToolItemBase::getIdFromHolder<this_t>(); }

QString RectangleItem::getName() const
{ return "Rectangle"; }

std::unique_ptr<ToolItemBase> RectangleItem::getThisCopy() const
{ return getThisCopyImpl<this_t>(); }

QRectF RectangleItem::getLimitRect() const
{
	auto const [x1, y1] = getStartPathPt();
	auto const [x2, y2] = getCurrentPathPt();

	QPointF const topLeft = { std::min(x1, x2), std::min(y1, y2) };
	QPointF const bottomRight = { std::max(x1, x2), std::max(y1, y2) };

	return QRectF(topLeft, bottomRight);
}

void RectangleItem::onPaint(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget)
{
	base_t::onPaint(painter, option, widget);
	painter->drawRect(getLimitRect());
}