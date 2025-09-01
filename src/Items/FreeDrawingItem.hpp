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

protected:
	void startPathImpl(QPointF const& pos) override;
	void updatePathImpl(QPointF const& pos) override;
	void endPathImpl(QPointF const& pos) override;

	QRectF boundingRectImpl() const override;
	void paintImpl(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget) override;
};
