#pragma once

#include "Items/Core/DrawingItemBase.hpp"
#include "Items/Core/ToolItemBase.hpp"

class TriangleItem : public DrawingItemBase
{
	using base_t = DrawingItemBase;
	using this_t = TriangleItem;

public:
	id_t getId() const override;
	QString getName() const override;

protected:
	std::unique_ptr<ToolItemBase> getThisCopy() const override;

	QPainterPath shape() const override;
};