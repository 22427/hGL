/*

    OpenGL ES loader generated by glad 0.1.13a0 on Wed Apr 12 15:11:57 2017.

    Language/Generator: C/C++
    Specification: gl
    APIs: gles2=2.0
    Profile: compatibility
    Extensions:
        GL_APPLE_rgb_422,
        GL_EXT_debug_marker,
        GL_EXT_discard_framebuffer,
        GL_EXT_texture_format_BGRA8888,
        GL_OES_EGL_image,
        GL_OES_EGL_image_external,
        GL_OES_compressed_ETC1_RGB8_texture,
        GL_OES_compressed_paletted_texture,
        GL_OES_depth24,
        GL_OES_depth32,
        GL_OES_mapbuffer,
        GL_OES_rgb8_rgba8,
        GL_OES_texture_npot,
        GL_OES_vertex_array_object,
        GL_OES_vertex_half_float
    Loader: True
    Local files: False
    Omit khrplatform: False

    Commandline:
        --profile="compatibility" --api="gles2=2.0" --generator="c" --spec="gl" --extensions="GL_APPLE_rgb_422,GL_EXT_debug_marker,GL_EXT_discard_framebuffer,GL_EXT_texture_format_BGRA8888,GL_OES_EGL_image,GL_OES_EGL_image_external,GL_OES_compressed_ETC1_RGB8_texture,GL_OES_compressed_paletted_texture,GL_OES_depth24,GL_OES_depth32,GL_OES_mapbuffer,GL_OES_rgb8_rgba8,GL_OES_texture_npot,GL_OES_vertex_array_object,GL_OES_vertex_half_float"
    Online:
        http://glad.dav1d.de/#profile=compatibility&language=c&specification=gl&loader=on&api=gles2%3D2.0&extensions=GL_APPLE_rgb_422&extensions=GL_EXT_debug_marker&extensions=GL_EXT_discard_framebuffer&extensions=GL_EXT_texture_format_BGRA8888&extensions=GL_OES_EGL_image&extensions=GL_OES_EGL_image_external&extensions=GL_OES_compressed_ETC1_RGB8_texture&extensions=GL_OES_compressed_paletted_texture&extensions=GL_OES_depth24&extensions=GL_OES_depth32&extensions=GL_OES_mapbuffer&extensions=GL_OES_rgb8_rgba8&extensions=GL_OES_texture_npot&extensions=GL_OES_vertex_array_object&extensions=GL_OES_vertex_half_float
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glad/glad.h>

struct gladGLversionStruct GLVersion;

#if defined(GL_ES_VERSION_3_0) || defined(GL_VERSION_3_0)
#define _GLAD_IS_SOME_NEW_VERSION 1
#endif

static int max_loaded_major;
static int max_loaded_minor;

static const char *exts = NULL;
static int num_exts_i = 0;
static const char **exts_i = NULL;

static int get_exts(void) {
#ifdef _GLAD_IS_SOME_NEW_VERSION
    if(max_loaded_major < 3) {
#endif
        exts = (const char *)glGetString(GL_EXTENSIONS);
#ifdef _GLAD_IS_SOME_NEW_VERSION
    } else {
        int index;

        num_exts_i = 0;
        glGetIntegerv(GL_NUM_EXTENSIONS, &num_exts_i);
        if (num_exts_i > 0) {
            exts_i = (const char **)realloc((void *)exts_i, num_exts_i * sizeof *exts_i);
        }

        if (exts_i == NULL) {
            return 0;
        }

        for(index = 0; index < num_exts_i; index++) {
            exts_i[index] = (const char*)glGetStringi(GL_EXTENSIONS, index);
        }
    }
#endif
    return 1;
}

static void free_exts(void) {
    if (exts_i != NULL) {
        free((char **)exts_i);
        exts_i = NULL;
    }
}

static int has_ext(const char *ext) {
#ifdef _GLAD_IS_SOME_NEW_VERSION
    if(max_loaded_major < 3) {
#endif
        const char *extensions;
        const char *loc;
        const char *terminator;
        extensions = exts;
        if(extensions == NULL || ext == NULL) {
            return 0;
        }

        while(1) {
            loc = strstr(extensions, ext);
            if(loc == NULL) {
                return 0;
            }

            terminator = loc + strlen(ext);
            if((loc == extensions || *(loc - 1) == ' ') &&
                (*terminator == ' ' || *terminator == '\0')) {
                return 1;
            }
            extensions = terminator;
        }
#ifdef _GLAD_IS_SOME_NEW_VERSION
    } else {
        int index;

        for(index = 0; index < num_exts_i; index++) {
            const char *e = exts_i[index];

            if(strcmp(e, ext) == 0) {
                return 1;
            }
        }
    }
#endif

    return 0;
}
int GLAD_GL_ES_VERSION_2_0;
PFNGLFLUSHPROC glad_glFlush;
PFNGLGETRENDERBUFFERPARAMETERIVPROC glad_glGetRenderbufferParameteriv;
PFNGLCLEARCOLORPROC glad_glClearColor;
PFNGLSTENCILMASKSEPARATEPROC glad_glStencilMaskSeparate;
PFNGLGETVERTEXATTRIBPOINTERVPROC glad_glGetVertexAttribPointerv;
PFNGLLINKPROGRAMPROC glad_glLinkProgram;
PFNGLBINDTEXTUREPROC glad_glBindTexture;
PFNGLFRAMEBUFFERRENDERBUFFERPROC glad_glFramebufferRenderbuffer;
PFNGLGETSTRINGPROC glad_glGetString;
PFNGLDETACHSHADERPROC glad_glDetachShader;
PFNGLLINEWIDTHPROC glad_glLineWidth;
PFNGLUNIFORM2FVPROC glad_glUniform2fv;
PFNGLCOMPILESHADERPROC glad_glCompileShader;
PFNGLDELETETEXTURESPROC glad_glDeleteTextures;
PFNGLSTENCILOPSEPARATEPROC glad_glStencilOpSeparate;
PFNGLSTENCILFUNCSEPARATEPROC glad_glStencilFuncSeparate;
PFNGLVERTEXATTRIB4FPROC glad_glVertexAttrib4f;
PFNGLDEPTHRANGEFPROC glad_glDepthRangef;
PFNGLUNIFORM4IVPROC glad_glUniform4iv;
PFNGLGETTEXPARAMETERIVPROC glad_glGetTexParameteriv;
PFNGLCLEARSTENCILPROC glad_glClearStencil;
PFNGLSAMPLECOVERAGEPROC glad_glSampleCoverage;
PFNGLGENTEXTURESPROC glad_glGenTextures;
PFNGLDEPTHFUNCPROC glad_glDepthFunc;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glad_glCompressedTexSubImage2D;
PFNGLUNIFORM1FPROC glad_glUniform1f;
PFNGLGETVERTEXATTRIBFVPROC glad_glGetVertexAttribfv;
PFNGLGETTEXPARAMETERFVPROC glad_glGetTexParameterfv;
PFNGLCREATESHADERPROC glad_glCreateShader;
PFNGLISBUFFERPROC glad_glIsBuffer;
PFNGLUNIFORM1IPROC glad_glUniform1i;
PFNGLGENRENDERBUFFERSPROC glad_glGenRenderbuffers;
PFNGLCOPYTEXSUBIMAGE2DPROC glad_glCopyTexSubImage2D;
PFNGLCOMPRESSEDTEXIMAGE2DPROC glad_glCompressedTexImage2D;
PFNGLDISABLEPROC glad_glDisable;
PFNGLUNIFORM2IPROC glad_glUniform2i;
PFNGLBLENDFUNCSEPARATEPROC glad_glBlendFuncSeparate;
PFNGLGETPROGRAMIVPROC glad_glGetProgramiv;
PFNGLCOLORMASKPROC glad_glColorMask;
PFNGLHINTPROC glad_glHint;
PFNGLBLENDEQUATIONPROC glad_glBlendEquation;
PFNGLGETUNIFORMLOCATIONPROC glad_glGetUniformLocation;
PFNGLBINDFRAMEBUFFERPROC glad_glBindFramebuffer;
PFNGLCULLFACEPROC glad_glCullFace;
PFNGLUNIFORM4FVPROC glad_glUniform4fv;
PFNGLDELETEPROGRAMPROC glad_glDeleteProgram;
PFNGLRENDERBUFFERSTORAGEPROC glad_glRenderbufferStorage;
PFNGLATTACHSHADERPROC glad_glAttachShader;
PFNGLUNIFORM3IPROC glad_glUniform3i;
PFNGLCHECKFRAMEBUFFERSTATUSPROC glad_glCheckFramebufferStatus;
PFNGLSHADERBINARYPROC glad_glShaderBinary;
PFNGLCOPYTEXIMAGE2DPROC glad_glCopyTexImage2D;
PFNGLUNIFORM3FPROC glad_glUniform3f;
PFNGLBINDATTRIBLOCATIONPROC glad_glBindAttribLocation;
PFNGLDRAWELEMENTSPROC glad_glDrawElements;
PFNGLUNIFORM2IVPROC glad_glUniform2iv;
PFNGLVERTEXATTRIB1FVPROC glad_glVertexAttrib1fv;
PFNGLBUFFERSUBDATAPROC glad_glBufferSubData;
PFNGLUNIFORM1IVPROC glad_glUniform1iv;
PFNGLGETBUFFERPARAMETERIVPROC glad_glGetBufferParameteriv;
PFNGLGENERATEMIPMAPPROC glad_glGenerateMipmap;
PFNGLGETSHADERIVPROC glad_glGetShaderiv;
PFNGLVERTEXATTRIB3FPROC glad_glVertexAttrib3f;
PFNGLGETACTIVEATTRIBPROC glad_glGetActiveAttrib;
PFNGLBLENDCOLORPROC glad_glBlendColor;
PFNGLGETSHADERPRECISIONFORMATPROC glad_glGetShaderPrecisionFormat;
PFNGLDEPTHMASKPROC glad_glDepthMask;
PFNGLUSEPROGRAMPROC glad_glUseProgram;
PFNGLSHADERSOURCEPROC glad_glShaderSource;
PFNGLBINDRENDERBUFFERPROC glad_glBindRenderbuffer;
PFNGLDELETERENDERBUFFERSPROC glad_glDeleteRenderbuffers;
PFNGLDELETEFRAMEBUFFERSPROC glad_glDeleteFramebuffers;
PFNGLDRAWARRAYSPROC glad_glDrawArrays;
PFNGLISPROGRAMPROC glad_glIsProgram;
PFNGLTEXSUBIMAGE2DPROC glad_glTexSubImage2D;
PFNGLGETUNIFORMIVPROC glad_glGetUniformiv;
PFNGLUNIFORM4IPROC glad_glUniform4i;
PFNGLCLEARPROC glad_glClear;
PFNGLVERTEXATTRIB4FVPROC glad_glVertexAttrib4fv;
PFNGLRELEASESHADERCOMPILERPROC glad_glReleaseShaderCompiler;
PFNGLUNIFORM2FPROC glad_glUniform2f;
PFNGLACTIVETEXTUREPROC glad_glActiveTexture;
PFNGLENABLEVERTEXATTRIBARRAYPROC glad_glEnableVertexAttribArray;
PFNGLBINDBUFFERPROC glad_glBindBuffer;
PFNGLISENABLEDPROC glad_glIsEnabled;
PFNGLSTENCILOPPROC glad_glStencilOp;
PFNGLREADPIXELSPROC glad_glReadPixels;
PFNGLUNIFORM4FPROC glad_glUniform4f;
PFNGLFRAMEBUFFERTEXTURE2DPROC glad_glFramebufferTexture2D;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glad_glGetFramebufferAttachmentParameteriv;
PFNGLUNIFORM3FVPROC glad_glUniform3fv;
PFNGLBUFFERDATAPROC glad_glBufferData;
PFNGLGETERRORPROC glad_glGetError;
PFNGLGETVERTEXATTRIBIVPROC glad_glGetVertexAttribiv;
PFNGLTEXPARAMETERIVPROC glad_glTexParameteriv;
PFNGLVERTEXATTRIB3FVPROC glad_glVertexAttrib3fv;
PFNGLGETFLOATVPROC glad_glGetFloatv;
PFNGLUNIFORM3IVPROC glad_glUniform3iv;
PFNGLVERTEXATTRIB2FVPROC glad_glVertexAttrib2fv;
PFNGLGENFRAMEBUFFERSPROC glad_glGenFramebuffers;
PFNGLSTENCILFUNCPROC glad_glStencilFunc;
PFNGLGETINTEGERVPROC glad_glGetIntegerv;
PFNGLGETATTACHEDSHADERSPROC glad_glGetAttachedShaders;
PFNGLISRENDERBUFFERPROC glad_glIsRenderbuffer;
PFNGLUNIFORM1FVPROC glad_glUniform1fv;
PFNGLUNIFORMMATRIX2FVPROC glad_glUniformMatrix2fv;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glad_glDisableVertexAttribArray;
PFNGLTEXIMAGE2DPROC glad_glTexImage2D;
PFNGLGETPROGRAMINFOLOGPROC glad_glGetProgramInfoLog;
PFNGLSTENCILMASKPROC glad_glStencilMask;
PFNGLGETSHADERINFOLOGPROC glad_glGetShaderInfoLog;
PFNGLISTEXTUREPROC glad_glIsTexture;
PFNGLISSHADERPROC glad_glIsShader;
PFNGLDELETEBUFFERSPROC glad_glDeleteBuffers;
PFNGLVERTEXATTRIBPOINTERPROC glad_glVertexAttribPointer;
PFNGLTEXPARAMETERFVPROC glad_glTexParameterfv;
PFNGLUNIFORMMATRIX3FVPROC glad_glUniformMatrix3fv;
PFNGLENABLEPROC glad_glEnable;
PFNGLBLENDEQUATIONSEPARATEPROC glad_glBlendEquationSeparate;
PFNGLGENBUFFERSPROC glad_glGenBuffers;
PFNGLFINISHPROC glad_glFinish;
PFNGLGETATTRIBLOCATIONPROC glad_glGetAttribLocation;
PFNGLDELETESHADERPROC glad_glDeleteShader;
PFNGLBLENDFUNCPROC glad_glBlendFunc;
PFNGLCREATEPROGRAMPROC glad_glCreateProgram;
PFNGLISFRAMEBUFFERPROC glad_glIsFramebuffer;
PFNGLVIEWPORTPROC glad_glViewport;
PFNGLVERTEXATTRIB2FPROC glad_glVertexAttrib2f;
PFNGLVERTEXATTRIB1FPROC glad_glVertexAttrib1f;
PFNGLGETUNIFORMFVPROC glad_glGetUniformfv;
PFNGLUNIFORMMATRIX4FVPROC glad_glUniformMatrix4fv;
PFNGLGETACTIVEUNIFORMPROC glad_glGetActiveUniform;
PFNGLTEXPARAMETERFPROC glad_glTexParameterf;
PFNGLTEXPARAMETERIPROC glad_glTexParameteri;
PFNGLFRONTFACEPROC glad_glFrontFace;
PFNGLCLEARDEPTHFPROC glad_glClearDepthf;
PFNGLGETSHADERSOURCEPROC glad_glGetShaderSource;
PFNGLSCISSORPROC glad_glScissor;
PFNGLGETBOOLEANVPROC glad_glGetBooleanv;
PFNGLPIXELSTOREIPROC glad_glPixelStorei;
PFNGLVALIDATEPROGRAMPROC glad_glValidateProgram;
PFNGLPOLYGONOFFSETPROC glad_glPolygonOffset;
int GLAD_GL_OES_vertex_array_object;
int GLAD_GL_OES_EGL_image_external;
int GLAD_GL_OES_compressed_paletted_texture;
int GLAD_GL_OES_mapbuffer;
int GLAD_GL_EXT_discard_framebuffer;
int GLAD_GL_OES_texture_npot;
int GLAD_GL_OES_depth32;
int GLAD_GL_APPLE_rgb_422;
int GLAD_GL_OES_rgb8_rgba8;
int GLAD_GL_EXT_texture_format_BGRA8888;
int GLAD_GL_OES_depth24;
int GLAD_GL_OES_compressed_ETC1_RGB8_texture;
int GLAD_GL_OES_EGL_image;
int GLAD_GL_EXT_debug_marker;
int GLAD_GL_OES_vertex_half_float;
PFNGLINSERTEVENTMARKEREXTPROC glad_glInsertEventMarkerEXT;
PFNGLPUSHGROUPMARKEREXTPROC glad_glPushGroupMarkerEXT;
PFNGLPOPGROUPMARKEREXTPROC glad_glPopGroupMarkerEXT;
PFNGLDISCARDFRAMEBUFFEREXTPROC glad_glDiscardFramebufferEXT;
PFNGLEGLIMAGETARGETTEXTURE2DOESPROC glad_glEGLImageTargetTexture2DOES;
PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC glad_glEGLImageTargetRenderbufferStorageOES;
PFNGLMAPBUFFEROESPROC glad_glMapBufferOES;
PFNGLUNMAPBUFFEROESPROC glad_glUnmapBufferOES;
PFNGLGETBUFFERPOINTERVOESPROC glad_glGetBufferPointervOES;
PFNGLBINDVERTEXARRAYOESPROC glad_glBindVertexArrayOES;
PFNGLDELETEVERTEXARRAYSOESPROC glad_glDeleteVertexArraysOES;
PFNGLGENVERTEXARRAYSOESPROC glad_glGenVertexArraysOES;
PFNGLISVERTEXARRAYOESPROC glad_glIsVertexArrayOES;
static void load_GL_ES_VERSION_2_0(GLADloadproc load) {
	if(!GLAD_GL_ES_VERSION_2_0) return;
	glad_glActiveTexture = (PFNGLACTIVETEXTUREPROC)load("glActiveTexture");
	glad_glAttachShader = (PFNGLATTACHSHADERPROC)load("glAttachShader");
	glad_glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)load("glBindAttribLocation");
	glad_glBindBuffer = (PFNGLBINDBUFFERPROC)load("glBindBuffer");
	glad_glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)load("glBindFramebuffer");
	glad_glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)load("glBindRenderbuffer");
	glad_glBindTexture = (PFNGLBINDTEXTUREPROC)load("glBindTexture");
	glad_glBlendColor = (PFNGLBLENDCOLORPROC)load("glBlendColor");
	glad_glBlendEquation = (PFNGLBLENDEQUATIONPROC)load("glBlendEquation");
	glad_glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC)load("glBlendEquationSeparate");
	glad_glBlendFunc = (PFNGLBLENDFUNCPROC)load("glBlendFunc");
	glad_glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)load("glBlendFuncSeparate");
	glad_glBufferData = (PFNGLBUFFERDATAPROC)load("glBufferData");
	glad_glBufferSubData = (PFNGLBUFFERSUBDATAPROC)load("glBufferSubData");
	glad_glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)load("glCheckFramebufferStatus");
	glad_glClear = (PFNGLCLEARPROC)load("glClear");
	glad_glClearColor = (PFNGLCLEARCOLORPROC)load("glClearColor");
	glad_glClearDepthf = (PFNGLCLEARDEPTHFPROC)load("glClearDepthf");
	glad_glClearStencil = (PFNGLCLEARSTENCILPROC)load("glClearStencil");
	glad_glColorMask = (PFNGLCOLORMASKPROC)load("glColorMask");
	glad_glCompileShader = (PFNGLCOMPILESHADERPROC)load("glCompileShader");
	glad_glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)load("glCompressedTexImage2D");
	glad_glCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)load("glCompressedTexSubImage2D");
	glad_glCopyTexImage2D = (PFNGLCOPYTEXIMAGE2DPROC)load("glCopyTexImage2D");
	glad_glCopyTexSubImage2D = (PFNGLCOPYTEXSUBIMAGE2DPROC)load("glCopyTexSubImage2D");
	glad_glCreateProgram = (PFNGLCREATEPROGRAMPROC)load("glCreateProgram");
	glad_glCreateShader = (PFNGLCREATESHADERPROC)load("glCreateShader");
	glad_glCullFace = (PFNGLCULLFACEPROC)load("glCullFace");
	glad_glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)load("glDeleteBuffers");
	glad_glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)load("glDeleteFramebuffers");
	glad_glDeleteProgram = (PFNGLDELETEPROGRAMPROC)load("glDeleteProgram");
	glad_glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)load("glDeleteRenderbuffers");
	glad_glDeleteShader = (PFNGLDELETESHADERPROC)load("glDeleteShader");
	glad_glDeleteTextures = (PFNGLDELETETEXTURESPROC)load("glDeleteTextures");
	glad_glDepthFunc = (PFNGLDEPTHFUNCPROC)load("glDepthFunc");
	glad_glDepthMask = (PFNGLDEPTHMASKPROC)load("glDepthMask");
	glad_glDepthRangef = (PFNGLDEPTHRANGEFPROC)load("glDepthRangef");
	glad_glDetachShader = (PFNGLDETACHSHADERPROC)load("glDetachShader");
	glad_glDisable = (PFNGLDISABLEPROC)load("glDisable");
	glad_glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)load("glDisableVertexAttribArray");
	glad_glDrawArrays = (PFNGLDRAWARRAYSPROC)load("glDrawArrays");
	glad_glDrawElements = (PFNGLDRAWELEMENTSPROC)load("glDrawElements");
	glad_glEnable = (PFNGLENABLEPROC)load("glEnable");
	glad_glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)load("glEnableVertexAttribArray");
	glad_glFinish = (PFNGLFINISHPROC)load("glFinish");
	glad_glFlush = (PFNGLFLUSHPROC)load("glFlush");
	glad_glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)load("glFramebufferRenderbuffer");
	glad_glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)load("glFramebufferTexture2D");
	glad_glFrontFace = (PFNGLFRONTFACEPROC)load("glFrontFace");
	glad_glGenBuffers = (PFNGLGENBUFFERSPROC)load("glGenBuffers");
	glad_glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)load("glGenerateMipmap");
	glad_glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)load("glGenFramebuffers");
	glad_glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)load("glGenRenderbuffers");
	glad_glGenTextures = (PFNGLGENTEXTURESPROC)load("glGenTextures");
	glad_glGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC)load("glGetActiveAttrib");
	glad_glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC)load("glGetActiveUniform");
	glad_glGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC)load("glGetAttachedShaders");
	glad_glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)load("glGetAttribLocation");
	glad_glGetBooleanv = (PFNGLGETBOOLEANVPROC)load("glGetBooleanv");
	glad_glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC)load("glGetBufferParameteriv");
	glad_glGetError = (PFNGLGETERRORPROC)load("glGetError");
	glad_glGetFloatv = (PFNGLGETFLOATVPROC)load("glGetFloatv");
	glad_glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)load("glGetFramebufferAttachmentParameteriv");
	glad_glGetIntegerv = (PFNGLGETINTEGERVPROC)load("glGetIntegerv");
	glad_glGetProgramiv = (PFNGLGETPROGRAMIVPROC)load("glGetProgramiv");
	glad_glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)load("glGetProgramInfoLog");
	glad_glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)load("glGetRenderbufferParameteriv");
	glad_glGetShaderiv = (PFNGLGETSHADERIVPROC)load("glGetShaderiv");
	glad_glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)load("glGetShaderInfoLog");
	glad_glGetShaderPrecisionFormat = (PFNGLGETSHADERPRECISIONFORMATPROC)load("glGetShaderPrecisionFormat");
	glad_glGetShaderSource = (PFNGLGETSHADERSOURCEPROC)load("glGetShaderSource");
	glad_glGetString = (PFNGLGETSTRINGPROC)load("glGetString");
	glad_glGetTexParameterfv = (PFNGLGETTEXPARAMETERFVPROC)load("glGetTexParameterfv");
	glad_glGetTexParameteriv = (PFNGLGETTEXPARAMETERIVPROC)load("glGetTexParameteriv");
	glad_glGetUniformfv = (PFNGLGETUNIFORMFVPROC)load("glGetUniformfv");
	glad_glGetUniformiv = (PFNGLGETUNIFORMIVPROC)load("glGetUniformiv");
	glad_glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)load("glGetUniformLocation");
	glad_glGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC)load("glGetVertexAttribfv");
	glad_glGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC)load("glGetVertexAttribiv");
	glad_glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC)load("glGetVertexAttribPointerv");
	glad_glHint = (PFNGLHINTPROC)load("glHint");
	glad_glIsBuffer = (PFNGLISBUFFERPROC)load("glIsBuffer");
	glad_glIsEnabled = (PFNGLISENABLEDPROC)load("glIsEnabled");
	glad_glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC)load("glIsFramebuffer");
	glad_glIsProgram = (PFNGLISPROGRAMPROC)load("glIsProgram");
	glad_glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC)load("glIsRenderbuffer");
	glad_glIsShader = (PFNGLISSHADERPROC)load("glIsShader");
	glad_glIsTexture = (PFNGLISTEXTUREPROC)load("glIsTexture");
	glad_glLineWidth = (PFNGLLINEWIDTHPROC)load("glLineWidth");
	glad_glLinkProgram = (PFNGLLINKPROGRAMPROC)load("glLinkProgram");
	glad_glPixelStorei = (PFNGLPIXELSTOREIPROC)load("glPixelStorei");
	glad_glPolygonOffset = (PFNGLPOLYGONOFFSETPROC)load("glPolygonOffset");
	glad_glReadPixels = (PFNGLREADPIXELSPROC)load("glReadPixels");
	glad_glReleaseShaderCompiler = (PFNGLRELEASESHADERCOMPILERPROC)load("glReleaseShaderCompiler");
	glad_glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)load("glRenderbufferStorage");
	glad_glSampleCoverage = (PFNGLSAMPLECOVERAGEPROC)load("glSampleCoverage");
	glad_glScissor = (PFNGLSCISSORPROC)load("glScissor");
	glad_glShaderBinary = (PFNGLSHADERBINARYPROC)load("glShaderBinary");
	glad_glShaderSource = (PFNGLSHADERSOURCEPROC)load("glShaderSource");
	glad_glStencilFunc = (PFNGLSTENCILFUNCPROC)load("glStencilFunc");
	glad_glStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEPROC)load("glStencilFuncSeparate");
	glad_glStencilMask = (PFNGLSTENCILMASKPROC)load("glStencilMask");
	glad_glStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATEPROC)load("glStencilMaskSeparate");
	glad_glStencilOp = (PFNGLSTENCILOPPROC)load("glStencilOp");
	glad_glStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC)load("glStencilOpSeparate");
	glad_glTexImage2D = (PFNGLTEXIMAGE2DPROC)load("glTexImage2D");
	glad_glTexParameterf = (PFNGLTEXPARAMETERFPROC)load("glTexParameterf");
	glad_glTexParameterfv = (PFNGLTEXPARAMETERFVPROC)load("glTexParameterfv");
	glad_glTexParameteri = (PFNGLTEXPARAMETERIPROC)load("glTexParameteri");
	glad_glTexParameteriv = (PFNGLTEXPARAMETERIVPROC)load("glTexParameteriv");
	glad_glTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC)load("glTexSubImage2D");
	glad_glUniform1f = (PFNGLUNIFORM1FPROC)load("glUniform1f");
	glad_glUniform1fv = (PFNGLUNIFORM1FVPROC)load("glUniform1fv");
	glad_glUniform1i = (PFNGLUNIFORM1IPROC)load("glUniform1i");
	glad_glUniform1iv = (PFNGLUNIFORM1IVPROC)load("glUniform1iv");
	glad_glUniform2f = (PFNGLUNIFORM2FPROC)load("glUniform2f");
	glad_glUniform2fv = (PFNGLUNIFORM2FVPROC)load("glUniform2fv");
	glad_glUniform2i = (PFNGLUNIFORM2IPROC)load("glUniform2i");
	glad_glUniform2iv = (PFNGLUNIFORM2IVPROC)load("glUniform2iv");
	glad_glUniform3f = (PFNGLUNIFORM3FPROC)load("glUniform3f");
	glad_glUniform3fv = (PFNGLUNIFORM3FVPROC)load("glUniform3fv");
	glad_glUniform3i = (PFNGLUNIFORM3IPROC)load("glUniform3i");
	glad_glUniform3iv = (PFNGLUNIFORM3IVPROC)load("glUniform3iv");
	glad_glUniform4f = (PFNGLUNIFORM4FPROC)load("glUniform4f");
	glad_glUniform4fv = (PFNGLUNIFORM4FVPROC)load("glUniform4fv");
	glad_glUniform4i = (PFNGLUNIFORM4IPROC)load("glUniform4i");
	glad_glUniform4iv = (PFNGLUNIFORM4IVPROC)load("glUniform4iv");
	glad_glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)load("glUniformMatrix2fv");
	glad_glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)load("glUniformMatrix3fv");
	glad_glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)load("glUniformMatrix4fv");
	glad_glUseProgram = (PFNGLUSEPROGRAMPROC)load("glUseProgram");
	glad_glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)load("glValidateProgram");
	glad_glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)load("glVertexAttrib1f");
	glad_glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)load("glVertexAttrib1fv");
	glad_glVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC)load("glVertexAttrib2f");
	glad_glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC)load("glVertexAttrib2fv");
	glad_glVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC)load("glVertexAttrib3f");
	glad_glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC)load("glVertexAttrib3fv");
	glad_glVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC)load("glVertexAttrib4f");
	glad_glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)load("glVertexAttrib4fv");
	glad_glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)load("glVertexAttribPointer");
	glad_glViewport = (PFNGLVIEWPORTPROC)load("glViewport");
}
static void load_GL_EXT_debug_marker(GLADloadproc load) {
	if(!GLAD_GL_EXT_debug_marker) return;
	glad_glInsertEventMarkerEXT = (PFNGLINSERTEVENTMARKEREXTPROC)load("glInsertEventMarkerEXT");
	glad_glPushGroupMarkerEXT = (PFNGLPUSHGROUPMARKEREXTPROC)load("glPushGroupMarkerEXT");
	glad_glPopGroupMarkerEXT = (PFNGLPOPGROUPMARKEREXTPROC)load("glPopGroupMarkerEXT");
}
static void load_GL_EXT_discard_framebuffer(GLADloadproc load) {
	if(!GLAD_GL_EXT_discard_framebuffer) return;
	glad_glDiscardFramebufferEXT = (PFNGLDISCARDFRAMEBUFFEREXTPROC)load("glDiscardFramebufferEXT");
}
static void load_GL_OES_EGL_image(GLADloadproc load) {
	if(!GLAD_GL_OES_EGL_image) return;
	glad_glEGLImageTargetTexture2DOES = (PFNGLEGLIMAGETARGETTEXTURE2DOESPROC)load("glEGLImageTargetTexture2DOES");
	glad_glEGLImageTargetRenderbufferStorageOES = (PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC)load("glEGLImageTargetRenderbufferStorageOES");
}
static void load_GL_OES_mapbuffer(GLADloadproc load) {
	if(!GLAD_GL_OES_mapbuffer) return;
	glad_glMapBufferOES = (PFNGLMAPBUFFEROESPROC)load("glMapBufferOES");
	glad_glUnmapBufferOES = (PFNGLUNMAPBUFFEROESPROC)load("glUnmapBufferOES");
	glad_glGetBufferPointervOES = (PFNGLGETBUFFERPOINTERVOESPROC)load("glGetBufferPointervOES");
}
static void load_GL_OES_vertex_array_object(GLADloadproc load) {
	if(!GLAD_GL_OES_vertex_array_object) return;
	glad_glBindVertexArrayOES = (PFNGLBINDVERTEXARRAYOESPROC)load("glBindVertexArrayOES");
	glad_glDeleteVertexArraysOES = (PFNGLDELETEVERTEXARRAYSOESPROC)load("glDeleteVertexArraysOES");
	glad_glGenVertexArraysOES = (PFNGLGENVERTEXARRAYSOESPROC)load("glGenVertexArraysOES");
	glad_glIsVertexArrayOES = (PFNGLISVERTEXARRAYOESPROC)load("glIsVertexArrayOES");
}
static int find_extensionsGLES2(void) {
	if (!get_exts()) return 0;
	GLAD_GL_APPLE_rgb_422 = has_ext("GL_APPLE_rgb_422");
	GLAD_GL_EXT_debug_marker = has_ext("GL_EXT_debug_marker");
	GLAD_GL_EXT_discard_framebuffer = has_ext("GL_EXT_discard_framebuffer");
	GLAD_GL_EXT_texture_format_BGRA8888 = has_ext("GL_EXT_texture_format_BGRA8888");
	GLAD_GL_OES_EGL_image = has_ext("GL_OES_EGL_image");
	GLAD_GL_OES_EGL_image_external = has_ext("GL_OES_EGL_image_external");
	GLAD_GL_OES_compressed_ETC1_RGB8_texture = has_ext("GL_OES_compressed_ETC1_RGB8_texture");
	GLAD_GL_OES_compressed_paletted_texture = has_ext("GL_OES_compressed_paletted_texture");
	GLAD_GL_OES_depth24 = has_ext("GL_OES_depth24");
	GLAD_GL_OES_depth32 = has_ext("GL_OES_depth32");
	GLAD_GL_OES_mapbuffer = has_ext("GL_OES_mapbuffer");
	GLAD_GL_OES_rgb8_rgba8 = has_ext("GL_OES_rgb8_rgba8");
	GLAD_GL_OES_texture_npot = has_ext("GL_OES_texture_npot");
	GLAD_GL_OES_vertex_array_object = has_ext("GL_OES_vertex_array_object");
	GLAD_GL_OES_vertex_half_float = has_ext("GL_OES_vertex_half_float");
	free_exts();
	return 1;
}

static void find_coreGLES2(void) {

    /* Thank you @elmindreda
     * https://github.com/elmindreda/greg/blob/master/templates/greg.c.in#L176
     * https://github.com/glfw/glfw/blob/master/src/context.c#L36
     */
    int i, major, minor;

    const char* version;
    const char* prefixes[] = {
        "OpenGL ES-CM ",
        "OpenGL ES-CL ",
        "OpenGL ES ",
        NULL
    };

    version = (const char*) glGetString(GL_VERSION);
    if (!version) return;

    for (i = 0;  prefixes[i];  i++) {
        const size_t length = strlen(prefixes[i]);
        if (strncmp(version, prefixes[i], length) == 0) {
            version += length;
            break;
        }
    }

