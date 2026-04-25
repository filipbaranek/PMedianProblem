#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../ViewModel/gridviewmodel.h"
#include <QVBoxLayout>

MainWindow::MainWindow(GridViewModel* viewModel, QWidget* parent)
    : QMainWindow(parent),
      _ui(new Ui::MainWindow),
      _viewModel(viewModel)
{
    _ui->setupUi(this);
    _ui->actionEuclidean_distance->setChecked(true);

    initConnections();
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::initConnections()
{
    connect(_ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(_ui->actionSave_as, &QAction::triggered, this, &MainWindow::saveItemsAs);
    connect(_ui->actionEuclidean_distance, &QAction::toggled, _ui->graphicsView, &Grid::setEuclideanMode);
}

void MainWindow::openFile()
{
    //TODO
}

void MainWindow::saveItemsAs()
{
    auto items = _ui->graphicsView->itemsToDTO();

    auto& nodes = items.first;
    auto& edges = items.second;

    _viewModel->saveItemsToFile(nodes, edges);
}
