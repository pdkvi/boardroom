#pragma once

#include <QGraphicsView>

class WhiteboardView : public QGraphicsView
{
	Q_OBJECT

	using base_t = QGraphicsView;
	using this_t = WhiteboardView;

private:
	QRectF m_sceneRect;

	QPoint m_lastMousePos;
	bool m_isViewRectDragging;
	bool m_hasDebugRendering;

public:
	explicit WhiteboardView(QWidget* parent = nullptr);

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