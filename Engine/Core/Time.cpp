#include "Time.h"

namespace squampernaut
{
	void squampernaut::Time::Tick()
	{
		clock_duration duration = clock::now() - m_startTimePoint;
		time = duration.count() / (float)clock::duration::period::den;

		duration = clock::now() - m_frameTimePoint;
		deltaTime = duration.count() / (float)clock::duration::period::den;

		m_frameTimePoint = clock::now();
	}

	//void squampernaut::Time::Reset()
	//{
	//}
}

