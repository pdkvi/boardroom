#include "InfiniteScrollGraphicsViewBase.hpp"

InfiniteScrollGraphicsViewBase::InfiniteScrollGraphicsViewBase(QGraphicsScene* scene, QWidget* parent)
	: base_t(scene, parent)
{
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	// limit the values from INT_MIN to INT_MAX,
	// because with large values, the logic of QGraphicsView breaks down.
	constexpr qreal minimum = INT_MIN;
	constexpr qreal maximum = INT_MAX;

	setSceneRect(minimum, minimum, maximum * 2, maximum * 2);
}

InfiniteScrollGraphicsViewBase::InfiniteScrollGraphicsViewBase(QWidget* parent)
	: this_t(nullptr, parent)
{
}

InfiniteScrollGraphicsViewBase::~InfiniteScrollGraphicsViewBase() = default;
