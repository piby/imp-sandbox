#-------------------------------------------------
#
# Project created by QtCreator 2017-08-04T14:18:39
#
#-------------------------------------------------

QT -= core gui

TARGET = imp
TEMPLATE = lib
CONFIG += c++14
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
 include/BufferFlags.hpp \
 include/CubemapTexture.hpp \
 include/CubemapTexture.inl \
 include/FrameBuffer.hpp \
 include/Frustum.hpp \
 include/MeshData.hpp \
 include/MultiSampleTexture.hpp \
 include/MultiSampleTexture.inl \
 include/MultiSampleRenderBuffer.hpp \
 include/RenderBuffer.hpp \
 include/Sampler.hpp \
 include/Sampler.inl \
 include/Shader.hpp \
 include/ShaderProgram.hpp \
 include/SimpleCamera.inl \
 include/SimpleCamera.hpp \
 include/Texture.hpp \
 include/Texture.inl \
 include/Utils.hpp \
 include/UniformBuffer.hpp \
 include/UniformBuffer.inl \
 include/VertexArray.hpp \
 include/VertexArray.inl \
 include/VertexBuffer.hpp \
 include/VertexBuffer.inl \
    include/SamplerFlags.hpp

SOURCES += \
 src/CubemapTexture.cpp \
 src/Utils.cpp \
 src/FrameBuffer.cpp \
 src/Frustum.cpp \
 src/MultiSampleTexture.cpp \
 src/MultiSampleRenderBuffer.cpp \
 src/Texture.cpp \
 src/Shader.cpp \
 src/ShaderProgram.cpp \
 src/SimpleCamera.cpp \
 src/RenderBuffer.cpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}
