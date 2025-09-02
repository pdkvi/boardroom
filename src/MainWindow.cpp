#include "MainWindow.hpp"

#include "WhiteboardToolsModel.hpp"
#include "WhiteboardScene.hpp"

#include "Tools/ShapeTool.hpp"
#include "Tools/PenTool.hpp"

MainWindow::MainWindow(QWidget* parent)
	: base_t(parent), m_ui(new Ui::MainWindow)
{
	m_ui->setupUi(this);

	auto* scene = qobject_cast<WhiteboardScene*>(m_ui->whiteboardView->scene());
	m_ui->historyView->setStack(scene->getCommandsStack());

	connect(m_ui->whiteboardViewDebugRenderingAction, &QAction::toggled,
		m_ui->whiteboardView, &WhiteboardView::setDebugRenderingEnabled);

	auto* toolsModel = new WhiteboardToolsModel;
	toolsModel->addTool(PenTool::getToolId());
	toolsModel->addTool(ShapeTool::getToolId());

	m_ui->toolsView->setModel(toolsModel);

	connect(m_ui->toolsView->selectionModel(), &QItemSelectionModel::currentRowChanged,
		m_ui->whiteboardView,
		[this](QModelIndex const& current, QModelIndex const& /*previous*/)
		{
			QAbstractItemModel const* model = m_ui->toolsView->model();

			QVariant const data = model->data(current, WhiteboardToolsModel::ItemRole::Data);
			auto const tool = data.value<std::shared_ptr<ITool const>>();

			m_ui->whiteboardView->setCurrentTool(tool->clone());
		}
	);
	m_ui->toolsView->selectionModel()->setCurrentIndex(toolsModel->index(0), QItemSelectionModel::ClearAndSelect);
}

MainWindow::~MainWindow()
{
	delete m_ui;
}
