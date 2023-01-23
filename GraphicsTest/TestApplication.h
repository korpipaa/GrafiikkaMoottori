/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// "THE BEER-WARE LICENSE" (Revision 42):
/// <mikko.romppainen@kamk.fi> wrote this file.  As long as you retain this notice you
/// can do whatever you want with this stuff. If we meet some day, and you think
/// this stuff is worth it, you can buy me a beer in return. Mikko Romppainen.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#ifndef _ENGINE_TEST_APPLICATION_H_
#define _ENGINE_TEST_APPLICATION_H_

#include <graphics/GraphicsApplication.h>
#include <core/Log.h>
#include "OGL/OGL.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <vector>
#include "graphics/GraphicsSystem.h"
#include "graphics/Texture2D.h"
#include <string>

namespace engine
{
	class Window;
	class GraphicsSystem;

		
	class TestApplication :
		public GraphicsApplication
	{
	public:
		TestApplication(Window* window, GraphicsSystem* graphics);
				
		~TestApplication();

		//Teht‰v‰ 3: Tekstuurin lis‰‰minen objektille----
		Texture2D* loadPic();

		//Texture2D * loadPic();

		//Teht‰v‰ 4: Tiedostojen lukeminen---------------
		std::string loadFile(const std::string& fileName);

		/// Updates application. Returns true, if application is running.
		virtual bool update(float deltaTime);
		
		/// Renders application.
		virtual void render(Window* window, GraphicsSystem* graphics);

	private:
		float						m_totalTime;
		GLuint					    m_programObject;
		
		/*std::vector<Shader*> m_shaders;
		std::vector<Texture2D*>m_textures;*/
		glm::mat4					m_view;
		glm::mat4					m_projection;
		glm::mat4					m_model;
		glm::mat4					m_model1;
	};

}

#endif

