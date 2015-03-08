#include "glextensions.h"


// OpenGL 1.0
PFNGLCLEARPROC glClear = NULL;
PFNGLCLEARCOLORPROC glClearColor = NULL;
PFNGLCLEARDEPTHPROC glClearDepth = NULL;
PFNGLTEXPARAMETERIPROC glTexParameteri = NULL;
PFNGLTEXIMAGE2DPROC glTexImage2D = NULL;
PFNGLCULLFACEPROC glCullFace = NULL;
PFNGLENABLEPROC glEnable = NULL;
PFNGLDEPTHFUNCPROC glDepthFunc = NULL;
PFNGLFRONTFACEPROC glFrontFace = NULL;

// OpenGL 1.1
PFNGLGENTEXTURESPROC glGenTextures = NULL;
PFNGLBINDTEXTUREPROC glBindTexture = NULL;
PFNGLDELETETEXTURESPROC glDeleteTextures = NULL;
PFNGLDRAWARRAYSPROC glDrawArrays = NULL;
PFNGLDRAWELEMENTSPROC glDrawElements = NULL;

// OpenGL 1.2
PFNGLBLENDCOLORPROC glBlendColor = NULL;
PFNGLBLENDEQUATIONPROC glBlendEquation = NULL;
PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElements = NULL;
PFNGLTEXIMAGE3DPROC glTexImage3D = NULL;
PFNGLTEXSUBIMAGE3DPROC glTexSubImage3D = NULL;
PFNGLCOPYTEXSUBIMAGE3DPROC glCopyTexSubImage3D = NULL;

// OpenGL 1.3
PFNGLACTIVETEXTUREPROC glActiveTexture = NULL;
PFNGLSAMPLECOVERAGEPROC glSampleCoverage = NULL;
PFNGLCOMPRESSEDTEXIMAGE3DPROC glCompressedTexImage3D = NULL;
PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D = NULL;
PFNGLCOMPRESSEDTEXIMAGE1DPROC glCompressedTexImage1D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glCompressedTexSubImage3D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC glCompressedTexSubImage1D = NULL;
PFNGLGETCOMPRESSEDTEXIMAGEPROC glGetCompressedTexImage = NULL;

// OpenGL 1.4
PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate = NULL;
PFNGLMULTIDRAWARRAYSPROC glMultiDrawArrays = NULL;
PFNGLMULTIDRAWELEMENTSPROC glMultiDrawElements = NULL;
PFNGLPOINTPARAMETERFPROC glPointParameterf = NULL;
PFNGLPOINTPARAMETERFVPROC glPointParameterfv = NULL;
PFNGLPOINTPARAMETERIPROC glPointParameteri = NULL;
PFNGLPOINTPARAMETERIVPROC glPointParameteriv = NULL;

// OpenGL 1.5
PFNGLGENQUERIESPROC glGenQueries = NULL;
PFNGLDELETEQUERIESPROC glDeleteQueries = NULL;
PFNGLISQUERYPROC glIsQuery = NULL;
PFNGLBEGINQUERYPROC glBeginQuery = NULL;
PFNGLENDQUERYPROC glEndQuery = NULL;
PFNGLGETQUERYIVPROC glGetQueryiv = NULL;
PFNGLGETQUERYOBJECTIVPROC glGetQueryObjectiv = NULL;
PFNGLGETQUERYOBJECTUIVPROC glGetQueryObjectuiv = NULL;
PFNGLBINDBUFFERPROC glBindBuffer = NULL;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = NULL;
PFNGLGENBUFFERSPROC glGenBuffers = NULL;
PFNGLISBUFFERPROC glIsBuffer = NULL;
PFNGLBUFFERDATAPROC glBufferData = NULL;
PFNGLBUFFERSUBDATAPROC glBufferSubData = NULL;
PFNGLGETBUFFERSUBDATAPROC glGetBufferSubData = NULL;
PFNGLMAPBUFFERPROC glMapBuffer = NULL;
PFNGLUNMAPBUFFERPROC glUnmapBuffer = NULL;
PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameteriv = NULL;
PFNGLGETBUFFERPOINTERVPROC glGetBufferPointerv = NULL;

