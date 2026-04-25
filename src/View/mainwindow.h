#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class GridViewModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(GridViewModel* fileManager, QWidget* parent = nullptr);

    ~MainWindow() override;

private slots:
    void openFile();

    void saveItemsAs();

private:
    void initConnections();

    Ui::MainWindow* _ui;
    GridViewModel*  _viewModel;
};
#endif // MAINWINDOW_H
