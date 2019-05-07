#ifndef __ZOpenGL_H__
#define __ZOpenGL_H__

#include "ZShader.hpp"
#include "Texture2D.hpp"
#include "IRenderLoop.h"

class ZOpenGL
{
public:
	static void init(IRenderLoop* iRenderLoop, int width, int height);
};

#endif