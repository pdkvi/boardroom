#include "LineItem.hpp"

#include <QPainter>

std::unique_ptr<ToolItemBase> LineItem::clone() const
{ return std::make_unique<this_t>(); }

ToolItemBase::id_t LineItem::getId() const
{ return ToolItemBase::getIdFromHolder<this_t>(); }

QString LineItem::getName() const
{ return "Line"; }

QRectF LineItem::getLimitRect() const
{
	auto const [x1, y1] = getStartPathPt();
	auto const [x2, y2] = getCurrentPathPt();

	QPointF const topLeft = { std::min(x1, x2), std::min(y1, y2) };
	QPointF const bottomRight = { std::max(x1, x2), std::max(y1, y2) };

	return QRectF(topLeft, bottomRight);
}

void LineItem::onPaint(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget)
{
	painter->drawLine(getStartPathPt(), getCurrentPathPt());
}
