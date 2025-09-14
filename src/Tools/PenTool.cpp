#include "PenTool.hpp"

#include "Items/FreeDrawingItem.hpp"

#include "Utility/SingleCall.hpp"

PenTool::PenTool()
{
	SingleCall<this_t>::run([]()
	{
		auto& supportedIds = ToolBase::getSupportedItemsIdFromHolder<this_t>();
		supportedIds.emplace(ToolItemRegistry::getItemId<FreeDrawingItem>());
	});

	setCurrentItemId(ToolItemRegistry::getItemId<FreeDrawingItem>());
}

std::unique_ptr<ToolBase> PenTool::clone() const
{ return std::make_unique<this_t>(); }

ToolBase::id_t PenTool::getId() const
{ return ToolBase::getIdFromHolder<this_t>(); }

std::unordered_set<ToolItemBase::id_t> const& PenTool::getSupportedItemsId() const
{ return ToolBase::getSupportedItemsIdFromHolder<this_t>(); }

QString PenTool::getName() const
{ return "Pen"; }

QIcon PenTool::getIcon() const
{ return QIcon{}; }
