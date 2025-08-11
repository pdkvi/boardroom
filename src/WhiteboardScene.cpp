#include "WhiteboardScene.hpp"

#include <QGraphicsSceneMouseEvent>

#include "Commands/DrawCommand.hpp"

WhiteboardScene::WhiteboardScene(QObject* parent)
	: base_t(parent), m_commandsStack(new QUndoStack(this))
{
}

QUndoStack* WhiteboardScene::getCommandsStack() noexcept
{
	return m_commandsStack;
}

void WhiteboardScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	m_currentHandDrawItem = new FreeHandDrawingItem(event->scenePos());
	addItem(m_currentHandDrawItem);
}

void WhiteboardScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	// updating scene bounding rect
	removeItem(m_currentHandDrawItem);
	addItem(m_currentHandDrawItem);

	m_commandsStack->push(new DrawCommand(m_currentHandDrawItem));
	m_currentHandDrawItem = nullptr;
	update();
}

void WhiteboardScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	if (m_currentHandDrawItem)
	{
		m_currentHandDrawItem->moveTo(event->scenePos());
		update();
	}

	base_t::mouseMoveEvent(event);
}