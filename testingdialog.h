#ifndef TESTINGDIALOG_H
#define TESTINGDIALOG_H

#include <QWidget>
#include "ui_testingdialog.h"

namespace Ui {
class TestingDialog;
}

class TestingDialog : public QWidget
{
    Q_OBJECT

public:
    explicit TestingDialog(QWidget *parent = 0);
    ~TestingDialog();

private:
    Ui::TestingDialog *ui;
};

#endif // TESTINGDIALOG_H
