//==============================================
//Name: Kathan Patel           
//Student ID: 148609191       
//Email: kjpatel30@myseneca.ca            
//Section: NEE        
//Date: 30/01/2022               
//==============================================


//I have done mostly all the coding by myselfand took some help for understanding some scopes from
//my personal tutor only copied the code that my professor provided to complete my workshopsand assignments.  
// (can provide tutor details upon request.)



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