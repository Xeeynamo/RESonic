#include "Matrix.h"
#include "Stack.h"
#include <math.h>

namespace XeEngine
{
	Stack<Matrix> matrixStack(64);
	Matrix matProjection;
	Matrix matView;
}

XeEngine::Matrix::Matrix()
{
	Identity(*this);
}
void XeEngine::Matrix::Identity()
{
	Identity(*this);
}
void XeEngine::Matrix::Transpose(Matrix& dst)
{
	Transpose(dst, *this);
}
void XeEngine::Matrix::Multiply(Matrix& dst, Matrix& src)
{
	Multiply(dst, *this, src);
}

void XeEngine::Matrix::Identity(Matrix& dst)
{
	dst._12 = dst._13 = dst._14 = 0.0f;
	dst._21 = dst._23 = dst._24 = 0.0f;
	dst._31 = dst._32 = dst._34 = 0.0f;
	dst._41 = dst._42 = dst._43 = 0.0f;
	dst._11 = dst._22 = dst._33 = dst._44 = 1.0f;
}
void XeEngine::Matrix::Transpose(Matrix& dst, Matrix& src)
{
	dst._11 = src._11;
	dst._12 = src._21;
	dst._13 = src._31;
	dst._14 = src._41;
	dst._21 = src._12;
	dst._22 = src._22;
	dst._23 = src._32;
	dst._24 = src._42;
	dst._31 = src._13;
	dst._32 = src._23;
	dst._33 = src._33;
	dst._34 = src._43;
	dst._41 = src._14;
	dst._42 = src._24;
	dst._43 = src._34;
	dst._44 = src._44;
}
void XeEngine::Matrix::Multiply(Matrix& dst, Matrix& src1, Matrix& src2)
{
	dst._11 = src1._11 * src2._11 + src1._12 * src2._21 + src1._13 * src2._31 + src1._14 * src2._41;
	dst._12 = src1._11 * src2._12 + src1._12 * src2._22 + src1._13 * src2._32 + src1._14 * src2._42;
	dst._13 = src1._11 * src2._13 + src1._12 * src2._23 + src1._13 * src2._33 + src1._14 * src2._43;
	dst._14 = src1._11 * src2._14 + src1._12 * src2._24 + src1._13 * src2._34 + src1._14 * src2._44;
	dst._21 = src1._21 * src2._11 + src1._22 * src2._21 + src1._23 * src2._31 + src1._24 * src2._41;
	dst._22 = src1._21 * src2._12 + src1._22 * src2._22 + src1._23 * src2._32 + src1._24 * src2._42;
	dst._23 = src1._21 * src2._13 + src1._22 * src2._23 + src1._23 * src2._33 + src1._24 * src2._43;
	dst._24 = src1._21 * src2._14 + src1._22 * src2._24 + src1._23 * src2._34 + src1._24 * src2._44;
	dst._31 = src1._31 * src2._11 + src1._32 * src2._21 + src1._33 * src2._31 + src1._34 * src2._41;
	dst._32 = src1._31 * src2._12 + src1._32 * src2._22 + src1._33 * src2._32 + src1._34 * src2._42;
	dst._33 = src1._31 * src2._13 + src1._32 * src2._23 + src1._33 * src2._33 + src1._34 * src2._43;
	dst._34 = src1._31 * src2._14 + src1._32 * src2._24 + src1._33 * src2._34 + src1._34 * src2._44;
	dst._41 = src1._41 * src2._11 + src1._42 * src2._21 + src1._43 * src2._31 + src1._44 * src2._41;
	dst._42 = src1._41 * src2._12 + src1._42 * src2._22 + src1._43 * src2._32 + src1._44 * src2._42;
	dst._43 = src1._41 * src2._13 + src1._42 * src2._23 + src1._43 * src2._33 + src1._44 * src2._43;
	dst._44 = src1._41 * src2._14 + src1._42 * src2._24 + src1._43 * src2._34 + src1._44 * src2._44;
}
void XeEngine::Matrix::RotateX(Matrix& dst, float angle)
{
	Identity(dst);
	dst._22 = cosf(angle);
	dst._23 = sinf(angle);
	dst._32 = -sinf(angle);
	dst._33 = cosf(angle);
}
void XeEngine::Matrix::RotateY(Matrix& dst, float angle)
{
	Identity(dst);
	dst._11 = cosf(angle);
	dst._13 = -sinf(angle);
	dst._31 = sinf(angle);
	dst._33 = cosf(angle);
}
void XeEngine::Matrix::RotateZ(Matrix& dst, float angle)
{
	Identity(dst);
	dst._11 = cosf(angle);
	dst._12 = sinf(angle);
	dst._21 = -sinf(angle);
	dst._22 = cosf(angle);
}
void XeEngine::Matrix::RotateYawPitchRoll(Matrix& dst, float yaw, float pitch, float roll)
{
	Identity(dst);
	dst._11 = ( cos(roll) * cos(yaw) ) + ( sin(roll) * sin(pitch) * sin(yaw) );
	dst._12 = ( sin(roll) * cos(pitch) );
	dst._13 = ( cos(roll) * -sin(yaw) ) + ( sin(roll) * sin(pitch) * cos(yaw) );
	dst._21 = (-sin(roll) * cos(yaw) ) + ( cos(roll) * sin(pitch) * sin(yaw) );
	dst._22 = ( cos(roll) * cos(pitch) );
	dst._23 = ( sin(roll) * sin(yaw) ) + ( cos(roll) * sin(pitch) * cos(yaw) );
	dst._31 = ( cos(pitch) * sin(yaw) );
	dst._32 = -sin(pitch);
	dst._33 = ( cos(pitch) * cos(yaw) );
	dst._44 = 1;
}
void XeEngine::Matrix::Scale(Matrix& dst, float x, float y, float z)
{
	Identity(dst);
	dst._11 = x;
	dst._22 = y;
	dst._33 = z;
}
void XeEngine::Matrix::Translate(Matrix& dst, float x, float y, float z)
{
	Identity(dst);
	dst._41 = x;
	dst._42 = y;
	dst._43 = z;
}
void XeEngine::Matrix::Perspective(Matrix& dst, const float fov, const float zNear, const float zFar)
{
	float s = cosf(0.5f * fov) / sinf(0.5f * fov);
	dst._11 = s;
	dst._12 = dst._13 = dst._14 = dst._21 = 0;
	dst._22 = s;
	dst._23 = dst._24 = dst._31 = dst._32 = 0;
	dst._33 = (zFar + zNear) / (zFar - zNear);
	dst._34 = -(2 * zFar * zNear) / (zFar - zNear);
	dst._31 = dst._32 = dst._34 = 0;
	dst._33 = 1;
}
void XeEngine::Matrix::PerspectiveX(Matrix& dst, const float fov, const float width, const float height, const float zNear, const float zFar)
{
	float w = cosf(0.5f * fov) / sinf(0.5f * fov);
	float h = (w * width) / height;
	dst._11 = w;
	dst._12 = dst._13 = dst._14 = dst._21 = 0;
	dst._22 = h;
	dst._23 = dst._24 = dst._31 = dst._32 = 0;
	dst._33 = (zFar + zNear) / (zFar - zNear);
	dst._34 = -(2 * zFar * zNear) / (zFar - zNear);
	dst._31 = dst._32 = dst._34 = 0;
	dst._33 = 1;
}
void XeEngine::Matrix::PerspectiveY(Matrix& dst, const float fov, const float width, const float height, const float zNear, const float zFar)
{
	float h = cosf(0.5f * fov) / sinf(0.5f * fov);
	float w = (h * height) / width;
	dst._11 = w;
	dst._12 = dst._13 = dst._14 = dst._21 = 0;
	dst._22 = h;
	dst._23 = dst._24 = dst._31 = dst._32 = 0;
	dst._33 = (zFar + zNear) / (zFar - zNear);
	dst._34 = -(2 * zFar * zNear) / (zFar - zNear);
	dst._31 = dst._32 = dst._34 = 0;
	dst._33 = 1;
}
void XeEngine::Matrix::Ortho(Matrix& dst, float left, float right, float bottom, float top, float znear, float zfar)
{
	dst.Identity();
	dst._11 = +2.0f / (right - left);
	dst._22 = +2.0f / (top - bottom);
	dst._33 = -2.0f / (zfar - znear);
	dst._41 = -((right + left) / (right - left));
	dst._42 = -((top + bottom) / (top - bottom));
	dst._43 = -((zfar + znear) / (zfar - znear));
}
void XeEngine::Matrix::GetProjection(Matrix& matrix)
{
	matrix = matProjection;
}
void XeEngine::Matrix::SetProjection(Matrix& matrix)
{
	matProjection = matrix;
}
void XeEngine::Matrix::Push(Matrix& matrix)
{
	matrixStack.Push(matrix);
}
void XeEngine::Matrix::Pop(Matrix& matrix)
{
	matrixStack.Pop(matrix);
}
void XeEngine::Matrix::Pop()
{
	matrixStack.Pop();
}
void XeEngine::Matrix::Peek(Matrix*& matrix)
{
	matrixStack.Peek(matrix);
}