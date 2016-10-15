#include <Engine.h>

namespace ENGINE_NAME {

	GLint GL3Texture::GetGLFilterMode(FilterMode& filter) {
		switch (filter) {
		case LINEAR:
			return GL_LINEAR;
		case NEAREST:
			return GL_NEAREST;
		default:
			std::cout << "Unknown Texture Filter!" << std::endl;
			return 0;
		}
	}

	GLint GL3Texture::GetGLWrapMode(WrapMode& wrap) {
		switch (wrap) {
		case REPEAT:
			return GL_REPEAT;
		case CLAMP:
			return GL_CLAMP;
		case MIRRORED_REPEAT:
			return GL_MIRRORED_REPEAT;
		case CLAMP_TO_EDGE:
			return GL_CLAMP_TO_EDGE;
		case CLAMP_TO_BORDER:
			return GL_CLAMP_TO_BORDER;
		default:
			std::cout << "Unknown Texture Wrap!" << std::endl;
			return 0;
		}
	}

	void GL3Texture::Initialize(uint width, uint height, FilterMode filterMode, WrapMode wrapMode, float* pixels, uint bits) {
		m_bits = bits;
		m_width = width;
		m_height = height;
		GLenum err = GL_NO_ERROR;
		if ((err = glGetError()) != GL_NO_ERROR) std::cout << "GLerror: " << err << " " << gluErrorString(err) << std::endl;
		GLCall(glGenTextures(1, &m_tID));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_tID));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GetGLFilterMode(filterMode)));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GetGLFilterMode(filterMode)));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GetGLWrapMode(wrapMode)));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GetGLWrapMode(wrapMode)));

		if (m_bits != 24 && m_bits != 32 && m_bits != 8)
			std::cout << "[Texture] Unsupported image bit-depth! (" << m_bits << ")" << std::endl;

		GLint internalFormat = m_bits == 32 ? GL_RGBA : m_bits == 24 ? GL_RGB : GL_RED;
		GLenum format = m_bits == 32 ? GL_BGRA : m_bits == 24 ? GL_BGR : GL_RED;
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, format, GL_FLOAT, pixels ? pixels : NULL));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}

	void GL3Texture::Initialize(uint width, uint height, FilterMode filterMode, WrapMode wrapMode, char* pixels, uint bits) {
		m_bits = bits;
		m_width = width;
		m_height = height;
		GLenum err = GL_NO_ERROR;
		if ((err = glGetError()) != GL_NO_ERROR) std::cout << "GLerror: " << err << " " << gluErrorString(err) << std::endl;
		GLCall(glGenTextures(1, &m_tID));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_tID));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GetGLFilterMode(filterMode)));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GetGLFilterMode(filterMode)));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GetGLWrapMode(wrapMode)));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GetGLWrapMode(wrapMode)));

		if (m_bits != 24 && m_bits != 32 && m_bits != 8)
			std::cout << "[Texture] Unsupported image bit-depth! (" << m_bits << ")" << std::endl;

		GLint internalFormat = m_bits == 32 ? GL_RGBA : m_bits == 24 ? GL_RGB : GL_RED;
		GLenum format = m_bits == 32 ? GL_BGRA : m_bits == 24 ? GL_BGR : GL_RED;
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, pixels ? pixels : NULL));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}

	void GL3Texture::Shutdown() {
		GLCall(glDeleteTextures(1, &m_tID));
	}

	void GL3Texture::Bind() const {
		GLCall(glBindTexture(GL_TEXTURE_2D, m_tID));
	}

	void GL3Texture::Unbind() {
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}
}