#include "form.h"
#include "ui_form.h"
#include "examplemyfocus.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    _keyboard = new widgetKeyBoard(false, this, false, ui->frame);
    _keyboard->setZoomFacility(true);
    _keyboard->enableSwitchingEcho(true);
    _keyboard->createKeyboard();
    _keyboard->hide(true);
    exampleMyFocus *extra = new exampleMyFocus(this, _keyboard);
    extra->move(100, 30);
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()
{
    _keyboard->show(this);
}

void Form::on_pushButton_2_clicked()
{
    _keyboard->hide(true);
}
