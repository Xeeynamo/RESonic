#include "XeEngineLV2.h"
#include <stdio.h>

uint xeeffect_program;
int xeeffect_texture;
int xeeffect_properties;
int xeeffect_clutindex;
int xeeffect_clutdepth;
int xeeffect_cluttexture;
int xeeffect_effect;
int xeeffect_mulvalue;
int xeeffect_saturation;
int xeeffect_fadefactor;

int xeeffect_parallaxTexture;
int xeeffect_parallaxWidth;
int xeeffect_parallaxCameraX;

void ShowLog(uint object, PFNGLGETSHADERIVPROC glGet__iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog);

GLuint XeEffect::CompileShader(GLenum type, char *filename)
{
	GLint length;
	GLuint shader;
	GLint shader_ok;

	XeEngine::Memory source;
	XeEngine::File f;
	if (!f.Open(XeEngine::String(filename), true)) return 0;
	length = f.Size();
	source.Alloc(length+1);
	f.Read(source.GetMemoryHandle(), length);
	((char*)source.GetMemoryHandle())[length] = 0;
	f.Close();

	XeEngine::MemoryHandle mem = source.GetMemoryHandle();
	shader = glCreateShader(type);
	glShaderSource(shader, 1, (const GLchar**)&mem, &length);
	source.Free();
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);
	if (!shader_ok)
	{
		ShowLog(shader, glGetShaderiv, glGetShaderInfoLog);
		printf("Failed to compile %s:\n", filename);
		glDeleteShader(shader);
		return 0;
	}
	return shader;
}
void XeEffect::MakeProgram(GLuint vertex_shader, GLuint fragment_shader)
{
	GLint program_ok;

	xeeffect_program = glCreateProgram();
	glAttachShader(xeeffect_program, vertex_shader);
	glAttachShader(xeeffect_program, fragment_shader);
	glLinkProgram(xeeffect_program);
	glGetProgramiv(xeeffect_program, GL_LINK_STATUS, &program_ok);
	if (!program_ok)
	{
		ShowLog(xeeffect_program, glGetProgramiv, glGetProgramInfoLog);
		printf("Failed to link shader program.\n");
		glDeleteProgram(xeeffect_program);
		return;
	}
	LoadUniformVariables();
}
void XeEffect::UseProgram(bool enabled)
{
	glUseProgram(enabled ? xeeffect_program : 0);
}

void ShowLog(GLuint object, PFNGLGETSHADERIVPROC glGet__iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog)
{
	GLint log_length;
	GLchar *log;

	glGet__iv(object, GL_INFO_LOG_LENGTH, &log_length);
	log = (GLchar*)malloc(log_length);
	glGet__InfoLog(object, log_length, NULL, log);
	printf("%s", log);
	free(log);
}
void XeEffect::LoadUniformVariables()
{
	UseProgram(true);
	xeeffect_texture = glGetUniformLocation(xeeffect_program, "texture");
	xeeffect_properties = glGetUniformLocation(xeeffect_program, "properties");
	xeeffect_clutindex = glGetUniformLocation(xeeffect_program, "clutindex");
	xeeffect_clutdepth = glGetUniformLocation(xeeffect_program, "clutdepth");
	xeeffect_cluttexture = glGetUniformLocation(xeeffect_program, "clut");
	xeeffect_effect = glGetUniformLocation(xeeffect_program, "effect");
	xeeffect_mulvalue = glGetUniformLocation(xeeffect_program, "mulvalue");
	xeeffect_saturation = glGetUniformLocation(xeeffect_program, "saturation");
	xeeffect_fadefactor = glGetUniformLocation(xeeffect_program, "fadefactor");

	// PARALLAX
	xeeffect_parallaxTexture = glGetUniformLocation(xeeffect_program, "parallax");
	xeeffect_parallaxWidth = glGetUniformLocation(xeeffect_program, "parallaxWidth");
	xeeffect_parallaxCameraX = glGetUniformLocation(xeeffect_program, "cameraX");
	
	SetMulValue(1.0f);
	SetSaturation(0.0f);
	SetFadeFactor(1.0f);
	SetClutIndex(0);
	SetClutDepth(0, 0);
	UseProgram(true);
}

void XeEffect::SetTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(xeeffect_texture, 0);
}
void XeEffect::SetClutTexture(GLint texture)
{
	glActiveTexture(GL_TEXTURE1);
	glUniform1i(xeeffect_cluttexture, 1);
	XeScene::Bind3DTexture(texture);
}
void XeEffect::SetProperties(GLuint properties)
{
	glUniform1i(xeeffect_properties, properties);
}
void XeEffect::SetClutDepth(int index, int depth)
{
	glUniform1f(xeeffect_clutdepth, depth != 0 ? (float(index)/float(depth)) : 0.0f);
}
void XeEffect::SetClutIndex(GLuint index)
{
	glUniform1f(xeeffect_clutindex, (float)(index)/256.0f);
}
void XeEffect::SetEffect(GLuint effect)
{
	glUniform1i(xeeffect_effect, effect);
}
void XeEffect::SetMulValue(GLfloat value)
{
	glUniform1f(xeeffect_mulvalue, value);
}
void XeEffect::SetSaturation(float value)
{
	glUniform1f(xeeffect_saturation, value);
}
void XeEffect::SetFadeFactor(float value)
{
	glUniform1f(xeeffect_fadefactor, value);
}

void XeEffect::SetParallaxTexture(int texture, int width)
{
	if (width == 0) return;
	glActiveTexture(GL_TEXTURE2);
	glUniform1i(xeeffect_parallaxTexture, 2);
	XeScene::Bind3DTexture(texture);
	
	glUniform1f(xeeffect_parallaxWidth, 1.0f/((float)width));
}
void XeEffect::SetCameraX(int camerax)
{
	glUniform1f(xeeffect_parallaxCameraX, (float)camerax);
}