// OpenGL 2.0
PFNGLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparate = NULL;
PFNGLDRAWBUFFERSPROC glDrawBuffers = NULL;
PFNGLSTENCILOPSEPARATEPROC glStencilOpSeparate = NULL;
PFNGLSTENCILFUNCSEPARATEPROC glStencilFuncSeparate = NULL;
PFNGLSTENCILMASKSEPARATEPROC glStencilMaskSeparate = NULL;
PFNGLATTACHSHADERPROC glAttachShader = NULL;
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation = NULL;
PFNGLCOMPILESHADERPROC glCompileShader = NULL;
PFNGLCREATEPROGRAMPROC glCreateProgram = NULL;
PFNGLCREATESHADERPROC glCreateShader = NULL;
PFNGLDELETEPROGRAMPROC glDeleteProgram = NULL;
PFNGLDELETESHADERPROC glDeleteShader = NULL;
PFNGLDETACHSHADERPROC glDetachShader = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = NULL;
PFNGLGETACTIVEATTRIBPROC glGetActiveAttrib = NULL;
PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform = NULL;
PFNGLGETATTACHEDSHADERSPROC glGetAttachedShaders = NULL;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation = NULL;
PFNGLGETPROGRAMIVPROC glGetProgramiv = NULL;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = NULL;
PFNGLGETSHADERIVPROC glGetShaderiv = NULL;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = NULL;
PFNGLGETSHADERSOURCEPROC glGetShaderSource = NULL;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = NULL;
PFNGLGETUNIFORMFVPROC glGetUniformfv = NULL;
PFNGLGETUNIFORMIVPROC glGetUniformiv = NULL;
PFNGLGETVERTEXATTRIBDVPROC glGetVertexAttribdv = NULL;
PFNGLGETVERTEXATTRIBFVPROC glGetVertexAttribfv = NULL;
PFNGLGETVERTEXATTRIBIVPROC glGetVertexAttribiv = NULL;
PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv = NULL;
PFNGLISPROGRAMPROC glIsProgram = NULL;
PFNGLISSHADERPROC glIsShader = NULL;
PFNGLLINKPROGRAMPROC glLinkProgram = NULL;
PFNGLSHADERSOURCEPROC glShaderSource = NULL;
PFNGLUSEPROGRAMPROC glUseProgram = NULL;
PFNGLUNIFORM1FPROC glUniform1f = NULL;
PFNGLUNIFORM2FPROC glUniform2f = NULL;
PFNGLUNIFORM3FPROC glUniform3f = NULL;
PFNGLUNIFORM4FPROC glUniform4f = NULL;
PFNGLUNIFORM1IPROC glUniform1i = NULL;
PFNGLUNIFORM2IPROC glUniform2i = NULL;
PFNGLUNIFORM3IPROC glUniform3i = NULL;
PFNGLUNIFORM4IPROC glUniform4i = NULL;
PFNGLUNIFORM1FVPROC glUniform1fv = NULL;
PFNGLUNIFORM2FVPROC glUniform2fv = NULL;
PFNGLUNIFORM3FVPROC glUniform3fv = NULL;
PFNGLUNIFORM4FVPROC glUniform4fv = NULL;
PFNGLUNIFORM1IVPROC glUniform1iv = NULL;
PFNGLUNIFORM2IVPROC glUniform2iv = NULL;
PFNGLUNIFORM3IVPROC glUniform3iv = NULL;
PFNGLUNIFORM4IVPROC glUniform4iv = NULL;
PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv = NULL;
PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv = NULL;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = NULL;
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

