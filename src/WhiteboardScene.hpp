#pragma once

#include <QGraphicsScene>

#include "FreeHandDrawingItem.hpp"

class WhiteboardScene : public QGraphicsScene
{
	Q_OBJECT

	using base_t = QGraphicsScene;
	using this_t = WhiteboardScene;

private:
	FreeHandDrawingItem* m_currentHandDrawItem = nullptr;

public:
	using base_t::base_t;

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
};