#pragma once

#include <QGraphicsScene>

#include "FreeHandDrawingItem.hpp"

class QUndoStack;

class WhiteboardScene : public QGraphicsScene
{
	Q_OBJECT

	using base_t = QGraphicsScene;
	using this_t = WhiteboardScene;

private:
	QUndoStack* m_commandsStack = nullptr;
	FreeHandDrawingItem* m_currentHandDrawItem = nullptr;

public:
	explicit WhiteboardScene(QObject* parent = nullptr);

	QUndoStack* getCommandsStack() noexcept;

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
};
