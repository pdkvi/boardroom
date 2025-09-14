#pragma once

#include "Items/Core/ToolItemBase.hpp"

class FreeDrawingItem : public ToolItemBase<FreeDrawingItem>
{
	using base_t = ToolItemBase;
	using this_t = FreeDrawingItem;

private:
	QPainterPath m_path;

public:
	QString getName() const override;
	QPainterPath shape() const override;

protected:
	void onPathStart() override;
	void onPathUpdate() override;
};
