#pragma once

#ifdef HGLES_USE_GLFW
#include "hgles_window_glfw.h"
#elif defined(HGLES_USE_PI)
#include "hgles_window_pi.h"
#endif
