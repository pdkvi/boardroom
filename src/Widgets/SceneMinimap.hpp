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

	std::optional<QPoint> mapFromScene(QPointF const& pt) const;
	std::optional<QRect> mapFromScene(QRectF const& rect) const;
	std::optional<QPointF> mapToScene(QPoint const& pt);

protected:
	void paintEvent(QPaintEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;

private:
	void paintTargetView(QPainter& painter);
	void paintTargetViewRect(QPainter& painter);

	/// @brief Get the number of scene units in one pixel of the minimap
	/// @return std::nullopt, if the target scene is nullptr
	std::optional<qreal> getSceneUnitsInPx() const;

	/// @brief Get a dimension that the scene completely fills
	/// @note During this check, both the aspect ratio of the scene and
	/// the aspect ratio of the minimap are taken into account.
	/// @return std::nullopt, if the target scene is nullptr
	std::optional<Qt::Orientation> getSceneOrientationInMinimap() const;

	/// @brief Get the point (0, 0) in the coordinates of the scene,
	/// taking into account the alignment of the minimap
	/// @return std::nullopt, if the target scene is nullptr
	std::optional<QPointF> getAlignedSceneTopLeftPt() const;
};