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

#include "renderer/Text2D.h"


using namespace GCL;

void Text2D::Render()
{
	GCLAssert(mTexture);

	WorldPoint2 topTextureCoord, bottomTextureCoord;

	topTextureCoord.x = 0.0;
	topTextureCoord.y = 0.0;
	bottomTextureCoord.x = 1.0;
	bottomTextureCoord.y = 1.0;
	const Texture &texture = *mTexture;
	texture.Bind();
	glBegin (GL_TRIANGLE_STRIP);
#if 0

	size_t width = texture.GetWidth();
	size_t height = texture.GetHeight();
	Real widthRatio = Real(width);
	Real heightRatio = Real(height);
	Real halfWidth = (widthRatio/2.0)*mScale.x;
	Real halfHeight = (heightRatio/2.0)*mScale.y;

	glTexCoord2f (bottomTextureCoord.x, topTextureCoord.y);
	glVertex3f (halfWidth+mPosition.x, -halfHeight+mPosition.y, 0.0);
	glTexCoord2f (topTextureCoord.x, topTextureCoord.y);
	glVertex3f (-halfWidth+mPosition.x, -halfHeight+mPosition.y, 0.0);
	glTexCoord2f (bottomTextureCoord.x, bottomTextureCoord.y);
	glVertex3f (halfWidth+mPosition.x, halfHeight+mPosition.y, 0.0);
	glTexCoord2f (topTextureCoord.x, bottomTextureCoord.y);
	glVertex3f (-halfWidth+mPosition.x, halfHeight+mPosition.y, 0.0);
#else
	glTexCoord2f (0.0, 0.0);
	glVertex3f (-1, -1, 0.0);
	glTexCoord2f (1.0, 0.0);
	glVertex3f (1, -1, 0.0);
	glTexCoord2f (0.0, 1.0);
	glVertex3f (-1, 1, 0.0);
	glTexCoord2f (1.0, 1.0);
	glVertex3f (1, 1, 0.0);
#endif
	glEnd ();
}
