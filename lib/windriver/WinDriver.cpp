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

#include "input/Input.h"
#if 1

#include <algorithm>
#include <iostream>
#include <sstream>


#include <gcl/Assert.h>
#include <gcl/Point2.h>
#include <gcl/Rect.h>


namespace GCL
{
const size_t KEYS_STATE_ARRAY_SIZE = 350;
std::map<uint32_t, bool> Input::keys;
bool Input::isLMousedown = false;
size_t Input::mouseX=0;
size_t Input::mouseY=0;

size_t Input::GetMouseX()
{
	return mouseX;
}
size_t Input::GetMouseY()
{
	return mouseY;
}
bool Input::IsLMouseDown()
{
	return isLMousedown;
}
bool Input::IsKeyUp(uint32_t key)
{
	return keys[key];
}
void Input::ProcessInput()
{
	//memset(keys, 0, KEYS_STATE_ARRAY_SIZE);
	SDL_Event event;

	while ( SDL_PollEvent(&event) )
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			keys[event.key.keysym.sym] = true;
			break;
		case SDL_KEYUP:
			//printf("%d %s\n",event.key.keysym.sym, SDL_GetKeyName(event.key.keysym.sym));
			keys[event.key.keysym.sym] = false;

			break;
		case SDL_MOUSEMOTION:
			/*printf("Mouse moved by %d,%d to (%d,%d)\n",
						event.motion.xrel, event.motion.yrel,
						event.motion.x, event.motion.y);*/

			mouseX = event.button.x;
			mouseY = event.button.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			/*printf("Mouse button %d pressed at (%d,%d)\n",
						event.button.button, event.button.x, event.button.y);*/
			isLMousedown = true;

			mouseX = event.button.x;
			mouseY = event.button.y;
			break;
		case SDL_MOUSEBUTTONUP:
			/*printf("Mouse button %d pressed at (%d,%d)\n",
						event.button.button, event.button.x, event.button.y);*/
			isLMousedown = false;
			mouseX = event.button.x;
			mouseY = event.button.y;

			break;
		case SDL_QUIT:
			exit(0);
		}
	}
	if (mouseX>640)
	{
		mouseX -= 640;
	}

}


Point2<int> origin;
Point2<int> currentPos;
Rect<int> selection;
bool isSelectionStarted = false;
bool hasSelection = false;
const Rect<int> &Input::ProcessSelection()
{
	currentPos.x = GetMouseX();
	currentPos.y = GetMouseY();
	if (IsLMouseDown())
	{
		if (!isSelectionStarted)
		{
			//start picking
			origin = currentPos;
			selection.x = origin.x;
			selection.y = origin.y;
			selection.width = origin.x;
			selection.height = origin.y;

			printf("staret picking\n");
		}
		isSelectionStarted = true;
		selection.x = std::min(currentPos.x,origin.x);
		selection.y = std::min(currentPos.y,origin.y);
		selection.width = selection.x + std::abs(currentPos.x - origin.x);
		selection.height = selection.y + std::abs(currentPos.y - origin.y);

		selection.x = std::max( selection.x, 0 );
		selection.y = std::max( selection.y, 0 );
		selection.width = std::min( selection.width, 640);
		selection.height = std::min( selection.height, 480 );
		selection.width -= selection.x;
		selection.height -= selection.y;

	}
	else
	{
		if (isSelectionStarted)
		{
			printf("end picking\n");
			//end picking
			isSelectionStarted = false;
			hasSelection = true;
			/*selection.width = selection.x - currentPos.x;
			selection.height =selection.y -  currentPos.y;*/

		}
	}
	return selection;
}
}
#endif