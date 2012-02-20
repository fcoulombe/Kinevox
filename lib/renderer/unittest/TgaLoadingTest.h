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
#pragma once

#include <fstream>

#include <gcl/UnitTest.h>
#include <renderer/TextureResource.h>


#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <unistd.h>

#include <algorithm>
#include <ostream>  // NOLINT
#include <sstream>
#include <vector>


using namespace GCL;

namespace TgaLoadingTest
{
void Test();
void Test()
{
	TEST_START

	//tga uncompressed
	{
		const char *fullFileName = TEXTURE_PATH"mushroomtga.tga";
		std::fstream fp(fullFileName, std::fstream::binary|std::fstream::in);
		AssertMsg_Test( fp.good(), fullFileName);

		TextureResource::TextureData data;
		TextureResource::LoadTga(fp, data);
		fp.close();
		Assert_Test(data.imageData);
		Assert_Test(data.mBitdepth==8);
		Assert_Test(data.mBytePerPixel==4);
		Assert_Test(data.mWidth==512);
		Assert_Test(data.mHeight==512);
		TextureResource::Unload(data);
	}

	//tga compressed
	{
		const char *fullFileName =TEXTURE_PATH"mushroomcompressedtga.tga";
		std::fstream fp(fullFileName, std::fstream::binary|std::fstream::in);
		AssertMsg_Test( fp.good(), fullFileName);

		TextureResource::TextureData data;
		TextureResource::LoadTga(fp, data);
		fp.close();
		Assert_Test(data.imageData);
		Assert_Test(data.mBitdepth==8);
		Assert_Test(data.mBytePerPixel==4);
		Assert_Test(data.mWidth==512);
		Assert_Test(data.mHeight==512);
		TextureResource::Unload(data);
	}

	{
		std::fstream fp(TEXTURE_PATH"texture.raw", std::fstream::binary|std::fstream::in);
		AssertMsg_Test( fp.good(), TEXTURE_PATH"texture.raw");


		TextureResource::TextureData data;
		TextureResource::LoadRaw(fp, data);
		fp.close();
		Assert_Test(data.imageData);
		Assert_Test(data.mBitdepth==8);
		Assert_Test(data.mBytePerPixel==3);
		Assert_Test(data.mWidth==256);
		Assert_Test(data.mHeight==256);
		TextureResource::Unload(data);
	}

}
}
