#include "Items/Core/ToolItemBase.hpp"

QGraphicsItem* ToolItemBase::getSceneItem()
{ return this; }

void ToolItemBase::startPath(QPointF const& pos)
{
	m_pathStartPt = m_currentPathPt = pos;
	onPathStart();

	m_limitRectBeforeRepaint = getLimitRect();
	update();
}

void ToolItemBase::updatePath(QPointF const& pos)
{
	m_currentPathPt = pos;
	onPathUpdate();

	update();
}

void ToolItemBase::endPath(QPointF const& pos)
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

QRectF ToolItemBase::boundingRect() const
{ return m_limitRectBeforeRepaint; }

void ToolItemBase::paint(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget)
{
	onPaint(painter, option, widget);
	m_limitRectBeforeRepaint = getLimitRect();
}

void ToolItemBase::onPathStart()
{}

void ToolItemBase::onPathUpdate()
{}

void ToolItemBase::onPathEnd()
{ onPathUpdate(); }

QPointF ToolItemBase::getStartPathPt() const
{ return m_pathStartPt; }

QPointF ToolItemBase::getCurrentPathPt() const
{ return m_currentPathPt; }
