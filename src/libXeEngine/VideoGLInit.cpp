#include "VideoGL.h"

bool XeEngine::VideoFramework::GL::LibrariesLoaded = false;

#ifdef PLATFORM_WINDOWS
#define xglGetProcAddress(m_name)		wglGetProcAddress((LPCSTR)m_name)
#elif PLATFORM_APPLE
#define xglGetProcAddress(m_name)		NSGLGetProcAddress((LPCSTR)m_name)
#elif PLATFORM_LINUX
#define xglGetProcAddress(m_name)		glXGetProcAddressARB((LPCSTR)m_name)
#elif PLATFORM_SUN
#define xglGetProcAddress(m_name)		dlGetProcAddress((LPCSTR)m_name)
#elif PLATFORM_ANDROID
#else
void xglGetProcAddress(const char* name)
{

}
#endif

PFNGLCOPYTEXSUBIMAGE3DPROC glCopyTexSubImage3D = NULL;
PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElements = NULL;
PFNGLTEXIMAGE3DPROC glTexImage3D = NULL;
PFNGLTEXSUBIMAGE3DPROC glTexSubImage3D = NULL;

PFNGLACTIVETEXTUREPROC glActiveTexture = NULL;
PFNGLCLIENTACTIVETEXTUREPROC glClientActiveTexture = NULL;
PFNGLCOMPRESSEDTEXIMAGE1DPROC glCompressedTexImage1D = NULL;
PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D = NULL;
PFNGLCOMPRESSEDTEXIMAGE3DPROC glCompressedTexImage3D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC glCompressedTexSubImage1D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glCompressedTexSubImage3D = NULL;
PFNGLGETCOMPRESSEDTEXIMAGEPROC glGetCompressedTexImage = NULL;
PFNGLLOADTRANSPOSEMATRIXDPROC glLoadTransposeMatrixd = NULL;
PFNGLLOADTRANSPOSEMATRIXFPROC glLoadTransposeMatrixf = NULL;
PFNGLMULTTRANSPOSEMATRIXDPROC glMultTransposeMatrixd = NULL;
PFNGLMULTTRANSPOSEMATRIXFPROC glMultTransposeMatrixf = NULL;
PFNGLMULTITEXCOORD1DPROC glMultiTexCoord1d = NULL;
PFNGLMULTITEXCOORD1DVPROC glMultiTexCoord1dv = NULL;
PFNGLMULTITEXCOORD1FPROC glMultiTexCoord1f = NULL;
PFNGLMULTITEXCOORD1FVPROC glMultiTexCoord1fv = NULL;
PFNGLMULTITEXCOORD1IPROC glMultiTexCoord1i = NULL;
PFNGLMULTITEXCOORD1IVPROC glMultiTexCoord1iv = NULL;
PFNGLMULTITEXCOORD1SPROC glMultiTexCoord1s = NULL;
PFNGLMULTITEXCOORD1SVPROC glMultiTexCoord1sv = NULL;
PFNGLMULTITEXCOORD2DPROC glMultiTexCoord2d = NULL;
PFNGLMULTITEXCOORD2DVPROC glMultiTexCoord2dv = NULL;
PFNGLMULTITEXCOORD2FPROC glMultiTexCoord2f = NULL;
PFNGLMULTITEXCOORD2FVPROC glMultiTexCoord2fv = NULL;
PFNGLMULTITEXCOORD2IPROC glMultiTexCoord2i = NULL;
PFNGLMULTITEXCOORD2IVPROC glMultiTexCoord2iv = NULL;
PFNGLMULTITEXCOORD2SPROC glMultiTexCoord2s = NULL;
PFNGLMULTITEXCOORD2SVPROC glMultiTexCoord2sv = NULL;
PFNGLMULTITEXCOORD3DPROC glMultiTexCoord3d = NULL;
PFNGLMULTITEXCOORD3DVPROC glMultiTexCoord3dv = NULL;
PFNGLMULTITEXCOORD3FPROC glMultiTexCoord3f = NULL;
PFNGLMULTITEXCOORD3FVPROC glMultiTexCoord3fv = NULL;
PFNGLMULTITEXCOORD3IPROC glMultiTexCoord3i = NULL;
PFNGLMULTITEXCOORD3IVPROC glMultiTexCoord3iv = NULL;
PFNGLMULTITEXCOORD3SPROC glMultiTexCoord3s = NULL;
PFNGLMULTITEXCOORD3SVPROC glMultiTexCoord3sv = NULL;
PFNGLMULTITEXCOORD4DPROC glMultiTexCoord4d = NULL;
PFNGLMULTITEXCOORD4DVPROC glMultiTexCoord4dv = NULL;
PFNGLMULTITEXCOORD4FPROC glMultiTexCoord4f = NULL;
PFNGLMULTITEXCOORD4FVPROC glMultiTexCoord4fv = NULL;
PFNGLMULTITEXCOORD4IPROC glMultiTexCoord4i = NULL;
PFNGLMULTITEXCOORD4IVPROC glMultiTexCoord4iv = NULL;
PFNGLMULTITEXCOORD4SPROC glMultiTexCoord4s = NULL;
PFNGLMULTITEXCOORD4SVPROC glMultiTexCoord4sv = NULL;
PFNGLSAMPLECOVERAGEPROC glSampleCoverage = NULL;

PFNGLBLENDCOLORPROC glBlendColor = NULL;
PFNGLBLENDEQUATIONPROC glBlendEquation = NULL;
PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate = NULL;
PFNGLFOGCOORDPOINTERPROC glFogCoordPointer = NULL;
PFNGLFOGCOORDDPROC glFogCoordd = NULL;
PFNGLFOGCOORDDVPROC glFogCoorddv = NULL;
PFNGLFOGCOORDFPROC glFogCoordf = NULL;
PFNGLFOGCOORDFVPROC glFogCoordfv = NULL;
PFNGLMULTIDRAWARRAYSPROC glMultiDrawArrays = NULL;
PFNGLMULTIDRAWELEMENTSPROC glMultiDrawElements = NULL;
PFNGLPOINTPARAMETERFPROC glPointParameterf = NULL;
PFNGLPOINTPARAMETERFVPROC glPointParameterfv = NULL;
PFNGLPOINTPARAMETERIPROC glPointParameteri = NULL;
PFNGLPOINTPARAMETERIVPROC glPointParameteriv = NULL;
PFNGLSECONDARYCOLOR3BPROC glSecondaryColor3b = NULL;
PFNGLSECONDARYCOLOR3BVPROC glSecondaryColor3bv = NULL;
PFNGLSECONDARYCOLOR3DPROC glSecondaryColor3d = NULL;
PFNGLSECONDARYCOLOR3DVPROC glSecondaryColor3dv = NULL;
PFNGLSECONDARYCOLOR3FPROC glSecondaryColor3f = NULL;
PFNGLSECONDARYCOLOR3FVPROC glSecondaryColor3fv = NULL;
PFNGLSECONDARYCOLOR3IPROC glSecondaryColor3i = NULL;
PFNGLSECONDARYCOLOR3IVPROC glSecondaryColor3iv = NULL;
PFNGLSECONDARYCOLOR3SPROC glSecondaryColor3s = NULL;
PFNGLSECONDARYCOLOR3SVPROC glSecondaryColor3sv = NULL;
PFNGLSECONDARYCOLOR3UBPROC glSecondaryColor3ub = NULL;
PFNGLSECONDARYCOLOR3UBVPROC glSecondaryColor3ubv = NULL;
PFNGLSECONDARYCOLOR3UIPROC glSecondaryColor3ui = NULL;
PFNGLSECONDARYCOLOR3UIVPROC glSecondaryColor3uiv = NULL;
PFNGLSECONDARYCOLOR3USPROC glSecondaryColor3us = NULL;
PFNGLSECONDARYCOLOR3USVPROC glSecondaryColor3usv = NULL;
PFNGLSECONDARYCOLORPOINTERPROC glSecondaryColorPointer = NULL;
PFNGLWINDOWPOS2DPROC glWindowPos2d = NULL;
PFNGLWINDOWPOS2DVPROC glWindowPos2dv = NULL;
PFNGLWINDOWPOS2FPROC glWindowPos2f = NULL;
PFNGLWINDOWPOS2FVPROC glWindowPos2fv = NULL;
PFNGLWINDOWPOS2IPROC glWindowPos2i = NULL;
PFNGLWINDOWPOS2IVPROC glWindowPos2iv = NULL;
PFNGLWINDOWPOS2SPROC glWindowPos2s = NULL;
PFNGLWINDOWPOS2SVPROC glWindowPos2sv = NULL;
PFNGLWINDOWPOS3DPROC glWindowPos3d = NULL;
PFNGLWINDOWPOS3DVPROC glWindowPos3dv = NULL;
PFNGLWINDOWPOS3FPROC glWindowPos3f = NULL;
PFNGLWINDOWPOS3FVPROC glWindowPos3fv = NULL;
PFNGLWINDOWPOS3IPROC glWindowPos3i = NULL;
PFNGLWINDOWPOS3IVPROC glWindowPos3iv = NULL;
PFNGLWINDOWPOS3SPROC glWindowPos3s = NULL;
PFNGLWINDOWPOS3SVPROC glWindowPos3sv = NULL;

