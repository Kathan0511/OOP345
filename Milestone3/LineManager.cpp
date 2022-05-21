 


#include <iostream>
#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"

using namespace sdds;
using namespace std;

LineManager::LineManager(const string& file, const vector<Workstation*>& stations) {
	Utilities utility;

	ifstream input(file);
	if (!input.is_open()) {
		throw string("Unable to open file.");
	}


	string data;
	while (!input.eof())
	{
		getline(input, data);
		size_t pos = 0;
		bool more = true;
		string AtStation, NextStation;
		AtStation = utility.extractToken(data, pos, more);

		if (more) {
			NextStation = utility.extractToken(data, pos, more);
		}

		Workstation* AtWorkstation = nullptr;
		Workstation* NextWorkstation = nullptr;
		for_each(stations.begin(), stations.end(), [&AtWorkstation, &NextWorkstation, AtStation, NextStation](Workstation* ws) {
			if (ws->getItemName() == AtStation) {
				AtWorkstation = ws;
			}
			else if (ws->getItemName() == NextStation) {
				NextWorkstation = ws;
			}
			});

		if (m_activeLine.size() == 0) {
			m_firstStation = AtWorkstation;
		}

		AtWorkstation->setNextStation(NextWorkstation);
		m_activeLine.push_back(AtWorkstation);
	}

	input.close();

}

void LineManager::reorderStations() {
	vector<Workstation*> NewSts;
	Workstation* PrevSts = nullptr;
	unsigned int Counts = 0;
	while (Counts < m_activeLine.size()) {
		for (unsigned int i = 0; i < m_activeLine.size(); i++) {
			if (m_activeLine[i]->getNextStation() == PrevSts) {
				NewSts.push_back(m_activeLine[i]);
				PrevSts = m_activeLine[i];
				Counts++;
				break;
			}
		}
	}
	reverse(NewSts.begin(), NewSts.end());
	m_firstStation = NewSts[0];
	m_activeLine = NewSts;
}
bool LineManager::run(ostream& os) {
	static int Counts = 0;
	Counts++;
	os << "Line Manager Iteration: " << Counts << endl;
	if (!g_pending.empty()) {
		(*m_firstStation) += move(g_pending.front());
		g_pending.pop_front();
	}
	for (unsigned int i = 0; i < m_activeLine.size(); i++) {
		m_activeLine[i]->fill(os);
	}
	for (unsigned int i = 0; i < m_activeLine.size(); i++) {
		m_activeLine[i]->attemptToMoveOrder();
	}
	bool empty = true;
	for (unsigned int i = 0; i < m_activeLine.size(); i++) {
		if (!m_activeLine[i]->empty()) {
			empty = false;
			break;
		}
	}
	return empty;
}

void LineManager::display(ostream& os) const {
	for (unsigned int i = 0; i < m_activeLine.size(); i++) {
		m_activeLine[i]->display(os);
	}
}