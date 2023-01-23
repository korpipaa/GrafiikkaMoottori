/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// "THE BEER-WARE LICENSE" (Revision 42):
/// <mikko.romppainen@kamk.fi> wrote this file.  As long as you retain this notice you
/// can do whatever you want with this stuff. If we meet some day, and you think
/// this stuff is worth it, you can buy me a beer in return. Mikko Romppainen.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#ifndef _ENGINE_OGLGRAPHICSSYSTEM_H_
#define _ENGINE_OGLGRAPHICSSYSTEM_H_

#include <graphics/GraphicsSystem.h>
#include <core/Ref.h>
#include <EGL/egl.h>
#include <OGL/OGL.h>
#include <vector> // std::vector
#include "graphics/Texture2D.h"

namespace engine
{
	class OGLShader :
		public Shader {
	public:
		OGLShader(
			const std::string& strVertexShader, 
			const std::string& strFragmentShader,
			const std::vector<std::string>& attribLocations);
		virtual ~OGLShader();
		virtual GLuint getUniformLocation(const char* const uniformName);
		virtual void useShader();

	private:
		GLuint m_programObject;
	};

	// Forward declare Window-class
	class Window;

	class OGLGraphicsSystem :
		public GraphicsSystem
	{
	public:

		// Creates new OpenGL ES 2.0 Graphics System binded to given window.
		OGLGraphicsSystem(Window* window);
		virtual ~OGLGraphicsSystem();

		virtual void clearScreen(float red, float green, float blue, bool setViewport);
		virtual GLuint CreateShaderProgram(const std::string& strVertexShader,const std::string& strFragmentShader);
		virtual void swapBuffers();

		void drawTriangles(Shader * shader,Texture2D* texture, float vertices[], float textureCoords[], int numvertices);

	private:
		engine::Ref<Window> m_window;	// Window where graphics is binded
		bool m_active;					// True-flag if all is okay.

		// Embedded OpenGLES member variables
		EGLDisplay m_eglDisplay; // Display object
		EGLContext m_eglContext; // Context object
		EGLSurface m_eglSurface; // Surface object
	};

}

#endif


