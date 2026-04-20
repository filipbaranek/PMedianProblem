#ifndef EDITNODE_H
#define EDITNODE_H

#include <QDialog>

class NodeView;
class QLineEdit;
class QComboBox;
class QPushButton;

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
    void updateNode();

private:
    NodeView*    _node;
    QLineEdit*   _name;
    QComboBox*   _type;
    QPushButton* _okBtn;
    QPushButton* _cancelBtn;

    //TODO POSITIONS
};

#endif // EDITNODE_H
