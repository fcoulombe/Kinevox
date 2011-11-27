#pragma once

#include <cstdlib>
#include <stdint.h>

#include "renderer/Camera.h"
#include "renderer/Renderer.h"
#include "renderer/ViewPort.h"


namespace GCL
{

class GLRenderer : public Renderer
{
public:
	GLRenderer();
	~GLRenderer();
	bool Update();
	virtual void Render(const RenderObjectList &renderObjectList);
	void Render(uint8_t *rgb_front, uint8_t *depth_front);
	void RenderExtra(uint8_t *rgb_front, size_t width, size_t height, size_t depth);


	void SetCamera(const Camera &camera) { mCamera = &camera; }

	const ViewPort &GetViewPort() const { return mViewPort; }

	uint32_t gl_depth_tex;
	uint32_t gl_rgb_tex;

	struct RenderState
	{
		void SetTextureEnabled(bool isEnabled);
	};
	RenderState mCurrentRenderState;


	const std::string &GetVendor() const { return mVendor; }
	const std::string &GetVersion() const { return mVersion; }
	const std::string &GetRenderer() const { return mRenderer; }
	const std::string &GetShadingLanguageVersion() const { return mShadingLanguageVersion; }
	const std::vector<std::string> &GetExtensions() const { return mExtensions; }

private:
	void Init3DState();
	void Init2DState();

	const Camera *mCamera;
	ViewPort mViewPort;

	std::string mVendor, mVersion,mRenderer, mShadingLanguageVersion;
	std::vector<std::string> mExtensions;




};
}
