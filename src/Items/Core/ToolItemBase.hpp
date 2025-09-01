#pragma once

#include <QGraphicsItem>
#include <QGraphicsScene>

#include "Utility/IdHolder.hpp"
#include "Utility/Registry.hpp"
#include "IToolItem.hpp"

using ToolItemRegistry = Registry<IToolItem>;

template <typename TToolItem>
class ToolItemBase : public QGraphicsItem, public IToolItem
{
	using id_holder_t = IdHolder<IToolItem, TToolItem>;

public:
	static id_t getToolItemId()
	{
		auto const & holder = id_holder_t::getInstance();
		return holder.getId();
	}

	id_t getId() const override { return getToolItemId(); }

	std::unique_ptr<IToolItem> clone() const override { return std::make_unique<TToolItem>(); }

	QGraphicsItem* getSceneItem() override { return this; }

	void endPath(QPointF const& pos) override
	{
		if (QGraphicsScene* scene = this->scene())
		{
			scene->removeItem(this);
			scene->addItem(this);
			scene->update();
		}
	}
};