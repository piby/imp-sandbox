#-------------------------------------------------
#
# Project created by QtCreator 2017-08-04T14:18:39
#
#-------------------------------------------------

QT -= core gui

TARGET = imp
TEMPLATE = lib

DEFINES += IMP_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

LIBS += -lGLEW
LIBS += -lGL

INCLUDEPATH += \
 $$PWD/include

HEADERS += \
 include/Utils.hpp \
 include/Frustum.hpp \
 include/Texture.hpp \
 include/Texture.inl \
 include/Shader.hpp \
 include/ShaderProgram.hpp \
 include/FrameBuffer.hpp \
 include/VertexBuffer.hpp \
 include/VertexBuffer.inl \
 include/VertexArray.hpp \
 include/VertexArray.inl \
 include/SimpleCamera.hpp \
 include/SimpleCamera.inl

SOURCES += \
 src/Utils.cpp \
 src/Frustum.cpp \
 src/Texture.cpp \
 src/Shader.cpp \
 src/ShaderProgram.cpp \
 src/FrameBuffer.cpp \
 src/SimpleCamera.cpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}
