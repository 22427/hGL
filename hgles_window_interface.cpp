#ifndef NDEBUG
#include "hgles_window_interface.h"


namespace hgles
{

WindowInterface::~WindowInterface()
{

}

WindowListener::~WindowListener()
{

}

void WindowListener::size_changed(const int /*w*/, const int /*h*/ )
{

}

void WindowListener::position_changed(const int /*x*/, const int /*y*/)
{

}

}
#endif
