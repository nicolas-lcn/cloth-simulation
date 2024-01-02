MOC_DIR = ./moc
OBJECTS_DIR = ./obj

INCLUDEPATH += $$PWD
INCLUDEPATH +=  external/Eigen

HEADERS       = glwidget.h \
                MassParticle.h \
                Spring.h \
                constraintgraph.h \
                massspringsolver.h \
                massspringsystem.h \
                mesh.h \
                simulationmanager.h \
                sphere.h \
                systembuilder.h \
                systemdrawer.h \
                window.h \
                mainwindow.h
SOURCES       = glwidget.cpp \
                MassParticle.cpp \
                Spring.cpp \
                constraintgraph.cpp \
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


