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

#include "renderer/Renderer.h"
#include "renderer/GPUProgram.h"

using namespace GCL;

void GCL::Renderer::Render( const RenderObjectList &renderObjectList )
{
	mCamera->Update();
	for (size_t i=0;  i<renderObjectList.size(); ++i)
	{
		const RenderObject *tempRenderObject = renderObjectList[i];
		const Material &tempMaterial = tempRenderObject->GetMaterial();
		tempMaterial.Bind();
		const Matrix44 &transform = tempRenderObject->GetTransform();
		GPUProgram *tempProgram = tempMaterial.GetShader();
		tempProgram->SetProjectionMatrix(mCamera->GetProjection());
		tempProgram->SetModelViewMatrix(mCamera->GetModelView()*transform);
		tempRenderObject->GetVBO().Render();
	}
	//RenderPipe::SendCommand(new RenderCommand(RENDERER_RENDER, &renderObjectList));
}
void GCL::Renderer::Render2D( const RenderObjectList &renderObjectList )
{
	Matrix44 ortho;
	ortho.SetOrtho(0.0, (Real)mViewPort.GetHeight(), (Real)mViewPort.GetWidth(), 0.0, -1.0, 1.0);
	for (size_t i=0;  i<renderObjectList.size(); ++i)
	{
		const RenderObject *tempRenderObject = renderObjectList[i];
		const Material &tempMaterial = tempRenderObject->GetMaterial();
		tempMaterial.Bind();
		const Matrix44 &transform = tempRenderObject->GetTransform();
		GPUProgram *tempProgram = tempMaterial.GetShader();
		tempProgram->SetProjectionMatrix(ortho);
		tempProgram->SetModelViewMatrix(Matrix44::IDENTITY*transform);
		tempRenderObject->GetVBO().Render();
	}
	//RenderPipe::SendCommand(new RenderCommand(RENDERER_RENDER, &renderObjectList));
}

template<typename VertexType>
void DrawNormals(const VertexData &data)
{
	std::vector<Point3<MeshReal> > normalLines;
	const VertexType *vertexData = (const VertexType *)(data.mVertexData); 
	for (size_t i=0; i<data.mVertexCount; ++i)
	{
		const VertexType &vertex = vertexData[i];
		normalLines.push_back(vertex.position);
		normalLines.push_back(vertex.position + (vertex.normal*0.5));
	}
	const VertexP *pos = (const VertexP *)(normalLines.data());
	VertexData lineData(pos, normalLines.size(), VertexP::GetComponentType());
	VertexBuffer buffer((const VertexP *)lineData.mVertexData, lineData.mVertexCount);
	buffer.Render(VBM_LINES);

}
