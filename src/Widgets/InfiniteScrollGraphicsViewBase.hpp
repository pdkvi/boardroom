#pragma once

#include "SceneViewBase.hpp"

/// @brief The base class for views that should scroll beyond the scope of the sceneRect() view.
/// @details So far, the behavior of this class is achieved by a hack
///	         in the form of installing the sceneRect() view in the maximum possible range.
///	         At the moment, this method does not prevent the manual installation by derived classes
///	         of sceneRect(), which will lead to a corrupted view state.

// TODO : Make a correct implementation.
class InfiniteScrollGraphicsViewBase : public SceneViewBase
{
	using base_t = SceneViewBase;
	using this_t = InfiniteScrollGraphicsViewBase;

public:
	explicit InfiniteScrollGraphicsViewBase(QGraphicsScene* scene, QWidget* parent = nullptr);
	explicit InfiniteScrollGraphicsViewBase(QWidget* parent = nullptr);

	~InfiniteScrollGraphicsViewBase() override  = 0;
};