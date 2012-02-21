#include "renderer/Sprite.h"
#include <gcl/Assert.h>
#include <renderer/ResourceManagerConfig.h>
#include <renderer/Texture.h>

#include <fstream>

using namespace GCL;


Sprite::Sprite(const char *filename)
: mCurrentFrame(0),
  mIsPlaying(false)
{
	LoadSprite(filename);
}

void Sprite::LoadSprite(const char * filename)
{
	const std::string fullFileName(std::string(SPRITE_PATH) + std::string(filename) + std::string(".spr"));

	std::fstream fp(fullFileName, std::fstream::binary|std::fstream::in);
	GCLAssertMsg(fp.good(), fullFileName);
	fp.read((char*)&mHeader, sizeof(SpriteDataHeader));
	std::cout << "width: " << mHeader.width<<std::endl;
	std::cout << "height: " << mHeader.height<<std::endl;
	std::cout << "frame count: " << mHeader.frameCount<<std::endl;
	std::cout << "texture count: " << mHeader.textureCount<<std::endl;
	for (size_t i=0; i<mHeader.textureCount; ++i)
	{
		uint32_t strLen;
		fp.read((char*)&strLen, sizeof(uint32_t));

		char *buffer = (char*)alloca(strLen+1);
		fp.read(buffer, strLen+1);

		std::string fullFileName(TEXTURE_PATH);
		fullFileName += buffer;
		mTextureList.push_back(new Texture(fullFileName.c_str()));
	}
	fp.close();
}


void Sprite::Play()
{
	mIsPlaying = true;
}

void Sprite::Pause()
{
	mIsPlaying = false;
}

void Sprite::Rewind()
{
	mCurrentFrame = 0;
}


void Sprite::Update()
{
	++mCurrentFrame;
	if (mCurrentFrame>=mHeader.frameCount)
		mCurrentFrame = 0;
}

void Sprite::Render() const
{
	GCLAssert(mTextureList.size());
	//figure out what is the texture coordinate for our current frame

	const Texture &firstTexture = *(mTextureList[0]);
	size_t framePerWidth = firstTexture.GetWidth()/mHeader.width;
	size_t rowPerTexture = firstTexture.GetHeight()/mHeader.height;

	//size_t offset = mHeader.width*mCurrentFrame;
	size_t whatRow = mCurrentFrame/framePerWidth;
	size_t whatCol = mCurrentFrame%framePerWidth;
	size_t whatTexture = whatRow/rowPerTexture;
	//adjust the column to offset in the texture
	whatRow = whatRow- (whatTexture*rowPerTexture);

	WorldPoint2 topTextureCoord, bottomTextureCoord;
	Real widthRatio = mHeader.width/Real(firstTexture.GetWidth());
	Real heightRatio = mHeader.height/Real(firstTexture.GetHeight());
	topTextureCoord.x = whatCol*widthRatio;
	topTextureCoord.y = whatRow*heightRatio;
	bottomTextureCoord.x = topTextureCoord.x +widthRatio;
	bottomTextureCoord.y = topTextureCoord.y +heightRatio;

	//std::cout << "top " << topTextureCoord << std::endl;
	//std::cout << "bot " <<bottomTextureCoord << std::endl;

	mTextureList[whatTexture]->Bind();
	glBegin (GL_TRIANGLE_STRIP);
#if 1
	glTexCoord2f (topTextureCoord.x, topTextureCoord.y);
	glVertex3f (-0.5+mPosition.x, -0.5+mPosition.y, 0.0);
	glTexCoord2f (bottomTextureCoord.x, topTextureCoord.y);
	glVertex3f (0.5+mPosition.x, -0.5+mPosition.y, 0.0);
	glTexCoord2f (topTextureCoord.x, bottomTextureCoord.y);
	glVertex3f (-0.5+mPosition.x, 0.5+mPosition.y, 0.0);
	glTexCoord2f (bottomTextureCoord.x, bottomTextureCoord.y);
	glVertex3f (0.5+mPosition.x, 0.5+mPosition.y, 0.0);
#else
	glTexCoord2f (0.0, 0.0);
			glVertex3f (-0.5, -0.5, 0.0);
			glTexCoord2f (1.0, 0.0);
			glVertex3f (0.5, -0.5, 0.0);
			glTexCoord2f (0.0, 1.0);
			glVertex3f (-0.5, 0.5, 0.0);
			glTexCoord2f (1.0, 1.0);
			glVertex3f (0.5, 0.5, 0.0);

#endif
	glEnd ();

}
