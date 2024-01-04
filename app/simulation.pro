MOC_DIR = ./moc
OBJECTS_DIR = ./obj

INCLUDEPATH += $$PWD
INCLUDEPATH +=  external/Eigen

HEADERS       = glwidget.h \
                constraints.h \
                massspringsolver.h \
                massspringsystem.h \
                simulationmanager.h \
                sphere.h \
                systembuilder.h \
                systemdrawer.h \
                window.h \
                mainwindow.h
SOURCES       = glwidget.cpp \
                constraints.cpp \
                main.cpp \
                massspringsolver.cpp \
                massspringsystem.cpp \
                simulationmanager.cpp \
                sphere.cpp \
                systembuilder.cpp \
                systemdrawer.cpp \
                window.cpp \
                mainwindow.cpp

RESOURCES += \
    shaders.qrc

QT           += widgets openglwidgets gui


