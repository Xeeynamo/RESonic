#pragma once
#include "Scene.h"

namespace XeEngine
{
	class Director
	{
	private:
		float drawInterval;
	protected:
	public:
		Director();
		~Director();

		void Initialize();

		float GetInterval() const;
		void SetInterval(float);
		float GetFPS();
	};
}