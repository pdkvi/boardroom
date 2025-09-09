#pragma once

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>

#include "Items/Core/IToolItem.hpp"

#include "Utility/IdHolder.hpp"
#include "Utility/Registry.hpp"

using ToolItemRegistry = Registry<IToolItem>;

template <typename TToolItem>
class ToolItemBase : public QGraphicsItem, public IToolItem
{
	using id_holder_t = IdHolder<IToolItem, TToolItem>;

private:
	QPointF m_pathStartPt;
	QPointF m_currentPathPt;

	QRectF m_limitRectBeforeRepaint;

public:
	ToolItemBase()
	{
		setFlag(ItemIsSelectable);
	}

	static id_t getToolItemId()
	{
		auto const & holder = id_holder_t::getInstance();
		return holder.getId();
	}

	id_t getId() const override { return getToolItemId(); }

	std::unique_ptr<IToolItem> clone() const override { return std::make_unique<TToolItem>(); }

	QGraphicsItem* getSceneItem() final { return this; }

	void startPath(QPointF const& pos) final
	{
		m_pathStartPt = m_currentPathPt = pos;
		onPathStart();

		m_limitRectBeforeRepaint = getLimitRect();
		update();
	}

	void updatePath(QPointF const& pos) final
	{
		m_currentPathPt = pos;
		onPathUpdate();

		update();
	}

	void endPath(QPointF const& pos) final
	{
		m_currentPathPt = pos;
		onPathEnd();

		if (QGraphicsScene* scene = this->scene())
		{
			scene->removeItem(getSceneItem());
			scene->addItem(getSceneItem());
			scene->update();
		}
	}

	QRectF boundingRect() const final { return m_limitRectBeforeRepaint; }

	void paint(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget) final
	{
		onPaint(painter, option, widget);
		m_limitRectBeforeRepaint = getLimitRect();
	}

protected:
	virtual void onPathStart() {}
	virtual void onPathUpdate() {}
	virtual void onPathEnd() { onPathUpdate(); }

	QPointF getStartPathPt() const { return m_pathStartPt; }
	QPointF getCurrentPathPt() const { return m_currentPathPt; }

	virtual QRectF getLimitRect() const { return shape().boundingRect(); };

	virtual void onPaint(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget)
	{
		painter->drawPath(shape());
	}
};