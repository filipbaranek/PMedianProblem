#ifndef EDITNODE_H
#define EDITNODE_H

#include <QDialog>

class NodeView;
class QLineEdit;
class QComboBox;

class NodeEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NodeEditDialog(NodeView* node, QWidget* parent = nullptr);

private slots:
    void updateNode();

private:
    NodeView*  _node;
    QLineEdit* _name;
    QComboBox* _type;
};

#endif // EDITNODE_H
