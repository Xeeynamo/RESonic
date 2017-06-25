#pragma once
#include "XeBase.h"

namespace XeEngine
{
	class EXPORT Matrix
	{
	public:
		union
		{
			struct
			{
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
			float m[4][4];
		};

		Matrix();

		void Identity();
		void Transpose(Matrix&);
		void Multiply(Matrix&, Matrix&);

		static void Identity(Matrix&);
		static void Transpose(Matrix&, Matrix&);
		static void Multiply(Matrix&, Matrix&, Matrix&);
		static void RotateX(Matrix&, float);
		static void RotateY(Matrix&, float);
		static void RotateZ(Matrix&, float);
		static void RotateYawPitchRoll(Matrix&, float, float, float);
		static void Scale(Matrix&, float, float, float);
		static void Translate(Matrix&, float, float, float);
		static void Perspective(Matrix& dst, const float fov, const float zNear, const float zFar);
		//D3DXMatrixPerspectiveFovRH
		static void PerspectiveX(Matrix& dst, const float fov, const float width, const float height, const float zNear, const float zFar);
		//D3DXMatrixPerspectiveFovLH
		static void PerspectiveY(Matrix& dst, const float fov, const float width, const float height, const float zNear, const float zFar);
		static void Ortho(Matrix&, float left, float right, float bottom, float top, float znear, float zfar);

		static void GetProjection(Matrix&);
		static void SetProjection(Matrix&);
		static void Push(Matrix&);
		static void Pop(Matrix&);
		static void Pop();
		static void Peek(Matrix*&);
	};
}