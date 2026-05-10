#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphcheck.h"
#include "solutionview.h"
#include "parameterview.h"
#include "../ViewModel/gridviewmodel.h"
#include <QVBoxLayout>

MainWindow::MainWindow(GridViewModel* viewModel, QWidget* parent)
    : QMainWindow(parent)
    , _ui(new Ui::MainWindow)
    , _viewModel(viewModel)
{
    setWindowTitle("P-Median problem");

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
    connect(_ui->actionRun, &QAction::triggered, _viewModel, &GridViewModel::solvePMedianProblem);
    connect(_ui->actionCheck, &QAction::triggered, _viewModel, &GridViewModel::checkGraphConnection);
    connect(_ui->actionOutput, &QAction::triggered, _viewModel, &GridViewModel::showLastSolutionOutput);
    connect(_ui->actionParameters, &QAction::triggered, _viewModel, &GridViewModel::updateConfigs);

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
    connect(_ui->graphicsView, &Grid::onDeleteNode, _viewModel, &GridViewModel::removeNode);
    connect(_ui->graphicsView, &Grid::onDeleteEdge, _viewModel, &GridViewModel::removeEdge);
    connect(_ui->graphicsView, &Grid::onClearSolution, _viewModel, &GridViewModel::clearSolution);
    connect(_viewModel, &GridViewModel::onClearSolution, _ui->graphicsView, &Grid::clearSolution);
    connect(_viewModel, &GridViewModel::onLoadFromFile, _ui->graphicsView, &Grid::insertItemsFromFile);
    connect(_viewModel, &GridViewModel::onShowOutput, _ui->graphicsView, &Grid::drawSolution);
    connect(_viewModel, &GridViewModel::onShowOutput, [](const PMedianSolutionView& solution) {
        PMedianSolutionDialog outputDialog(solution);
        outputDialog.exec();
    });
    connect(_viewModel, &GridViewModel::onCheckGraphConnection, [](const QString& message) {
        GraphCheck graphCheckDialog(message);
        graphCheckDialog.exec();
    });
    connect(_viewModel, &GridViewModel::onUpdateConfigs, [](
        PMedianConfig& pMedianConfig, SimulatedAnnealingConfig& simAnnealConfig) {
        ParameterDialog parameterDialog(pMedianConfig, simAnnealConfig);
        parameterDialog.exec();
    });
}
