#pragma once

#include <QUndoCommand>

class QGraphicsScene;
class QGraphicsItem;

class DrawCommand : public QUndoCommand
{
	using base_t = QUndoCommand;
	using this_t = DrawCommand;

private:
	QGraphicsScene* m_scene = nullptr;
	QGraphicsItem* m_item = nullptr;

public:
	explicit DrawCommand(QGraphicsItem* item, QUndoCommand* parent = nullptr);
	~DrawCommand() override;

	void redo() override;
	void undo() override;
};
