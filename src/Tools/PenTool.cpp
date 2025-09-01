#include "PenTool.hpp"

#include "Utility/SingleCall.hpp"
#include "Items/FreeDrawingItem.hpp"

PenTool::PenTool()
{
	SingleCall<this_t>::run([]()
	{
		s_supportedItemsId.emplace(FreeDrawingItem::getToolItemId());
	});

	setCurrentItemId(FreeDrawingItem::getToolItemId());
}

QString PenTool::getName() const
{
	return "Pen";
}

QIcon PenTool::getIcon() const
{
	return QIcon{};
}
