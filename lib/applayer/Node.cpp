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

#include "applayer/Node.h"
#include <algorithm>


using namespace GCL;

void Node::DeleteChild( Node &child )
{
	auto it = std::find(mChilds.begin(), mChilds.end(), &child);
	GCLAssert(it != mChilds.end());
	mChilds.erase(it);
	child.SetParent(nullptr);
	delete &child;
}

void Node::DetachChild( Node &child )
{
	auto it = std::find(mChilds.begin(), mChilds.end(), &child);
	GCLAssert(it != mChilds.end());
	mChilds.erase(it);
	child.SetParent(nullptr);
}

GCL::Node::Node() 
	: mId((uint32_t)-1),
	mTransform(true)
{
	mParentNode = nullptr;
}

GCL::Node::Node( const NodeData *data, Node *parent /*= nullptr*/ ) 
	: mId(data->mId),
	mTransform(true)
{
	mParentNode = parent;
	mName = data->GetName();
	mTransform = data->GetTransform();
	uint32_t numChilds = data->GetNumChilds();
	for (size_t i=0; i<numChilds; ++i)
	{
		mChilds.push_back(new Node(data->GetChild(i), this));
	}
}

GCL::Node::Node( const std::string &name, Node *parent )
	: mId((uint32_t)-1),
	mTransform(true),
	mName(name)
{
	mParentNode = parent;
}

GCL::Node::~Node()
{
	if (mParentNode)
	{
		mParentNode->DetachChild(*this);
	}
	for (auto it = mChilds.begin(); it != mChilds.end(); ++it)
	{
		Node *tempNode = *it;
		tempNode->SetParent(nullptr);
		delete tempNode;
	}
	mChilds.clear();
}

void GCL::Node::SetOrientation( Real x,Real y,Real z )
{
	const WorldPoint4 backupPosition = mTransform[3];
	Matrix44 xRot;
	xRot.SetRotationX(x);
	Matrix44 yRot;
	yRot.SetRotationY(y);
	Matrix44 zRot;
	zRot.SetRotationZ(z);
	mTransform = xRot * yRot * zRot;

	mTransform.SetPosition(backupPosition);
}
