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

#include <gcl/UnitTest.h>
#include <input/Input.h>

namespace GCL
{

class KinevoxTestCounter : public TestCounter
{
public:
	KinevoxTestCounter(const char *file)
	: TestCounter(file)
	{

	}

	~KinevoxTestCounter()
	{

	}

	bool mIsInteractive;
};

}


#define KINEVOX_TEST_START KinevoxTestCounter testCounter(__FILE__);
#define KINEVOX_TEST_LOOP_START \
size_t i=0;\
	bool isLooping = gTestConfig.mIsInteractive;\
while(i<2 || isLooping)\
{\
\


#define KINEVOX_TEST_LOOP_END 	\
	++i;\
Input::ProcessInput();\
if (Input::IsKeyUp(SDLK_ESCAPE))\
	isLooping = false;\
}\
\

