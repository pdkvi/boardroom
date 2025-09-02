#include "ShapeTool.hpp"

#include "Items/Shapes/RectangleItem.hpp"
#include "Items/Shapes/TriangleItem.hpp"
#include "Items/Shapes/EllipseItem.hpp"
#include "Items/Shapes/LineItem.hpp"

#include "Utility/SingleCall.hpp"

ShapeTool::ShapeTool()
{
	SingleCall<this_t>::run([]()
	{
		s_supportedItemsId.emplace(LineItem::getToolItemId());
		s_supportedItemsId.emplace(RectangleItem::getToolItemId());
		s_supportedItemsId.emplace(EllipseItem::getToolItemId());
		s_supportedItemsId.emplace(TriangleItem::getToolItemId());
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
