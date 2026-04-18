#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Components/grid.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) , _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    auto* central = new QWidget(this);
    setCentralWidget(central);

    auto* layout = new QVBoxLayout(central);

    auto* grid = new Grid(central);
    layout->addWidget(grid);
}

MainWindow::~MainWindow()
{
    delete _ui;
}