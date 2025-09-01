#pragma once

#include "Core/ToolBase.hpp"

class IToolItem;

class PenTool : public ToolBase<PenTool>
{
	using this_t = PenTool;

public:
	PenTool();

	QString getName() const override;
	QIcon getIcon() const override;
};
