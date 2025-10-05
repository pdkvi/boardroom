#pragma once

#include "Widgets/InfiniteScrollGraphicsViewBase.hpp"
#include "Widgets/SceneMinimap.hpp"

#include "Tools/Core/ToolBase.hpp"

#include "Items/Core/ToolItemBase.hpp"

class WhiteboardView : public InfiniteScrollGraphicsViewBase
{
	Q_OBJECT

	using base_t = InfiniteScrollGraphicsViewBase;
	using this_t = WhiteboardView;

	enum class CurrentState
	{
		Drawing,
		Moving,
		Selection,
		Nothing
	};

private:
	QRectF m_sceneRect;

	QPoint m_lastMousePos;
	CurrentState m_state;
	bool m_hasDebugRendering;

	std::unique_ptr<ToolBase> m_currentTool;
	std::unique_ptr<ToolItemBase> m_currentItem;

	SceneMinimap* m_minimap;

public:
	explicit WhiteboardView(QWidget* parent = nullptr);

	void setCurrentTool(std::unique_ptr<ToolBase>&& tool);
	std::unique_ptr<ToolBase> const& getCurrentTool() const;

	QRectF targetSceneRect() const;

	void setDebugRenderingEnabled(bool value);

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
