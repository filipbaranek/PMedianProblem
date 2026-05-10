#include "solutionview.h"
#include "../Services/pmedianevaluator.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>

PMedianSolutionDialog::PMedianSolutionDialog(const PMedianSolutionView& solution, QWidget* parent)
    : QDialog(parent)
    , _solution(solution)
{
    setWindowTitle("Solution output");

    initUI();
    loadFromSolution();
    initConnections();
}

void PMedianSolutionDialog::initUI()
{
    setMinimumSize(QSize{600, 500});

    QVBoxLayout* mainLayout   = new QVBoxLayout();
    QHBoxLayout* buttonLayout = new QHBoxLayout();

    _output   = new QTextEdit(this);
    _okButton = new QPushButton("Ok", this);

    mainLayout->addWidget(_output);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(buttonLayout);

    buttonLayout->addStretch();
    buttonLayout->addWidget(_okButton);
    buttonLayout->addStretch();

    setLayout(mainLayout);
}

void PMedianSolutionDialog::loadFromSolution()
{
    QString text;

    if (_solution.assignments.empty() || _solution.selectedStorages.empty())
    {
        text += R"(
            <div align='center'>
                <h2>No solution to show yet</h2>
            </div>
        )";
    }
    else
    {
        text += R"(
            <div align='center'>
                <h1>P-Median Solution</h1>
            </div>
        )";
        text += QString("<b>Total cost:</b> %1<br><br>").arg(_solution.totalCost);
        text += "<b>Selected storages:</b><br>";

        for (auto& storage : _solution.selectedStorages)
        {
            text += QString("&nbsp;&nbsp;&bull; %1<br>").arg(storage._name);
        }

        text += "<br><b>Assignments:</b><br>";
        for (const auto& [client, storage]
             : _solution.assignments)
        {
            text += QString("&nbsp;&nbsp;%1 &rarr; %2<br>").arg(client._name, storage._name);
        }
    }

    _output->setHtml(text);
}

void PMedianSolutionDialog::initConnections()
{
    connect(_okButton, &QPushButton::clicked, this, &QDialog::accept);
}
