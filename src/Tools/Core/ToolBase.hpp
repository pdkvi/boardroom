#pragma once

#include <unordered_set>

#include "Utility/IdHolder.hpp"
#include "Utility/Registry.hpp"
#include "ITool.hpp"

#include "Items/Core/ToolItemBase.hpp"

using ToolRegistry = Registry<ITool>;

template <typename TTool>
class ToolBase : public ITool
{
	using id_holder_t = IdHolder<ITool, TTool>;

protected:
	static inline std::unordered_set<id_t> s_supportedItemsId;

private:
	id_t m_currentItemId = id_t{};

public:
	static id_t getToolId()
	{
		auto const& holder = id_holder_t::getInstance();
		return holder.getId();
	}

	id_t getId() const override { return getToolId(); }

	std::unique_ptr<ITool> clone() const override { return std::make_unique<TTool>(); }

	std::unordered_set<id_t> const& getAvailableItemsId() override
	{
		return s_supportedItemsId;
	}

	id_t getCurrentItemId() const override
	{
		return m_currentItemId;
	}

	void setCurrentItemId(id_t id) override
	{
		if (s_supportedItemsId.contains(id) == false)
			return;

		m_currentItemId = id;
	}

	std::unique_ptr<IToolItem> createItem() override
	{
		return ToolItemRegistry::getItem(getCurrentItemId())->clone();
	}
};
