#pragma once

#include <QFrame>

class QGraphicsView;

class SceneMinimap : public QFrame
{
	Q_OBJECT

	using base_t = QFrame;

private:
	QGraphicsView* m_targetView;

public:
	explicit SceneMinimap(QWidget* parent = nullptr);

	bool eventFilter(QObject* watched, QEvent* event) override;

	QGraphicsView const* getTargetView() const;
	void setTargetView(QGraphicsView* targetView);

	QPoint mapFromScene(QPointF const& pt) const;
	QRect mapFromScene(QRectF const& rect) const;
	QPointF mapToScene(QPoint const& pt);

protected:
	void paintEvent(QPaintEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
};