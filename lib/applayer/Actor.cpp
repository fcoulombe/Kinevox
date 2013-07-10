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

#include "applayer/Actor.h"
#include "applayer/GCLApplication.h"

#include <script/ConfigLua.h>

using namespace GCL;

Actor::Actor(const char *name, const char *archetype)
	:mName(name),
	mTransform(true)
{
	std::string archFile(ARCHETYPE_PATH);
	archFile += archetype;
	archFile += ".arch";
	ConfigLua conf(archFile.c_str());
	PtrLuaTableIterator it = conf.GetTableIterator("Archetype.Components");
	while (!it->End())
	{
		const std::string componentName = it->GetKey();
		PtrLuaTableIterator compIt = it->GetTableIterator();
		std::pair<const char *, Component *> tempComponent = Component::CreateComponent(this, componentName, compIt );
		mComponentList.insert(tempComponent);
		(void)tempComponent;
		++(*it);
	}
	//we need post init phase since some component depend on other but cannot 
	//guarantee that they will be created at first init time
	for (auto it = mComponentList.begin(); it != mComponentList.end(); ++it)
	{
		Component *tempComponent = it->second;
		tempComponent->PostInit();
	}

	mParent = NULL;
	GCLApplication::RegisterRenderObject(this);
}

Actor::~Actor()
{
	for (auto it = mComponentList.begin(); it != mComponentList.end(); ++it)
	{
		Component *tempComponent = it->second;
		delete tempComponent;
	}
	mComponentList.clear();
	if (mParent)
	{
		mParent->RemoveChild(this);
	}
	GCLApplication::ReleaseRenderObject(this);
}

void GCL::Actor::RemoveChild( const Actor *child )
{
	auto it = std::find(mChilds.begin(), mChilds.end(), child);
	GCLAssert(it != mChilds.end());
	mChilds.erase(it);
}