PFNGLBEGINQUERYPROC glBeginQuery = NULL;
PFNGLBINDBUFFERPROC glBindBuffer = NULL;
PFNGLBUFFERDATAPROC glBufferData = NULL;
PFNGLBUFFERSUBDATAPROC glBufferSubData = NULL;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = NULL;
PFNGLDELETEQUERIESPROC glDeleteQueries = NULL;
PFNGLENDQUERYPROC glEndQuery = NULL;
PFNGLGENBUFFERSPROC glGenBuffers = NULL;
PFNGLGENQUERIESPROC glGenQueries = NULL;
PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameteriv = NULL;
PFNGLGETBUFFERPOINTERVPROC glGetBufferPointerv = NULL;
PFNGLGETBUFFERSUBDATAPROC glGetBufferSubData = NULL;
PFNGLGETQUERYOBJECTIVPROC glGetQueryObjectiv = NULL;
PFNGLGETQUERYOBJECTUIVPROC glGetQueryObjectuiv = NULL;
PFNGLGETQUERYIVPROC glGetQueryiv = NULL;
PFNGLISBUFFERPROC glIsBuffer = NULL;
PFNGLISQUERYPROC glIsQuery = NULL;
PFNGLMAPBUFFERPROC glMapBuffer = NULL;
PFNGLUNMAPBUFFERPROC glUnmapBuffer = NULL;

PFNGLATTACHSHADERPROC glAttachShader = NULL;
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation = NULL;
PFNGLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparate = NULL;
PFNGLCOMPILESHADERPROC glCompileShader = NULL;
PFNGLCREATEPROGRAMPROC glCreateProgram = NULL;
PFNGLCREATESHADERPROC glCreateShader = NULL;
PFNGLDELETEPROGRAMPROC glDeleteProgram = NULL;
PFNGLDELETESHADERPROC glDeleteShader = NULL;
PFNGLDETACHSHADERPROC glDetachShader = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = NULL;
PFNGLDRAWBUFFERSPROC glDrawBuffers = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = NULL;
PFNGLGETACTIVEATTRIBPROC glGetActiveAttrib = NULL;
PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform = NULL;
PFNGLGETATTACHEDSHADERSPROC glGetAttachedShaders = NULL;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation = NULL;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = NULL;
PFNGLGETPROGRAMIVPROC glGetProgramiv = NULL;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = NULL;
PFNGLGETSHADERSOURCEPROC glGetShaderSource = NULL;
PFNGLGETSHADERIVPROC glGetShaderiv = NULL;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = NULL;
PFNGLGETUNIFORMFVPROC glGetUniformfv = NULL;
PFNGLGETUNIFORMIVPROC glGetUniformiv = NULL;
PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv = NULL;
PFNGLGETVERTEXATTRIBDVPROC glGetVertexAttribdv = NULL;
PFNGLGETVERTEXATTRIBFVPROC glGetVertexAttribfv = NULL;
PFNGLGETVERTEXATTRIBIVPROC glGetVertexAttribiv = NULL;
PFNGLISPROGRAMPROC glIsProgram = NULL;
PFNGLISSHADERPROC glIsShader = NULL;
PFNGLLINKPROGRAMPROC glLinkProgram = NULL;
PFNGLSHADERSOURCEPROC glShaderSource = NULL;
PFNGLSTENCILFUNCSEPARATEPROC glStencilFuncSeparate = NULL;
PFNGLSTENCILMASKSEPARATEPROC glStencilMaskSeparate = NULL;
PFNGLSTENCILOPSEPARATEPROC glStencilOpSeparate = NULL;
PFNGLUNIFORM1FPROC glUniform1f = NULL;
PFNGLUNIFORM1FVPROC glUniform1fv = NULL;
PFNGLUNIFORM1IPROC glUniform1i = NULL;
PFNGLUNIFORM1IVPROC glUniform1iv = NULL;
PFNGLUNIFORM2FPROC glUniform2f = NULL;
PFNGLUNIFORM2FVPROC glUniform2fv = NULL;
PFNGLUNIFORM2IPROC glUniform2i = NULL;
PFNGLUNIFORM2IVPROC glUniform2iv = NULL;
PFNGLUNIFORM3FPROC glUniform3f = NULL;
PFNGLUNIFORM3FVPROC glUniform3fv = NULL;
PFNGLUNIFORM3IPROC glUniform3i = NULL;
PFNGLUNIFORM3IVPROC glUniform3iv = NULL;
PFNGLUNIFORM4FPROC glUniform4f = NULL;
PFNGLUNIFORM4FVPROC glUniform4fv = NULL;
PFNGLUNIFORM4IPROC glUniform4i = NULL;
PFNGLUNIFORM4IVPROC glUniform4iv = NULL;
PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv = NULL;
PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv = NULL;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = NULL;
PFNGLUSEPROGRAMPROC glUseProgram = NULL;
PFNGLVALIDATEPROGRAMPROC glValidateProgram = NULL;
PFNGLVERTEXATTRIB1DPROC glVertexAttrib1d = NULL;
PFNGLVERTEXATTRIB1DVPROC glVertexAttrib1dv = NULL;
PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f = NULL;
PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv = NULL;
PFNGLVERTEXATTRIB1SPROC glVertexAttrib1s = NULL;
PFNGLVERTEXATTRIB1SVPROC glVertexAttrib1sv = NULL;
PFNGLVERTEXATTRIB2DPROC glVertexAttrib2d = NULL;
PFNGLVERTEXATTRIB2DVPROC glVertexAttrib2dv = NULL;
PFNGLVERTEXATTRIB2FPROC glVertexAttrib2f = NULL;
PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv = NULL;
PFNGLVERTEXATTRIB2SPROC glVertexAttrib2s = NULL;
PFNGLVERTEXATTRIB2SVPROC glVertexAttrib2sv = NULL;
PFNGLVERTEXATTRIB3DPROC glVertexAttrib3d = NULL;
PFNGLVERTEXATTRIB3DVPROC glVertexAttrib3dv = NULL;
PFNGLVERTEXATTRIB3FPROC glVertexAttrib3f = NULL;
PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv = NULL;
PFNGLVERTEXATTRIB3SPROC glVertexAttrib3s = NULL;
PFNGLVERTEXATTRIB3SVPROC glVertexAttrib3sv = NULL;
PFNGLVERTEXATTRIB4NBVPROC glVertexAttrib4Nbv = NULL;
PFNGLVERTEXATTRIB4NIVPROC glVertexAttrib4Niv = NULL;
PFNGLVERTEXATTRIB4NSVPROC glVertexAttrib4Nsv = NULL;
PFNGLVERTEXATTRIB4NUBPROC glVertexAttrib4Nub = NULL;
PFNGLVERTEXATTRIB4NUBVPROC glVertexAttrib4Nubv = NULL;
PFNGLVERTEXATTRIB4NUIVPROC glVertexAttrib4Nuiv = NULL;
PFNGLVERTEXATTRIB4NUSVPROC glVertexAttrib4Nusv = NULL;
PFNGLVERTEXATTRIB4BVPROC glVertexAttrib4bv = NULL;
PFNGLVERTEXATTRIB4DPROC glVertexAttrib4d = NULL;
PFNGLVERTEXATTRIB4DVPROC glVertexAttrib4dv = NULL;
PFNGLVERTEXATTRIB4FPROC glVertexAttrib4f = NULL;
PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv = NULL;
PFNGLVERTEXATTRIB4IVPROC glVertexAttrib4iv = NULL;
PFNGLVERTEXATTRIB4SPROC glVertexAttrib4s = NULL;
PFNGLVERTEXATTRIB4SVPROC glVertexAttrib4sv = NULL;
PFNGLVERTEXATTRIB4UBVPROC glVertexAttrib4ubv = NULL;
PFNGLVERTEXATTRIB4UIVPROC glVertexAttrib4uiv = NULL;
PFNGLVERTEXATTRIB4USVPROC glVertexAttrib4usv = NULL;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = NULL;

PFNGLUNIFORMMATRIX2X3FVPROC glUniformMatrix2x3fv = NULL;
PFNGLUNIFORMMATRIX2X4FVPROC glUniformMatrix2x4fv = NULL;
PFNGLUNIFORMMATRIX3X2FVPROC glUniformMatrix3x2fv = NULL;
PFNGLUNIFORMMATRIX3X4FVPROC glUniformMatrix3x4fv = NULL;
PFNGLUNIFORMMATRIX4X2FVPROC glUniformMatrix4x2fv = NULL;
PFNGLUNIFORMMATRIX4X3FVPROC glUniformMatrix4x3fv = NULL;

