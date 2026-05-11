#include "helpview.h"
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

HelpDialog::HelpDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Help");

    initUI();
    initConnections();
}

void HelpDialog::initUI()
{
    setMinimumSize(QSize{650, 550});

    QVBoxLayout* mainLayout   = new QVBoxLayout();
    QHBoxLayout* buttonLayout = new QHBoxLayout();

    _info     = new QTextEdit(this);
    _okButton = new QPushButton("Got it", this);

    _info->setReadOnly(true);

    QString html;
    html += "<div style='text-align:center; font-family: sans-serif; line-height: 1.6;'>";
    html += "<h1>Graph Legend & Controls</h1>";
    html += "<hr>";
    html += "<h3>Node Identifiers</h3>";
    html += "<p><b style='color: blue;'>Blue Node</b> &mdash; Represents a <b>Customer</b> requiring service.</p>";
    html += "<p><b style='color: magenta;'>Magenta Node</b> &mdash; Represents a "
            "<b>Potential Storage</b> facility (not yet used).</p>";
    html += "<p><b style='color: green;'>Green Node</b> &mdash; Represents a "
            "<b>Selected Storage</b> facility chosen by the P-Median algorithm.</p>";
    html += "<br>";
    html += "<h3>Connections</h3>";
    html += "<p><b style='color: #00BFFF;'>Light Blue Edge</b> &mdash; A standard "
            "<b>Route</b> connecting two locations.</p>";
    html += "<p><b style='color: #FFD700; background-color: #333;'>Yellow Edge</b> &mdash; "
            "A <b>Solution Assignment</b> indicating which storage serves which customer.</p>";
    html += "<br>";
    html += "<hr>";
    html += "<h3>User Controls</h3>";
    html += "<p><b>Workspace Interaction:</b> Right-click on the empty grid space to open the context menu. "
            "From there, you can add new nodes, create edges, or clear the entire grid/solution.</p>";
    html += "<p><b>Item Modification:</b> Every item on the screen is <b>modifiable</b>. "
            "Simply right-click on any node or edge to edit its properties or remove it.</p>";
    html += "</div>";

    _info->setHtml(html);

    mainLayout->addWidget(_info);
    mainLayout->addSpacing(10);

    buttonLayout->addStretch();
    buttonLayout->addWidget(_okButton);
    buttonLayout->addStretch();

    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
}

void HelpDialog::initConnections()
{
    connect(_okButton, &QPushButton::clicked, this, &QDialog::accept);
}
