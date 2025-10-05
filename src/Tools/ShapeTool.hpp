#pragma once

#include "Tools/Core/ToolBase.hpp"

class ShapeTool : public ToolBase
{
	using this_t = ShapeTool;

public:
	ShapeTool();

	std::unique_ptr<ToolBase> clone() const override;

	id_t getId() const override;
	QString getName() const override;
	QIcon getIcon() const override;

	std::unordered_set<ToolItemBase::id_t> const& getSupportedItemsId() const override;
};
