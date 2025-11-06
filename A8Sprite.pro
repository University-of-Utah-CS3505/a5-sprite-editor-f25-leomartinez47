QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += include

SOURCES += \
    src/eraser.cpp \
    src/pencil.cpp \
    src/project.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/projectview.cpp \
    src/sprite.cpp \
    src/canvaspane.cpp \
    src/frameselectionpane.cpp \
    src/previewpane.cpp \
    src/tool.cpp \
    src/toolpane.cpp

HEADERS += \
    include/Tool.h \
    include/eraser.h \
    include/mainwindow.h \
    include/pencil.h \
    include/sprite.h \
    include/projectview.h \
    include/canvaspane.h \
    include/frameselectionpane.h \
    include/previewpane.h \
    include/tool.h \
    include/toolpane.h \
    include/project.h

FORMS += \
    ui/canvaspane.ui \
    ui/frameselectionpane.ui \
    ui/previewpane.ui \
    ui/projectview.ui \
    ui/toolpane.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
