hGLES - Handy OpenGL|ES
===============================
This is a small wrapper representing an OpenGL|ES 2.0 + Pi Context and its Objects.

Context Version and Extensions
-------------------------------
In the implementation it is assuomed that OpenGL|ES 2.0 is supported as well as the following extensions.
  - GL_OES_compressed_ETC1_RGB8_texture
  - GL_OES_compressed_paletted_texture
  - GL_OES_texture_npot
  - GL_OES_depth24
  - GL_OES_vertex_half_float
  - GL_OES_EGL_image
  - GL_OES_EGL_image_external
  - GL_EXT_discard_framebuffer
  - GL_OES_rgb8_rgba8
  - GL_OES_depth32
  - GL_OES_mapbuffer
  - GL_EXT_texture_format_BGRA8888
  - GL_APPLE_rgb_422
  - GL_EXT_debug_marker
  
Those are the extensions supported by the RaspberryPi's VideoCore IV.

VAOs
----------------------------
Vertex Array Objects are supported eighter by the GL_OES_vertex_array_object extension or by emulating the same effect.

Dependencies
----------------------------
hGL uses
- **GLFW3** as a default for context creation. 
- **GLM** is used to represent matrices and vectors. 
- **GLAD** is used for the extension loading.
