#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget* parent)
    : base_t(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}
