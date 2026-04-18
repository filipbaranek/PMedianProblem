#include "editedge.h"
#include "Workspace/EdgeView.h"
#include "Workspace/NodeView.h"
#include <QCheckBox>
#include <QComboBox>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>

EdgeEditDialog::EdgeEditDialog(EdgeView* edge, QWidget* parent)
    : QDialog(parent), _edge(edge)
{
    setWindowTitle("Edit edge");

    initUI();
    loadFromEdge();
    initConnections();
}

void EdgeEditDialog::initUI()
{
    auto* layout = new QFormLayout(this);

    _isValid = new QCheckBox(this);
    _isOriented = new QCheckBox(this);
    _useEuclideanDistance = new QCheckBox(this);

    _nodeFrom = new QComboBox(this);
    _nodeTo   = new QLabel(this);

    layout->addRow("Valid:", _isValid);
    layout->addRow("Oriented:", _isOriented);
    layout->addRow("Euclidean distance:", _useEuclideanDistance);
    layout->addRow("Node from:", _nodeFrom);
    layout->addRow("Node to:", _nodeTo);

    auto* buttonLayout = new QHBoxLayout();

    _okBtn     = new QPushButton("OK");
    _cancelBtn = new QPushButton("Cancel");

    buttonLayout->addWidget(_okBtn);
    buttonLayout->addWidget(_cancelBtn);

    layout->addRow(buttonLayout);
}

void EdgeEditDialog::loadFromEdge()
{
    _isValid->setChecked(_edge->isValid());
    _isOriented->setChecked(_edge->isOriented());
    _useEuclideanDistance->setChecked(_edge->useEuclideanDistance());

    _nodeFrom->addItem(_edge->from()->name());
    _nodeFrom->addItem(_edge->to()->name());
    int fromIndex = _nodeFrom->findText(_edge->from()->name());
    _nodeFrom->setCurrentIndex(fromIndex);

    _nodeTo->setText(_edge->to()->name());
}

void EdgeEditDialog::initConnections()
{
    connect(_nodeFrom, &QComboBox::currentTextChanged, this, [this](const QString& text) {
        if (text == _edge->from()->name())
        {
            _nodeTo->setText(_edge->to()->name());
        }
        else
        {
            _nodeTo->setText(_edge->from()->name());
        }
    });
    connect(_okBtn, &QPushButton::clicked, this, &EdgeEditDialog::updateEdge);
    connect(_cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
}

void EdgeEditDialog::updateEdge()
{
    _edge->setIsValid(_isValid->isChecked());
    _edge->setIsOriented(_isOriented->isChecked());
    _edge->setUseEuclideanDistance(_useEuclideanDistance->isChecked());
    _edge->setFrom(_nodeFrom->currentText());
    accept();
}
