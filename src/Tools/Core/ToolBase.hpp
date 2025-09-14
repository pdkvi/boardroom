#pragma once

#include <unordered_set>
#include <memory>

#include <QIcon>

#include "Items/Core/ToolItemBase.hpp"

#include "Utility/IdHolder.hpp"
#include "Utility/Registry.hpp"

class ToolBase : public SelectedConstruction
{
	friend Registry;

	using this_t = ToolBase;

public:
	using id_t = size_t;

private:
	id_t m_currentItemId = id_t{};

public:
	~ToolBase() override = default;
	virtual std::unique_ptr<ToolBase> clone() const = 0;

	virtual id_t getId() const = 0;
	virtual QString getName() const = 0;
	virtual QIcon getIcon() const = 0;

	virtual std::unordered_set<ToolItemBase::id_t> const& getSupportedItemsId() const = 0;

	ToolItemBase::id_t getCurrentItemId() const;
	void setCurrentItemId(ToolItemBase::id_t id);

	std::unique_ptr<ToolItemBase> createItem();

protected:
	template <typename TDerived> requires std::derived_from<TDerived, this_t>
	static id_t getIdFromHolder()
	{
		auto const& holder = IdHolder<this_t, TDerived>::getInstance();
		return holder.getId();
	}

	template <typename TDerived> requires std::derived_from<TDerived, this_t>
	static std::unordered_set<ToolItemBase::id_t>& getSupportedItemsIdFromHolder()
	{
		static std::unordered_set<ToolItemBase::id_t> supportedIds;
		return supportedIds;
	}
};

using ToolRegistry = Registry<ToolBase>;