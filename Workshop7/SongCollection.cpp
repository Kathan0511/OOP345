




#include <fstream>
#include <numeric>
#include <functional>
#include <iomanip>

#include "SongCollection.h"

using namespace std;

namespace sdds
{
	string& SongCollection::trim(string& token)
	{
		if (!token.empty())
		{
			token.erase(0, token.find_first_not_of(' '));
			token.erase(token.find_last_not_of(' ') + 1);
		}
		return token;
	}

	SongCollection::SongCollection(string fileName)
	{
		std::ifstream file(fileName);
		if (!file)
		{
			throw "File name is Invalid.";
			return;
		}
		while (file)
		{
			Song song;
			string line;
			getline(file, line);
			if (file)
			{
				trim(song.SongTitle = line.substr(0, 25));
				trim(song.SongArtist = line.substr(25, 25));
				trim(song.SongAlbum = line.substr(50, 25));
				try {
					song.Release_Year = stoi(line.substr(75, 5));
				}
				catch (...) {
					song.Release_Year = 0;
				}
				song.SongLength = stoi(line.substr(80, 5));
				song.m_price = stod(line.substr(85, 5));
				S_collect.push_back(song);
			}
		}
		file.close();
	}

	void SongCollection::display(std::ostream& out) const
	{
		for_each(S_collect.begin(), S_collect.end(), [&out](const Song& song)
			{
				out << song << endl;
			});

		size_t lenghtSum = accumulate(S_collect.begin(), S_collect.end(), 0u, [](const size_t& sumLength, const Song& song)
			 
			{
				return sumLength + song.SongLength;
			});
		out << std::setw(89) << std::setfill('-') << '\n' << std::setfill(' ');
		out << "| ";
		out.width(77);
		out << "Total Listening Time: "
			<< lenghtSum / 3600 << ":" << (lenghtSum - (lenghtSum / 3600) * 3600) / 60
			<< ":"
			<< lenghtSum % 60;
		out << " |" << endl;
	}


	void SongCollection::sort(string column) {
		if (column == "title")
			std::sort(S_collect.begin(), S_collect.end(), []
				(const Song& SFront, const Song& SAfter)
				{return SFront.SongTitle < SAfter.SongTitle; });

		if (column == "artist")
			std::sort(S_collect.begin(), S_collect.end(), []
			(const Song& SFront, const Song& SAfter) 
			{return SFront.SongArtist < SAfter.SongArtist; });

		if (column == "album")
			std::sort(S_collect.begin(), S_collect.end(), []
			(const Song& SFront, const Song& SAfter) 
			{return SFront.SongAlbum < SAfter.SongAlbum; });

		if (column == "length")
			std::sort(S_collect.begin(), S_collect.end(), []
			(const Song& SFront, const Song& SAfter) 
			{return SFront.SongLength < SAfter.SongLength; });

		if (column == "year")
			std::sort(S_collect.begin(), S_collect.end(), []
			(const Song& SFront, const Song& SAfter)
			{return SFront.Release_Year < SAfter.Release_Year; });

		if (column == "price")
			std::sort(S_collect.begin(), S_collect.end(), []
			(const Song& SFront, const Song& SAfter) 
			{return SFront.m_price < SAfter.m_price; });
	}


	void SongCollection::cleanAlbum()
	{
		for_each(S_collect.begin(), S_collect.end(), [](Song& song) { song.SongAlbum = song.SongAlbum == "[None]" ? "" : song.SongAlbum; });
	}


	bool SongCollection::inCollection(string artist) const
	{
		auto valid = find_if(S_collect.begin(), S_collect.end(), [&artist](const Song& song) {return song.SongArtist == artist; });
		return valid != S_collect.end();
	}


	::list<Song> SongCollection::getSongsForArtist(string artist) const
	{
		auto count = count_if(S_collect.begin(), S_collect.end(), [&artist](const Song& song)
			{
				return song.SongArtist == artist;
			});

		list<Song>songsListed(count);

		copy_if(S_collect.begin(), S_collect.end(), songsListed.begin(), [&artist](const Song& song)
			{
				return song.SongArtist == artist;
			});

		return songsListed;
	}


	ostream& operator<<(ostream& out, const Song& src)
	{
		out << "| ";
		out << left << setw(20) << src.SongTitle;
		out << " | ";
		out << left << setw(15) << src.SongArtist;
		out << " | ";
		out << left << setw(20) << src.SongAlbum;
		out << " | ";
		if (src.Release_Year > 0)
			out << right << setw(6) << src.Release_Year;
		else
			out << right << setw(6) << ' ';
		out << " | ";
		out << src.SongLength / 60 << ":";
		out << right << setw(2) << setfill('0') << src.SongLength % 60 << setfill(' ');
		out << " | ";
		out << src.m_price;
		out << " |";
		return out;
	}

	
}