#include "editnodeview.h"
#include "Workspace/NodeView.h"
#include "../Common/nodetype.h"
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QLabel>

NodeEditDialog::NodeEditDialog(NodeView* node, QWidget* parent)
    : QDialog(parent)
    , _node(node)
{
    setWindowTitle("Edit node");

    initUI();
    loadFromEdge();
    initConnections();
}

void NodeEditDialog::initUI()
{
    auto* mainLayout = new QVBoxLayout(this);

    _layout = new QFormLayout();

    _name            = new QLineEdit(this);
    _type            = new QComboBox(this);
    _posX            = new QDoubleSpinBox(this);
    _posY            = new QDoubleSpinBox(this);
    _fixedCosts      = new QDoubleSpinBox(this);
    _fixedCostsLabel = new QLabel(this);

    _layout->addRow("Name:", _name);
    _layout->addRow("Type:", _type);
    _layout->addRow("Pos X:", _posX);
    _layout->addRow("Pos Y:", _posY);
    _layout->addRow(_fixedCostsLabel, _fixedCosts);

    mainLayout->addLayout(_layout);
    mainLayout->addStretch(1);

    auto* buttonLayout = new QHBoxLayout();

    _okBtn     = new QPushButton("OK");
    _cancelBtn = new QPushButton("Cancel");

    buttonLayout->addWidget(_okBtn);
    buttonLayout->addWidget(_cancelBtn);

    mainLayout->addLayout(buttonLayout);

    setMinimumHeight(200);
    setMinimumWidth(210);
}

void NodeEditDialog::loadFromEdge()
{
    _name->setText(_node->name());

    _type->addItem("Customer", static_cast<int32_t>(NodeType::CUSTOMER));
    _type->addItem("Storage", static_cast<int32_t>(NodeType::STORAGE));
    int currentTypeIndex = _type->findData(static_cast<int32_t>(_node->nodeType()));
    _type->setCurrentIndex(currentTypeIndex);

    _posX->setMinimum(std::numeric_limits<double>::lowest());
    _posX->setMaximum(std::numeric_limits<double>::max());
    _posX->setValue(_node->posX());

    _posY->setMinimum(std::numeric_limits<double>::lowest());
    _posY->setMaximum(std::numeric_limits<double>::max());
    _posY->setValue(-_node->posY());

    _fixedCostsLabel->setText("Fixed costs");
    _fixedCosts->setValue(_node->fixedCosts());
    updateFixedCostsParam();
}

void NodeEditDialog::initConnections()
{
    connect(_type, &QComboBox::currentIndexChanged, this, &NodeEditDialog::updateFixedCostsParam);
    connect(_cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
    connect(_okBtn, &QPushButton::clicked, this, &NodeEditDialog::updateNode);
}

void NodeEditDialog::updateFixedCostsParam()
{
    if (static_cast<NodeType>(_type->currentData().toInt()) == NodeType::CUSTOMER)
    {
        _layout->setRowVisible(_fixedCosts, false);
        _layout->setRowVisible(_fixedCostsLabel, false);
    }
    else
    {
        _layout->setRowVisible(_fixedCosts, true);
        _layout->setRowVisible(_fixedCostsLabel, true);
    }
}

void NodeEditDialog::updateNode()
{
    _node->setName(_name->text());
    _node->setNodeType(static_cast<NodeType>(_type->currentData().toInt()));
    _node->setPosX(_posX->value());
    _node->setPosY(-_posY->value());
    accept();
}
