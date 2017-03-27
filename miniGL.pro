TEMPLATE = lib

TARGET = miniGL
CONFIG   += dll
CONFIG   -= app_bundle


INCLUDEPATH += include/dep\
               include
SOURCES += \ 
    src/main.cpp \
    dep/glad/src/glad.c \
    src/mgl_glfw_window.cpp \
    src/mgl_buffer.cpp \
    src/mgl_texture.cpp \
    src/mgl_vertex_array.cpp \
    src/mgl_shader.cpp \
    src/mgl_context_state.cpp

CONFIG += c++11

DESTDIR = bin
OBJECTS_DIR = obj

LIBS += -L./dep/lib -lglfw -lstb -ldl -lm -lpthread -lX11 -lGL -lXrandr -lXi -lXinerama -lXcursor

HEADERS += \
    include/mgl_window.h \
    include/mgl_glfw_window.h \
    include/mgl_buffer.h \
    include/mgl_texture.h \
    include/mgl_vertex_array.h \
    include/mgl_shader.h \
    include/mgl_object.h \
    include/mgl_log.h \
    include/mgl_context_state.h \
    include/mgl_dll.h
