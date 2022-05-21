



#include <iostream>
#include<chrono>

#ifndef SDDS_TIMEDTASK_H_
#define SDDS_TIMEDTASK_H_

namespace sdds
{
	const int MAX = 10;
	class TimedTask
	{
	public:
		std::chrono::steady_clock::time_point clockStartTime;
		std::chrono::steady_clock::time_point clockEndTime;

		struct Task
		{
			std::string taskName;
			std::string TimedUnits;
			std::chrono::steady_clock::duration taskDuration;
		};

		Task the_task[MAX]; int taskRecords = 0;
    	friend std::ostream& operator<<(std::ostream& os, const TimedTask& tasks);
		void startClock();
		void stopClock();
		void addTask(std::string name);
	private:

	};
}
#endif
