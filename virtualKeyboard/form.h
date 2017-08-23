#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "keyboard/widgetKeyBoard.h"


namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Form *ui;
    widgetKeyBoard  *_keyboard;
};

#endif // FORM_H
