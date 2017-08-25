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
    src/GLTFLoader.hpp \
    src/MeshData.hpp \
    src/StaticMesh.hpp

SOURCES = \
    src/main.cpp \
    src/GLTFLoader.cpp \
    src/StaticMesh.cpp

