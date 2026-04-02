#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) , _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    auto* central = new QWidget(this);
    setCentralWidget(central);

    auto* layout = new QVBoxLayout(central);

    auto* grid = new Grid(this);
    layout->addWidget(grid);
}

MainWindow::~MainWindow()
{
    delete _ui;
}