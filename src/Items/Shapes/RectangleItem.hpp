#pragma once

#include "Items/Core/ToolItemBase.hpp"

class RectangleItem : public ToolItemBase<RectangleItem>
{
public:
	QString getName() const override;
	QPainterPath shape() const override;
};