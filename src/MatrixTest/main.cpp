#include <stdio.h>
#include <D3dx9math.h>
#include "Matrix.h"
#pragma comment(lib, "D3dx9.lib")

using namespace XeEngine;

void PrintMatrix(D3DXMATRIX& matrix)
{
	for(int i=0; i<4; i++)
	{
		printf("%+.6f %+.6f %+.6f %+.6f\n", matrix.m[i][0], matrix.m[i][1], matrix.m[i][2], matrix.m[i][3]);
	}
	printf("\n");
}
void PrintMatrix(Matrix& matrix)
{
	for(int i=0; i<4; i++)
	{
		printf("%+.6f %+.6f %+.6f %+.6f\n", matrix.m[i][0], matrix.m[i][1], matrix.m[i][2], matrix.m[i][3]);
	}
	printf("\n");
}
bool Compare(Matrix& m, D3DXMATRIX& d3dm)
{
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			if (m.m[i][j] != d3dm.m[i][j])
			{
				printf("(%.9f != %.9f)\n", m.m[i][j], d3dm.m[i][j]);
				return false;
			}
		}
	}
	return true;
}
void ErrorIfNotEqual(Matrix& m, D3DXMATRIX& d3dm)
{
	if (Compare(m, d3dm) == false)
	{
		printf("NOT EQUAL!\n");
		PrintMatrix(d3dm);
		PrintMatrix(m);
		while(1);
	}
}

int main()
{
	Matrix m, m1;
	D3DXMATRIX d, d1;
	D3DXMatrixIdentity(&d);
	ErrorIfNotEqual(m, d);

	Matrix::Scale(m, 2.0f, 4.0f, 6.0f);
	D3DXMatrixScaling(&d, 2.0f, 4.0f, 6.0f);
	ErrorIfNotEqual(m, d);

	Matrix::Translate(m, 2.0f, 4.0f, 6.0f);
	D3DXMatrixTranslation(&d, 2.0f, 4.0f, 6.0f);
	ErrorIfNotEqual(m, d);

	Matrix::RotateX(m, 8.0f);
	D3DXMatrixRotationX(&d, 8.0f);
	ErrorIfNotEqual(m, d);

	Matrix::RotateY(m, 4.0f);
	D3DXMatrixRotationY(&d, 4.0f);
	ErrorIfNotEqual(m, d);

	Matrix::RotateZ(m, 2.0f);
	D3DXMatrixRotationZ(&d, 2.0f);
	ErrorIfNotEqual(m, d);
	
	/*Matrix::RotateYawPitchRoll(m, 32.0f, 64.0f, 128.0f);
	D3DXMatrixRotationYawPitchRoll(&d, 32.0f, 64.0f, 128.0f);
	ErrorIfNotEqual(m, d);*/

	m.Transpose(m1);
	D3DXMatrixTranspose(&d1, &d);
	ErrorIfNotEqual(m, d);

	Matrix::Ortho(m, 800.0f, 600.0f, -10.0f, +10.0f);
	D3DXMatrixOrthoLH(&d, 800.0f, 600.0f, -10.0f, +10.0f);
	ErrorIfNotEqual(m, d);

	Matrix::Ortho(m, 1.0f, 800.0f, 600.0f, 3.0f, -10.0f, +10.0f);
	D3DXMatrixOrthoOffCenterRH(&d, 1.0f, 800.0f, 600.0f, 3.0f, -10.0f, +10.0f);
	ErrorIfNotEqual(m, d);

	printf("OK!");
	while(1);

	PrintMatrix(d);
	PrintMatrix(m);
}