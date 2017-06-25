#pragma once
#include "VideoGL.h"

namespace XeEngine
{
	class Window;
	namespace VideoFramework
	{
		class GL21 : public GL
		{
		public:
			GL21(Window*);
			~GL21();
		private:
			static const char gl21ShaderVx[];
			static const char gl21ShaderFx[];
			static const char gl21ShaderFxPalette[];
		private:
			GLint shaderCompiled[4];
			GLint shaderPrograms[2];
			GLint v_mytexture;
			GLint v_cluttexture;
			const Vertex* m_prevdata;

			void _SendVertices(const Vertex* data, const size_t count, const Primitives primitives);
			void _SendIndexedVertices(const Vertex* data, const u16* indices, const size_t count, const Primitives primitives);
			void _UsePalette(const bool);
			void _SelectPalette(const TextureID&);

			bool GLVerInit();
			bool CompileShader(const char* source, const int length, const u32 type, GLint& id);
			bool BuildProgram(GLint* shaders, u32 count, GLint& id);
			void ShaderError(GLuint object, PFNGLGETSHADERIVPROC glGet__iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog);
		};
	}
}