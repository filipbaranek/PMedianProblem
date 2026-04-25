#ifndef EDITEDGE_H
#define EDITEDGE_H

#include <QDialog>

class EdgeView;
class QCheckBox;
class QComboBox;
class QLabel;
class QPushButton;
class QFormLayout;
class QDoubleSpinBox;

class EdgeEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EdgeEditDialog(EdgeView* edge, QWidget* parent = nullptr);

private:
    void initUI();

    void loadFromEdge();

    void initConnections();

private slots:
    void updateOrientationLogic();

    void updateDistanceLogic();

    void updateEdge();

private:
    EdgeView*       _edge;
    QFormLayout*    _layout;
    QCheckBox*      _isValid;
    QCheckBox*      _isOriented;
    QCheckBox*      _useEuclideanDistance;
    QPushButton*    _okBtn;
    QPushButton*    _cancelBtn;
    QComboBox*      _nodeFrom;
    QLabel*         _nodeTo;
    QLabel*         _distanceLabel;
    QDoubleSpinBox* _distanceInputBox;

    //TODO if !useEuclidean then define distance input box
};

#endif // EDITEDGE_H
