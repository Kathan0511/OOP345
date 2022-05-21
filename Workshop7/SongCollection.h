



#ifndef SDDS_SONGCOLLECTION_H
#define SDDS_SONGCOLLECTION_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <functional>
#include <list>

using namespace std;

namespace sdds
{
	struct Song
	{
		string SongArtist{};
		string SongTitle{};
		string SongAlbum{};
		double m_price{};
		size_t Release_Year{};
		size_t SongLength{};
	};


	class SongCollection
	
{
		vector<Song> S_collect;
	public:
		explicit SongCollection(string file);
		[[nodiscard]] bool inCollection(string) const;
		[[nodiscard]] ::list<Song> getSongsForArtist(string) const;
		void display(std::ostream& out) const;
		void sort(string);
		void cleanAlbum();
		string& trim(string& token);
	};
	ostream& operator<<(ostream& out, const Song& src);
}
#endif