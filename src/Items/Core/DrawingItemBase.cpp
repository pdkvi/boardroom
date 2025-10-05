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

void DrawingItemBase::onPaint(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget)
{
	painter->setPen(QPen{ m_color, m_thickness });

	// TODO: Redesign the architecture, hardcoded call. If the child of
	// DrawingItemBase decides to override onPaint(), then onPaint() from
	// ToolItemBase will still be called for it.
	base_t::onPaint(painter, option, widget);
}
