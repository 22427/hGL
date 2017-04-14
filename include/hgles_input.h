#pragma once
#include "hgles_input_interface.h"
#include "hgles_input_keys.h"

#ifdef HGLES_USE_GLFW
#include "hgles_input_glfw.h"
#elif defined(HGLES_USE_PI)
#include "hgles_input_pi.h"
#endif
