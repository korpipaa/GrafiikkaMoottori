#include "Texture2D.h"
#include <string>
#include "OGL/OGL.h"
#include <core/Object.h>


namespace engine
{

	Texture2D::Texture2D(int width, int height, int bytesPerPixel, const GLubyte*pixels)
		:Object()
		, m_textureId(0)
	{

		assert(bytesPerPixel == 3 || bytesPerPixel == 4);
		//Use tightly packed data
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// Generate a texture object
		glGenTextures(1, &m_textureId);

		// Bind the texture object
		glBindTexture(GL_TEXTURE_2D, m_textureId);

		// Load the texture
		GLuint fmt = bytesPerPixel == 3 ? GL_RGB : GL_RGB; //Format is either RGB or RGBA depending on bit depth
		glTexImage2D(GL_TEXTURE_2D, 0, fmt, width, width, 0, fmt, GL_UNSIGNED_BYTE, pixels);

		// Set the filtering mode
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}


	Texture2D::~Texture2D()
	{
	}
	void Texture2D::getTextureid()
	{
		return m_textureid;
	}

}