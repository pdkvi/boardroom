#pragma once

#include "Core/ToolItemBase.hpp"

class EllipseItem : public ToolItemBase<EllipseItem>
{
private:
	QPointF m_startPt;
	QPointF m_endPt;

public:
	QString getName() const override;

protected:
	void startPathImpl(QPointF const& pos) override;
	void updatePathImpl(QPointF const& pos) override;
	void endPathImpl(QPointF const& pos) override;

	QRectF boundingRectImpl() const override;
	void paintImpl(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget) override;
};