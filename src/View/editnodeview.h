#ifndef EDITNODE_H
#define EDITNODE_H

#include <QDialog>

class NodeView;
class QFormLayout;
class QLineEdit;
class QComboBox;
class QPushButton;
class QDoubleSpinBox;
class QLabel;

class NodeEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NodeEditDialog(NodeView* node, QWidget* parent = nullptr);

private:
    void initUI();

    void loadFromEdge();

    void initConnections();

private slots:
    void updateFixedCostsParam();

    void updateNode();

private:
    NodeView*       _node;
    QFormLayout*    _layout;
    QLineEdit*      _name;
    QComboBox*      _type;
    QDoubleSpinBox* _posX;
    QDoubleSpinBox* _posY;
    QDoubleSpinBox* _fixedCosts;
    QLabel*         _fixedCostsLabel;
    QPushButton*    _okBtn;
    QPushButton*    _cancelBtn;
};

#endif // EDITNODE_H
