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
		auto& supportedIds = ToolBase::getSupportedItemsIdFromHolder<this_t>();
		supportedIds.emplace(ToolItemRegistry::getItemId<LineItem>());
		supportedIds.emplace(ToolItemRegistry::getItemId<RectangleItem>());
		supportedIds.emplace(ToolItemRegistry::getItemId<EllipseItem>());
		supportedIds.emplace(ToolItemRegistry::getItemId<TriangleItem>());
	});

	setCurrentItemId(ToolItemRegistry::getItemId<RectangleItem>());
}

std::unique_ptr<ToolBase> ShapeTool::clone() const
{ return std::make_unique<this_t>(); }

ToolBase::id_t ShapeTool::getId() const
{ return ToolBase::getIdFromHolder<this_t>(); }

std::unordered_set<ToolItemBase::id_t> const& ShapeTool::getSupportedItemsId() const
{ return ToolBase::getSupportedItemsIdFromHolder<this_t>(); }

QString ShapeTool::getName() const
{
	return "Shape tool";
}

QIcon ShapeTool::getIcon() const
{
	return QIcon{};
}
