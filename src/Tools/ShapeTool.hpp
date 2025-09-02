#pragma once

#include "Core/ToolBase.hpp"

class IToolItem;

class ShapeTool : public ToolBase<ShapeTool>
{
	using this_t = ShapeTool;

public:
	ShapeTool();

	QString getName() const override;
	QIcon getIcon() const override;
};
