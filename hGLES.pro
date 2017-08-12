TARGET = hGLES

TEMPLATE = lib
#TEMPLATE = app

CONFIG   += dll
DEFINES  += HGLES_BUILDING_DLL
#CONFIG += staticlib
CONFIG += c++11
CONFIG -= qt

DESTDIR = lib
OBJECTS_DIR = obj

CONFIG(release, debug|release): DEFINES += NDEBUG

INCLUDEPATH += include/dep\
               include
SOURCES += \
    src/main.cpp \
    dep/glad/src/glad.c \
	src/hgles_context_state.cpp \
    src/hgles_window_glfw.cpp \
    src/hgles_input_glfw.cpp \
    src/hgles_window_pi.cpp \
    src/hgles_input_pi.cpp \
    src/hgles_input_interface.cpp \
    src/hgles_window_interface.cpp

HEADERS += \
    include/hgles_context_state.h \
    include/hgles_dll.h \
    include/hgles_log.h \
    include/hgles_window.h \
    include/hgles_window_glfw.h \
    include/hgles_input_keys.h \
    include/hgles_input_keys_glfw.h \
    include/hgles_input_keys_pi.h \
    include/hgles_input_glfw.h \
    include/hgles_input_pi.h \
    include/hgles_window_interface.h \
    include/hgles_input_interface.h \
    include/hgles_input.h \
    include/hgles_window_pi.h


# crude hack to determine wheather this is build on a RaspberryPI
exists(/opt/vc/lib/libmmal.so){
DEFINES += HGLES_USE_PI
LIBS += -L/opt/vc/lib/ -ldl -lbcm_host -lvcos -lvchiq_arm -lGLESv2 -lEGL -lpthread -lrt
INCLUDEPATH += /opt/vc/include/
QMAKE_CXXFLAGS += -Wno-variadic-macros -std=c++11

}
else{
DEFINES += HGLES_USE_GLFW
CONFIG( staticlib, staticlib| dll) {
LIBS+= -L./lib -lglfw3 -lX11 -lGL -lXrandr -lXi -lXinerama -lXcursor -ldl -lm -lpthread
}else{
LIBS += -L./lib -lglfw -ldl -lm -lpthread
}
}








