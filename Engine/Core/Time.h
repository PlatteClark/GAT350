#pragma once
#include <chrono>

namespace squampernaut
{
	class Time
	{
	private:
		using clock = std::chrono::high_resolution_clock;
		using clock_duration = clock::duration;
		using clock_rep = clock::rep;


	public:
		Time() : 
			m_startTimePoint{clock::now()},
			m_frameTimePoint{clock::now()} 
		{}

		void Tick();

		void Reset() { m_startTimePoint = clock::now(); };

	public:
			//how much time has elapsed
		float deltaTime = 0;
		float time = 0;

	private:

			//time point at start of application
		clock::time_point m_startTimePoint;
			//time point at start of frame
		clock::time_point m_frameTimePoint;

	};
}