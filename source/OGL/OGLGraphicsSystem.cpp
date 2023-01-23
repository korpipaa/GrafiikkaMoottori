/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// "THE BEER-WARE LICENSE" (Revision 42):
/// <mikko.romppainen@kamk.fi> wrote this file.  As long as you retain this notice you
/// can do whatever you want with this stuff. If we meet some day, and you think
/// this stuff is worth it, you can buy me a beer in return. Mikko Romppainen.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#include <OGL/OGLGraphicsSystem.h>
#include <graphics/Window.h>
#include <initializer_list>
#include <cstdlib>
#include <core/Log.h>

namespace engine
{
	// Anonymous namespace for helper functions.
	namespace {
		GLuint LoadShader(GLenum type, const char *shaderSrc) {
			// Create the shader object
			GLuint shader = glCreateShader(type);
			if (shader == 0) return 0;

			// Load the shader source
			glShaderSource(shader, 1, &shaderSrc, NULL);
			// Compile the shader
			glCompileShader(shader);
			// Check the compile status
			GLint compiled;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
			if (!compiled) {
				GLint infoLen = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
				if (infoLen > 1) {
					char* infoLog = (char*)malloc(sizeof(char) * infoLen);
					glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
					LOGI("Error compiling shader:\n%s\n", infoLog);
					free(infoLog);
				}
				glDeleteShader(shader);
				return 0;
			}

			return shader;
		}

	}

	OGLShader::OGLShader(
		const std::string& strVertexShader,
		const std::string& strFragmentShader,
		const std::vector<std::string>& attribLocations)
		: m_programObject(0)
	{
		GLuint vertexShader;
		GLuint fragmentShader;		
		GLint linked;

		// Load the vertex/fragment shaders
		vertexShader = LoadShader(GL_VERTEX_SHADER, strVertexShader.c_str());
		fragmentShader = LoadShader(GL_FRAGMENT_SHADER, strFragmentShader.c_str());

		// Create the program object
		m_programObject = glCreateProgram();
		if (m_programObject == 0)	return;

		glAttachShader(m_programObject, vertexShader);
		glAttachShader(m_programObject, fragmentShader);

		// Bind attribute locatins
		for (size_t i = 0; i < attribLocations.size(); ++i) {
			glBindAttribLocation(m_programObject, i, attribLocations[i].c_str());
		}
		// Link the program
		glLinkProgram(m_programObject);

		// Check the link status
		glGetProgramiv(m_programObject, GL_LINK_STATUS, &linked);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		if (!linked)
		{
			GLint infoLen = 0;

			glGetProgramiv(m_programObject, GL_INFO_LOG_LENGTH, &infoLen);

			if (infoLen > 1)
			{
				char* infoLog = (char*)malloc(sizeof(char) * infoLen);

				glGetProgramInfoLog(m_programObject, infoLen, NULL, infoLog);
				LOGI("Error linking program:\n%s\n", infoLog);

				free(infoLog);
			}

			glDeleteProgram(m_programObject);
			m_programObject = 0;
			return;
		}
	}


	OGLShader::~OGLShader()
	{
		if (m_programObject != 0) {
			glDeleteProgram(m_programObject);
			m_programObject = 0;
		}
	}

	GLuint OGLShader::getUniformLocation(const char * const uniformName)
	{
		return glGetUniformLocation(m_programObject, uniformName);
	}


	void OGLShader::useShader() {
		// Use the program object
		if (m_programObject != 0) {
			glUseProgram(m_programObject);
		}
	}

	OGLGraphicsSystem::OGLGraphicsSystem(Window* window)
		: GraphicsSystem()
		, m_window(window)
		, m_active(false)
	{
		assert(window != 0);
		
		// Here specify the attributes of the desired configuration.
		// Below, we select an EGLConfig with at least 8 bits per color
		// component compatible with on-screen windows
		const EGLint attribs[] = {
				EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
				EGL_BLUE_SIZE, 8,
				EGL_GREEN_SIZE, 8,
				EGL_RED_SIZE, 8,
				EGL_ALPHA_SIZE, 8,
				EGL_DEPTH_SIZE, 16,
				EGL_NONE
		};
		EGLint w, h, format;
		EGLint numConfigs;
		EGLConfig config;
		m_eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);

		eglInitialize(m_eglDisplay, 0, 0);

