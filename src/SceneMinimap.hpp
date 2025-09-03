#pragma once

#include <QWidget>

class QGraphicsView;

class SceneMinimapImpl;

class SceneMinimap : public QWidget
{
	Q_OBJECT

	using base_t = QWidget;

private:
	SceneMinimapImpl* m_impl;

public:
	explicit SceneMinimap(QWidget* parent = nullptr);

	QGraphicsView const* getTargetView() const;
	void setTargetView(QGraphicsView const* targetView);
};