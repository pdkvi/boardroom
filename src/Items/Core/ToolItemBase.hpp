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

private:
	QRectF m_boundingRectBeforeUpdate;

public:
	static id_t getToolItemId()
	{
		auto const & holder = id_holder_t::getInstance();
		return holder.getId();
	}

	id_t getId() const override { return getToolItemId(); }

	std::unique_ptr<IToolItem> clone() const override { return std::make_unique<TToolItem>(); }

	QGraphicsItem* getSceneItem() override { return this; }

	void startPath(QPointF const& pos) final
	{
		startPathImpl(pos);

		m_boundingRectBeforeUpdate = boundingRectImpl();
		update();
	}

	void updatePath(QPointF const& pos) final
	{
		updatePathImpl(pos);
		update();
	}

	void endPath(QPointF const& pos) final
	{
		endPathImpl(pos);

		if (QGraphicsScene* scene = this->scene())
		{
			scene->removeItem(this);
			scene->addItem(this);
			scene->update();
		}
	}

	QRectF boundingRect() const final
	{
		return m_boundingRectBeforeUpdate;
	}

	void paint(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget) final
	{
		paintImpl(painter, option, widget);
		m_boundingRectBeforeUpdate = boundingRectImpl();
	}

protected:
	virtual void startPathImpl(QPointF const& pos) = 0;
	virtual void updatePathImpl(QPointF const& pos) = 0;
	virtual void endPathImpl(QPointF const& pos) = 0;

	virtual QRectF boundingRectImpl() const = 0;
	virtual void paintImpl(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget) = 0;
};