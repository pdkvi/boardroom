#pragma once

#include <QFrame>

class QGraphicsScene;
class QGraphicsView;

class SceneMinimap : public QFrame
{
	Q_OBJECT

	using base_t = QFrame;

private:
	QGraphicsView* m_targetView;
	QColor m_viewRectColor;

public:
	explicit SceneMinimap(QWidget* parent = nullptr);

	bool eventFilter(QObject* watched, QEvent* event) override;

	QGraphicsScene* getTargetScene() const;

	QGraphicsView* getTargetView() const;
	void setTargetView(QGraphicsView* targetView);

	QPoint mapFromScene(QPointF const& pt) const;
	QRect mapFromScene(QRectF const& rect) const;
	QPointF mapToScene(QPoint const& pt);

protected:
	void paintEvent(QPaintEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;

private:
	void paintTargetView(QPainter& painter);
	void paintTargetViewRect(QPainter& painter);
};