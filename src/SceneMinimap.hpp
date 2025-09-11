#pragma once

#include <QFrame>

class QGraphicsView;

class SceneMinimap : public QFrame
{
	Q_OBJECT

	using base_t = QFrame;

private:
	QGraphicsView const* m_targetView;

public:
	explicit SceneMinimap(QWidget* parent = nullptr);

	QGraphicsView const* getTargetView() const;
	void setTargetView(QGraphicsView const* targetView);

	QPoint mapFromScene(QPointF const& pt) const;
	QRect mapFromScene(QRectF const& rect) const;

protected:
	void paintEvent(QPaintEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
};