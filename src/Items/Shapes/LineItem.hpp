#pragma once

#include "Items/Core/ToolItemBase.hpp"

class LineItem : public ToolItemBase<LineItem>
{
public:
	QString getName() const override;

protected:
	QRectF getLimitRect() const override;
	void onPaint(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget) override;
};