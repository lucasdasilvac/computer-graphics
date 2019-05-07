TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += c++11

INCLUDEPATH += lib
INCLUDEPATH += gui_glut
INCLUDEPATH += user

DEFINES += USE_SDL
LIBS += -lglut -l3ds -lGLU -lGL -lm -lSDL -lSDL_image

HEADERS += \
    Ball.h \
    Car.h \
    Ground.h \
    Object.h \
    Racket.h \
    Stand.h \
    TennisCourt.h \
    Tree.h \
    lib/Camera.h \
    lib/CameraDistante.h \
    lib/CameraJogo.h \
    lib/Desenha.h \
    lib/Vetor3D.h \
    lib/model3ds.h \
    lib/stanfordbunny.h

SOURCES += \
    Ball.cpp \
    Car.cpp \
    Ground.cpp \
    Object.cpp \
    Racket.cpp \
    Stand.cpp \
    TennisCourt.cpp \
    Tree.cpp \
    lib/Camera.cpp \
    lib/CameraDistante.cpp \
    lib/CameraJogo.cpp \
    lib/Desenha.cpp \
    lib/Vetor3D.cpp \
    lib/model3ds.cpp \
    main.cpp

