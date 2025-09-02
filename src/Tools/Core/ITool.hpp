#pragma once

#include <unordered_set>
#include <memory>

#include <QIcon>

#include "Items/Core/IToolItem.hpp"

class ITool
{
public:
	using id_t = size_t;

public:
	virtual ~ITool() = default;

	virtual id_t getId() const = 0;
	virtual std::unique_ptr<ITool> clone() const = 0;

	virtual std::unordered_set<IToolItem::id_t> const& getAvailableItemsId() = 0;
	virtual IToolItem::id_t getCurrentItemId() const = 0;
	virtual void setCurrentItemId(IToolItem::id_t id) = 0;

	virtual QString getName() const = 0;
	virtual QIcon getIcon() const = 0;

	virtual std::unique_ptr<IToolItem> createItem() = 0;
};