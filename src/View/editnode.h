#ifndef EDITNODE_H
#define EDITNODE_H

#include <QDialog>
#include <QLineEdit>
#include "Workspace/NodeView.h"

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
};

#endif // EDITNODE_H
