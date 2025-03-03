QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    agendamento.cpp \
    cadastroalterar.cpp \
    cadastrocliente.cpp \
    cadastropesquisar.cpp \
    cadastropet.cpp \
    cancelarconsulta.cpp \
    consultasdodia.cpp \
    database.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    petalterar.cpp \
    remarcacao.cpp

HEADERS += \
    agendamento.h \
    cadastroalterar.h \
    cadastrocliente.h \
    cadastropesquisar.h \
    cadastropet.h \
    cancelarconsulta.h \
    consultasdodia.h \
    database.h \
    mainwindow.h \
    menu.h \
    petalterar.h \
    remarcacao.h

FORMS += \
    agendamento.ui \
    cadastroalterar.ui \
    cadastrocliente.ui \
    cadastropesquisar.ui \
    cadastropet.ui \
    cancelarconsulta.ui \
    consultasdodia.ui \
    mainwindow.ui \
    menu.ui \
    petalterar.ui \
    remarcacao.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc
