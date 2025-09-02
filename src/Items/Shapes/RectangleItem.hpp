#pragma once

#include "Items/Core/ToolItemBase.hpp"

class RectangleItem : public ToolItemBase<RectangleItem>
{
public:
	QString getName() const override;

protected:
	QRectF getLimitRect() const override;
	void onPaint(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget) override;
};