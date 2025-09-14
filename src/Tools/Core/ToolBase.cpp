#include "ToolBase.hpp"

ToolItemBase::id_t ToolBase::getCurrentItemId() const
{ return m_currentItemId; }

void ToolBase::setCurrentItemId(ToolItemBase::id_t id)
{
	if (getSupportedItemsId().contains(id) == false)
	{
		Q_ASSERT(false && "Trying to set an unsupported item to the current one");
		return;
	}

	m_currentItemId = id;
}

std::unique_ptr<ToolItemBase> ToolBase::createItem()
{ return ToolItemRegistry::getItem(getCurrentItemId())->clone(); }
