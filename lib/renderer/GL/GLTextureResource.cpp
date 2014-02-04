/*
 * Copyright (C) 2014 by Francois Coulombe
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

#include "renderer/GL/GLTextureResource.h"
#include "renderer/TextureResource.h"

#include <iostream>
#include <gcl/Assert.h>

using namespace GCL;
GLTextureResource::GLTextureResource( const TextureResource &textureRes )
: GPUResource(),
mTextureId((GLuint)-1),
mTextureUnit((GLuint)0)
{
	Initialize(textureRes);
}

GLTextureResource::~GLTextureResource()
{
	RenderPipe::SendCommandSync([&](){
	glBindTexture(GL_TEXTURE_2D, 0);  glErrorCheck();
	});
	delete mPBO;
	RenderPipe::SendCommandSync([&](){
	glDeleteTextures(1, &mTextureId); glErrorCheck();
	});
}
void GLTextureResource::Initialize(const TextureResource &resource )
{
	const PixelBuffer &data = resource.mTextureData.imageData;
	RenderPipe::SendCommand([&](){
	glGenTextures(1, &mTextureId); glErrorCheck();
	glBindTexture(GL_TEXTURE_2D, mTextureId);glErrorCheck();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);glErrorCheck();
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);glErrorCheck();
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);glErrorCheck();
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);glErrorCheck();
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);glErrorCheck();

	GCLAssert(BytesPerPixel[data.mBytesPerPixel-1]<= GL_RGBA);

	glTexImage2D(GL_TEXTURE_2D, 0, BytePerPixel[data.mBytesPerPixel-1],
		(GLsizei)data.mWidth, (GLsizei)data.mHeight, 0,BytesPerPixel[data.mBytesPerPixel-1],
		GL_UNSIGNED_BYTE, NULL);glErrorCheck();
	});
	mPBO = new GLPixelBufferHAL();

	RenderPipe::SendCommand([&](){
	if (data.mPixels)
	{
		mPBO->BindUnsafe();
		mPBO->PushDataUnsafe(data.mWidth, data.mHeight, data.mBytesPerPixel, data.mPixels);
		//push from pbo to texture
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, (GLsizei)data.mWidth,
			(GLsizei)data.mHeight, BytesPerPixel[data.mBytesPerPixel-1],
			GL_UNSIGNED_BYTE, 0);glErrorCheck();
		mPBO->UnBindUnsafe();
	}
	glGenerateMipmap(GL_TEXTURE_2D);glErrorCheck();
	});
}



const uint8_t *GLTextureResource::GetPixelBufferFromVRAM() const
{
	mPBO->Bind();
	uint8_t *buffer = mPBO->PullData(GetWidth(), GetHeight(), GetBytesPerPixel());
	mPBO->UnBind();
	return buffer;
}

const uint8_t *GLTextureResource::GetTextureFromVRAM() const
{
	Bind();
	uint8_t *data;

	RenderPipe::SendCommandSync([&](){
	GLint width, height, format;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &format);
	size_t bpp = (format == GL_RGB8)?3:4;
	size_t imageSize = width*height*bpp;

	data = new uint8_t[imageSize];
	memset(data, 0, imageSize);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);glErrorCheck();
	if (bpp == 3)
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, data);  
	else
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glErrorCheck();
	});
	return data;
}


