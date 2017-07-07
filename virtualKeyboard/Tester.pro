# -------------------------------------------------
# Project created by QtCreator 2009-06-23T15:25:37
# -------------------------------------------------
TARGET = Tester
TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets multimedia
}

SOURCES += main.cpp \
    tester.cpp \
    keyboard/QKeyPushButton.cpp \
    keyboard/widgetKeyBoard.cpp \
    examplemyfocus.cpp \
    form.cpp

HEADERS += tester.h \
    keyboard/QKeyPushButton.h \
    keyboard/widgetKeyBoard.h \
    examplemyfocus.h \
    form.h

FORMS += tester.ui \
    form.ui

TRANSLATIONS += virtualBoard_it.ts \
    virtualBoard_ru.ts \
    virtualBoard_en.ts \
    virtualBoard_de.ts \
    virtualBoard_fr.ts

RESOURCES += virtualboard.qrc \
    languages.qrc
