#pragma once
#include "XeBase.h"

#define PROPERTIES_CLUT		0x00000001

class XeEffect
{
protected:
	static void LoadUniformVariables();
public:
	static uint CompileShader(uint type, char *filename);
	static void MakeProgram(uint vertex_shader, uint fragment_shader);
	static void UseProgram(bool);

	static void SetTexture();
	static void SetProperties(uint properties);
	static void SetEffect(uint effect);
	static void SetMulValue(float value);
	static void SetSaturation(float value);
	static void SetFadeFactor(float value);

	///// CLUT
	//! \brief Imposta la profondità della clut in una texture clut 3D
	static void SetClutDepth(int index, int depth);
	//! \brief Imposta l'altezza della clut in una texture clut 3D o 2D
	static void SetClutIndex(uint index);
	static void SetClutTexture(int texture);

	///// PARALLAX
	static void SetParallaxTexture(int texture, int width);
	static void SetCameraX(int camerax);
};