		// Here, the application chooses the configuration it desires.
        // find the best match if possible, otherwise use the very first one
		eglChooseConfig(m_eglDisplay, attribs, nullptr, 0, &numConfigs);
		EGLConfig* supportedConfigs = new EGLConfig[numConfigs];
		assert(supportedConfigs);
		eglChooseConfig(m_eglDisplay, attribs, supportedConfigs, numConfigs, &numConfigs);
		assert(numConfigs);
		int i = 0;
		for (; i < numConfigs; i++)
		{
			EGLConfig& cfg = supportedConfigs[i];
			EGLint a;
		//	LOGI("EGL_CONFIG[%d]:", i);
			eglGetConfigAttrib(m_eglDisplay, cfg, EGL_RED_SIZE, &a);
		//	LOGI("  EGL_RED_SIZE: %d", a);
			eglGetConfigAttrib(m_eglDisplay, cfg, EGL_GREEN_SIZE, &a);
		//	LOGI("  EGL_GREEN_SIZE: %d", a);
			eglGetConfigAttrib(m_eglDisplay, cfg, EGL_BLUE_SIZE, &a);
		//	LOGI("  EGL_BLUE_SIZE: %d", a);
			eglGetConfigAttrib(m_eglDisplay, cfg, EGL_ALPHA_SIZE, &a);
		//	LOGI("  EGL_ALPHA_SIZE: %d", a);
			eglGetConfigAttrib(m_eglDisplay, cfg, EGL_DEPTH_SIZE, &a);
		//	LOGI("  EGL_DEPTH_SIZE: %d", a);
			eglGetConfigAttrib(m_eglDisplay, cfg, EGL_STENCIL_SIZE, &a);
		//	LOGI("  EGL_STENCIL_SIZE: %d", a);
			eglGetConfigAttrib(m_eglDisplay, cfg, EGL_SAMPLE_BUFFERS, &a);
		//	LOGI("  EGL_SAMPLE_BUFFERS: %d", a);
		}

		config = supportedConfigs[0];
		for (; i < numConfigs; i++)
		{
			EGLint r, g, b, d;
			EGLConfig& cfg = supportedConfigs[i];
			if (eglGetConfigAttrib(m_eglDisplay, cfg, EGL_RED_SIZE, &r) &&
				eglGetConfigAttrib(m_eglDisplay, cfg, EGL_GREEN_SIZE, &g) &&
				eglGetConfigAttrib(m_eglDisplay, cfg, EGL_BLUE_SIZE, &b) &&
				eglGetConfigAttrib(m_eglDisplay, cfg, EGL_DEPTH_SIZE, &d) &&
				r == 8 && g == 8 && b == 8 && d == 0 ) {

				config = supportedConfigs[i];
				break;
			}
		}
	
		// EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
        // guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
        // As soon as we picked a EGLConfig, we can safely reconfigure the
        // ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID.
		eglGetConfigAttrib(m_eglDisplay, config, EGL_NATIVE_VISUAL_ID, &format);
		m_eglSurface = eglCreateWindowSurface(m_eglDisplay, config, window->getNativeWindow(), NULL);
		EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };
		m_eglContext = eglCreateContext(m_eglDisplay, config, NULL, contextAttribs);

		if (eglMakeCurrent(m_eglDisplay, m_eglSurface, m_eglSurface, m_eglContext) == EGL_FALSE) {
			assert(0);//LOGW("Unable to eglMakeCurrent");
		}

		// Get size of the surface
		eglQuerySurface(m_eglDisplay, m_eglSurface, EGL_WIDTH, &w);
		eglQuerySurface(m_eglDisplay, m_eglSurface, EGL_HEIGHT, &h);
		window->setSize(w,h);

		LOGI("OpenGL information:");
		LOGI("  GL_VENDOR: %s", glGetString(GL_VENDOR));
		LOGI("  GL_RENDERER: %s", glGetString(GL_RENDERER));
		LOGI("  GL_VERSION: %s", glGetString(GL_VERSION));
		LOGI("  GL_EXTENSIONS: %s", glGetString(GL_EXTENSIONS));
		LOGI("Surface size: %dx%d", w, h);
		
		m_active = true;
	}


	OGLGraphicsSystem::~OGLGraphicsSystem()
	{
	}

	
	

	void OGLGraphicsSystem::clearScreen(float red, float green, float blue, bool setViewport)
	{
		// Sets wiewport and clears the screen by given color.
		if (setViewport)
			glViewport(0, 0, m_window->getWidth(), m_window->getHeight());
		glClearColor(red, green, blue, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	GLuint OGLGraphicsSystem::CreateShaderProgram(const std::string& strVertexShader,const std::string& strFragmentShader)
	{
		GLuint vertexShader;
		GLuint fragmentShader;
		vertexShader = LoadShader(GL_VERTEX_SHADER, strVertexShader.c_str());
		fragmentShader = LoadShader(GL_FRAGMENT_SHADER, strFragmentShader.c_str());

		// Create the program object
		GLuint m_programObject = glCreateProgram();
		glAttachShader(m_programObject, vertexShader);
		glAttachShader(m_programObject, fragmentShader);
		glBindAttribLocation(m_programObject, 0, "vPosition");
		glLinkProgram(m_programObject);
		return m_programObject;
	}
	
	
	void OGLGraphicsSystem::swapBuffers()
	{
		eglSwapBuffers(m_eglDisplay, m_eglSurface);
	}

	void OGLGraphicsSystem::drawTriangles(Shader* shader, Texture2D* texture ,float vertices[], float textureCoords[], int numvertices)
	{
		//Bind shader
		shader->useShader();

		//positions
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
		glEnableVertexAttribArray(0);

		//texture coordinates
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, textureCoords);
		glEnableVertexAttribArray(1);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->getTextureid());

		glUniform1i(shader->getUniformLocation("texture"), 0);

		//Draw vertex arrays as trangle.
		glDrawArrays(GL_TRIANGLES, 0, numvertices);
	}
}