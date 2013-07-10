/*
 * Copyright (C) 2011 by Francois Coulombe
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#include "renderer/GL/GLRenderer.h"

#include <sstream>

#include <3rdparty/OpenGL.h>
#include <gcl/Assert.h>
#include <gcl/StringUtil.h>

#include "renderer/Camera.h"
#include "renderer/Material.h"
#include "renderer/RenderObject.h"
#include "renderer/Text2D.h"
#include "renderer/GL/GLGPUProgram.h"
#include "renderer/GL/GLRenderUtils.h"
#include "renderer/GL/GLShader.h"
#include "renderer/GL/GLVertexBuffer.h"

#include <GL/wglext.h>
using namespace GCL;

void GLRenderer::Init3DState()
{
	glErrorCheck();
    glViewport(0,0,(GLsizei)mViewPort.GetWidth(),(GLsizei)mViewPort.GetHeight()); 
	glErrorCheck();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); glErrorCheck();
	glClearDepth(1.0); glErrorCheck();
	glDepthMask(GL_TRUE); glErrorCheck();
	glDepthFunc(GL_LESS); glErrorCheck();
	glEnable(GL_DEPTH_TEST); glErrorCheck();
	glDisable(GL_BLEND); glErrorCheck();

	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); glErrorCheck();
	

	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL); glErrorCheck();
}

GLRenderer::GLRenderer(size_t windowsHandle)
	:   mFov(45.0),
	mAspect(640.0/480.0),
	mNear(0.1),
	mFar(100.0),
	mModelView(true)
{
	mProjection.SetPerspective(mFov,mAspect,mNear,mFar);
	
	// remember the window handle (HWND)
	mhWnd = (HWND)windowsHandle;

	// get the device context (DC)
	mhDC = GetDC( mhWnd );
	GCLAssertMsg(mhDC, "Failed to get the device context");

	// set the pixel format for the DC
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory( &pfd, sizeof( pfd ) );
	pfd.nSize = sizeof( pfd );
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	int format = ChoosePixelFormat( mhDC, &pfd );
	BOOL wglRet = SetPixelFormat( mhDC, format, &pfd );
	HGLRC tempContext = wglCreateContext(mhDC); 
	wglRet = wglMakeCurrent(mhDC,tempContext);

#if USE_OPENGL3
	int attribs[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 2,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC) wglGetProcAddress("wglCreateContextAttribsARB");
	if(wglCreateContextAttribsARB != NULL)
	{
		mhRC = wglCreateContextAttribsARB(mhDC,0, attribs);
		wglMakeCurrent(NULL,NULL); 
		wglDeleteContext(tempContext);
		wglRet = wglMakeCurrent( mhDC, mhRC );
	}
	else
#endif
	{
		// fall back on normal context
		mhRC = tempContext;
	}
	// make it the current render context
	
#if ENABLE_GLEW
	glewExperimental=TRUE;
	GLenum err = glewInit();
	GCLAssertMsg(GLEW_OK == err, (const char *)glewGetErrorString(err));
	mGlewVersion = std::string((const char*)glewGetString(GLEW_VERSION));
	glGetError(); //glew generates an error that can be ignored. on 3.x+
	glErrorCheck();
#else
	mGlewVersion  = std::string("Unused");
#endif


	Init3DState();
	mVersion = std::string((const char*)glGetString(GL_VERSION)); glErrorCheck();
	mVendor = std::string((const char*)glGetString(GL_VENDOR));glErrorCheck();
	mRenderer = std::string((const char*)glGetString(GL_RENDERER));glErrorCheck();
	const char *ver = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);glErrorCheck();
	mShadingLanguageVersion = std::string(ver);
	char delim = ' ';

	GLint n, i;
	glGetIntegerv(GL_NUM_EXTENSIONS, &n);glErrorCheck();
	std::string extString;
	for (i = 0; i < n; i++)
	{
		const char *ex = (const char*)glGetStringi(GL_EXTENSIONS, i); glErrorCheck();
		extString = extString +ex;
		extString = extString + " ";
	}
	
	StringUtil::Explode(extString, mExtensions ,delim); 


}
GLRenderer::~GLRenderer()
{
	mExtensions.clear();
	wglMakeCurrent( NULL, NULL );
	wglDeleteContext( mhRC );
	ReleaseDC( mhWnd, mhDC );
}

bool GLRenderer::Update()
{
	return true;
}


void GLRenderer::PreRender()
{
	glClearColor(0.0, 0.0, 1.0, 0.0); glErrorCheck();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); glErrorCheck();
}
void GLRenderer::PostRender()
{
}


void GLRenderer::RenderState::SetTextureEnabled(bool isEnabled)
{
	if (isEnabled)
	{
		glEnable(GL_TEXTURE_2D); glErrorCheck();
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, 0);  glErrorCheck();
		glDisable(GL_TEXTURE_2D); glErrorCheck();
	}
}


Matrix44 GLRenderer::GetGLProjection()
{
    Matrix44 projectionMatrixd;
        Matrix44f projectionMatrix;
	glGetFloatv(GL_PROJECTION_MATRIX, (GLfloat*)&projectionMatrix);

	projectionMatrixd[0].x = projectionMatrix.m0.x;
	projectionMatrixd[0].y = projectionMatrix.m0.y;
	projectionMatrixd[0].z = projectionMatrix.m0.z;
	projectionMatrixd[0].w = projectionMatrix.m0.w;
	projectionMatrixd[1].x = projectionMatrix.m1.x;
	projectionMatrixd[1].y = projectionMatrix.m1.y;
	projectionMatrixd[1].z = projectionMatrix.m1.z;
	projectionMatrixd[1].w = projectionMatrix.m1.w;
	projectionMatrixd[2].x = projectionMatrix.m2.x;
	projectionMatrixd[2].y = projectionMatrix.m2.y;
	projectionMatrixd[2].z = projectionMatrix.m2.z;
	projectionMatrixd[2].w = projectionMatrix.m2.w;
	projectionMatrixd[3].x = projectionMatrix.m3.x;
	projectionMatrixd[3].y = projectionMatrix.m3.y;
	projectionMatrixd[3].z = projectionMatrix.m3.z;
	projectionMatrixd[3].w = projectionMatrix.m3.w;

	return projectionMatrixd;
}
Matrix44 GLRenderer::GetGLModelView()
{
    Matrix44 modelViewMatrixd;
	Matrix44f modelViewMatrix;
	glGetFloatv(GL_PROJECTION_MATRIX, (GLfloat*)&modelViewMatrix);
	
	modelViewMatrixd[0].x = modelViewMatrix.m0.x;
	modelViewMatrixd[0].y = modelViewMatrix.m0.y;
	modelViewMatrixd[0].z = modelViewMatrix.m0.z;
	modelViewMatrixd[0].w = modelViewMatrix.m0.w;
	modelViewMatrixd[1].x = modelViewMatrix.m1.x;
	modelViewMatrixd[1].y = modelViewMatrix.m1.y;
	modelViewMatrixd[1].z = modelViewMatrix.m1.z;
	modelViewMatrixd[1].w = modelViewMatrix.m1.w;
	modelViewMatrixd[2].x = modelViewMatrix.m2.x;
	modelViewMatrixd[2].y = modelViewMatrix.m2.y;
	modelViewMatrixd[2].z = modelViewMatrix.m2.z;
	modelViewMatrixd[2].w = modelViewMatrix.m2.w;
	modelViewMatrixd[3].x = modelViewMatrix.m3.x;
	modelViewMatrixd[3].y = modelViewMatrix.m3.y;
	modelViewMatrixd[3].z = modelViewMatrix.m3.z;
	modelViewMatrixd[3].w = modelViewMatrix.m3.w;
	return modelViewMatrixd;
}

void GLRenderer::SwapBuffer()
{
	SwapBuffers( mhDC );
}

void GCL::GLRenderer::SetProjection( const Camera *camera )
{
	mProjection.SetPerspective(camera->GetFov(),camera->GetAspectRatio(),camera->GetNear(),camera->GetFar());
	mModelView= Inverse(camera->GetTransform());
}
