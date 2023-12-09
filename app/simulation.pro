MOC_DIR = ./moc
OBJECTS_DIR = ./obj

INCLUDEPATH += $$PWD
INCLUDEPATH +=  external/glm-0.9.7.1/

HEADERS       = glwidget.h \
                MassParticle.h \
                Spring.h \
                massspringsystem.h \
                mesh.h \
                simulationmanager.h \
                sphere.h \
                window.h \
                mainwindow.h
SOURCES       = glwidget.cpp \
                MassParticle.cpp \
                Spring.cpp \
                main.cpp \
                massspringsystem.cpp \
                simulationmanager.cpp \
                sphere.cpp \
                window.cpp \
                mainwindow.cpp

RESOURCES += \
    shaders.qrc

QT           += widgets openglwidgets gui