/* PR #18 */
#ifdef _MSC_VER
    sscanf_s(version, "%d.%d", &major, &minor);
#else
    sscanf(version, "%d.%d", &major, &minor);
#endif

    GLVersion.major = major; GLVersion.minor = minor;
    max_loaded_major = major; max_loaded_minor = minor;
	GLAD_GL_ES_VERSION_2_0 = (major == 2 && minor >= 0) || major > 2;
	if (GLVersion.major > 2 || (GLVersion.major >= 2 && GLVersion.minor >= 0)) {
		max_loaded_major = 2;
		max_loaded_minor = 0;
	}
}

int gladLoadGLES2Loader(GLADloadproc load) {
	GLVersion.major = 0; GLVersion.minor = 0;
	glGetString = (PFNGLGETSTRINGPROC)load("glGetString");
	if(glGetString == NULL) return 0;
	if(glGetString(GL_VERSION) == NULL) return 0;
	find_coreGLES2();
	load_GL_ES_VERSION_2_0(load);

	if (!find_extensionsGLES2()) return 0;
	load_GL_EXT_debug_marker(load);
	load_GL_EXT_discard_framebuffer(load);
	load_GL_OES_EGL_image(load);
	load_GL_OES_mapbuffer(load);
	load_GL_OES_vertex_array_object(load);
	return GLVersion.major != 0 || GLVersion.minor != 0;
}

