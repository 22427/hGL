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
               glm\
               include
SOURCES += \
    hgles_context_state.cpp \
    hgles_window_glfw.cpp \
    hgles_input_glfw.cpp \
    hgles_window_pi.cpp \
    hgles_input_pi.cpp \
    hgles_input_interface.cpp \
    hgles_window_interface.cpp \
    hgles_glad.c

HEADERS += \
    hgles_context_state.h \
    hgles_dll.h \
    hgles_log.h \
    hgles_window.h \
    hgles_window_glfw.h \
    hgles_input_keys.h \
    hgles_input_keys_glfw.h \
    hgles_input_keys_pi.h \
    hgles_input_glfw.h \
    hgles_input_pi.h \
    hgles_window_interface.h \
    hgles_input_interface.h \
    hgles_input.h \
    hgles_window_pi.h \
    hgles_glad.h


# crude hack to determine wheather this is build on a RaspberryPI
exists(/opt/vc/lib/libmmal.so){
DEFINES += USE_PI
LIBS += -L/opt/vc/lib/ -ldl -lbcm_host -lvcos -lvchiq_arm -lGLESv2 -lEGL -lpthread -lrt
INCLUDEPATH += /opt/vc/include/
QMAKE_CXXFLAGS += -Wno-variadic-macros -std=c++11

}
else{
CONFIG( staticlib, staticlib| dll) {
LIBS+= -L./lib -lglfw3 -lX11 -lGL -lXrandr -lXi -lXinerama -lXcursor -ldl -lm -lpthread
}else{
LIBS += -L./lib -lglfw -ldl -lm -lpthread
QMAKE_RPATHDIR += \$\$ORIGIN
QMAKE_LFLAGS += '-Wl,-rpath,\'\$$ORIGIN\''
}
}








