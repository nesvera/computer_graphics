QT += widgets

SOURCES += main.cpp \
           mainwindow.cpp \
           glCanvas2d.cpp \
    myCanvas.cpp \
    DrawComponent.cpp \
    Point.cpp \
    ControlPoint.cpp \
    Line.cpp \
    Rect.cpp \
    Circ.cpp \
    Belzier.cpp

HEADERS += \
           mainwindow.h \
    glCanvas2d.h \
    DrawComponent.h \
    Point.h \
    ControlPoint.h \
    control.h \
    Line.h \
    Rect.h \
    Circ.h \
    Belzier.h

target.path = $$[QT_INSTALL_EXAMPLES]/opengl/qopenglwidget

INSTALLS += target
