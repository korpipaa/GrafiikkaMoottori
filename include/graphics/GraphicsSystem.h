/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// "THE BEER-WARE LICENSE" (Revision 42):
/// <mikko.romppainen@kamk.fi> wrote this file.  As long as you retain this notice you
/// can do whatever you want with this stuff. If we meet some day, and you think
/// this stuff is worth it, you can buy me a beer in return. Mikko Romppainen.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#ifndef _ENGINE_GRAPHICSSYSTEM_H_
#define _ENGINE_GRAPHICSSYSTEM_H_

#include <core/Object.h>
#include <stdint.h>
#include <string>
#include "OGL/OGL.h"

namespace engine
{
	class Texture2D;
	class Shader {
	public:
		Shader() {}
		virtual ~Shader() {}
		virtual void useShader() = 0;
		virtual GLuint getUniformLocation(const char* const uniformName) = 0;
		//getUniformLocation();

		
	};

	class GraphicsSystem :
		public Object
	{
	public:
		virtual GLuint CreateShaderProgram(const std::string& strVertexShader, const std::string& strFragmentShader) = 0;

		GraphicsSystem();
		virtual ~GraphicsSystem();
		// Clears the screen using given color
		virtual void clearScreen(float red, float green, float blue, bool setViewport) = 0;

		// Method for swapping backbuffer to screen.
		virtual void swapBuffers() = 0;

		//method for draw texture
		virtual void drawTriangles(Shader* shader, Texture2D* texture, float vertices[], float textureCoords[], int numvertices) = 0;
	};

}

#endif

