#pragma once

#include <iostream>
#include <gcl/Assert.h>
#include <gcl/Point3.h>
#include "renderer/OpenGL.h"

namespace GCL
{

inline void DrawCube(const WorldPoint3 &position, Real size)
{
	const Real halfSize = size/2;
#if !defined(ES1) && !defined(ES2)
	glBegin(GL_QUADS);
	//front face
	glVertex3d(position.x-halfSize, position.y-halfSize, position.z+halfSize);
	glVertex3d(position.x+halfSize, position.y-halfSize, position.z+halfSize);
	glVertex3d(position.x+halfSize, position.y+halfSize, position.z+halfSize);
	glVertex3d(position.x-halfSize, position.y+halfSize, position.z+halfSize);

	//backface
	glVertex3d(position.x-halfSize, position.y-halfSize, position.z-halfSize);
	glVertex3d(position.x+halfSize, position.y-halfSize, position.z-halfSize);
	glVertex3d(position.x+halfSize, position.y+halfSize, position.z-halfSize);
	glVertex3d(position.x-halfSize, position.y+halfSize, position.z-halfSize);

	//bot face
	glVertex3d(position.x-halfSize, position.y-halfSize, position.z+halfSize);
	glVertex3d(position.x+halfSize, position.y-halfSize, position.z+halfSize);
	glVertex3d(position.x+halfSize, position.y-halfSize, position.z-halfSize);
	glVertex3d(position.x-halfSize, position.y-halfSize, position.z-halfSize);

	//top face
	glVertex3d(position.x-halfSize, position.y+halfSize, position.z+halfSize);
	glVertex3d(position.x+halfSize, position.y+halfSize, position.z+halfSize);
	glVertex3d(position.x+halfSize, position.y+halfSize, position.z-halfSize);
	glVertex3d(position.x-halfSize, position.y+halfSize, position.z-halfSize);

	//left face
	glVertex3d(position.x-halfSize, position.y+halfSize, position.z+halfSize);
	glVertex3d(position.x-halfSize, position.y+halfSize, position.z-halfSize);
	glVertex3d(position.x-halfSize, position.y-halfSize, position.z-halfSize);
	glVertex3d(position.x-halfSize, position.y-halfSize, position.z+halfSize);

	//right face
	glVertex3d(position.x+halfSize, position.y+halfSize, position.z+halfSize);
	glVertex3d(position.x+halfSize, position.y+halfSize, position.z-halfSize);
	glVertex3d(position.x+halfSize, position.y-halfSize, position.z-halfSize);
	glVertex3d(position.x+halfSize, position.y-halfSize, position.z+halfSize);
	glEnd();
#else
    
    GCLAssert(false, "TBD");
    
#endif
	glErrorCheck();

}

inline void WriteCube(WorldPoint3* cubeData, const WorldPoint3 &position, Real size)
{
	const Real halfSize = size/2;

	//front face
	*cubeData = WorldPoint3(position.x-halfSize, position.y-halfSize, position.z+halfSize); ++cubeData;
	*cubeData = WorldPoint3(position.x+halfSize, position.y-halfSize, position.z+halfSize); ++cubeData;
	*cubeData = WorldPoint3(position.x+halfSize, position.y+halfSize, position.z+halfSize); ++cubeData;
	*cubeData = WorldPoint3(position.x-halfSize, position.y+halfSize, position.z+halfSize); ++cubeData;

	//backface
	*cubeData = WorldPoint3(position.x-halfSize, position.y-halfSize, position.z-halfSize); ++cubeData;
	*cubeData = WorldPoint3(position.x+halfSize, position.y-halfSize, position.z-halfSize); ++cubeData;
	*cubeData = WorldPoint3(position.x+halfSize, position.y+halfSize, position.z-halfSize); ++cubeData;
	*cubeData = WorldPoint3(position.x-halfSize, position.y+halfSize, position.z-halfSize); ++cubeData;

	//bot face
	*cubeData = WorldPoint3(position.x-halfSize, position.y-halfSize, position.z+halfSize); ++cubeData;
	*cubeData = WorldPoint3(position.x+halfSize, position.y-halfSize, position.z+halfSize); ++cubeData;
	*cubeData = WorldPoint3(position.x+halfSize, position.y-halfSize, position.z-halfSize); ++cubeData;
	*cubeData = WorldPoint3(position.x-halfSize, position.y-halfSize, position.z-halfSize); ++cubeData;

	//top face
	*cubeData = WorldPoint3(position.x-halfSize, position.y+halfSize, position.z+halfSize); ++cubeData;
	*cubeData = WorldPoint3(position.x+halfSize, position.y+halfSize, position.z+halfSize); ++cubeData;
	*cubeData = WorldPoint3(position.x+halfSize, position.y+halfSize, position.z-halfSize); ++cubeData;
	*cubeData = WorldPoint3(position.x-halfSize, position.y+halfSize, position.z-halfSize); ++cubeData;

	//left face
	*cubeData = WorldPoint3(position.x-halfSize, position.y+halfSize, position.z+halfSize); ++cubeData;
	*cubeData = WorldPoint3(position.x-halfSize, position.y+halfSize, position.z-halfSize); ++cubeData;
	*cubeData = WorldPoint3(position.x-halfSize, position.y-halfSize, position.z-halfSize); ++cubeData;
	*cubeData = WorldPoint3(position.x-halfSize, position.y-halfSize, position.z+halfSize); ++cubeData;

	//right face
	*cubeData = WorldPoint3(position.x+halfSize, position.y+halfSize, position.z+halfSize);
	*cubeData = WorldPoint3(position.x+halfSize, position.y+halfSize, position.z-halfSize);
	*cubeData = WorldPoint3(position.x+halfSize, position.y-halfSize, position.z-halfSize);
	*cubeData = WorldPoint3(position.x+halfSize, position.y-halfSize, position.z+halfSize);


}

}
