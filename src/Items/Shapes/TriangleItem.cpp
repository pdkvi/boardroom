#include "TriangleItem.hpp"

#include <QVector2D>
#include <QPainter>

std::unique_ptr<ToolItemBase> TriangleItem::clone() const
{ return std::make_unique<SelectedConstructionImpl<this_t>>(); }

ToolItemBase::id_t TriangleItem::getId() const
{ return ToolItemBase::getIdFromHolder<this_t>(); }

QString TriangleItem::getName() const
{ return "Triangle"; }

QRectF TriangleItem::getLimitRect() const
{
	auto const [x1, y1] = getStartPathPt();
	auto const [x2, y2] = getCurrentPathPt();

	QPointF const topLeft = { std::min(x1, x2), std::min(y1, y2) };
	QPointF const bottomRight = { std::max(x1, x2), std::max(y1, y2) };

	return QRectF(topLeft, bottomRight);
}

void TriangleItem::onPaint(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget)
{
	QRectF const& rect = getLimitRect();

	QPainterPath path;
	path.moveTo(rect.bottomLeft());
	path.lineTo(rect.left() + rect.width() / 2, rect.top());
	path.lineTo(rect.bottomRight());
	path.lineTo(rect.bottomLeft());

	painter->drawPath(path);
}
