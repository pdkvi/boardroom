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

public:
	explicit WhiteboardView(QWidget* parent = nullptr);

	void syncViewRectWithScene();
	void syncViewRectWithScreen();

protected:
	void paintEvent(QPaintEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;

	void wheelEvent(QWheelEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
};