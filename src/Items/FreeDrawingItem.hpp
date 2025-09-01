#pragma once

#include "Core/ToolItemBase.hpp"

class FreeDrawingItem : public ToolItemBase<FreeDrawingItem>
{
	using base_t = ToolItemBase;
	using this_t = FreeDrawingItem;

private:
	QPainterPath m_path;

public:
	QString getName() const override;

	void startPath(QPointF const& pos) override;
	void updatePath(QPointF const& pos) override;
	void endPath(QPointF const& pos) override;

	QRectF boundingRect() const override;
	void paint(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget) override;
};
