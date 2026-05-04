#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphcheck.h"
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
    // ToolBar
    connect(_ui->actionCheck, &QAction::triggered, _viewModel, &GridViewModel::checkGraphConnection);

    // UI
    connect(_ui->actionOpen, &QAction::triggered, _viewModel, &GridViewModel::loadItemsFromFile);
    connect(_ui->actionSave_as, &QAction::triggered, _viewModel, &GridViewModel::saveItemsToFile);
    connect(_ui->actionEuclidean_distance, &QAction::toggled, _ui->graphicsView, &Grid::setEuclideanMode);

    // Events
    connect(_ui->graphicsView, &Grid::onClear, _viewModel, &GridViewModel::clear);
    connect(_ui->graphicsView, &Grid::onAddNode, _viewModel, &GridViewModel::setNode);
    connect(_ui->graphicsView, &Grid::onAddEdge, _viewModel, &GridViewModel::setEdge);
    connect(_ui->graphicsView, &Grid::onUpdateNode, _viewModel, &GridViewModel::setNode);
    connect(_ui->graphicsView, &Grid::onUpdateEdge, _viewModel, &GridViewModel::setEdge);
    connect(_ui->graphicsView, &Grid::onDeleteEdge, _viewModel, &GridViewModel::removeNode);
    connect(_ui->graphicsView, &Grid::onDeleteEdge, _viewModel, &GridViewModel::removeEdge);
    connect(_viewModel, &GridViewModel::onLoadFromFile, _ui->graphicsView, &Grid::insertItemsFromFile);

    connect(_viewModel, &GridViewModel::onCheckGraphConnection, [](const QString& message) {
        GraphCheck graphCheckDialog(message);
        graphCheckDialog.exec();
    });
}
