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

#include <string>
#include <gcl/Point4.h>
#include "common/BufferWriter.h"
#include "common/StringTableData.h"


namespace GCL
{


struct MaterialData
{
	WorldPoint4 mDiffuse;
	WorldPoint4 mAmbient;
	WorldPoint4 mEmissive;
	Real mShininess;

	enum StringTableId
	{
		MATERIAL_NAME,
		TEXTURE_NAME
	};
	StringTableData mStringTable;
};

GCLINLINE BufferWriter & operator<<( BufferWriter& buffer, const MaterialData &materialData)
{
	buffer << materialData.mDiffuse;
	buffer << materialData.mAmbient;
	buffer << materialData.mEmissive;
	buffer << materialData.mStringTable;
	return buffer;
}
GCLINLINE std::ostream& operator<<( std::ostream& output, const MaterialData &materialData)
{

	output << materialData.mDiffuse<<std::endl;
	output << materialData.mAmbient<<std::endl;
	output << materialData.mEmissive<<std::endl;
	output << materialData.mStringTable<<std::endl;

	return output;
}
}
