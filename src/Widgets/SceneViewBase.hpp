#pragma once

#include <QGraphicsView>

class SceneViewBase : public QGraphicsView
{
	Q_OBJECT

	using base_t = QGraphicsView;
	using this_t = SceneViewBase;

private:
	QTransform m_lastViewportTransform;

public:
	using base_t::base_t;

signals:
	void transformChanged();

protected:
	void paintEvent(QPaintEvent* event) override;
};