// OpenGL 2.1
PFNGLUNIFORMMATRIX2X3FVPROC glUniformMatrix2x3fv = NULL;
PFNGLUNIFORMMATRIX3X2FVPROC glUniformMatrix3x2fv = NULL;
PFNGLUNIFORMMATRIX2X4FVPROC glUniformMatrix2x4fv = NULL;
PFNGLUNIFORMMATRIX4X2FVPROC glUniformMatrix4x2fv = NULL;
PFNGLUNIFORMMATRIX3X4FVPROC glUniformMatrix3x4fv = NULL;
PFNGLUNIFORMMATRIX4X3FVPROC glUniformMatrix4x3fv = NULL;

// OpenGL 3.0
PFNGLCOLORMASKIPROC glColorMaski = NULL;
PFNGLGETBOOLEANI_VPROC glGetBooleani_v = NULL;
PFNGLGETINTEGERI_VPROC glGetIntegeri_v = NULL;
PFNGLENABLEIPROC glEnablei = NULL;
PFNGLDISABLEIPROC glDisablei = NULL;
PFNGLISENABLEDIPROC glIsEnabledi = NULL;
PFNGLBEGINTRANSFORMFEEDBACKPROC glBeginTransformFeedback = NULL;
PFNGLENDTRANSFORMFEEDBACKPROC glEndTransformFeedback = NULL;
PFNGLBINDBUFFERRANGEPROC glBindBufferRange = NULL;
PFNGLBINDBUFFERBASEPROC glBindBufferBase = NULL;
PFNGLTRANSFORMFEEDBACKVARYINGSPROC glTransformFeedbackVaryings = NULL;
PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glGetTransformFeedbackVarying = NULL;
PFNGLCLAMPCOLORPROC glClampColor = NULL;
PFNGLBEGINCONDITIONALRENDERPROC glBeginConditionalRender = NULL;
PFNGLENDCONDITIONALRENDERPROC glEndConditionalRender = NULL;
PFNGLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer = NULL;
PFNGLGETVERTEXATTRIBIIVPROC glGetVertexAttribIiv = NULL;
PFNGLGETVERTEXATTRIBIUIVPROC glGetVertexAttribIuiv = NULL;
PFNGLVERTEXATTRIBI1IPROC glVertexAttribI1i = NULL;
PFNGLVERTEXATTRIBI2IPROC glVertexAttribI2i = NULL;
PFNGLVERTEXATTRIBI3IPROC glVertexAttribI3i = NULL;
PFNGLVERTEXATTRIBI4IPROC glVertexAttribI4i = NULL;
PFNGLVERTEXATTRIBI1UIPROC glVertexAttribI1ui = NULL;
PFNGLVERTEXATTRIBI2UIPROC glVertexAttribI2ui = NULL;
PFNGLVERTEXATTRIBI3UIPROC glVertexAttribI3ui = NULL;
PFNGLVERTEXATTRIBI4UIPROC glVertexAttribI4ui = NULL;
PFNGLVERTEXATTRIBI1IVPROC glVertexAttribI1iv = NULL;
PFNGLVERTEXATTRIBI2IVPROC glVertexAttribI2iv = NULL;
PFNGLVERTEXATTRIBI3IVPROC glVertexAttribI3iv = NULL;
PFNGLVERTEXATTRIBI4IVPROC glVertexAttribI4iv = NULL;
PFNGLVERTEXATTRIBI1UIVPROC glVertexAttribI1uiv = NULL;
PFNGLVERTEXATTRIBI2UIVPROC glVertexAttribI2uiv = NULL;
PFNGLVERTEXATTRIBI3UIVPROC glVertexAttribI3uiv = NULL;
PFNGLVERTEXATTRIBI4UIVPROC glVertexAttribI4uiv = NULL;
PFNGLVERTEXATTRIBI4BVPROC glVertexAttribI4bv = NULL;
PFNGLVERTEXATTRIBI4SVPROC glVertexAttribI4sv = NULL;
PFNGLVERTEXATTRIBI4UBVPROC glVertexAttribI4ubv = NULL;
PFNGLVERTEXATTRIBI4USVPROC glVertexAttribI4usv = NULL;
PFNGLGETUNIFORMUIVPROC glGetUniformuiv = NULL;
PFNGLBINDFRAGDATALOCATIONPROC glBindFragDataLocation = NULL;
PFNGLGETFRAGDATALOCATIONPROC glGetFragDataLocation = NULL;
PFNGLUNIFORM1UIPROC glUniform1ui = NULL;
PFNGLUNIFORM2UIPROC glUniform2ui = NULL;
PFNGLUNIFORM3UIPROC glUniform3ui = NULL;
PFNGLUNIFORM4UIPROC glUniform4ui = NULL;
PFNGLUNIFORM1UIVPROC glUniform1uiv = NULL;
PFNGLUNIFORM2UIVPROC glUniform2uiv = NULL;
PFNGLUNIFORM3UIVPROC glUniform3uiv = NULL;
PFNGLUNIFORM4UIVPROC glUniform4uiv = NULL;
PFNGLTEXPARAMETERIIVPROC glTexParameterIiv = NULL;
PFNGLTEXPARAMETERIUIVPROC glTexParameterIuiv = NULL;
PFNGLGETTEXPARAMETERIIVPROC glGetTexParameterIiv = NULL;
PFNGLGETTEXPARAMETERIUIVPROC glGetTexParameterIuiv = NULL;
PFNGLCLEARBUFFERIVPROC glClearBufferiv = NULL;
PFNGLCLEARBUFFERUIVPROC glClearBufferuiv = NULL;
PFNGLCLEARBUFFERFVPROC glClearBufferfv = NULL;
PFNGLCLEARBUFFERFIPROC glClearBufferfi = NULL;
PFNGLGETSTRINGIPROC glGetStringi = NULL;

