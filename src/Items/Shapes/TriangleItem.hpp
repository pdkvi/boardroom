#pragma once

#include "Items/Core/ToolItemBase.hpp"

class TriangleItem : public ToolItemBase<TriangleItem>
{
public:
	QString getName() const override;
	QPainterPath shape() const override;
};