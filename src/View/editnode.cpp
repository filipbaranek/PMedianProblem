#include "editnode.h"
#include "Workspace/NodeView.h"
#include "../Common/NodeType.h"
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>

NodeEditDialog::NodeEditDialog(NodeView* node, QWidget* parent)
    :QDialog(parent), _node(node)
{
    setWindowTitle("Edit node");

    initUI();
    loadFromEdge();
    initConnections();
}

void NodeEditDialog::initUI()
{
    auto* layout = new QFormLayout(this);

    _name = new QLineEdit(this);
    _type = new QComboBox(this);

    layout->addRow("Name:", _name);
    layout->addRow("Type:", _type);

    auto* buttonLayout = new QHBoxLayout();

    _okBtn     = new QPushButton("OK");
    _cancelBtn = new QPushButton("Cancel");

    buttonLayout->addWidget(_okBtn);
    buttonLayout->addWidget(_cancelBtn);

    layout->addRow(buttonLayout);
}

void NodeEditDialog::loadFromEdge()
{
    _name->setText(_node->name());

    _type->addItem("Customer", static_cast<int32_t>(NodeType::CUSTOMER));
    _type->addItem("Storage", static_cast<int32_t>(NodeType::STORAGE));
    int currentTypeIndex = _type->findData(static_cast<int32_t>(_node->nodeType()));
    _type->setCurrentIndex(currentTypeIndex);
}

void NodeEditDialog::initConnections()
{
    connect(_cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
    connect(_okBtn, &QPushButton::clicked, this, &NodeEditDialog::updateNode);
}

void NodeEditDialog::updateNode()
{
    _node->setName(_name->text());
    _node->setNodeType(static_cast<NodeType>(_type->currentData().toInt()));
    accept();
}
