#pragma once

#include "Items/Core/ToolItemBase.hpp"

class DrawingItemBase : public ToolItemBase
{
	using base_t = ToolItemBase;
	using this_t = DrawingItemBase;

private:
	QColor m_color;
	qreal m_thickness;

public:
	explicit DrawingItemBase(QColor color = Qt::darkBlue, qreal thickness = 2.0);

	void copyTo(ToolItemBase* target) const override;

protected:
	QRectF getLimitRect() const override;
	void onPaint(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget) override;
};