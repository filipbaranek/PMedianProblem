#ifndef HELPVIEW_H
#define HELPVIEW_H

#include <QDialog>

class QTextEdit;
class QPushButton;

class HelpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HelpDialog(QWidget* parent = nullptr);

private:
    void initUI();

    void initConnections();

private:
    QTextEdit*   _info;
    QPushButton* _okButton;
};

#endif // HELPVIEW_H
