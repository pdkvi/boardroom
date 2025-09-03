#include "SceneMinimap.hpp"

#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QHBoxLayout>

class SceneMinimapImpl : public QGraphicsView
{
	using base_t = QGraphicsView;

public:
	QGraphicsView const* m_targetView;

public:
	explicit SceneMinimapImpl(QWidget* parent = nullptr)
		: base_t(parent), m_targetView(nullptr)
	{
		setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	}

public:
	QGraphicsView const* getTargetView() const { return m_targetView; }

	void setTargetView(QGraphicsView const* targetView)
	{
		m_targetView = targetView;
		setScene(m_targetView->scene());
	}

protected:
	void paintEvent(QPaintEvent* event) override
	{
		fitInView(sceneRect(), Qt::KeepAspectRatio);
		base_t::paintEvent(event);

		if (m_targetView == nullptr)
			return;

		QRectF const screenSceneRect = mapToScene(QRect{ 0, 0, width(), height() }).boundingRect();

		QRectF const targetScreenSceneRect = m_targetView->mapToScene(QRect{ 0, 0, m_targetView->width(), m_targetView->height() }).boundingRect();
		if (targetScreenSceneRect.contains(screenSceneRect))
			return;

		QPainter painter(viewport());

		painter.setPen(QColor(0, 0, 255, 128));
		painter.setBrush(QColor(0, 0, 255, 64));
		painter.drawRect(mapFromScene(targetScreenSceneRect).boundingRect());
	}
};

SceneMinimap::SceneMinimap(QWidget* parent)
	: base_t(parent), m_impl(new SceneMinimapImpl(this))
{
	auto* layout = new QHBoxLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(m_impl);

	setLayout(layout);
}

QGraphicsView const* SceneMinimap::getTargetView() const
{
	return m_impl->getTargetView();
}

void SceneMinimap::setTargetView(QGraphicsView const* targetView)
{
	m_impl->setTargetView(targetView);
}