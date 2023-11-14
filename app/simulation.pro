MOC_DIR = ./moc
OBJECTS_DIR = ./obj

INCLUDEPATH += $$PWD
INCLUDEPATH +=  external/glm-0.9.7.1/

HEADERS       = glwidget.h \
                MassParticle.h \
                Sphere.h \
                Spring.h \
                window.h \
                mainwindow.h
SOURCES       = glwidget.cpp \
                main.cpp \
                window.cpp \
                mainwindow.cpp

RESOURCES += \
    shaders.qrc

QT           += widgets openglwidgets gui


