#include "EllipseItem.hpp"

#include <QPainter>

ToolItemBase::id_t EllipseItem::getId() const
{ return ToolItemBase::getIdFromHolder<this_t>(); }

QString EllipseItem::getName() const
{ return "Ellipse"; }

std::unique_ptr<ToolItemBase> EllipseItem::getThisCopy() const
{ return getThisCopyImpl<this_t>(); }

QRectF EllipseItem::getLimitRect() const
{
	auto const [x1, y1] = getStartPathPt();
	auto const [x2, y2] = getCurrentPathPt();

	QPointF const topLeft = { std::min(x1, x2), std::min(y1, y2) };
	QPointF const bottomRight = { std::max(x1, x2), std::max(y1, y2) };

	return QRectF(topLeft, bottomRight);
}

void EllipseItem::onPaint(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget)
{
	base_t::onPaint(painter, option, widget);

	QRectF const ellipseRect = [&]
	{
		qreal const halfPenWidth = painter->pen().widthF() / 2;
		return getLimitRect().adjusted(halfPenWidth, halfPenWidth, -halfPenWidth, -halfPenWidth);
	}();

	painter->setClipRect(getLimitRect());
	painter->drawEllipse(ellipseRect);
}