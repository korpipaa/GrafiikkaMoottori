#include "MVP.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>

namespace engine
{


	MVP::MVP()
	{
	}
	MVP::MVP(glm::mat4 _view, glm::mat4 _projection, glm::mat4 _model)
	{
		m_view = _view;
		m_projection = _projection;
		m_model = _model;
		m_mvp = m_model * m_view * m_projection;
	}
	MVP::~MVP()
	{
	}
	glm::mat4 MVP::getMVP()
	{
		return m_mvp;
	}
	glm::mat4 MVP::rotateModel(glm::vec3 rotation, float deltaTime)
	{
		m_model = glm::rotate(m_model, deltaTime, rotation);
		m_mvp = m_model * m_view * m_projection;
		return m_mvp;
	}
	glm::mat4 MVP::scaleModel(glm::vec3 scale)
	{
		m_model = glm::scale(m_model, scale);
		m_mvp = m_model * m_view * m_projection;
		return m_mvp;
	}
	
}
