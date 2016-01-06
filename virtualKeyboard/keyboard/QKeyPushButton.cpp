/***************************************************************************
 *   Copyright (C) 2008/2016 by Giovanni Romano                            *
 *   giovanni.romano.76@gmail.com                                          *
 *                                                                         *
 *   This program may be distributed under the terms of the Q Public       *
 *   License as defined by Trolltech AS of Norway and appearing in the     *
 *   file LICENSE.QPL included in the packaging of this file.              *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 ***************************************************************************/


#include "QKeyPushButton.h"
#include "widgetKeyBoard.h"
#include <QKeyEvent>
#include <QCoreApplication>
#include <QLabel>
#include <QDebug>
#include <QApplication>


QKeyPushButton::QKeyPushButton(QString notTranslatedText, QWidget *parent) : QPushButton(parent), m_parent(parent), m_notTranslatedText(notTranslatedText)
{
	this->setStyleSheet(QString(DEFAULT_STYLE_BUTTON) + QString(DEFAULT_BACKGROUND_BUTTON));
	connect(this, SIGNAL(pressedKey(bool)), SLOT(getKeyPress(bool)));
        if ((static_cast<widgetKeyBoard *> (parent))->isEmbeddedKeyboard() == true)
            this->style_embedded = QString(EMBEDDED_KEYBOARD);
}

void QKeyPushButton::getKeyPress(bool capsStatus)
{
	int 		keyCode = 0;
	QKeyEvent	*key = NULL;
	QString		text = this->text();
	//
	// per tutti i car speciali tranne il CAPS (RETURN, ALT, SHIFT, ecc...) inoltra al componente widgetKeyBoard:
        if (NO_SPECIAL_KEY(text) == false && (IS_BACK(text) == true || IS_BACK_EMB(text) == true || IS_TAB(text) == true || IS_RETURN(text) == true || IS_CTRL_LEFT(text) == true ||
                        IS_ALT(text) == true || IS_CANC(text) == true || IS_CUT_LEFT(text) == true || IS_PASSWORD(text) || IS_PASSWORD_EMB(text) || IS_PASTE(text) || IS_COPY(text)))
		key = new QKeyEvent(QEvent::KeyPress, keyCode, Qt::NoModifier, text);
	else { // trattasi di caratteri stampabili
        keyCode = text.toUtf8()[0]; // prende il valore numerico (sempre maiuscolo)
        if (capsStatus == false) { // se deve prendere minuscolo, controlla se il carattere è alfabetico
            // AW - Alain Weiler <sigmastgt@web.de>
            text = text.toLower();
            key = new QKeyEvent(QEvent::KeyPress, keyCode, Qt::NoModifier, text);
		}
		else
            key = new QKeyEvent(QEvent::KeyPress, keyCode, Qt::ShiftModifier, text);
	}
    ((widgetKeyBoard *) this->m_parent)->receiptChildKey(key, NULL);
	QCoreApplication::processEvents();
}


void QKeyPushButton::mousePressEvent(QMouseEvent *)
{
    static bool             m_capsActive = true;
    widgetKeyBoard          *tmpKeyBoard = (widgetKeyBoard *)this->m_parent;
    QString                 text = this->text();
    QString                 defaultStyleButton = QString(DEFAULT_STYLE_BUTTON);
    QString                 changedColorButton = QString(CHANGED_BACKGROUND_BUTTON);
	//
	// se si tratta del maiuscolo:
    if (IS_CAPS(text) == true) {
        if (m_capsActive == false)
			m_capsActive = true;
		else {
            changedColorButton = QString(DEFAULT_BACKGROUND_BUTTON);
			m_capsActive = false;
		}
        this->setStyleSheet(defaultStyleButton + changedColorButton + this->style_embedded);
		this->repaint();
		QCoreApplication::processEvents();
	}
    else if (tmpKeyBoard->isEnabledSwitchingEcho() == true && (IS_PASSWORD(text) == true || IS_PASSWORD_EMB(text) == true))
        tmpKeyBoard->switchKeyEchoMode(tmpKeyBoard->currentTextBox());
	else {
        this->setStyleSheet(defaultStyleButton + changedColorButton + this->style_embedded);
		this->repaint();
		QCoreApplication::processEvents();
		emit pressedKey(m_capsActive);
	}
    this->m_oldYKey = 0;
    if (tmpKeyBoard->isEmbeddedKeyboard() == true && tmpKeyBoard->isZoomFacilityEnable() && NO_SPECIAL_KEY(text) && text.trimmed().length() != 0) {
        tmpKeyBoard->setCursor(Qt::BlankCursor);
        tmpKeyBoard->zoomedWidget()->setGeometry(this->x() - 5, this->y() - 20, tmpKeyBoard->zoomedWidget()->width(), tmpKeyBoard->zoomedWidget()->height());
        tmpKeyBoard->zoomedWidget()->setText(this->text());
        tmpKeyBoard->zoomedWidget()->show();
        QCoreApplication::processEvents();
    }
}

void QKeyPushButton::mouseReleaseEvent(QMouseEvent * /* event */)
{
    widgetKeyBoard  *tmpKeyBoard = (widgetKeyBoard *) this->m_parent;
    bool            pressedEcho = IS_PASSWORD(this->text()) == true || IS_PASSWORD_EMB(this->text()) == true;

    if (IS_CAPS(this->text()) == false && pressedEcho == false) {
        if (tmpKeyBoard->isEmbeddedKeyboard() == true && tmpKeyBoard->isZoomFacilityEnable() && NO_SPECIAL_KEY(this->text())  && this->text().trimmed().length() != 0) {
            tmpKeyBoard->setCursor(Qt::ArrowCursor);
            tmpKeyBoard->zoomedWidget()->hide();
            QCoreApplication::processEvents();
        }        
        this->setStyleSheet(QString(DEFAULT_STYLE_BUTTON) + QString(DEFAULT_BACKGROUND_BUTTON) + this->style_embedded);
    }
    else if (pressedEcho == true && tmpKeyBoard->isEnabledSwitchingEcho() == false && tmpKeyBoard->currentTextBox()->echoMode() == QLineEdit::Normal)
        this->setStyleSheet(QString(DEFAULT_STYLE_BUTTON) + QString(DEFAULT_BACKGROUND_BUTTON) + this->style_embedded);
    tmpKeyBoard->soundClick();
}

void QKeyPushButton::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
        this->setText(QApplication::translate("widgetKeyBoard", m_notTranslatedText.toUtf8().constData()));
    else
        QWidget::changeEvent(event);
}

