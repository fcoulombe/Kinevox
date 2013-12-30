/*
 * Copyright (C) 2013 by Francois Coulombe
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

#include "applayer/ScriptApi.h"
#include <script/ScriptResourceManager.h>
#include <script/Lua.h>
#include <gcl/Config.h>

using namespace GCL;

int KLog(lua_State * /*L*/);
int KLog(lua_State * L)
{
	const char *str = lua_tostring(L, 1);
	std::cout << "[Script] " << str << std::endl;
	return 1;
}

int KGetScreenWidth(lua_State * L)
{
	int width = Config::Instance().GetInt("DEFAULT_VIEWPORT_WIDTH");
	lua_pushinteger(L, width);
	return 1;
}

int KGetScreenHeight(lua_State * L)
{
	int height = Config::Instance().GetInt("DEFAULT_VIEWPORT_HEIGHT");
	lua_pushinteger(L, height);
	return 1;
}

static const luaL_Reg kinevoxExposedFunc[] = {
		{ "Log", KLog },
		{ "GetScreenWidth", KGetScreenWidth},
		{ "GetScreenHeight", KGetScreenHeight},
		{ NULL, NULL } };
int luaopen_kinevoxLib(lua_State * L) {
	luaL_newlib(L, kinevoxExposedFunc);
	return 1;
}

ScriptApi::ScriptApi() {
	ScriptResourceManager::Instance().ExposeModule("kinevox",
			luaopen_kinevoxLib);
}
