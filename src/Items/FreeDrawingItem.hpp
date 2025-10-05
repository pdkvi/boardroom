#pragma once

#include "Items/Core/DrawingItemBase.hpp"
#include "Items/Core/ToolItemBase.hpp"

class FreeDrawingItem : public DrawingItemBase
{
	using base_t = DrawingItemBase;
	using this_t = FreeDrawingItem;

private:
	QPainterPath m_path;

public:
	void copyTo(ToolItemBase* target) const override;

	id_t getId() const override;
	QString getName() const override;

protected:
	std::unique_ptr<ToolItemBase> getThisCopy() const override;

	void onPathStart() override;
	void onPathUpdate() override;

	QRectF getLimitRect() const override;
	void onPaint(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget) override;
};
