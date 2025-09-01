#include "ShapeTool.hpp"

#include "Items/RectangleItem.hpp"
#include "Items/CircleItem.hpp"

#include "Utility/SingleCall.hpp"

ShapeTool::ShapeTool()
{
	SingleCall<this_t>::run([]()
	{
		s_supportedItemsId.emplace(RectangleItem::getToolItemId());
	});

	setCurrentItemId(RectangleItem::getToolItemId());
}

QString ShapeTool::getName() const
{
	return "Shape tool";
}

QIcon ShapeTool::getIcon() const
{
	return QIcon{};
}
