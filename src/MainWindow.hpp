#pragma once

#include "ui_MainWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    using base_t = QMainWindow;
    using this_t = MainWindow;

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow* m_ui;
};