#pragma once

#include <QGraphicsView>

/// @brief The base class for views that should scroll beyond the scope of the sceneRect() view.
/// @details So far, the behavior of this class is achieved by a hack
///	         in the form of installing the sceneRect() view in the range
///	         from -DBL_MAX / 2 to DBL_MAX / 2. At the moment, this method
///	         does not prevent the manual installation by derived classes of sceneRect(),
///	         which will lead to a corrupted view state.

// TODO : Make a correct implementation.
class InfiniteScrollGraphicsViewBase : public QGraphicsView
{
	using base_t = QGraphicsView;
	using this_t = InfiniteScrollGraphicsViewBase;

public:
	explicit InfiniteScrollGraphicsViewBase(QGraphicsScene* scene, QWidget* parent = nullptr);
	explicit InfiniteScrollGraphicsViewBase(QWidget* parent = nullptr);

	~InfiniteScrollGraphicsViewBase() override  = 0;
};