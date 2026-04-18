#ifndef EDITEDGE_H
#define EDITEDGE_H

#include <QDialog>

class EdgeView;
class QCheckBox;
class QComboBox;
class QLabel;
class QPushButton;

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
    void updateEdge();

private:
    EdgeView*    _edge;
    QCheckBox*   _isValid;
    QCheckBox*   _isOriented;
    QCheckBox*   _useEuclideanDistance;
    QComboBox*   _nodeFrom;
    QLabel*      _nodeTo;
    QPushButton* _okBtn;
    QPushButton* _cancelBtn;
};

#endif // EDITEDGE_H