// OpenGL 3.1
PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstanced = NULL;
PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstanced = NULL;
PFNGLTEXBUFFERPROC glTexBuffer = NULL;
PFNGLPRIMITIVERESTARTINDEXPROC glPrimitiveRestartIndex = NULL;

// OpenGL 3.2
PFNGLGETINTEGER64I_VPROC glGetInteger64i_v = NULL;
PFNGLGETBUFFERPARAMETERI64VPROC glGetBufferParameteri64v = NULL;
PFNGLPROGRAMPARAMETERIPROC glProgramParameteri = NULL;
PFNGLFRAMEBUFFERTEXTUREPROC glFramebufferTexture = NULL;

//OpenGL 4.0 ??
PFNGLGENERATEMIPMAPPROC glGenerateMipmap = NULL;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = NULL;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray = NULL;
PFNGLUNIFORMBLOCKBINDINGPROC glUniformBlockBinding = NULL;
PFNGLGETACTIVEUNIFORMBLOCKIVPROC glGetActiveUniformBlockiv = NULL;
PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers = NULL;
PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer = NULL;
PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers = NULL;
PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D = NULL;
PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus = NULL;
PFNGLGETUNIFORMBLOCKINDEXPROC glGetUniformBlockIndex = NULL;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = NULL;
PFNGLGETPROGRAMINTERFACEIVPROC glGetProgramInterfaceiv = NULL;
PFNGLGETPROGRAMRESOURCEIVPROC glGetProgramResourceiv = NULL;
PFNGLGETPROGRAMRESOURCENAMEPROC glGetProgramResourceName = NULL;

