#include "FreeDrawingItem.hpp"

QString FreeDrawingItem::getName() const
{
	return "Free drawing";
}

QPainterPath FreeDrawingItem::shape() const
{
	return m_path;
}

void FreeDrawingItem::onPathStart()
{
	m_path.moveTo(getStartPathPt());
}

void FreeDrawingItem::onPathUpdate()
{
	m_path.lineTo(getCurrentPathPt());
}