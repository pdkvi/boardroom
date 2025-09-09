#pragma once

#include "Items/Core/ToolItemBase.hpp"

class EllipseItem : public ToolItemBase<EllipseItem>
{
public:
	QString getName() const override;
	QPainterPath shape() const override;
};