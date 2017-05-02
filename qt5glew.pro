#-------------------------------------------------
#
# Project created by QtCreator 2015-06-17T10:02:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt5glew
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    camera.cpp \
    mywindow.cpp \
    programmainwindow.cpp

HEADERS  += widget.h \
    camera.h \
    mywindow.h \
    programmainwindow.h

//macx: LIBS += -L$$PWD/../../Homebrew/Cellar/glew/1.12.0/lib/ -lGLEW.1.12.0
//LIBS += "F:/library/glew-2.0.0/glew-2.0.0/build/cmake/mingw_build/lib/libglew32.a"
//LIBS += -LF:/library/glut-3.7.6-bin_mingw/glut-3.7.6-bin/ -lglut32
//LIBS += -LF:/library/winglut/winlib/ -llibglut32win

LIBS += -LF:/library/glew-2.0.0/glew-2.0.0/build/cmake/mingw_build/lib/ -llibglew32
LIBS += -LF:/library/glew-2.0.0/glew-2.0.0/build/cmake/mingw_build/lib/ -llibfreeglut
//LIBS += "F:/library/glew-2.0.0/glew-2.0.0/build/cmake/mingw_build/lib/libglew32.a"
//LIBS += "F:/library/glew-2.0.0/glew-2.0.0/build/cmake/mingw_build/lib/libfreeglut.a"
LIBS += -lopengl32 -lglu32 -luser32


INCLUDEPATH += F:/library/glm-0.9.7.5/glm \
            F:/library/glew-2.0.0/glew-2.0.0/include \
            F:/library/freeglut-MinGW-3.0.0-1.mp/freeglut/include
DEPENDPATH += F:/library/glm-0.9.7.5/glm \
            F:/library/glew-2.0.0/glew-2.0.0/include \
            F:/library/freeglut-3.0.0/freeglut-3.0.0/build_mingw/bin \
            F:/library/glew-2.0.0/glew-2.0.0/build/cmake/mingw_build/bin

DISTFILES += \
    basictransformvshader.vert \
    basictransformfshader.frag \
    basiclambert.vert \
    basiclambert.frag
