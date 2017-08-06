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
 src/SimpleModel.hpp

SOURCES = \
 src/main.cpp \
 src/SimpleModel.cpp
