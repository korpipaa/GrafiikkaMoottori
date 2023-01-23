#include <core/Object.h>
#include <stdint.h>
#include <string>
#include "OGL/OGL.h"
#include <core/Object.h>
#include <graphics/GraphicsSystem.h>
#include <graphics/Window.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#pragma once
namespace engine
{
	class MVP
	{
	public:
		MVP();
		MVP(glm::mat4 _view, glm::mat4 _projection, glm::mat4 _model);
		~MVP();
		glm::mat4 getMVP();
		glm::mat4 rotateModel(glm::vec3 rotation, float deltaTime);
		glm::mat4 scaleModel(glm::vec3 scale);
	private:
		glm::mat4 m_view;
		glm::mat4 m_projection;
		glm::mat4 m_model;
		glm::mat4 m_mvp;
	};

}