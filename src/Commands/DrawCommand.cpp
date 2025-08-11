#include "DrawCommand.hpp"

#include <QGraphicsItem>
#include <QGraphicsScene>

DrawCommand::DrawCommand(QGraphicsItem* item, QUndoCommand* parent)
	: base_t(QObject::tr("Drawing"), parent),
	  m_scene(item->scene()),
	  m_item(item)
{
	Q_ASSERT(m_scene);
	Q_ASSERT(m_item);
}

DrawCommand::~DrawCommand()
{
	if (m_item->scene() == nullptr)
		delete m_item;
}

void DrawCommand::redo()
{
	m_scene->addItem(m_item);
	QUndoCommand::redo();
}

void DrawCommand::undo()
{
	m_scene->removeItem(m_item);
	QUndoCommand::undo();
}
