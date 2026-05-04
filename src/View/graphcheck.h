#ifndef GRAPHCHECK_H
#define GRAPHCHECK_H

#include <QDialog>

class QPushButton;

class GraphCheck : public QDialog
{
    Q_OBJECT

public:
    GraphCheck(const QString& message, QWidget* parent = nullptr);

    void initUI(const QString& message);

    void initConnections();

private:
    QPushButton* _okButton;
};

#endif // GRAPHCHECK_H
