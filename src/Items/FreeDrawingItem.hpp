#pragma once

#include "Items/Core/ToolItemBase.hpp"

class FreeDrawingItem : public ToolItemBase
{
	using base_t = ToolItemBase;
	using this_t = FreeDrawingItem;

private:
	QPainterPath m_path;

public:
	std::unique_ptr<ToolItemBase> clone() const override;

	id_t getId() const override;
	QString getName() const override;

protected:
	void onPathStart() override;
	void onPathUpdate() override;

	QRectF getLimitRect() const override;
	void onPaint(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget) override;
};
