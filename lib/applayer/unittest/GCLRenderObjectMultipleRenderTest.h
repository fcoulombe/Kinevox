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
#include <sstream>

#include <applayer/GCLApplication.h>
#include <applayer/GCLRenderObject.h>

#include <gcl/UnitTest.h>

using namespace GCL;
namespace GCLRenderObjectMultipleRenderTest
{


void Test()
{
	TEST_START

	GCLApplication::Initialize();
	{
	GCLRenderObject obj("TestObject");
	Assert_Test(GCLApplication::IsRegistered(obj));
	Assert_Test(obj.GetTransform() == Matrix44::IDENTITY);

	const WorldPoint3 position(0.0,0.0, -10.0);
	obj.SetPosition(position);
	Matrix44 positionTestMat(true); //identity
	positionTestMat.SetPosition(position);
	std::stringstream s;
	s<<positionTestMat << "\n==\n" << obj.GetTransform() << std::endl;
	AssertMsg_Test(positionTestMat == obj.GetTransform(), s.str().c_str());


	for (size_t i=0;i<100; ++i)
	{
	GCLApplication::Update();
	GCLApplication::Render();
	usleep(1);
	}
	}
	GCLApplication::Terminate();
}
}
