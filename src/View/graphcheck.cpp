#include "graphcheck.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

GraphCheck::GraphCheck(const QString& message, QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Graph connection check");
    initUI(message);
    initConnections();
    setMinimumWidth(300);
}

void GraphCheck::initUI(const QString& message)
{
    _okButton = new QPushButton("Ok", this);

    auto* layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel(message, this), 0, Qt::AlignCenter);
    layout->addWidget(_okButton, 0 , Qt::AlignCenter);
    layout->setSpacing(10);
    layout->setContentsMargins(15, 15, 15, 15);
}

void GraphCheck::initConnections()
{
    connect(_okButton, &QPushButton::clicked, this, &QDialog::accept);
}
