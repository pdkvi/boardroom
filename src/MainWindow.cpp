#include "MainWindow.hpp"

#include "WhiteboardScene.hpp"

MainWindow::MainWindow(QWidget* parent)
	: base_t(parent), m_ui(new Ui::MainWindow)
{
	m_ui->setupUi(this);

	auto* scene = qobject_cast<WhiteboardScene*>(m_ui->whiteboardView->scene());
	m_ui->historyView->setStack(scene->getCommandsStack());

	connect(m_ui->whiteboardViewDebugRenderingAction, &QAction::toggled,
		m_ui->whiteboardView, &WhiteboardView::setDebugRenderingEnabled);
}

MainWindow::~MainWindow()
{
	delete m_ui;
}
