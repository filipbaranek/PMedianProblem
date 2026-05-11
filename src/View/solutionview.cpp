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

    _output->setReadOnly(true);

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
    QString html;

    html += R"(
        <div style='text-align:center; font-size:16px;'>
    )";
    if (_solution.assignments.empty() || _solution.selectedStorages.empty())
    {
        html += R"(
            <h2>No solution to show yet</h2>
        )";
    }
    else
    {
        html += R"(
            <h1 style='font-size:32px;'>P-Median Solution</h1>
        )";

        html += QString(
            "<p><b style='font-size:20px;'>Total cost:</b> "
            "<span style='font-size:20px;'>%1</span></p>")
            .arg(_solution.totalCost);

        html += R"(
            <p><b style='font-size:22px;'>Selected storages:</b></p>
        )";

        for (auto& storage : _solution.selectedStorages)
        {
            html += QString("<p style='font-size:18px;'>&bull; %1</p>").arg(storage._name);
        }

        html += R"(
            <br>
            <p><b style='font-size:22px;'>Assignments:</b></p>
        )";

        for (const auto& [client, storage] : _solution.assignments)
        {
            html += QString("<p style='font-size:18px;'>%1 &rarr; %2</p>")
                .arg(client._name, storage._name);
        }
    }

    html += "</div>";

    _output->setHtml(html);
}

void PMedianSolutionDialog::initConnections()
{
    connect(_okButton, &QPushButton::clicked, this, &QDialog::accept);
}
