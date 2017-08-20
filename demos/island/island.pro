TEMPLATE = app
CONFIG += c++14
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += \
 $$PWD/../../imp/include \
 $$PWD/../ext/tinygltf

LIBS += \
 -lGLEW \
 -lglfw \
 -lGL \
 -L$$PWD/../../build/imp/ -limp

HEADERS = \
    src/SimpleMesh.hpp \
    src/GLTFLoader.hpp

SOURCES = \
    src/main.cpp \
    src/SimpleMesh.cpp \
    src/GLTFLoader.cpp