PFNGLBEGINCONDITIONALRENDERPROC glBeginConditionalRender = NULL;
PFNGLBEGINTRANSFORMFEEDBACKPROC glBeginTransformFeedback = NULL;
PFNGLBINDFRAGDATALOCATIONPROC glBindFragDataLocation = NULL;
PFNGLCLAMPCOLORPROC glClampColor = NULL;
PFNGLCLEARBUFFERFIPROC glClearBufferfi = NULL;
PFNGLCLEARBUFFERFVPROC glClearBufferfv = NULL;
PFNGLCLEARBUFFERIVPROC glClearBufferiv = NULL;
PFNGLCLEARBUFFERUIVPROC glClearBufferuiv = NULL;
PFNGLCOLORMASKIPROC glColorMaski = NULL;
PFNGLDISABLEIPROC glDisablei = NULL;
PFNGLENABLEIPROC glEnablei = NULL;
PFNGLENDCONDITIONALRENDERPROC glEndConditionalRender = NULL;
PFNGLENDTRANSFORMFEEDBACKPROC glEndTransformFeedback = NULL;
PFNGLGETBOOLEANI_VPROC glGetBooleani_v = NULL;
PFNGLGETFRAGDATALOCATIONPROC glGetFragDataLocation = NULL;
PFNGLGETSTRINGIPROC glGetStringi = NULL;
PFNGLGETTEXPARAMETERIIVPROC glGetTexParameterIiv = NULL;
PFNGLGETTEXPARAMETERIUIVPROC glGetTexParameterIuiv = NULL;
PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glGetTransformFeedbackVarying = NULL;
PFNGLGETUNIFORMUIVPROC glGetUniformuiv = NULL;
PFNGLGETVERTEXATTRIBIIVPROC glGetVertexAttribIiv = NULL;
PFNGLGETVERTEXATTRIBIUIVPROC glGetVertexAttribIuiv = NULL;
PFNGLISENABLEDIPROC glIsEnabledi = NULL;
PFNGLTEXPARAMETERIIVPROC glTexParameterIiv = NULL;
PFNGLTEXPARAMETERIUIVPROC glTexParameterIuiv = NULL;
PFNGLTRANSFORMFEEDBACKVARYINGSPROC glTransformFeedbackVaryings = NULL;
PFNGLUNIFORM1UIPROC glUniform1ui = NULL;
PFNGLUNIFORM1UIVPROC glUniform1uiv = NULL;
PFNGLUNIFORM2UIPROC glUniform2ui = NULL;
PFNGLUNIFORM2UIVPROC glUniform2uiv = NULL;
PFNGLUNIFORM3UIPROC glUniform3ui = NULL;
PFNGLUNIFORM3UIVPROC glUniform3uiv = NULL;
PFNGLUNIFORM4UIPROC glUniform4ui = NULL;
PFNGLUNIFORM4UIVPROC glUniform4uiv = NULL;
PFNGLVERTEXATTRIBI1IPROC glVertexAttribI1i = NULL;
PFNGLVERTEXATTRIBI1IVPROC glVertexAttribI1iv = NULL;
PFNGLVERTEXATTRIBI1UIPROC glVertexAttribI1ui = NULL;
PFNGLVERTEXATTRIBI1UIVPROC glVertexAttribI1uiv = NULL;
PFNGLVERTEXATTRIBI2IPROC glVertexAttribI2i = NULL;
PFNGLVERTEXATTRIBI2IVPROC glVertexAttribI2iv = NULL;
PFNGLVERTEXATTRIBI2UIPROC glVertexAttribI2ui = NULL;
PFNGLVERTEXATTRIBI2UIVPROC glVertexAttribI2uiv = NULL;
PFNGLVERTEXATTRIBI3IPROC glVertexAttribI3i = NULL;
PFNGLVERTEXATTRIBI3IVPROC glVertexAttribI3iv = NULL;
PFNGLVERTEXATTRIBI3UIPROC glVertexAttribI3ui = NULL;
PFNGLVERTEXATTRIBI3UIVPROC glVertexAttribI3uiv = NULL;
PFNGLVERTEXATTRIBI4BVPROC glVertexAttribI4bv = NULL;
PFNGLVERTEXATTRIBI4IPROC glVertexAttribI4i = NULL;
PFNGLVERTEXATTRIBI4IVPROC glVertexAttribI4iv = NULL;
PFNGLVERTEXATTRIBI4SVPROC glVertexAttribI4sv = NULL;
PFNGLVERTEXATTRIBI4UBVPROC glVertexAttribI4ubv = NULL;
PFNGLVERTEXATTRIBI4UIPROC glVertexAttribI4ui = NULL;
PFNGLVERTEXATTRIBI4UIVPROC glVertexAttribI4uiv = NULL;
PFNGLVERTEXATTRIBI4USVPROC glVertexAttribI4usv = NULL;
PFNGLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer = NULL;

PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstanced = NULL;
PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstanced = NULL;
PFNGLPRIMITIVERESTARTINDEXPROC glPrimitiveRestartIndex = NULL;
PFNGLTEXBUFFERPROC glTexBuffer = NULL;

PFNGLFRAMEBUFFERTEXTUREPROC glFramebufferTexture = NULL;
//PFNGLGETBUFFERPARAMETERI64VPROC glGetBufferParameteri64v = NULL;
//PFNGLGETINTEGER64I_VPROC glGetInteger64i_v = NULL;

PFNGLVERTEXATTRIBDIVISORPROC glVertexAttribDivisor = NULL;

PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;

