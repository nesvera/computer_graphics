QT += widgets

SOURCES += main.cpp \
           mainwindow.cpp \
           glCanvas2d.cpp \
    myCanvas.cpp \
    DrawComponent.cpp \
    Pipeline.cpp \
    Motor.cpp \
    Virabrequim.cpp \
    Camisa.cpp \
    bloco.cpp \
    biela.cpp \
    pistao.cpp

HEADERS += \
           mainwindow.h \
    glCanvas2d.h \
    DrawComponent.h \
    Vector3.h \
    Matrix4.h \
    Pipeline.h \
    Motor.h \
    Virabrequim.h \
    Edge.h \
    Camisa.h \
    circulo.h \
    cilindro.h \
    cubo.h \
    bloco.h \
    biela.h \
    pistao.h

target.path = $$[QT_INSTALL_EXAMPLES]/opengl/qopenglwidget

INSTALLS += target
