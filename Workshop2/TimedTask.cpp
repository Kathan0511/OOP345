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



#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;

#include "TimedTask.h"

namespace sdds
{

	void TimedTask::startClock()
	{
		clockStartTime = std::chrono::steady_clock::now();
	}
	void TimedTask::stopClock()
	{
		clockEndTime = std::chrono::steady_clock::now();
	}

	ostream& operator<<(std::ostream& os, const TimedTask& tasks) {
		os << "--------------------------\n" << "Execution Times:\n--------------------------\n";
		for (int t = 0; t < tasks.taskRecords; t++) {
			os << std::setw(21) << std::left << tasks.the_task[t].taskName << " ";
			os << std::setw(13) << std::right << tasks.the_task[t].taskDuration.count() << " " << tasks.the_task[t].TimedUnits << "\n";
		}
		return os << "--------------------------\n";
	}

	void TimedTask::addTask(std::string name) {

		the_task[taskRecords].taskName = name;
		the_task[taskRecords].taskDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(clockEndTime - clockStartTime);
		the_task[taskRecords].TimedUnits = "nanoseconds";

		taskRecords += 1;
	}



}