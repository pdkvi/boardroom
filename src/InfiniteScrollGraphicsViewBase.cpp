#include "InfiniteScrollGraphicsViewBase.hpp"


InfiniteScrollGraphicsViewBase::InfiniteScrollGraphicsViewBase(QGraphicsScene* scene, QWidget* parent)
	: base_t(scene, parent)
{
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	constexpr qreal minimum = -std::numeric_limits<qreal>::max() / 2;
	constexpr qreal maximum = std::numeric_limits<qreal>::max();

	setSceneRect(minimum, minimum, maximum, maximum);
}

InfiniteScrollGraphicsViewBase::InfiniteScrollGraphicsViewBase(QWidget* parent)
	: this_t(nullptr, parent)
{
}

InfiniteScrollGraphicsViewBase::~InfiniteScrollGraphicsViewBase() = default;
