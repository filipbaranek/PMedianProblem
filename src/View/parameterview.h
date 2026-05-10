#ifndef PARAMETERVIEW_H
#define PARAMETERVIEW_H

#include <QDialog>
#include "../Services/pmedianevaluator.h"
#include "../Services/simulatedannealing.h"

class QPushButton;
class QLabel;
class QSpinBox;
class QDoubleSpinBox;

class ParameterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ParameterDialog(
        PMedianConfig& pMedianConfig,
        SimulatedAnnealingConfig& simAnnealConfig,
        QWidget* parent = nullptr);

private:
    void initUI();

    void initConnections();

private slots:
    void updateConfigs();

private:
    QSpinBox*       _p;
    QDoubleSpinBox* _transportCosts;
    QDoubleSpinBox* _startTemp;
    QDoubleSpinBox* _minTemp;
    QDoubleSpinBox* _alpha;
    QSpinBox*       _iterPerTemp;
    QPushButton*    _okButton;
    QPushButton*    _cancelButton;

    PMedianConfig&            _pMedianConfig;
    SimulatedAnnealingConfig& _simAnnealConfig;
};

#endif // PARAMETERVIEW_H
