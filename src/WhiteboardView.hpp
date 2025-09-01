#pragma once

#include <QGraphicsView>

#include "Items/Core/IToolItem.hpp"

#include "Tools/Core/ITool.hpp"

class WhiteboardView : public QGraphicsView
{
	Q_OBJECT

	using base_t = QGraphicsView;
	using this_t = WhiteboardView;

	enum class CurrentState
	{
		Drawing,
		Moving,
		Nothing
	};

private:
	QRectF m_sceneRect;

	QPoint m_lastMousePos;
	CurrentState m_state;
	bool m_hasDebugRendering;

	std::unique_ptr<ITool> m_currentTool;
	std::unique_ptr<IToolItem> m_currentItem;

public:
	explicit WhiteboardView(QWidget* parent = nullptr);

	void setCurrentTool(std::unique_ptr<ITool>&& tool);
	std::unique_ptr<ITool> const& getCurrentTool() const;

	void setDebugRenderingEnabled(bool value);

	void syncViewRectWithScene();
	void syncViewRectWithScreen();

private:
	void renderDebugInformation(QPainter& painter) const;

protected:
	void paintEvent(QPaintEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;

	void wheelEvent(QWheelEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
};
