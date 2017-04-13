TEMPLATE = lib
#TEMPLATE = app
TARGET = hGLES
CONFIG   += dll
DEFINES  += MGL_BUILDING_DLL
CONFIG   -= app_bundle


INCLUDEPATH += include/dep\			   
               include
SOURCES += \ 
    src/main.cpp \
    dep/glad/src/glad.c \
    src/hgles_buffer.cpp \
    src/hgles_context_state.cpp \
    src/hgles_texture.cpp \
    src/hgles_vertex_array.cpp \
    src/hgles_shader.cpp \
    src/hgles_window_glfw.cpp \
    src/hgles_input_glfw.cpp \
    src/hgles_window_pi.cpp

CONFIG += c++11

exists(/opt/vc/lib/libmmal.so){

DEFINES += HGLES_USE_PI
-L/opt/vc/lib/ -lbcm_host -lvcos -lvchiq_arm -lGLESv2 -lEGL -lpthread -lrt
}
else{
DEFINES += HGLES_USE_GLFW
LIBS += -L./dep/lib -lglfw -ldl -lm -lpthread -lX11 -lGL -lXrandr -lXi -lXinerama -lXcursor
}


DESTDIR = lib
OBJECTS_DIR = obj


HEADERS += \
    include/hgles_buffer.h \
    include/hgles_context_state.h \
    include/hgles_dll.h \
    include/hgles_log.h \
    include/hgles_object.h \
    include/hgles_shader.h \
    include/hgles_vertex_array.h \
    include/hgles_window.h \
    include/hgles_texture.h \
    include/hgles_window_glfw.h \
    include/hgles_input_keys.h \
    include/hgles_input_keys_glfw.h \
    include/hgles_input_glfw.h \
    include/hgles_window_interface.h \
    include/hgles_input_interface.h \
    include/hgles_input.h \
    include/hgles_window_pi.h
