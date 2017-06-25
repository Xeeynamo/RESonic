#include "VideoGL21.h"
#include "Memory.h"
#include "System.h"

namespace XeEngine
{
	namespace VideoFramework
	{
		const char GL21::gl21ShaderVx[] =
		{
			"#version 120\n"
			"varying vec3 texcoord;"
			"varying vec4 vertex_color;"
			"uniform mat4 mProjection;"
			"uniform mat4 mView;"
			"void main()"
			"{"
				//"gl_Position = mProjection * mView * in_Position;"
				"gl_Position = gl_Vertex;"
				"gl_TexCoord[0]  = gl_MultiTexCoord0;"
				"texcoord = vec3(gl_TexCoord[0].xy, 0);"
				"vertex_color = gl_Color;"
			"}"
		};
		const char GL21::gl21ShaderFxPalette[] =
		{
			"#version 120\n"
			"uniform sampler2D mytexture;"
			"uniform sampler2D clutTexture;"
			"varying vec3 texcoord;"
			"varying vec4 vertex_color;"
			"uniform float mulvalue;"
			"uniform float saturation;"
			"uniform float fadefactor;"

			"void main()"
			"{"
				"vec4 precolor = texture2D(mytexture, texcoord.xy);\n"
				"precolor = texture2D(clutTexture, vec2(precolor.a, texcoord.z));\n"
				//"float gray = (precolor.r + precolor.g + precolor.b) / 3.0;\n"
				//"precolor.rgb += (gray - precolor.rgb) * saturation;"
				//"precolor.rgb *= mulvalue;"
				//"precolor.a *= fadefactor;"
				"gl_FragColor = precolor * vertex_color;"
			"}"
		};
		const char GL21::gl21ShaderFx[] =
		{
			"#version 120\n"
			"uniform sampler2D mytexture;"
			"varying vec3 texcoord;"
			"varying vec4 vertex_color;"

			"void main()"
			"{"
				"gl_FragColor = texture2D(mytexture, texcoord.xy) * vertex_color;"
			"}"
		};

		GL21::GL21(Window* window) : GL(window)
		{
			m_name = "OpenGL 2.1";
			m_prevdata = nullptr;
		}
		GL21::~GL21()
		{

		}

		void GL21::_SendVertices(const Vertex* data, const size_t count, const Primitives primitives)
		{
			if (m_prevdata != data)
			{
				m_prevdata = data;
				glVertexPointer(2, GL_FLOAT, sizeof(Vertex), &data->x);
				glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &data->u);
				glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex), &data->color);
			}
			glDrawArrays(c_primitives[primitives], 0, count);
		}
		void GL21::_SendIndexedVertices(const Vertex* data, const u16* indices, const size_t count, const Primitives primitives)
		{
			if (m_prevdata != data)
			{
				m_prevdata = data;
				glVertexPointer(2, GL_FLOAT, sizeof(Vertex), &data->x);
				glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &data->u);
				glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex), &data->color);
			}
			glDrawElements(c_primitives[primitives], count * 3, GL_UNSIGNED_SHORT, indices);
		}
		void GL21::_UsePalette(const bool palette)
		{
			glUseProgram(shaderPrograms[palette == true]);
		}
		void GL21::_SelectPalette(const TextureID& id)
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, id);
			glActiveTexture(GL_TEXTURE0);
		}

		bool GL21::GLVerInit()
		{
			bool success = true;
			success &= CompileShader(gl21ShaderVx, sizeof(gl21ShaderVx), 0, shaderCompiled[0]);
			success &= CompileShader(gl21ShaderFx, sizeof(gl21ShaderFx), 1, shaderCompiled[1]);
			shaderCompiled[2] = shaderCompiled[0];
			success &= CompileShader(gl21ShaderFxPalette, sizeof(gl21ShaderFxPalette), 1, shaderCompiled[3]);
			if (success == false)
				return false;

			success &= BuildProgram(&shaderCompiled[0], 2, shaderPrograms[0]);
			glUseProgram(shaderPrograms[0]);
			v_mytexture = glGetUniformLocation(shaderPrograms[0], "mytexture");
			glUniform1i(v_mytexture, 0);

			success &= BuildProgram(&shaderCompiled[2], 2, shaderPrograms[1]);
			glUseProgram(shaderPrograms[1]);
			v_mytexture = glGetUniformLocation(shaderPrograms[1], "mytexture");
			v_cluttexture = glGetUniformLocation(shaderPrograms[1], "clutTexture");
			glUniform1i(v_mytexture, 0);
			glUniform1i(v_cluttexture, 1);

			if (success == false)
				return false;

			glUseProgram(shaderPrograms[0]);

			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);

			return true;
		}


		bool GL21::CompileShader(const char* source, const int length, const u32 type, GLint& id)
		{
			GLenum shaderType;
			switch(type)
			{
			case 0:
				shaderType = GL_VERTEX_SHADER;
				break;
			case 1:
				shaderType = GL_FRAGMENT_SHADER;
				break;
			default:
				return false;
			}
			id = glCreateShader(shaderType);
			if (id == 0) return false;

			GLint shader_ok = GL_FALSE;
			glShaderSource(id, 1, (const GLchar**)&source, &length);
			glCompileShader(id);
			glGetShaderiv(id, GL_COMPILE_STATUS, &shader_ok);

			if (shader_ok == GL_FALSE)
			{
				ShaderError(id, glGetShaderiv, glGetShaderInfoLog);
				glDeleteShader(id);
				return false;
			}
			return true;
		}
		bool GL21::BuildProgram(GLint* shaders, u32 count, GLint& id)
		{
			GLint program_ok;

			id = glCreateProgram();
			for(u32 i = 0; i < count; i++)
			{
				glAttachShader(id, shaders[(ptrdiff_t)i]);
			}
			glLinkProgram(id);

			glGetProgramiv(id, GL_LINK_STATUS, &program_ok);
			if (program_ok == GL_FALSE)
			{
				ShaderError((GLuint)id, glGetProgramiv, glGetProgramInfoLog);
				glDeleteProgram(id);
				return false;
			}
			return true;
		}
		void GL21::ShaderError(GLuint object, PFNGLGETSHADERIVPROC glGet__iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog)
		{
			Memory log;
			GLint log_length;
			GLchar* outlog;

			glGet__iv(object, GL_INFO_LOG_LENGTH, &log_length);
			log.Alloc(log_length);
			outlog = (GLchar*)log.GetMemoryHandle();
			glGet__InfoLog(object, log.Size(), NULL, outlog);
			con.Log(DEBUG_LEVEL_WARNING, "%s", outlog);
		}
	}
}