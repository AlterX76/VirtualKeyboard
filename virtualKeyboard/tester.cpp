
#include "tester.h"
#include "ui_tester.h"
#include <QLabel>
#include <QDesktopWidget>
#include <QTranslator>
#include <QDebug>
#include "form.h"

Tester::Tester(QWidget *parent)
    : QWidget(parent), ui(new Ui::Tester), myKeyboard(NULL)
{
    QListWidgetItem     defaultLanguage("English");

    ui->setupUi(this);    
    myTranslator = new QTranslator(this);
    this->myKeyboard = new widgetKeyBoard(false);
    this->myKeyboard->setZoomFacility(true);
    this->myKeyboard->enableSwitchingEcho(true); // enable possibility to change echo through keyboard
    this->myKeyboard->createKeyboard(); // only create keyboard
    ui->verticalLayout->addWidget(new QLabel(tr("Focus that below without virtual keyboard TAB:")));
    ui->verticalLayout->addWidget(new exampleMyFocus(this->myKeyboard)); // example how-to voluntary focus (hand-focus or mouse-focus)
    ui->verticalLayout->addWidget(new exampleMyFocus(this->myKeyboard)); // example how-to voluntary focus (hand-focus or mouse-focus) - second example
    ui->listWidget->addItem("Italian");
    ui->listWidget->addItem("German");
    ui->listWidget->addItem("French");
    ui->listWidget->addItem(defaultLanguage.text());
    ui->listWidget->addItem("Russian");
    ui->listWidget->addItem("Arabic");
    ui->listWidget->setCurrentRow(3);
    on_listWidget_itemClicked(&defaultLanguage);
    move((QApplication::desktop()->screenGeometry().width() - this->width()) / 2, (QApplication::desktop()->screenGeometry().height() - this->height()) / 2);
}

Tester::~Tester()
{
    delete ui;    
    delete (this->myKeyboard);
}

widgetKeyBoard *Tester::getKeyboard()
{
    return (this->myKeyboard);
}

void Tester::on_pushButton_clicked()
{
    myKeyboard->show(this); // once created keyboard object, use this method to switch between windows
#if QT_VERSION >= 0x050000
    this->myKeyboard->move(this->x(), this->y() + this->myKeyboard->height()); // to move keyboard	
#else
	 // move to center of screen, just below QLineEdit widget
	 this->myKeyboard->move((QApplication::desktop()->screenGeometry().width() - myKeyboard->width())/2, this->y() + this->height() + 33);	// AW - 33 = height of window title bar + height of window frame
#endif
}

void Tester::on_pushButton_2_clicked()
{
    myKeyboard->hide(true);
}


void Tester::closeEvent(QCloseEvent * event)
{
    myKeyboard->hide(true);
    QWidget::closeEvent(event);
}

void Tester::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
        ui->retranslateUi(this);
    else
        QWidget::changeEvent(event);
}


void Tester::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QLocale             *local;
    QString             newLang = item->text();

    if (newLang == "French")
        local = new QLocale(QLocale::French);
    else if (newLang == "Russian")
        local = new QLocale(QLocale::Russian);
    else if (newLang == "German")
        local = new QLocale(QLocale::German);
    else if (newLang == "Italian")
        local = new QLocale(QLocale::Italian);
    else if (newLang == "English")
        local = new QLocale(QLocale::English);
    else if (newLang == "Arabic")
        local = new QLocale(QLocale::Arabic);
    else
        local = new QLocale();
    if (myTranslator->load(*local, QLatin1String("virtualBoard"), QLatin1String("_"), QLatin1String(":/")))
        qApp->installTranslator(myTranslator);
    else
        qDebug("Failed to load a translation for QT in your local language");
}

void Tester::on_pushButton_3_clicked()
{
    Form *emb = new Form();

    emb->show();
}
