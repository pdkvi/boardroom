#pragma once

#include <QGraphicsItem>

class FreeHandDrawingItem : public QGraphicsItem
{
	using base_t = QGraphicsItem;
	using this_t = FreeHandDrawingItem;

private:
	QPainterPath m_path;

public:
	explicit FreeHandDrawingItem(QPointF const& startPt, QGraphicsItem* parent = nullptr);

	QRectF boundingRect() const override;

	void paint(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget) override;
	void moveTo(QPointF const& pt);
};