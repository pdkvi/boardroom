#pragma once

#include "Items/Core/ToolItemBase.hpp"

class EllipseItem : public ToolItemBase
{
	using this_t = EllipseItem;

public:
	std::unique_ptr<ToolItemBase> clone() const override;

	id_t getId() const override;
	QString getName() const override;

protected:
	QRectF getLimitRect() const override;
	void onPaint(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget) override;
};