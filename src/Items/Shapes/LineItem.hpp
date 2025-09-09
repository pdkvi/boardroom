#pragma once

#include "Items/Core/ToolItemBase.hpp"

class LineItem : public ToolItemBase<LineItem>
{
public:
	QString getName() const override;
	QPainterPath shape() const override;
};