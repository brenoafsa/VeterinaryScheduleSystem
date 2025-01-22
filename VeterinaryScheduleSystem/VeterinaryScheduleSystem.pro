QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    agendamento.cpp \
    animal.cpp \
    cadastroPet.cpp \
    casdastrocliente.cpp \
    consulta.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    remarcacao.cpp \
    sistema.cpp \
    tutor.cpp \
    veterinario.cpp

HEADERS += \
    agendamento.h \
    animal.h \
    cadastroPet.h \
    casdastrocliente.h \
    consulta.h \
    database.h \
    mainwindow.h \
    menu.h \
    remarcacao.h \
    sistema.h \
    tutor.h \
    veterinario.h

FORMS += \
    agendamento.ui \
    cadastroPet.ui \
    casdastrocliente.ui \
    mainwindow.ui \
    menu.ui \
    remarcacao.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
