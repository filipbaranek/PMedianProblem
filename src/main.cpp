#include <QApplication>
#include "View/mainwindow.h"
#include "Services/filemanager.h"
#include "ViewModel/gridviewmodel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto fileManager = std::make_shared<FileManager>();

    GridViewModel gridViewModel(fileManager);

    MainWindow w(&gridViewModel);
    w.showMaximized();

    return QCoreApplication::exec();
}
