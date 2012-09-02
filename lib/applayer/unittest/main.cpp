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
 */#include <iostream>

#include "GCLApplicationTest.h"
#include "GCLApplicationCameraTest.h"
#include "GCLRenderObjectTest.h"
#include "GCLRenderObjectWithMaterialTest.h"
#include "GCLRenderObjectMultipleRenderTest.h"
#include "GCLRenderTargetTest.h"
#include "GCLRenderObject2DTest.h"
#include "GCLText2DTest.h"

int main(int /*argc*/, char ** /*argv*/)
{
	try
	{
		GCLApplicationTest::Test();
		GCLApplicationCameraTest::Test();
		GCLRenderObjectTest::Test();
		GCLRenderTargetTest::Test();
		GCLRenderObjectWithMaterialTest::Test();
		GCLRenderObjectMultipleRenderTest::Test();
		GCLRenderObject2DTest::Test();
		GCLText2DTest::Test();
	}
	catch (GCLException &e)
	{
		std::stringstream str;
		str << "[FAILED] \n";
		std::string what = e.what();
		str << what;

		str << std::endl;
		std::string finalOutput;
		finalOutput = str.str();
		std::cerr << finalOutput;
		return -1;
	}
	catch (std::exception &e)
	{
		std::cerr << "[FAILED] " << e.what() << std::endl;
		return -1;
	}
	catch (...)
	{
		std::cerr << "[FAILED] not sure what happened" << std::endl;
	}

	return 0;
}
