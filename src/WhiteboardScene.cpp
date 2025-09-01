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
	base_t::mousePressEvent(event);
}

void WhiteboardScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	base_t::mouseReleaseEvent(event);
}

void WhiteboardScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	base_t::mouseMoveEvent(event);
}