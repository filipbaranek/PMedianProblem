#include "editedgeview.h"
#include "Workspace/EdgeView.h"
#include "Workspace/NodeView.h"
#include <QCheckBox>
#include <QComboBox>
#include <QFormLayout>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QLabel>

EdgeEditDialog::EdgeEditDialog(EdgeView* edge, QWidget* parent)
    : QDialog(parent), _edge(edge)
{
    setWindowTitle("Edit edge");

    initUI();
    loadFromEdge();
    initConnections();
    updateOrientationLogic();
    updateDistanceLogic();
}

void EdgeEditDialog::initUI()
{
    auto* mainLayout = new QVBoxLayout(this);
    _layout          = new QFormLayout();

    _isValid              = new QCheckBox(this);
    _useEuclideanDistance = new QCheckBox(this);
    _distanceLabel        = new QLabel(this);
    _distanceInputBox     = new QDoubleSpinBox(this);
    _isOriented           = new QCheckBox(this);
    _nodeFrom             = new QComboBox(this);
    _nodeTo               = new QLabel(this);

    _layout->addRow("Valid:", _isValid);
    _layout->addRow("Euclidean distance:", _useEuclideanDistance);
    _layout->addRow("Distance:", _distanceLabel);
    _layout->addRow("Distance:", _distanceInputBox);
    _layout->addRow("Oriented:", _isOriented);
    _layout->addRow("Node from:", _nodeFrom);
    _layout->addRow("Node to:", _nodeTo);

    mainLayout->addLayout(_layout);
    mainLayout->addStretch(1);

    auto* button_layout = new QHBoxLayout();
    _okBtn              = new QPushButton("OK");
    _cancelBtn          = new QPushButton("Cancel");
    button_layout->addWidget(_okBtn);
    button_layout->addWidget(_cancelBtn);

    mainLayout->addLayout(button_layout);

    this->setMinimumHeight(200);
}

void EdgeEditDialog::loadFromEdge()
{
    _isValid->setChecked(_edge->isValid());
    _isOriented->setChecked(_edge->isOriented());
    _useEuclideanDistance->setChecked(_edge->useEuclideanDistance());

    _distanceLabel->setText(QString::number(_edge->distance()));
    _distanceInputBox->setMinimum(std::numeric_limits<double>::min());
    _distanceInputBox->setMaximum(std::numeric_limits<double>::max());
    _distanceInputBox->setValue(_edge->distance());

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
    connect(_isOriented, &QCheckBox::checkStateChanged, this, &EdgeEditDialog::updateOrientationLogic);
    connect(_useEuclideanDistance, &QCheckBox::checkStateChanged, this, &EdgeEditDialog::updateDistanceLogic);
    connect(_okBtn, &QPushButton::clicked, this, &EdgeEditDialog::updateEdge);
    connect(_cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
}

void EdgeEditDialog::updateOrientationLogic()
{
    _layout->setRowVisible(_nodeFrom, _isOriented->isChecked());
    _layout->setRowVisible(_nodeTo, _isOriented->isChecked());
}

void EdgeEditDialog::updateDistanceLogic()
{
    _layout->setRowVisible(_distanceLabel, _useEuclideanDistance->isChecked());
    _layout->setRowVisible(_distanceInputBox, !_useEuclideanDistance->isChecked());

    if (_useEuclideanDistance->isChecked())
    {
        _edge->setDistance();
        _distanceLabel->setText(QString::number(_edge->distance()));
    }
}

void EdgeEditDialog::updateEdge()
{
    _edge->setIsValid(_isValid->isChecked());
    _edge->setIsOriented(_isOriented->isChecked());
    _edge->setUseEuclideanDistance(_useEuclideanDistance->isChecked());
    _edge->setFrom(_nodeFrom->currentText());

    if (_useEuclideanDistance->isChecked())
    {
        _edge->setDistance();
    }
    else
    {
        _edge->setDistance(_distanceInputBox->value());
    }

    accept();
}
