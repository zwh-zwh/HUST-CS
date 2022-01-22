QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS \
    _GLIBCXX_USE_CXX11_ABI=0

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    QtTipsDlgView.cpp \
    QtWidgetsFL.cpp \
    QtWidgetsLoc.cpp \
    QtWidgetsQU.cpp \
    fun.cpp \
    main.cpp \
    map.cpp

HEADERS += \
    QtTipsDlgView.h \
    QtWidgetsFL.h \
    QtWidgetsLoc.h \
    QtWidgetsQU.h \
    fun.h \
    map.h

FORMS += \
    QtTipsDlgView.ui \
    QtWidgetsFL.ui \
    QtWidgetsLoc.ui \
    QtWidgetsQU.ui \
    map.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    map.qrc \
    map.qrc