float XeEngine::VideoFramework::GL::xglVersion()
{
	return (float)atof((const char*)glGetString(GL_VERSION));
}
void XeEngine::VideoFramework::GL::xglLoadLibraries()
{
	if (LibrariesLoaded == true)
		return;

	xglLoadLibrariesExtensions();
	if (!xglLoadLibraries12())
	{
		con.Log(DEBUG_LEVEL_WARNING, "No 1.2");
		//return;
	}
	if (!xglLoadLibraries13())
	{
		con.Log(DEBUG_LEVEL_WARNING, "No 1.3");
		//return;
	}
	if (!xglLoadLibraries14())
	{
		con.Log(DEBUG_LEVEL_WARNING, "No 1.4");
		//return;
	}
	if (!xglLoadLibraries15())
	{
		con.Log(DEBUG_LEVEL_WARNING, "No 1.5");
		//return;
	}
	if (!xglLoadLibraries20())
	{
		con.Log(DEBUG_LEVEL_WARNING, "No 2.0");
		//return;
	}
	if (!xglLoadLibraries21())
	{
		con.Log(DEBUG_LEVEL_WARNING, "No 2.1");
		//return;
	}
	if (!xglLoadLibraries30())
	{
		con.Log(DEBUG_LEVEL_WARNING, "No 3.0");
		//return;
	}
	if (!xglLoadLibraries31())
	{
		con.Log(DEBUG_LEVEL_WARNING, "No 3.1");
		//return;
	}
	if (!xglLoadLibraries32())
	{
		con.Log(DEBUG_LEVEL_WARNING, "No 3.2");
		//return;
	}
	if (!xglLoadLibraries33())
	{
		con.Log(DEBUG_LEVEL_WARNING, "No 3.3");
		//return;
	}

	LibrariesLoaded = true;
}
bool XeEngine::VideoFramework::GL::xglLoadLibraries12()
{
	GLboolean r = GL_FALSE;

	r = ((glCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3DPROC)xglGetProcAddress((const GLchar*)"glCopyTexSubImage3D")) == NULL) || r;
	r = ((glDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC)xglGetProcAddress((const GLchar*)"glDrawRangeElements")) == NULL) || r;
	r = ((glTexImage3D = (PFNGLTEXIMAGE3DPROC)xglGetProcAddress((const GLchar*)"glTexImage3D")) == NULL) || r;
	r = ((glTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC)xglGetProcAddress((const GLchar*)"glTexSubImage3D")) == NULL) || r;

	return r == 0;
}
bool XeEngine::VideoFramework::GL::xglLoadLibraries13()
{
	GLboolean r = GL_FALSE;

	r = ((glActiveTexture = (PFNGLACTIVETEXTUREPROC)xglGetProcAddress((const GLchar*)"glActiveTexture")) == NULL) || r;
	r = ((glClientActiveTexture = (PFNGLCLIENTACTIVETEXTUREPROC)xglGetProcAddress((const GLchar*)"glClientActiveTexture")) == NULL) || r;
	r = ((glCompressedTexImage1D = (PFNGLCOMPRESSEDTEXIMAGE1DPROC)xglGetProcAddress((const GLchar*)"glCompressedTexImage1D")) == NULL) || r;
	r = ((glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)xglGetProcAddress((const GLchar*)"glCompressedTexImage2D")) == NULL) || r;
	r = ((glCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3DPROC)xglGetProcAddress((const GLchar*)"glCompressedTexImage3D")) == NULL) || r;
	r = ((glCompressedTexSubImage1D = (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)xglGetProcAddress((const GLchar*)"glCompressedTexSubImage1D")) == NULL) || r;
	r = ((glCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)xglGetProcAddress((const GLchar*)"glCompressedTexSubImage2D")) == NULL) || r;
	r = ((glCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)xglGetProcAddress((const GLchar*)"glCompressedTexSubImage3D")) == NULL) || r;
	r = ((glGetCompressedTexImage = (PFNGLGETCOMPRESSEDTEXIMAGEPROC)xglGetProcAddress((const GLchar*)"glGetCompressedTexImage")) == NULL) || r;
	r = ((glLoadTransposeMatrixd = (PFNGLLOADTRANSPOSEMATRIXDPROC)xglGetProcAddress((const GLchar*)"glLoadTransposeMatrixd")) == NULL) || r;
	r = ((glLoadTransposeMatrixf = (PFNGLLOADTRANSPOSEMATRIXFPROC)xglGetProcAddress((const GLchar*)"glLoadTransposeMatrixf")) == NULL) || r;
	r = ((glMultTransposeMatrixd = (PFNGLMULTTRANSPOSEMATRIXDPROC)xglGetProcAddress((const GLchar*)"glMultTransposeMatrixd")) == NULL) || r;
	r = ((glMultTransposeMatrixf = (PFNGLMULTTRANSPOSEMATRIXFPROC)xglGetProcAddress((const GLchar*)"glMultTransposeMatrixf")) == NULL) || r;
	r = ((glMultiTexCoord1d = (PFNGLMULTITEXCOORD1DPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord1d")) == NULL) || r;
	r = ((glMultiTexCoord1dv = (PFNGLMULTITEXCOORD1DVPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord1dv")) == NULL) || r;
	r = ((glMultiTexCoord1f = (PFNGLMULTITEXCOORD1FPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord1f")) == NULL) || r;
	r = ((glMultiTexCoord1fv = (PFNGLMULTITEXCOORD1FVPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord1fv")) == NULL) || r;
	r = ((glMultiTexCoord1i = (PFNGLMULTITEXCOORD1IPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord1i")) == NULL) || r;
	r = ((glMultiTexCoord1iv = (PFNGLMULTITEXCOORD1IVPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord1iv")) == NULL) || r;
	r = ((glMultiTexCoord1s = (PFNGLMULTITEXCOORD1SPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord1s")) == NULL) || r;
	r = ((glMultiTexCoord1sv = (PFNGLMULTITEXCOORD1SVPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord1sv")) == NULL) || r;
	r = ((glMultiTexCoord2d = (PFNGLMULTITEXCOORD2DPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord2d")) == NULL) || r;
	r = ((glMultiTexCoord2dv = (PFNGLMULTITEXCOORD2DVPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord2dv")) == NULL) || r;
	r = ((glMultiTexCoord2f = (PFNGLMULTITEXCOORD2FPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord2f")) == NULL) || r;
	r = ((glMultiTexCoord2fv = (PFNGLMULTITEXCOORD2FVPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord2fv")) == NULL) || r;
	r = ((glMultiTexCoord2i = (PFNGLMULTITEXCOORD2IPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord2i")) == NULL) || r;
	r = ((glMultiTexCoord2iv = (PFNGLMULTITEXCOORD2IVPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord2iv")) == NULL) || r;
	r = ((glMultiTexCoord2s = (PFNGLMULTITEXCOORD2SPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord2s")) == NULL) || r;
	r = ((glMultiTexCoord2sv = (PFNGLMULTITEXCOORD2SVPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord2sv")) == NULL) || r;
	r = ((glMultiTexCoord3d = (PFNGLMULTITEXCOORD3DPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord3d")) == NULL) || r;
	r = ((glMultiTexCoord3dv = (PFNGLMULTITEXCOORD3DVPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord3dv")) == NULL) || r;
	r = ((glMultiTexCoord3f = (PFNGLMULTITEXCOORD3FPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord3f")) == NULL) || r;
	r = ((glMultiTexCoord3fv = (PFNGLMULTITEXCOORD3FVPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord3fv")) == NULL) || r;
	r = ((glMultiTexCoord3i = (PFNGLMULTITEXCOORD3IPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord3i")) == NULL) || r;
	r = ((glMultiTexCoord3iv = (PFNGLMULTITEXCOORD3IVPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord3iv")) == NULL) || r;
	r = ((glMultiTexCoord3s = (PFNGLMULTITEXCOORD3SPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord3s")) == NULL) || r;
	r = ((glMultiTexCoord3sv = (PFNGLMULTITEXCOORD3SVPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord3sv")) == NULL) || r;
	r = ((glMultiTexCoord4d = (PFNGLMULTITEXCOORD4DPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord4d")) == NULL) || r;
	r = ((glMultiTexCoord4dv = (PFNGLMULTITEXCOORD4DVPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord4dv")) == NULL) || r;
	r = ((glMultiTexCoord4f = (PFNGLMULTITEXCOORD4FPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord4f")) == NULL) || r;
	r = ((glMultiTexCoord4fv = (PFNGLMULTITEXCOORD4FVPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord4fv")) == NULL) || r;
	r = ((glMultiTexCoord4i = (PFNGLMULTITEXCOORD4IPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord4i")) == NULL) || r;
	r = ((glMultiTexCoord4iv = (PFNGLMULTITEXCOORD4IVPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord4iv")) == NULL) || r;
	r = ((glMultiTexCoord4s = (PFNGLMULTITEXCOORD4SPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord4s")) == NULL) || r;
	r = ((glMultiTexCoord4sv = (PFNGLMULTITEXCOORD4SVPROC)xglGetProcAddress((const GLchar*)"glMultiTexCoord4sv")) == NULL) || r;
	r = ((glSampleCoverage = (PFNGLSAMPLECOVERAGEPROC)xglGetProcAddress((const GLchar*)"glSampleCoverage")) == NULL) || r;

	return r == 0;
}
bool XeEngine::VideoFramework::GL::xglLoadLibraries14()
{
	GLboolean r = GL_FALSE;

	r = ((glBlendColor = (PFNGLBLENDCOLORPROC)xglGetProcAddress((const GLchar*)"glBlendColor")) == NULL) || r;
	r = ((glBlendEquation = (PFNGLBLENDEQUATIONPROC)xglGetProcAddress((const GLchar*)"glBlendEquation")) == NULL) || r;
	r = ((glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)xglGetProcAddress((const GLchar*)"glBlendFuncSeparate")) == NULL) || r;
	r = ((glFogCoordPointer = (PFNGLFOGCOORDPOINTERPROC)xglGetProcAddress((const GLchar*)"glFogCoordPointer")) == NULL) || r;
	r = ((glFogCoordd = (PFNGLFOGCOORDDPROC)xglGetProcAddress((const GLchar*)"glFogCoordd")) == NULL) || r;
	r = ((glFogCoorddv = (PFNGLFOGCOORDDVPROC)xglGetProcAddress((const GLchar*)"glFogCoorddv")) == NULL) || r;
	r = ((glFogCoordf = (PFNGLFOGCOORDFPROC)xglGetProcAddress((const GLchar*)"glFogCoordf")) == NULL) || r;
	r = ((glFogCoordfv = (PFNGLFOGCOORDFVPROC)xglGetProcAddress((const GLchar*)"glFogCoordfv")) == NULL) || r;
	r = ((glMultiDrawArrays = (PFNGLMULTIDRAWARRAYSPROC)xglGetProcAddress((const GLchar*)"glMultiDrawArrays")) == NULL) || r;
	r = ((glMultiDrawElements = (PFNGLMULTIDRAWELEMENTSPROC)xglGetProcAddress((const GLchar*)"glMultiDrawElements")) == NULL) || r;
	r = ((glPointParameterf = (PFNGLPOINTPARAMETERFPROC)xglGetProcAddress((const GLchar*)"glPointParameterf")) == NULL) || r;
	r = ((glPointParameterfv = (PFNGLPOINTPARAMETERFVPROC)xglGetProcAddress((const GLchar*)"glPointParameterfv")) == NULL) || r;
	r = ((glPointParameteri = (PFNGLPOINTPARAMETERIPROC)xglGetProcAddress((const GLchar*)"glPointParameteri")) == NULL) || r;
	r = ((glPointParameteriv = (PFNGLPOINTPARAMETERIVPROC)xglGetProcAddress((const GLchar*)"glPointParameteriv")) == NULL) || r;
	r = ((glSecondaryColor3b = (PFNGLSECONDARYCOLOR3BPROC)xglGetProcAddress((const GLchar*)"glSecondaryColor3b")) == NULL) || r;
	r = ((glSecondaryColor3bv = (PFNGLSECONDARYCOLOR3BVPROC)xglGetProcAddress((const GLchar*)"glSecondaryColor3bv")) == NULL) || r;
	r = ((glSecondaryColor3d = (PFNGLSECONDARYCOLOR3DPROC)xglGetProcAddress((const GLchar*)"glSecondaryColor3d")) == NULL) || r;
	r = ((glSecondaryColor3dv = (PFNGLSECONDARYCOLOR3DVPROC)xglGetProcAddress((const GLchar*)"glSecondaryColor3dv")) == NULL) || r;
	r = ((glSecondaryColor3f = (PFNGLSECONDARYCOLOR3FPROC)xglGetProcAddress((const GLchar*)"glSecondaryColor3f")) == NULL) || r;
	r = ((glSecondaryColor3fv = (PFNGLSECONDARYCOLOR3FVPROC)xglGetProcAddress((const GLchar*)"glSecondaryColor3fv")) == NULL) || r;
	r = ((glSecondaryColor3i = (PFNGLSECONDARYCOLOR3IPROC)xglGetProcAddress((const GLchar*)"glSecondaryColor3i")) == NULL) || r;
	r = ((glSecondaryColor3iv = (PFNGLSECONDARYCOLOR3IVPROC)xglGetProcAddress((const GLchar*)"glSecondaryColor3iv")) == NULL) || r;
	r = ((glSecondaryColor3s = (PFNGLSECONDARYCOLOR3SPROC)xglGetProcAddress((const GLchar*)"glSecondaryColor3s")) == NULL) || r;
	r = ((glSecondaryColor3sv = (PFNGLSECONDARYCOLOR3SVPROC)xglGetProcAddress((const GLchar*)"glSecondaryColor3sv")) == NULL) || r;
	r = ((glSecondaryColor3ub = (PFNGLSECONDARYCOLOR3UBPROC)xglGetProcAddress((const GLchar*)"glSecondaryColor3ub")) == NULL) || r;
	r = ((glSecondaryColor3ubv = (PFNGLSECONDARYCOLOR3UBVPROC)xglGetProcAddress((const GLchar*)"glSecondaryColor3ubv")) == NULL) || r;
	r = ((glSecondaryColor3ui = (PFNGLSECONDARYCOLOR3UIPROC)xglGetProcAddress((const GLchar*)"glSecondaryColor3ui")) == NULL) || r;
	r = ((glSecondaryColor3uiv = (PFNGLSECONDARYCOLOR3UIVPROC)xglGetProcAddress((const GLchar*)"glSecondaryColor3uiv")) == NULL) || r;
	r = ((glSecondaryColor3us = (PFNGLSECONDARYCOLOR3USPROC)xglGetProcAddress((const GLchar*)"glSecondaryColor3us")) == NULL) || r;
	r = ((glSecondaryColor3usv = (PFNGLSECONDARYCOLOR3USVPROC)xglGetProcAddress((const GLchar*)"glSecondaryColor3usv")) == NULL) || r;
	r = ((glSecondaryColorPointer = (PFNGLSECONDARYCOLORPOINTERPROC)xglGetProcAddress((const GLchar*)"glSecondaryColorPointer")) == NULL) || r;
	r = ((glWindowPos2d = (PFNGLWINDOWPOS2DPROC)xglGetProcAddress((const GLchar*)"glWindowPos2d")) == NULL) || r;
	r = ((glWindowPos2dv = (PFNGLWINDOWPOS2DVPROC)xglGetProcAddress((const GLchar*)"glWindowPos2dv")) == NULL) || r;
	r = ((glWindowPos2f = (PFNGLWINDOWPOS2FPROC)xglGetProcAddress((const GLchar*)"glWindowPos2f")) == NULL) || r;
	r = ((glWindowPos2fv = (PFNGLWINDOWPOS2FVPROC)xglGetProcAddress((const GLchar*)"glWindowPos2fv")) == NULL) || r;
	r = ((glWindowPos2i = (PFNGLWINDOWPOS2IPROC)xglGetProcAddress((const GLchar*)"glWindowPos2i")) == NULL) || r;
	r = ((glWindowPos2iv = (PFNGLWINDOWPOS2IVPROC)xglGetProcAddress((const GLchar*)"glWindowPos2iv")) == NULL) || r;
	r = ((glWindowPos2s = (PFNGLWINDOWPOS2SPROC)xglGetProcAddress((const GLchar*)"glWindowPos2s")) == NULL) || r;
	r = ((glWindowPos2sv = (PFNGLWINDOWPOS2SVPROC)xglGetProcAddress((const GLchar*)"glWindowPos2sv")) == NULL) || r;
	r = ((glWindowPos3d = (PFNGLWINDOWPOS3DPROC)xglGetProcAddress((const GLchar*)"glWindowPos3d")) == NULL) || r;
	r = ((glWindowPos3dv = (PFNGLWINDOWPOS3DVPROC)xglGetProcAddress((const GLchar*)"glWindowPos3dv")) == NULL) || r;
	r = ((glWindowPos3f = (PFNGLWINDOWPOS3FPROC)xglGetProcAddress((const GLchar*)"glWindowPos3f")) == NULL) || r;
	r = ((glWindowPos3fv = (PFNGLWINDOWPOS3FVPROC)xglGetProcAddress((const GLchar*)"glWindowPos3fv")) == NULL) || r;
	r = ((glWindowPos3i = (PFNGLWINDOWPOS3IPROC)xglGetProcAddress((const GLchar*)"glWindowPos3i")) == NULL) || r;
	r = ((glWindowPos3iv = (PFNGLWINDOWPOS3IVPROC)xglGetProcAddress((const GLchar*)"glWindowPos3iv")) == NULL) || r;
	r = ((glWindowPos3s = (PFNGLWINDOWPOS3SPROC)xglGetProcAddress((const GLchar*)"glWindowPos3s")) == NULL) || r;
	r = ((glWindowPos3sv = (PFNGLWINDOWPOS3SVPROC)xglGetProcAddress((const GLchar*)"glWindowPos3sv")) == NULL) || r;

	return r == 0;
}
bool XeEngine::VideoFramework::GL::xglLoadLibraries15()
{
	GLboolean r = GL_FALSE;

	r = ((glBeginQuery = (PFNGLBEGINQUERYPROC)xglGetProcAddress((const GLchar*)"glBeginQuery")) == NULL) || r;
	r = ((glBindBuffer = (PFNGLBINDBUFFERPROC)xglGetProcAddress((const GLchar*)"glBindBuffer")) == NULL) || r;
	r = ((glBufferData = (PFNGLBUFFERDATAPROC)xglGetProcAddress((const GLchar*)"glBufferData")) == NULL) || r;
	r = ((glBufferSubData = (PFNGLBUFFERSUBDATAPROC)xglGetProcAddress((const GLchar*)"glBufferSubData")) == NULL) || r;
	r = ((glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)xglGetProcAddress((const GLchar*)"glDeleteBuffers")) == NULL) || r;
	r = ((glDeleteQueries = (PFNGLDELETEQUERIESPROC)xglGetProcAddress((const GLchar*)"glDeleteQueries")) == NULL) || r;
	r = ((glEndQuery = (PFNGLENDQUERYPROC)xglGetProcAddress((const GLchar*)"glEndQuery")) == NULL) || r;
	r = ((glGenBuffers = (PFNGLGENBUFFERSPROC)xglGetProcAddress((const GLchar*)"glGenBuffers")) == NULL) || r;
	r = ((glGenQueries = (PFNGLGENQUERIESPROC)xglGetProcAddress((const GLchar*)"glGenQueries")) == NULL) || r;
	r = ((glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC)xglGetProcAddress((const GLchar*)"glGetBufferParameteriv")) == NULL) || r;
	r = ((glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC)xglGetProcAddress((const GLchar*)"glGetBufferPointerv")) == NULL) || r;
	r = ((glGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC)xglGetProcAddress((const GLchar*)"glGetBufferSubData")) == NULL) || r;
	r = ((glGetQueryObjectiv = (PFNGLGETQUERYOBJECTIVPROC)xglGetProcAddress((const GLchar*)"glGetQueryObjectiv")) == NULL) || r;
	r = ((glGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIVPROC)xglGetProcAddress((const GLchar*)"glGetQueryObjectuiv")) == NULL) || r;
	r = ((glGetQueryiv = (PFNGLGETQUERYIVPROC)xglGetProcAddress((const GLchar*)"glGetQueryiv")) == NULL) || r;
	r = ((glIsBuffer = (PFNGLISBUFFERPROC)xglGetProcAddress((const GLchar*)"glIsBuffer")) == NULL) || r;
	r = ((glIsQuery = (PFNGLISQUERYPROC)xglGetProcAddress((const GLchar*)"glIsQuery")) == NULL) || r;
	r = ((glMapBuffer = (PFNGLMAPBUFFERPROC)xglGetProcAddress((const GLchar*)"glMapBuffer")) == NULL) || r;
	r = ((glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)xglGetProcAddress((const GLchar*)"glUnmapBuffer")) == NULL) || r;

	return r == 0;
}
bool XeEngine::VideoFramework::GL::xglLoadLibraries20()
{
	GLboolean r = GL_FALSE;

	r = ((glAttachShader = (PFNGLATTACHSHADERPROC)xglGetProcAddress((const GLchar*)"glAttachShader")) == NULL) || r;
	r = ((glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)xglGetProcAddress((const GLchar*)"glBindAttribLocation")) == NULL) || r;
	r = ((glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC)xglGetProcAddress((const GLchar*)"glBlendEquationSeparate")) == NULL) || r;
	r = ((glCompileShader = (PFNGLCOMPILESHADERPROC)xglGetProcAddress((const GLchar*)"glCompileShader")) == NULL) || r;
	r = ((glCreateProgram = (PFNGLCREATEPROGRAMPROC)xglGetProcAddress((const GLchar*)"glCreateProgram")) == NULL) || r;
	r = ((glCreateShader = (PFNGLCREATESHADERPROC)xglGetProcAddress((const GLchar*)"glCreateShader")) == NULL) || r;
	r = ((glDeleteProgram = (PFNGLDELETEPROGRAMPROC)xglGetProcAddress((const GLchar*)"glDeleteProgram")) == NULL) || r;
	r = ((glDeleteShader = (PFNGLDELETESHADERPROC)xglGetProcAddress((const GLchar*)"glDeleteShader")) == NULL) || r;
	r = ((glDetachShader = (PFNGLDETACHSHADERPROC)xglGetProcAddress((const GLchar*)"glDetachShader")) == NULL) || r;
	r = ((glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)xglGetProcAddress((const GLchar*)"glDisableVertexAttribArray")) == NULL) || r;
	r = ((glDrawBuffers = (PFNGLDRAWBUFFERSPROC)xglGetProcAddress((const GLchar*)"glDrawBuffers")) == NULL) || r;
	r = ((glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)xglGetProcAddress((const GLchar*)"glEnableVertexAttribArray")) == NULL) || r;
	r = ((glGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC)xglGetProcAddress((const GLchar*)"glGetActiveAttrib")) == NULL) || r;
	r = ((glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC)xglGetProcAddress((const GLchar*)"glGetActiveUniform")) == NULL) || r;
	r = ((glGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC)xglGetProcAddress((const GLchar*)"glGetAttachedShaders")) == NULL) || r;
	r = ((glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)xglGetProcAddress((const GLchar*)"glGetAttribLocation")) == NULL) || r;
	r = ((glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)xglGetProcAddress((const GLchar*)"glGetProgramInfoLog")) == NULL) || r;
	r = ((glGetProgramiv = (PFNGLGETPROGRAMIVPROC)xglGetProcAddress((const GLchar*)"glGetProgramiv")) == NULL) || r;
	r = ((glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)xglGetProcAddress((const GLchar*)"glGetShaderInfoLog")) == NULL) || r;
	r = ((glGetShaderSource = (PFNGLGETSHADERSOURCEPROC)xglGetProcAddress((const GLchar*)"glGetShaderSource")) == NULL) || r;
	r = ((glGetShaderiv = (PFNGLGETSHADERIVPROC)xglGetProcAddress((const GLchar*)"glGetShaderiv")) == NULL) || r;
	r = ((glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)xglGetProcAddress((const GLchar*)"glGetUniformLocation")) == NULL) || r;
	r = ((glGetUniformfv = (PFNGLGETUNIFORMFVPROC)xglGetProcAddress((const GLchar*)"glGetUniformfv")) == NULL) || r;
	r = ((glGetUniformiv = (PFNGLGETUNIFORMIVPROC)xglGetProcAddress((const GLchar*)"glGetUniformiv")) == NULL) || r;
	r = ((glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC)xglGetProcAddress((const GLchar*)"glGetVertexAttribPointerv")) == NULL) || r;
	r = ((glGetVertexAttribdv = (PFNGLGETVERTEXATTRIBDVPROC)xglGetProcAddress((const GLchar*)"glGetVertexAttribdv")) == NULL) || r;
	r = ((glGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC)xglGetProcAddress((const GLchar*)"glGetVertexAttribfv")) == NULL) || r;
	r = ((glGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC)xglGetProcAddress((const GLchar*)"glGetVertexAttribiv")) == NULL) || r;
	r = ((glIsProgram = (PFNGLISPROGRAMPROC)xglGetProcAddress((const GLchar*)"glIsProgram")) == NULL) || r;
	r = ((glIsShader = (PFNGLISSHADERPROC)xglGetProcAddress((const GLchar*)"glIsShader")) == NULL) || r;
	r = ((glLinkProgram = (PFNGLLINKPROGRAMPROC)xglGetProcAddress((const GLchar*)"glLinkProgram")) == NULL) || r;
	r = ((glShaderSource = (PFNGLSHADERSOURCEPROC)xglGetProcAddress((const GLchar*)"glShaderSource")) == NULL) || r;
	r = ((glStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEPROC)xglGetProcAddress((const GLchar*)"glStencilFuncSeparate")) == NULL) || r;
	r = ((glStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATEPROC)xglGetProcAddress((const GLchar*)"glStencilMaskSeparate")) == NULL) || r;
	r = ((glStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC)xglGetProcAddress((const GLchar*)"glStencilOpSeparate")) == NULL) || r;
	r = ((glUniform1f = (PFNGLUNIFORM1FPROC)xglGetProcAddress((const GLchar*)"glUniform1f")) == NULL) || r;
	r = ((glUniform1fv = (PFNGLUNIFORM1FVPROC)xglGetProcAddress((const GLchar*)"glUniform1fv")) == NULL) || r;
	r = ((glUniform1i = (PFNGLUNIFORM1IPROC)xglGetProcAddress((const GLchar*)"glUniform1i")) == NULL) || r;
	r = ((glUniform1iv = (PFNGLUNIFORM1IVPROC)xglGetProcAddress((const GLchar*)"glUniform1iv")) == NULL) || r;
	r = ((glUniform2f = (PFNGLUNIFORM2FPROC)xglGetProcAddress((const GLchar*)"glUniform2f")) == NULL) || r;
	r = ((glUniform2fv = (PFNGLUNIFORM2FVPROC)xglGetProcAddress((const GLchar*)"glUniform2fv")) == NULL) || r;
	r = ((glUniform2i = (PFNGLUNIFORM2IPROC)xglGetProcAddress((const GLchar*)"glUniform2i")) == NULL) || r;
	r = ((glUniform2iv = (PFNGLUNIFORM2IVPROC)xglGetProcAddress((const GLchar*)"glUniform2iv")) == NULL) || r;
	r = ((glUniform3f = (PFNGLUNIFORM3FPROC)xglGetProcAddress((const GLchar*)"glUniform3f")) == NULL) || r;
	r = ((glUniform3fv = (PFNGLUNIFORM3FVPROC)xglGetProcAddress((const GLchar*)"glUniform3fv")) == NULL) || r;
	r = ((glUniform3i = (PFNGLUNIFORM3IPROC)xglGetProcAddress((const GLchar*)"glUniform3i")) == NULL) || r;
	r = ((glUniform3iv = (PFNGLUNIFORM3IVPROC)xglGetProcAddress((const GLchar*)"glUniform3iv")) == NULL) || r;
	r = ((glUniform4f = (PFNGLUNIFORM4FPROC)xglGetProcAddress((const GLchar*)"glUniform4f")) == NULL) || r;
	r = ((glUniform4fv = (PFNGLUNIFORM4FVPROC)xglGetProcAddress((const GLchar*)"glUniform4fv")) == NULL) || r;
	r = ((glUniform4i = (PFNGLUNIFORM4IPROC)xglGetProcAddress((const GLchar*)"glUniform4i")) == NULL) || r;
	r = ((glUniform4iv = (PFNGLUNIFORM4IVPROC)xglGetProcAddress((const GLchar*)"glUniform4iv")) == NULL) || r;
	r = ((glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)xglGetProcAddress((const GLchar*)"glUniformMatrix2fv")) == NULL) || r;
	r = ((glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)xglGetProcAddress((const GLchar*)"glUniformMatrix3fv")) == NULL) || r;
	r = ((glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)xglGetProcAddress((const GLchar*)"glUniformMatrix4fv")) == NULL) || r;
	r = ((glUseProgram = (PFNGLUSEPROGRAMPROC)xglGetProcAddress((const GLchar*)"glUseProgram")) == NULL) || r;
	r = ((glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)xglGetProcAddress((const GLchar*)"glValidateProgram")) == NULL) || r;
	r = ((glVertexAttrib1d = (PFNGLVERTEXATTRIB1DPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib1d")) == NULL) || r;
	r = ((glVertexAttrib1dv = (PFNGLVERTEXATTRIB1DVPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib1dv")) == NULL) || r;
	r = ((glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib1f")) == NULL) || r;
	r = ((glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib1fv")) == NULL) || r;
	r = ((glVertexAttrib1s = (PFNGLVERTEXATTRIB1SPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib1s")) == NULL) || r;
	r = ((glVertexAttrib1sv = (PFNGLVERTEXATTRIB1SVPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib1sv")) == NULL) || r;
	r = ((glVertexAttrib2d = (PFNGLVERTEXATTRIB2DPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib2d")) == NULL) || r;
	r = ((glVertexAttrib2dv = (PFNGLVERTEXATTRIB2DVPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib2dv")) == NULL) || r;
	r = ((glVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib2f")) == NULL) || r;
	r = ((glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib2fv")) == NULL) || r;
	r = ((glVertexAttrib2s = (PFNGLVERTEXATTRIB2SPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib2s")) == NULL) || r;
	r = ((glVertexAttrib2sv = (PFNGLVERTEXATTRIB2SVPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib2sv")) == NULL) || r;
	r = ((glVertexAttrib3d = (PFNGLVERTEXATTRIB3DPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib3d")) == NULL) || r;
	r = ((glVertexAttrib3dv = (PFNGLVERTEXATTRIB3DVPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib3dv")) == NULL) || r;
	r = ((glVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib3f")) == NULL) || r;
	r = ((glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib3fv")) == NULL) || r;
	r = ((glVertexAttrib3s = (PFNGLVERTEXATTRIB3SPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib3s")) == NULL) || r;
	r = ((glVertexAttrib3sv = (PFNGLVERTEXATTRIB3SVPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib3sv")) == NULL) || r;
	r = ((glVertexAttrib4Nbv = (PFNGLVERTEXATTRIB4NBVPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib4Nbv")) == NULL) || r;
	r = ((glVertexAttrib4Niv = (PFNGLVERTEXATTRIB4NIVPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib4Niv")) == NULL) || r;
	r = ((glVertexAttrib4Nsv = (PFNGLVERTEXATTRIB4NSVPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib4Nsv")) == NULL) || r;
	r = ((glVertexAttrib4Nub = (PFNGLVERTEXATTRIB4NUBPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib4Nub")) == NULL) || r;
	r = ((glVertexAttrib4Nubv = (PFNGLVERTEXATTRIB4NUBVPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib4Nubv")) == NULL) || r;
	r = ((glVertexAttrib4Nuiv = (PFNGLVERTEXATTRIB4NUIVPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib4Nuiv")) == NULL) || r;
	r = ((glVertexAttrib4Nusv = (PFNGLVERTEXATTRIB4NUSVPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib4Nusv")) == NULL) || r;
	r = ((glVertexAttrib4bv = (PFNGLVERTEXATTRIB4BVPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib4bv")) == NULL) || r;
	r = ((glVertexAttrib4d = (PFNGLVERTEXATTRIB4DPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib4d")) == NULL) || r;
	r = ((glVertexAttrib4dv = (PFNGLVERTEXATTRIB4DVPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib4dv")) == NULL) || r;
	r = ((glVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib4f")) == NULL) || r;
	r = ((glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib4fv")) == NULL) || r;
	r = ((glVertexAttrib4iv = (PFNGLVERTEXATTRIB4IVPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib4iv")) == NULL) || r;
	r = ((glVertexAttrib4s = (PFNGLVERTEXATTRIB4SPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib4s")) == NULL) || r;
	r = ((glVertexAttrib4sv = (PFNGLVERTEXATTRIB4SVPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib4sv")) == NULL) || r;
	r = ((glVertexAttrib4ubv = (PFNGLVERTEXATTRIB4UBVPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib4ubv")) == NULL) || r;
	r = ((glVertexAttrib4uiv = (PFNGLVERTEXATTRIB4UIVPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib4uiv")) == NULL) || r;
	r = ((glVertexAttrib4usv = (PFNGLVERTEXATTRIB4USVPROC)xglGetProcAddress((const GLchar*)"glVertexAttrib4usv")) == NULL) || r;
	r = ((glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)xglGetProcAddress((const GLchar*)"glVertexAttribPointer")) == NULL) || r;

	return r == 0;
}
bool XeEngine::VideoFramework::GL::xglLoadLibraries21()
{
	GLboolean r = GL_FALSE;

	r = ((glUniformMatrix2x3fv = (PFNGLUNIFORMMATRIX2X3FVPROC)xglGetProcAddress((const GLchar*)"glUniformMatrix2x3fv")) == NULL) || r;
	r = ((glUniformMatrix2x4fv = (PFNGLUNIFORMMATRIX2X4FVPROC)xglGetProcAddress((const GLchar*)"glUniformMatrix2x4fv")) == NULL) || r;
	r = ((glUniformMatrix3x2fv = (PFNGLUNIFORMMATRIX3X2FVPROC)xglGetProcAddress((const GLchar*)"glUniformMatrix3x2fv")) == NULL) || r;
	r = ((glUniformMatrix3x4fv = (PFNGLUNIFORMMATRIX3X4FVPROC)xglGetProcAddress((const GLchar*)"glUniformMatrix3x4fv")) == NULL) || r;
	r = ((glUniformMatrix4x2fv = (PFNGLUNIFORMMATRIX4X2FVPROC)xglGetProcAddress((const GLchar*)"glUniformMatrix4x2fv")) == NULL) || r;
	r = ((glUniformMatrix4x3fv = (PFNGLUNIFORMMATRIX4X3FVPROC)xglGetProcAddress((const GLchar*)"glUniformMatrix4x3fv")) == NULL) || r;

	return r == 0;
}
bool XeEngine::VideoFramework::GL::xglLoadLibraries30()
{
	GLboolean r = GL_FALSE;

	r = ((glBeginConditionalRender = (PFNGLBEGINCONDITIONALRENDERPROC)xglGetProcAddress((const GLchar*)"glBeginConditionalRender")) == NULL) || r;
	r = ((glBeginTransformFeedback = (PFNGLBEGINTRANSFORMFEEDBACKPROC)xglGetProcAddress((const GLchar*)"glBeginTransformFeedback")) == NULL) || r;
	r = ((glBindFragDataLocation = (PFNGLBINDFRAGDATALOCATIONPROC)xglGetProcAddress((const GLchar*)"glBindFragDataLocation")) == NULL) || r;
	r = ((glClampColor = (PFNGLCLAMPCOLORPROC)xglGetProcAddress((const GLchar*)"glClampColor")) == NULL) || r;
	r = ((glClearBufferfi = (PFNGLCLEARBUFFERFIPROC)xglGetProcAddress((const GLchar*)"glClearBufferfi")) == NULL) || r;
	r = ((glClearBufferfv = (PFNGLCLEARBUFFERFVPROC)xglGetProcAddress((const GLchar*)"glClearBufferfv")) == NULL) || r;
	r = ((glClearBufferiv = (PFNGLCLEARBUFFERIVPROC)xglGetProcAddress((const GLchar*)"glClearBufferiv")) == NULL) || r;
	r = ((glClearBufferuiv = (PFNGLCLEARBUFFERUIVPROC)xglGetProcAddress((const GLchar*)"glClearBufferuiv")) == NULL) || r;
	r = ((glColorMaski = (PFNGLCOLORMASKIPROC)xglGetProcAddress((const GLchar*)"glColorMaski")) == NULL) || r;
	r = ((glDisablei = (PFNGLDISABLEIPROC)xglGetProcAddress((const GLchar*)"glDisablei")) == NULL) || r;
	r = ((glEnablei = (PFNGLENABLEIPROC)xglGetProcAddress((const GLchar*)"glEnablei")) == NULL) || r;
	r = ((glEndConditionalRender = (PFNGLENDCONDITIONALRENDERPROC)xglGetProcAddress((const GLchar*)"glEndConditionalRender")) == NULL) || r;
	r = ((glEndTransformFeedback = (PFNGLENDTRANSFORMFEEDBACKPROC)xglGetProcAddress((const GLchar*)"glEndTransformFeedback")) == NULL) || r;
	r = ((glGetBooleani_v = (PFNGLGETBOOLEANI_VPROC)xglGetProcAddress((const GLchar*)"glGetBooleani_v")) == NULL) || r;
	r = ((glGetFragDataLocation = (PFNGLGETFRAGDATALOCATIONPROC)xglGetProcAddress((const GLchar*)"glGetFragDataLocation")) == NULL) || r;
	r = ((glGetStringi = (PFNGLGETSTRINGIPROC)xglGetProcAddress((const GLchar*)"glGetStringi")) == NULL) || r;
	r = ((glGetTexParameterIiv = (PFNGLGETTEXPARAMETERIIVPROC)xglGetProcAddress((const GLchar*)"glGetTexParameterIiv")) == NULL) || r;
	r = ((glGetTexParameterIuiv = (PFNGLGETTEXPARAMETERIUIVPROC)xglGetProcAddress((const GLchar*)"glGetTexParameterIuiv")) == NULL) || r;
	r = ((glGetTransformFeedbackVarying = (PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)xglGetProcAddress((const GLchar*)"glGetTransformFeedbackVarying")) == NULL) || r;
	r = ((glGetUniformuiv = (PFNGLGETUNIFORMUIVPROC)xglGetProcAddress((const GLchar*)"glGetUniformuiv")) == NULL) || r;
	r = ((glGetVertexAttribIiv = (PFNGLGETVERTEXATTRIBIIVPROC)xglGetProcAddress((const GLchar*)"glGetVertexAttribIiv")) == NULL) || r;
	r = ((glGetVertexAttribIuiv = (PFNGLGETVERTEXATTRIBIUIVPROC)xglGetProcAddress((const GLchar*)"glGetVertexAttribIuiv")) == NULL) || r;
	r = ((glIsEnabledi = (PFNGLISENABLEDIPROC)xglGetProcAddress((const GLchar*)"glIsEnabledi")) == NULL) || r;
	r = ((glTexParameterIiv = (PFNGLTEXPARAMETERIIVPROC)xglGetProcAddress((const GLchar*)"glTexParameterIiv")) == NULL) || r;
	r = ((glTexParameterIuiv = (PFNGLTEXPARAMETERIUIVPROC)xglGetProcAddress((const GLchar*)"glTexParameterIuiv")) == NULL) || r;
	r = ((glTransformFeedbackVaryings = (PFNGLTRANSFORMFEEDBACKVARYINGSPROC)xglGetProcAddress((const GLchar*)"glTransformFeedbackVaryings")) == NULL) || r;
	r = ((glUniform1ui = (PFNGLUNIFORM1UIPROC)xglGetProcAddress((const GLchar*)"glUniform1ui")) == NULL) || r;
	r = ((glUniform1uiv = (PFNGLUNIFORM1UIVPROC)xglGetProcAddress((const GLchar*)"glUniform1uiv")) == NULL) || r;
	r = ((glUniform2ui = (PFNGLUNIFORM2UIPROC)xglGetProcAddress((const GLchar*)"glUniform2ui")) == NULL) || r;
	r = ((glUniform2uiv = (PFNGLUNIFORM2UIVPROC)xglGetProcAddress((const GLchar*)"glUniform2uiv")) == NULL) || r;
	r = ((glUniform3ui = (PFNGLUNIFORM3UIPROC)xglGetProcAddress((const GLchar*)"glUniform3ui")) == NULL) || r;
	r = ((glUniform3uiv = (PFNGLUNIFORM3UIVPROC)xglGetProcAddress((const GLchar*)"glUniform3uiv")) == NULL) || r;
	r = ((glUniform4ui = (PFNGLUNIFORM4UIPROC)xglGetProcAddress((const GLchar*)"glUniform4ui")) == NULL) || r;
	r = ((glUniform4uiv = (PFNGLUNIFORM4UIVPROC)xglGetProcAddress((const GLchar*)"glUniform4uiv")) == NULL) || r;
	r = ((glVertexAttribI1i = (PFNGLVERTEXATTRIBI1IPROC)xglGetProcAddress((const GLchar*)"glVertexAttribI1i")) == NULL) || r;
	r = ((glVertexAttribI1iv = (PFNGLVERTEXATTRIBI1IVPROC)xglGetProcAddress((const GLchar*)"glVertexAttribI1iv")) == NULL) || r;
	r = ((glVertexAttribI1ui = (PFNGLVERTEXATTRIBI1UIPROC)xglGetProcAddress((const GLchar*)"glVertexAttribI1ui")) == NULL) || r;
	r = ((glVertexAttribI1uiv = (PFNGLVERTEXATTRIBI1UIVPROC)xglGetProcAddress((const GLchar*)"glVertexAttribI1uiv")) == NULL) || r;
	r = ((glVertexAttribI2i = (PFNGLVERTEXATTRIBI2IPROC)xglGetProcAddress((const GLchar*)"glVertexAttribI2i")) == NULL) || r;
	r = ((glVertexAttribI2iv = (PFNGLVERTEXATTRIBI2IVPROC)xglGetProcAddress((const GLchar*)"glVertexAttribI2iv")) == NULL) || r;
	r = ((glVertexAttribI2ui = (PFNGLVERTEXATTRIBI2UIPROC)xglGetProcAddress((const GLchar*)"glVertexAttribI2ui")) == NULL) || r;
	r = ((glVertexAttribI2uiv = (PFNGLVERTEXATTRIBI2UIVPROC)xglGetProcAddress((const GLchar*)"glVertexAttribI2uiv")) == NULL) || r;
	r = ((glVertexAttribI3i = (PFNGLVERTEXATTRIBI3IPROC)xglGetProcAddress((const GLchar*)"glVertexAttribI3i")) == NULL) || r;
	r = ((glVertexAttribI3iv = (PFNGLVERTEXATTRIBI3IVPROC)xglGetProcAddress((const GLchar*)"glVertexAttribI3iv")) == NULL) || r;
	r = ((glVertexAttribI3ui = (PFNGLVERTEXATTRIBI3UIPROC)xglGetProcAddress((const GLchar*)"glVertexAttribI3ui")) == NULL) || r;
	r = ((glVertexAttribI3uiv = (PFNGLVERTEXATTRIBI3UIVPROC)xglGetProcAddress((const GLchar*)"glVertexAttribI3uiv")) == NULL) || r;
	r = ((glVertexAttribI4bv = (PFNGLVERTEXATTRIBI4BVPROC)xglGetProcAddress((const GLchar*)"glVertexAttribI4bv")) == NULL) || r;
	r = ((glVertexAttribI4i = (PFNGLVERTEXATTRIBI4IPROC)xglGetProcAddress((const GLchar*)"glVertexAttribI4i")) == NULL) || r;
	r = ((glVertexAttribI4iv = (PFNGLVERTEXATTRIBI4IVPROC)xglGetProcAddress((const GLchar*)"glVertexAttribI4iv")) == NULL) || r;
	r = ((glVertexAttribI4sv = (PFNGLVERTEXATTRIBI4SVPROC)xglGetProcAddress((const GLchar*)"glVertexAttribI4sv")) == NULL) || r;
	r = ((glVertexAttribI4ubv = (PFNGLVERTEXATTRIBI4UBVPROC)xglGetProcAddress((const GLchar*)"glVertexAttribI4ubv")) == NULL) || r;
	r = ((glVertexAttribI4ui = (PFNGLVERTEXATTRIBI4UIPROC)xglGetProcAddress((const GLchar*)"glVertexAttribI4ui")) == NULL) || r;
	r = ((glVertexAttribI4uiv = (PFNGLVERTEXATTRIBI4UIVPROC)xglGetProcAddress((const GLchar*)"glVertexAttribI4uiv")) == NULL) || r;
	r = ((glVertexAttribI4usv = (PFNGLVERTEXATTRIBI4USVPROC)xglGetProcAddress((const GLchar*)"glVertexAttribI4usv")) == NULL) || r;
	r = ((glVertexAttribIPointer = (PFNGLVERTEXATTRIBIPOINTERPROC)xglGetProcAddress((const GLchar*)"glVertexAttribIPointer")) == NULL) || r;

	return r == 0;
}
bool XeEngine::VideoFramework::GL::xglLoadLibraries31()
{
	GLboolean r = GL_FALSE;

	r = ((glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC)xglGetProcAddress((const GLchar*)"glDrawArraysInstanced")) == NULL) || r;
	r = ((glDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC)xglGetProcAddress((const GLchar*)"glDrawElementsInstanced")) == NULL) || r;
	r = ((glPrimitiveRestartIndex = (PFNGLPRIMITIVERESTARTINDEXPROC)xglGetProcAddress((const GLchar*)"glPrimitiveRestartIndex")) == NULL) || r;
	r = ((glTexBuffer = (PFNGLTEXBUFFERPROC)xglGetProcAddress((const GLchar*)"glTexBuffer")) == NULL) || r;

	return r == 0;
}
bool XeEngine::VideoFramework::GL::xglLoadLibraries32()
{
	GLboolean r = GL_FALSE;

	r = ((glFramebufferTexture = (PFNGLFRAMEBUFFERTEXTUREPROC)xglGetProcAddress((const GLchar*)"glFramebufferTexture")) == NULL) || r;
	//r = ((glGetBufferParameteri64v = (PFNGLGETBUFFERPARAMETERI64VPROC)glewGetProcAddress((const GLchar*)"glGetBufferParameteri64v")) == NULL) || r;
	//r = ((glGetInteger64i_v = (PFNGLGETINTEGER64I_VPROC)glewGetProcAddress((const GLchar*)"glGetInteger64i_v")) == NULL) || r;

	return r == 0;
}
bool XeEngine::VideoFramework::GL::xglLoadLibraries33()
{
	GLboolean r = GL_FALSE;

	r = ((glVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORPROC)xglGetProcAddress((const GLchar*)"glVertexAttribDivisor")) == NULL) || r;

	return r == 0;
}
bool XeEngine::VideoFramework::GL::xglLoadLibrariesExtensions()
{
	GLboolean r = GL_FALSE;

#ifdef PLATFORM_WINDOWS
	r = ((wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)xglGetProcAddress((const GLchar*)"wglSwapIntervalEXT")) == NULL) || r;
#endif

	return r == 0;
}
