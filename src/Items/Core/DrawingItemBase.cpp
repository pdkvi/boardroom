#include "DrawingItemBase.hpp"

#include <QPainter>

DrawingItemBase::DrawingItemBase(QColor color, qreal thickness)
	: m_color(color), m_thickness(thickness)
{
}

void DrawingItemBase::copyTo(ToolItemBase* target) const
{
	base_t::copyTo(target);
	if (auto casted = dynamic_cast<DrawingItemBase*>(target))
	{
		casted->m_color = m_color;
		casted->m_thickness = m_thickness;
	}
}

QRectF DrawingItemBase::getLimitRect() const
{
	qreal const halfThick = m_thickness / 2.0;

	QRectF const baseLimitRect = base_t::getLimitRect();
	return baseLimitRect.adjusted(-halfThick, -halfThick, halfThick, halfThick);
}

void DrawingItemBase::onPaint(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget)
{
	QPen pen(m_color, m_thickness);
	pen.setCapStyle(Qt::RoundCap);
	painter->setPen(pen);

	// TODO: Redesign the architecture, hardcoded call. If the child of
	// DrawingItemBase decides to override onPaint(), then onPaint() from
	// ToolItemBase will still be called for it.
	base_t::onPaint(painter, option, widget);
}
