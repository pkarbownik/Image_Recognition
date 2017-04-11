#ifndef GRADIENT_H
#define GRADIENT_H

#include <QMainWindow>

namespace Ui {
class Gradient;
}

class Gradient : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gradient(QWidget *parent = 0);
    ~Gradient();

private:
    Ui::Gradient *ui;
};

#endif // GRADIENT_H
