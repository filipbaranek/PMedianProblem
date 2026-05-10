#ifndef SOLUTIONVIEW_H
#define SOLUTIONVIEW_H

#include <QDialog>

class PMedianSolutionView;
class QTextEdit;
class QPushButton;

class PMedianSolutionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PMedianSolutionDialog(const PMedianSolutionView& solution, QWidget* parent = nullptr);

private:
    void initUI();

    void loadFromSolution();

    void initConnections();

private:
    const PMedianSolutionView& _solution;
    QTextEdit*                 _output;
    QPushButton*               _okButton;
};

#endif // SOLUTIONVIEW_H
