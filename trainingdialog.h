#ifndef TRAININGDIALOG_H
#define TRAININGDIALOG_H

#include <QWidget>
#include "ui_trainingdialog.h"

namespace Ui {
class TrainingDialog;
}

class TrainingDialog : public QWidget
{
    Q_OBJECT

public:
    explicit TrainingDialog(QWidget *parent = 0);
    ~TrainingDialog();

private:
    Ui::TrainingDialog *ui;
};

#endif // TRAININGDIALOG_H
