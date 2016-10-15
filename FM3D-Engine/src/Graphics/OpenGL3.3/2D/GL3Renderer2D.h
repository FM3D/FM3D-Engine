#pragma once
#include <Engine.h>

#define GL3RENDERER2D_MAX_SPRITES	60000
#define GL3RENDERER2D_SPRITE_SIZE	sizeof(VertexData) * 4
#define GL3RENDERER2D_BUFFER_SIZE	GL3RENDERER2D_SPRITE_SIZE * GL3RENDERER2D_MAX_SPRITES
#define GL3RENDERER2D_INDICES_SIZE	GL3RENDERER2D_MAX_SPRITES * 6
#define GL3RENDERER2D_MAX_TEXTURES	32 - 1

#define GL3RENDERER2D_SHADER_VERTEX_INDEX	0
#define GL3RENDERER2D_SHADER_UV_INDEX		1
#define GL3RENDERER2D_SHADER_COLOR_INDEX	2

namespace ENGINE_NAME {

	class ENGINE_DLL GL3Renderer2D : public Renderer2D {
	private:
		struct VertexData {
			Vector3f vertex;
			Vector2f uv;
			unsigned int color;
		};

		class ENGINE_DLL Shader2D : public GL3Shader {
		private:
			GLint loc_prMatrix;
			GLint loc_tex;
			GLint loc_texBits;
		public:
			Shader2D(const char* vertPath, const char* fragPath) : GL3Shader(vertPath, fragPath) { GetAllUniformLocations(); };

			void Init(Matrix4f prm) {
				SetUniform1i(loc_tex, 0);
				prm.Transpose();
				SetUniformMat4(loc_prMatrix, prm);
			}

			void LoadTexBits(int bits) {
				SetUniform1i(loc_texBits, bits);
			}
		protected:
			void GetAllUniformLocations() {
				loc_prMatrix = GetUniformLocation("pr_matrix");
				loc_tex = GetUniformLocation("tex");
				loc_texBits = GetUniformLocation("texBits");
			};
			void BindAttributes() {};
		};

		GLuint m_vao;
		GLuint m_vbo;
		GLuint m_ibo;
		Shader2D* m_shader;
		GLsizei m_indicesCount;
		VertexData* m_buffer;
		const GL3Texture* m_texture;
	public:
		void Begin() override;
		void Submit(Quad* quad) override;
		void End() override;
		void Flush() override;

		void DrawString(const Text& text, const Vector3f& position) override;

		void Initialize(Matrix4f projectionMatrix);
		void SetProjectionMatrix(const Matrix4f& projectionMatrix) override;
		void Shutdown() override;
	};
}