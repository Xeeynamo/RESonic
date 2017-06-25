#pragma once

namespace XeEngine
{
	class Animation
	{
	private:
	protected:
	public:
		Animation();
		~Animation();

		void Update();
		void Pause();
		void Resume();
		void Reset();
		void JumpToFrame(int);

		void SetRepeations(int);
		void SetTexture();
		void SetDelay(int);

		int GetFrameCount() const;
	};
}