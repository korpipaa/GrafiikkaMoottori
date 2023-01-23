#include <core/Object.h>
#include <stdint.h>
#include <string>
#include "OGL/OGL.h"
#include <core/Object.h>
#include <graphics/GraphicsSystem.h>
#include <graphics/Window.h>

//#ifndef _ENGINE_OGL_H_
#define _ENGINE_OGL_H_

#pragma once
namespace engine
{

	class Texture2D :public Object
	{
	public:
		Texture2D(int width, int height, int bytesPerPixel, const GLubyte*pixels);
		~Texture2D();

		GLuint getTextureid();
		

		GLuint m_textureId;
	};

}