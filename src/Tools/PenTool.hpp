#pragma once

#include "Tools/Core/ToolBase.hpp"

class PenTool : public ToolBase
{
	using this_t = PenTool;

public:
	PenTool();

	std::unique_ptr<ToolBase> clone() const override;

	id_t getId() const override;
	QString getName() const override;
	QIcon getIcon() const override;

	std::unordered_set<ToolItemBase::id_t> const& getSupportedItemsId() const override;
};
