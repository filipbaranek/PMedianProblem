#include "editnode.h"

#include <QVBoxLayout>
#include <QPushButton>

NodeEditDialog::NodeEditDialog(NodeView* node, QWidget* parent)
    :QDialog(parent), _node(node)
{
    setWindowTitle("Edit node");

    auto* layout = new QVBoxLayout(this);

    _name = new QLineEdit(this);
    _name->setText(node->name());

    layout->addWidget(_name);

    auto* buttonLayout = new QHBoxLayout();

    auto* okBtn     = new QPushButton("OK");
    auto* cancelBtn = new QPushButton("Cancel");

    buttonLayout->addWidget(okBtn);
    buttonLayout->addWidget(cancelBtn);

    layout->addLayout(buttonLayout);

    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
    connect(okBtn, &QPushButton::clicked, this, &NodeEditDialog::updateNode);
}

void NodeEditDialog::updateNode()
{
    _node->setName(_name->text());
    //TODO
    accept();
}
