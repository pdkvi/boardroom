#pragma once

#include "Items/Core/DrawingItemBase.hpp"
#include "Items/Core/ToolItemBase.hpp"

class RectangleItem : public DrawingItemBase
{
	using base_t = DrawingItemBase;
	using this_t = RectangleItem;

public:
	id_t getId() const override;
	QString getName() const override;

protected:
	std::unique_ptr<ToolItemBase> getThisCopy() const override;

	QRectF getLimitRect() const override;
	void onPaint(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget) override;
};