#define GET_PROC_ADDRESS(NAME) \
    *((unsigned char**)&NAME) = (unsigned char*)context->resolve(#NAME);

void GLExt::init(Context *context)
{
    // OpenGL 1.1
    GET_PROC_ADDRESS(glClear);
    GET_PROC_ADDRESS(glClearColor);
    GET_PROC_ADDRESS(glClearDepth);
    GET_PROC_ADDRESS(glTexParameteri);
    GET_PROC_ADDRESS(glTexImage2D);
    GET_PROC_ADDRESS(glCullFace);
    GET_PROC_ADDRESS(glEnable);
    GET_PROC_ADDRESS(glDepthFunc);
    GET_PROC_ADDRESS(glFrontFace);

    // OpenGL 1.1
    GET_PROC_ADDRESS(glGenTextures);
    GET_PROC_ADDRESS(glBindTexture);
    GET_PROC_ADDRESS(glDeleteTextures);
    GET_PROC_ADDRESS(glDrawArrays);
    GET_PROC_ADDRESS(glDrawElements);

    // OpenGL 1.2
    GET_PROC_ADDRESS(glBlendColor)
    GET_PROC_ADDRESS(glBlendEquation)
    GET_PROC_ADDRESS(glDrawRangeElements)
    GET_PROC_ADDRESS(glTexImage3D)
    GET_PROC_ADDRESS(glTexSubImage3D)
    GET_PROC_ADDRESS(glCopyTexSubImage3D)

    // OpenGL 1.3
    GET_PROC_ADDRESS(glActiveTexture)
    GET_PROC_ADDRESS(glSampleCoverage)
    GET_PROC_ADDRESS(glCompressedTexImage3D)
    GET_PROC_ADDRESS(glCompressedTexImage2D)
    GET_PROC_ADDRESS(glCompressedTexImage1D)
    GET_PROC_ADDRESS(glCompressedTexSubImage3D)
    GET_PROC_ADDRESS(glCompressedTexSubImage2D)
    GET_PROC_ADDRESS(glCompressedTexSubImage1D)
    GET_PROC_ADDRESS(glGetCompressedTexImage)

    // OpenGL 1.4
    GET_PROC_ADDRESS(glBlendFuncSeparate)
    GET_PROC_ADDRESS(glMultiDrawArrays)
    GET_PROC_ADDRESS(glMultiDrawElements)
    GET_PROC_ADDRESS(glPointParameterf)
    GET_PROC_ADDRESS(glPointParameterfv)
    GET_PROC_ADDRESS(glPointParameteri)
    GET_PROC_ADDRESS(glPointParameteriv)

    // OpenGL 1.5
    GET_PROC_ADDRESS(glGenQueries)
    GET_PROC_ADDRESS(glDeleteQueries)
    GET_PROC_ADDRESS(glIsQuery)
    GET_PROC_ADDRESS(glBeginQuery)
    GET_PROC_ADDRESS(glEndQuery)
    GET_PROC_ADDRESS(glGetQueryiv)
    GET_PROC_ADDRESS(glGetQueryObjectiv)
    GET_PROC_ADDRESS(glGetQueryObjectuiv)
    GET_PROC_ADDRESS(glBindBuffer)
    GET_PROC_ADDRESS(glDeleteBuffers)
    GET_PROC_ADDRESS(glGenBuffers)
    GET_PROC_ADDRESS(glIsBuffer)
    GET_PROC_ADDRESS(glBufferData)
    GET_PROC_ADDRESS(glBufferSubData)
    GET_PROC_ADDRESS(glGetBufferSubData)
    GET_PROC_ADDRESS(glMapBuffer)
    GET_PROC_ADDRESS(glUnmapBuffer)
    GET_PROC_ADDRESS(glGetBufferParameteriv)
    GET_PROC_ADDRESS(glGetBufferPointerv)

    // OpenGL 2.0
    GET_PROC_ADDRESS(glBlendEquationSeparate)
    GET_PROC_ADDRESS(glDrawBuffers)
    GET_PROC_ADDRESS(glStencilOpSeparate)
    GET_PROC_ADDRESS(glStencilFuncSeparate)
    GET_PROC_ADDRESS(glStencilMaskSeparate)
    GET_PROC_ADDRESS(glAttachShader)
    GET_PROC_ADDRESS(glBindAttribLocation)
    GET_PROC_ADDRESS(glCompileShader)
    GET_PROC_ADDRESS(glCreateProgram)
    GET_PROC_ADDRESS(glCreateShader)
    GET_PROC_ADDRESS(glDeleteProgram)
    GET_PROC_ADDRESS(glDeleteShader)
    GET_PROC_ADDRESS(glDetachShader)
    GET_PROC_ADDRESS(glDisableVertexAttribArray)
    GET_PROC_ADDRESS(glEnableVertexAttribArray)
    GET_PROC_ADDRESS(glGetActiveAttrib)
    GET_PROC_ADDRESS(glGetActiveUniform)
    GET_PROC_ADDRESS(glGetAttachedShaders)
    GET_PROC_ADDRESS(glGetAttribLocation)
    GET_PROC_ADDRESS(glGetProgramiv)
    GET_PROC_ADDRESS(glGetProgramInfoLog)
    GET_PROC_ADDRESS(glGetShaderiv)
    GET_PROC_ADDRESS(glGetShaderInfoLog)
    GET_PROC_ADDRESS(glGetShaderSource)
    GET_PROC_ADDRESS(glGetUniformLocation)
    GET_PROC_ADDRESS(glGetUniformfv)
    GET_PROC_ADDRESS(glGetUniformiv)
    GET_PROC_ADDRESS(glGetVertexAttribdv)
    GET_PROC_ADDRESS(glGetVertexAttribfv)
    GET_PROC_ADDRESS(glGetVertexAttribiv)
    GET_PROC_ADDRESS(glGetVertexAttribPointerv)
    GET_PROC_ADDRESS(glIsProgram)
    GET_PROC_ADDRESS(glIsShader)
    GET_PROC_ADDRESS(glLinkProgram)
    GET_PROC_ADDRESS(glShaderSource)
    GET_PROC_ADDRESS(glUseProgram)
    GET_PROC_ADDRESS(glUniform1f)
    GET_PROC_ADDRESS(glUniform2f)
    GET_PROC_ADDRESS(glUniform3f)
    GET_PROC_ADDRESS(glUniform4f)
    GET_PROC_ADDRESS(glUniform1i)
    GET_PROC_ADDRESS(glUniform2i)
    GET_PROC_ADDRESS(glUniform3i)
    GET_PROC_ADDRESS(glUniform4i)
    GET_PROC_ADDRESS(glUniform1fv)
    GET_PROC_ADDRESS(glUniform2fv)
    GET_PROC_ADDRESS(glUniform3fv)
    GET_PROC_ADDRESS(glUniform4fv)
    GET_PROC_ADDRESS(glUniform1iv)
    GET_PROC_ADDRESS(glUniform2iv)
    GET_PROC_ADDRESS(glUniform3iv)
    GET_PROC_ADDRESS(glUniform4iv)
    GET_PROC_ADDRESS(glUniformMatrix2fv)
    GET_PROC_ADDRESS(glUniformMatrix3fv)
    GET_PROC_ADDRESS(glUniformMatrix4fv)
    GET_PROC_ADDRESS(glValidateProgram)
    GET_PROC_ADDRESS(glVertexAttrib1d)
    GET_PROC_ADDRESS(glVertexAttrib1dv)
    GET_PROC_ADDRESS(glVertexAttrib1f)
    GET_PROC_ADDRESS(glVertexAttrib1fv)
    GET_PROC_ADDRESS(glVertexAttrib1s)
    GET_PROC_ADDRESS(glVertexAttrib1sv)
    GET_PROC_ADDRESS(glVertexAttrib2d)
    GET_PROC_ADDRESS(glVertexAttrib2dv)
    GET_PROC_ADDRESS(glVertexAttrib2f)
    GET_PROC_ADDRESS(glVertexAttrib2fv)
    GET_PROC_ADDRESS(glVertexAttrib2s)
    GET_PROC_ADDRESS(glVertexAttrib2sv)
    GET_PROC_ADDRESS(glVertexAttrib3d)
    GET_PROC_ADDRESS(glVertexAttrib3dv)
    GET_PROC_ADDRESS(glVertexAttrib3f)
    GET_PROC_ADDRESS(glVertexAttrib3fv)
    GET_PROC_ADDRESS(glVertexAttrib3s)
    GET_PROC_ADDRESS(glVertexAttrib3sv)
    GET_PROC_ADDRESS(glVertexAttrib4Nbv)
    GET_PROC_ADDRESS(glVertexAttrib4Niv)
    GET_PROC_ADDRESS(glVertexAttrib4Nsv)
    GET_PROC_ADDRESS(glVertexAttrib4Nub)
    GET_PROC_ADDRESS(glVertexAttrib4Nubv)
    GET_PROC_ADDRESS(glVertexAttrib4Nuiv)
    GET_PROC_ADDRESS(glVertexAttrib4Nusv)
    GET_PROC_ADDRESS(glVertexAttrib4bv)
    GET_PROC_ADDRESS(glVertexAttrib4d)
    GET_PROC_ADDRESS(glVertexAttrib4dv)
    GET_PROC_ADDRESS(glVertexAttrib4f)
    GET_PROC_ADDRESS(glVertexAttrib4fv)
    GET_PROC_ADDRESS(glVertexAttrib4iv)
    GET_PROC_ADDRESS(glVertexAttrib4s)
    GET_PROC_ADDRESS(glVertexAttrib4sv)
    GET_PROC_ADDRESS(glVertexAttrib4ubv)
    GET_PROC_ADDRESS(glVertexAttrib4uiv)
    GET_PROC_ADDRESS(glVertexAttrib4usv)
    GET_PROC_ADDRESS(glVertexAttribPointer)

    // OpenGL 2.1
    GET_PROC_ADDRESS(glUniformMatrix2x3fv)
    GET_PROC_ADDRESS(glUniformMatrix3x2fv)
    GET_PROC_ADDRESS(glUniformMatrix2x4fv)
    GET_PROC_ADDRESS(glUniformMatrix4x2fv)
    GET_PROC_ADDRESS(glUniformMatrix3x4fv)
    GET_PROC_ADDRESS(glUniformMatrix4x3fv)

    // OpenGL 3.0
    GET_PROC_ADDRESS(glColorMaski)
    GET_PROC_ADDRESS(glGetBooleani_v)
    GET_PROC_ADDRESS(glGetIntegeri_v)
    GET_PROC_ADDRESS(glEnablei)
    GET_PROC_ADDRESS(glDisablei)
    GET_PROC_ADDRESS(glIsEnabledi)
    GET_PROC_ADDRESS(glBeginTransformFeedback)
    GET_PROC_ADDRESS(glEndTransformFeedback)
    GET_PROC_ADDRESS(glBindBufferRange)
    GET_PROC_ADDRESS(glBindBufferBase)
    GET_PROC_ADDRESS(glTransformFeedbackVaryings)
    GET_PROC_ADDRESS(glGetTransformFeedbackVarying)
    GET_PROC_ADDRESS(glClampColor)
    GET_PROC_ADDRESS(glBeginConditionalRender)
    GET_PROC_ADDRESS(glEndConditionalRender)
    GET_PROC_ADDRESS(glVertexAttribIPointer)
    GET_PROC_ADDRESS(glGetVertexAttribIiv)
    GET_PROC_ADDRESS(glGetVertexAttribIuiv)
    GET_PROC_ADDRESS(glVertexAttribI1i)
    GET_PROC_ADDRESS(glVertexAttribI2i)
    GET_PROC_ADDRESS(glVertexAttribI3i)
    GET_PROC_ADDRESS(glVertexAttribI4i)
    GET_PROC_ADDRESS(glVertexAttribI1ui)
    GET_PROC_ADDRESS(glVertexAttribI2ui)
    GET_PROC_ADDRESS(glVertexAttribI3ui)
    GET_PROC_ADDRESS(glVertexAttribI4ui)
    GET_PROC_ADDRESS(glVertexAttribI1iv)
    GET_PROC_ADDRESS(glVertexAttribI2iv)
    GET_PROC_ADDRESS(glVertexAttribI3iv)
    GET_PROC_ADDRESS(glVertexAttribI4iv)
    GET_PROC_ADDRESS(glVertexAttribI1uiv)
    GET_PROC_ADDRESS(glVertexAttribI2uiv)
    GET_PROC_ADDRESS(glVertexAttribI3uiv)
    GET_PROC_ADDRESS(glVertexAttribI4uiv)
    GET_PROC_ADDRESS(glVertexAttribI4bv)
    GET_PROC_ADDRESS(glVertexAttribI4sv)
    GET_PROC_ADDRESS(glVertexAttribI4ubv)
    GET_PROC_ADDRESS(glVertexAttribI4usv)
    GET_PROC_ADDRESS(glGetUniformuiv)
    GET_PROC_ADDRESS(glBindFragDataLocation)
    GET_PROC_ADDRESS(glGetFragDataLocation)
    GET_PROC_ADDRESS(glUniform1ui)
    GET_PROC_ADDRESS(glUniform2ui)
    GET_PROC_ADDRESS(glUniform3ui)
    GET_PROC_ADDRESS(glUniform4ui)
    GET_PROC_ADDRESS(glUniform1uiv)
    GET_PROC_ADDRESS(glUniform2uiv)
    GET_PROC_ADDRESS(glUniform3uiv)
    GET_PROC_ADDRESS(glUniform4uiv)
    GET_PROC_ADDRESS(glTexParameterIiv)
    GET_PROC_ADDRESS(glTexParameterIuiv)
    GET_PROC_ADDRESS(glGetTexParameterIiv)
    GET_PROC_ADDRESS(glGetTexParameterIuiv)
    GET_PROC_ADDRESS(glClearBufferiv)
    GET_PROC_ADDRESS(glClearBufferuiv)
    GET_PROC_ADDRESS(glClearBufferfv)
    GET_PROC_ADDRESS(glClearBufferfi)
    GET_PROC_ADDRESS(glGetStringi)

    // OpenGL 3.1
    GET_PROC_ADDRESS(glDrawArraysInstanced)
    GET_PROC_ADDRESS(glDrawElementsInstanced)
    GET_PROC_ADDRESS(glTexBuffer)
    GET_PROC_ADDRESS(glPrimitiveRestartIndex)

    // OpenGL 3.2
    GET_PROC_ADDRESS(glGetInteger64i_v)
    GET_PROC_ADDRESS(glGetBufferParameteri64v)
    GET_PROC_ADDRESS(glProgramParameteri)
    GET_PROC_ADDRESS(glFramebufferTexture)

    // OpenGL 4 ??
    GET_PROC_ADDRESS(glGenerateMipmap);
    GET_PROC_ADDRESS(glGenVertexArrays);
    GET_PROC_ADDRESS(glBindVertexArray);
    GET_PROC_ADDRESS(glUniformBlockBinding);
    GET_PROC_ADDRESS(glGetActiveUniformBlockiv);
    GET_PROC_ADDRESS(glGenFramebuffers);
    GET_PROC_ADDRESS(glBindFramebuffer);
    GET_PROC_ADDRESS(glDeleteFramebuffers);
    GET_PROC_ADDRESS(glFramebufferTexture2D);
    GET_PROC_ADDRESS(glCheckFramebufferStatus);
    GET_PROC_ADDRESS(glGetUniformBlockIndex);
    GET_PROC_ADDRESS(glDeleteVertexArrays);
    GET_PROC_ADDRESS(glGetProgramInterfaceiv);
    GET_PROC_ADDRESS(glGetProgramResourceiv);
    GET_PROC_ADDRESS(glGetProgramResourceName);
}