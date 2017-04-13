#ifdef HGLES_USE_PI
#include <hgles_window_pi.h>


namespace hgles
{


bool create_window(EGL_DISPMANX_WINDOW_T& nativewindow,
		unsigned int width,
		unsigned int height,
		unsigned int x,
		unsigned int y)
{
	bcm_host_init();
	int32_t success = 0;


	DISPMANX_ELEMENT_HANDLE_T dispman_element;
	DISPMANX_DISPLAY_HANDLE_T dispman_display;
	DISPMANX_UPDATE_HANDLE_T dispman_update;
	VC_RECT_T dst_rect;
	VC_RECT_T src_rect;


	unsigned int display_width;
	unsigned int display_height;

	success = graphics_get_display_size(
			0 /* LCD */,
			&display_width,
			&display_height);

	if ( success < 0 )
{
		return false;
	}

	display_width = width;
	display_height = height;

	dst_rect.x = x;
	dst_rect.y = y;
	dst_rect.width = display_width;
	dst_rect.height = display_height;

	src_rect.x = x;
	src_rect.y = y;
	src_rect.width = display_width << 16;
	src_rect.height = display_height << 16;

	dispman_display = vc_dispmanx_display_open( 0 /* LCD */);
	dispman_update = vc_dispmanx_update_start( 0 );

	dispman_element = vc_dispmanx_element_add(
			dispman_update,
			dispman_display,
			0/*layer*/,
			&dst_rect,
			0/*src*/,
			&src_rect,
			DISPMANX_PROTECTION_NONE,
			0 /*alpha*/,
			0/*clamp*/,
			(DISPMANX_TRANSFORM_T) 0/*transform*/);

	nativewindow.element = dispman_element;
	nativewindow.width = display_width;
	nativewindow.height = display_height;
	vc_dispmanx_update_submit_sync( dispman_update );

	return true;

}



bool pt::GLES2Context::create_egl_context(
		EGLNativeWindowType hWnd,
		EGLDisplay *eglDisplay,
		EGLContext *eglContext,
		EGLSurface *eglSurface,
		EGLint attribList[],
		EGLContext shared,
		bool pbuffered,
		int width,
		int height)
{
	EGLint numConfigs;
	EGLint majorVersion;
	EGLint minorVersion;
	EGLDisplay display;
	EGLContext context;
	EGLSurface surface;
	EGLConfig config;
	EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };


	// Get Display
	display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	if ( display  == EGL_NO_DISPLAY )
	{
		ERROR("EGL: get display failed");
		return false;
	}

	// Initialize EGL
	if ( !eglInitialize(display, &majorVersion, &minorVersion) )
	{
		ERROR("EGL: initialization failed: %#x",eglGetError());
		return false;
	}

	// Get configs
	if ( !eglGetConfigs(display, NULL, 0, &numConfigs) )
	{
		ERROR("EGL: get config failed");
		return false;
	}

	// Choose config
	if ( !eglChooseConfig(display, attribList, &config, 1, &numConfigs) )
	{
		ERROR("EGL: choose config failed!");
		return false;
	}
	// Create a surface
	surface = eglCreateWindowSurface(
			display,
			config,
			(EGLNativeWindowType)hWnd,
			NULL);

	if ( surface == EGL_NO_SURFACE )
	{
		ERROR("EGL: surface creation failed!");
		return false;
	}

	// Create a GL context
	context = eglCreateContext(display, config, shared, contextAttribs );
	if ( context == EGL_NO_CONTEXT )
	{
		ERROR("EGL: context creation failed!");
		return false;
	}

	// Make the context current
	if ( !eglMakeCurrent(display, surface, surface, context) )
	{
		ERROR("EGL: make current failed!");
		return false;
	}

	*eglDisplay = display;
	*eglSurface = surface;
	*eglContext = context;
	return true;
}





Window::Window(const uint32_t w, const uint32_t h, const uint32_t x, const uint32_t y)
{
	m_should_close = false;
	EGLint attribList[] =
	{
		EGL_RED_SIZE,      8,
		EGL_GREEN_SIZE,    8,
		EGL_BLUE_SIZE,     8,
		EGL_ALPHA_SIZE,    8,
		EGL_DEPTH_SIZE,   16,
		EGL_STENCIL_SIZE,  0,
		EGL_SAMPLE_BUFFERS,1,
		EGL_NONE
	};


	if(!create_window(&m_win_handle,width,height,x,y))
		ERROR("failed creating window!");


	if(!create_egl_context(reinterpret_cast<EGLNativeWindowType>(m_win_handle),
				&m_display,
				&m_context,
				&m_surface,
				attribList,
				EGL_NO_CONTEXT,
				false,width,height))
		ERROR("failed creating context!");

}













}





#endif
