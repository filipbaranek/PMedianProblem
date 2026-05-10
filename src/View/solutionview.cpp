#include "solutionview.h"
#include "../Services/pmedianevaluator.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>

PMedianSolutionDialog::PMedianSolutionDialog(const PMedianSolutionView& solution, QWidget* parent)
    : _solution(solution)
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

    text += "=== P-Median Solution ===\n\n";
    text += QString("Total cost: %1\n\n").arg(_solution.totalCost);
    text += "Selected storages:\n";

    for (auto& storage : _solution.selectedStorages)
    {
        text += QString("  - %1\n").arg(storage._name);
    }

    text += "\nAssignments:\n";
    for (const auto& [client, storage] : _solution.assignments)
    {
        text += QString("  %1 -> %2\n").arg(client._name, storage._name);
    }

    _output->setText(text);
}

void PMedianSolutionDialog::initConnections()
{
    connect(_okButton, &QPushButton::clicked, this, &QDialog::accept);
}
