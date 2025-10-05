#include "SceneViewBase.hpp"

void SceneViewBase::paintEvent(QPaintEvent* event)
{
	if (m_lastViewportTransform != viewportTransform())
	{
		emit transformChanged();
		m_lastViewportTransform = viewportTransform();
	}

	base_t::paintEvent(event);
}
