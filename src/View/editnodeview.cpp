#include "editnodeview.h"
#include "Workspace/NodeView.h"
#include "../Helpers/NodeType.h"
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QLabel>

NodeEditDialog::NodeEditDialog(NodeView* node, QWidget* parent)
    : QDialog(parent), _node(node)
{
    setWindowTitle("Edit node");

    initUI();
    loadFromEdge();
    initConnections();
}

void NodeEditDialog::initUI()
{
    auto* layout = new QFormLayout(this);

    _name               = new QLineEdit(this);
    _type               = new QComboBox(this);
    _posX               = new QDoubleSpinBox(this);
    _posY               = new QDoubleSpinBox(this);
    _variableParam      = new QDoubleSpinBox(this);
    _variableParamLabel = new QLabel(this);

    layout->addRow("Name:", _name);
    layout->addRow("Type:", _type);
    layout->addRow("Pos X:", _posX);
    layout->addRow("Pos Y:", _posY);
    layout->addRow(_variableParamLabel, _variableParam);

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

    _posX->setMinimum(std::numeric_limits<double>::lowest());
    _posX->setMaximum(std::numeric_limits<double>::max());
    _posX->setValue(_node->posX());

    _posY->setMinimum(std::numeric_limits<double>::lowest());
    _posY->setMaximum(std::numeric_limits<double>::max());
    _posY->setValue(-_node->posY());

    _variableParam->setValue(_node->variableParam());
    updateVariableParams();
}

void NodeEditDialog::initConnections()
{
    connect(_type, &QComboBox::currentIndexChanged, this, &NodeEditDialog::updateVariableParams);
    connect(_cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
    connect(_okBtn, &QPushButton::clicked, this, &NodeEditDialog::updateNode);
}

void NodeEditDialog::updateVariableParams()
{
    if (static_cast<NodeType>(_type->currentData().toInt()) == NodeType::CUSTOMER)
    {
        _variableParamLabel->setText("Demand");
    }
    else
    {
        _variableParamLabel->setText("Capacity");
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
