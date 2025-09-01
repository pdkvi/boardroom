#pragma once

#include <memory>

class QGraphicsItem;

class IToolItem
{
public:
	using id_t = size_t;

public:
	virtual ~IToolItem() = default;

	virtual id_t getId() const = 0;
	virtual std::unique_ptr<IToolItem> clone() const = 0;

	virtual QString getName() const = 0;
	virtual QGraphicsItem* getSceneItem() = 0;

	virtual void startPath(QPointF const& pos) = 0;
	virtual void updatePath(QPointF const& pos) = 0;
	virtual void endPath(QPointF const& pos) = 0;
};