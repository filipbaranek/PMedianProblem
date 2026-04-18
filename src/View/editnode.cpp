#include "editnode.h"
#include "Workspace/NodeView.h"
#include "../Common/NodeType.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>

NodeEditDialog::NodeEditDialog(NodeView* node, QWidget* parent)
    :QDialog(parent), _node(node)
{
    setWindowTitle("Edit node");

    auto* layout = new QVBoxLayout(this);

    _name = new QLineEdit(this);
    _name->setText(node->name());

    _type = new QComboBox(this);
    _type->addItem("Customer", static_cast<int32_t>(NodeType::CUSTOMER));
    _type->addItem("Storage", static_cast<int32_t>(NodeType::STORAGE));
    int currentTypeIndex = _type->findData(static_cast<int32_t>(_node->nodeType()));
    _type->setCurrentIndex(currentTypeIndex);

    layout->addWidget(_name);
    layout->addWidget(_type);

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
    _node->setNodeType(static_cast<NodeType>(_type->currentData().toInt()));
    accept();
}
