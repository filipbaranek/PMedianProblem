#include "parameterview.h"
#include "QVBoxLayout"
#include "QFormLayout"
#include <QPushButton>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLabel>

ParameterDialog::ParameterDialog(
    PMedianConfig& pMedianConfig,
    SimulatedAnnealingConfig& simAnnealConfig,
    QWidget* parent
)
    : QDialog(parent)
    , _pMedianConfig(pMedianConfig)
    , _simAnnealConfig(simAnnealConfig)
{
    setWindowTitle("PMedian algorithm parameter settings");

    initUI();
    initConnections();
}

void ParameterDialog::initUI()
{
    auto* mainLayout = new QVBoxLayout(this);
    auto* formLayout = new QFormLayout();

    _p = new QSpinBox(this);
    _p->setMinimum(1);
    _p->setMaximum(1000);
    _p->setValue(1);

    _transportCosts = new QDoubleSpinBox(this);
    _transportCosts->setMinimum(0.0);
    _transportCosts->setMaximum(std::numeric_limits<double>::max());
    _transportCosts->setDecimals(4);
    _transportCosts->setValue(_pMedianConfig.transportCosts);

    formLayout->addRow("P value:", _p);
    formLayout->addRow("Transport costs:", _transportCosts);

    _startTemp = new QDoubleSpinBox(this);
    _startTemp->setMinimum(0.0);
    _startTemp->setMaximum(std::numeric_limits<double>::max());
    _startTemp->setDecimals(4);
    _startTemp->setValue(_simAnnealConfig.startTemp);

    _minTemp = new QDoubleSpinBox(this);
    _minTemp->setMinimum(0.0);
    _minTemp->setMaximum(std::numeric_limits<double>::max());
    _minTemp->setDecimals(6);
    _minTemp->setValue(_simAnnealConfig.minTemp);

    _alpha = new QDoubleSpinBox(this);
    _alpha->setMinimum(0.0);
    _alpha->setMaximum(1.0);
    _alpha->setSingleStep(0.01);
    _alpha->setDecimals(4);
    _alpha->setValue(_simAnnealConfig.alpha);

    _iterPerTemp = new QSpinBox(this);
    _iterPerTemp->setMinimum(1);
    _iterPerTemp->setMaximum(100000);
    _iterPerTemp->setValue(_simAnnealConfig.iterPerTemp);

    formLayout->addRow("Start temperature:", _startTemp);
    formLayout->addRow("Min temperature:", _minTemp);
    formLayout->addRow("Alpha:", _alpha);
    formLayout->addRow("Iterations per temp:", _iterPerTemp);

    auto* buttonLayout = new QHBoxLayout();

    _okButton = new QPushButton("OK", this);
    _cancelButton = new QPushButton("Cancel", this);

    buttonLayout->addWidget(_okButton);
    buttonLayout->addWidget(_cancelButton);

    mainLayout->addLayout(formLayout);
    mainLayout->addStretch(1);
    mainLayout->addLayout(buttonLayout);

    setMinimumHeight(250);
    setMaximumHeight(250);
    setMinimumWidth(300);
    setMaximumWidth(300);
}

void ParameterDialog::initConnections()
{
    connect(_cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(_okButton, &QPushButton::clicked, this, &ParameterDialog::updateConfigs);
}

void ParameterDialog::updateConfigs()
{
    _pMedianConfig.p              = _p->value();
    _pMedianConfig.transportCosts = _transportCosts->value();
    _simAnnealConfig.alpha        = _alpha->value();
    _simAnnealConfig.iterPerTemp  = _iterPerTemp->value();
    _simAnnealConfig.minTemp      = _minTemp->value();
    _simAnnealConfig.startTemp    = _startTemp->value();
    accept();
}
