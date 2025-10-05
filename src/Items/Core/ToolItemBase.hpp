#pragma once

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>

#include "Utility/SelectedConstruction.hpp"
#include "Utility/IdHolder.hpp"
#include "Utility/Registry.hpp"

class ToolItemBase : public QGraphicsItem, public SelectedConstruction
{
	friend Registry;

	using this_t = ToolItemBase;

public:
	using id_t = size_t;

private:
	QPointF m_pathStartPt;
	QPointF m_currentPathPt;

	QRectF m_limitRectBeforeRepaint;

public:
	ToolItemBase();
	~ToolItemBase() override = default;

	virtual std::unique_ptr<ToolItemBase> clone() const;
	virtual void copyTo(ToolItemBase* target) const;

	virtual id_t getId() const = 0;
	virtual QString getName() const = 0;

	QGraphicsItem* getSceneItem();

	void startPath(QPointF const& pos);
	void updatePath(QPointF const& pos);
	void endPath(QPointF const& pos);

	QRectF boundingRect() const final;
	void paint(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget) final;

protected:
	virtual std::unique_ptr<ToolItemBase> getThisCopy() const = 0;

	template <typename TDerived> requires std::derived_from<TDerived, this_t>
	static std::unique_ptr<ToolItemBase> getThisCopyImpl()
	{ return std::make_unique<SelectedConstructionImpl<TDerived>>(); }

	template <typename TDerived> requires std::derived_from<TDerived, this_t>
	static id_t getIdFromHolder()
	{
		auto const& holder = IdHolder<this_t, TDerived>::getInstance();
		return holder.getId();
	}

	QPointF getStartPathPt() const;
	QPointF getCurrentPathPt() const;

	virtual void onPathStart();
	virtual void onPathUpdate();
	virtual void onPathEnd();

	virtual QRectF getLimitRect() const;
	virtual void onPaint(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget);
};

using ToolItemRegistry = Registry<ToolItemBase>;