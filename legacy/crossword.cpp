#include <bits/stdc++.h>
#include <header.h>

using namespace std;

const char dephis{'-'};

std::vector<std::string> crosswordCopy;

void print()
{
	for(auto str : crosswordCopy)
	{
		std::cout << str << std::endl;
	}
}
struct place
{
	enum class orientationType{horizontal, vertical};
	int x{0};
	int y{0};
	orientationType orientation;
	int len{0};
	std::string dataString;
	std::string backupString;
	bool occupied{false};

	place(int x_, int y_, orientationType o_, int len_)
		: x{x_}, y{y_}, orientation{o_}, len{len_}, dataString{std::string(len_, dephis)} {}
	int contains(int x_, int y_) const //// unused
	{
		if(orientation == orientationType::horizontal)
		{
			if(y_ == y && x_ >= x && x_ - x < len) return x_ - x;
		}
		else /// if(orientation == orientationType::vertical)
		{
			if(x_ == x && y_ >= y && y_ - y < len) return y_ - y;
		}
		return -1;
	}

	void setCrossword(std::string in)
	{
		if(in.size() != len) return;
		if(orientation == orientationType::horizontal)
		{
			for(int i = 0; i < len; ++i)
			{
				crosswordCopy[this->y][this->x + i] = in[i];
			}
		}
		else /// if(orientation == orientationType::vertical)
		{
			for(int i = 0; i < len; ++i)
			{
				crosswordCopy[this->y + i][this->x] = in[i];
			}
		}
	}

	bool fits(const std::string & in) const
	{
		if(occupied) return false;
		if(len != in.size()) return false;
		for(int i = 0; i < len; ++i)
		{
			char ch;
			if(orientation == orientationType::horizontal)
			{
				ch = crosswordCopy[this->y][this->x + i];
			}
			else /// if(orientation == orientationType::vertical)
			{
				ch = crosswordCopy[this->y + i][this->x];
			}
//			std::cout << i << " " << ch << " " << in[i] << std::endl;
			if(ch != dephis && ch != in[i])
			{
				return false;
			}
		}
		return true;
	}

	void setStr(const std::string & in)
	{
		backupString = dataString;
		dataString = in;
		setCrossword(dataString);
		occupied = true;
	}

	void clearStr()
	{
		dataString = backupString;
		setCrossword(backupString);
		occupied = false;
	}


};

std::ostream & operator<< (std::ostream & os, place pl)
{
	os
			<< pl.x << " "
			<< pl.y << " "
			<< pl.len  << " "
			<< (pl.orientation == place::orientationType::horizontal ? "hor" : "ver");
	return os;
}

std::vector<place> readCrossword(const std::vector<std::string> & crossword)
{
	std::vector<place> res{};
	for(int i = 0; i < 10; ++i) /// each row = y
	{
		int j = 0; /// x counter
		bool on{false};
		int sta = 0;

		while (j < 10)
		{
			if(crossword[i][j] == dephis && !on) { on = true; sta = j;}
			if(crossword[i][j] != dephis && on)
			{
				on = false;
				if(j - sta > 1)
				{
					res.push_back(place(sta, i, place::orientationType::horizontal, j - sta));
				}
			}
			++j;
		}
		if(on && 10 - sta > 1) /// place ends on the edge
		{
			res.push_back(place(sta, i, place::orientationType::horizontal, 10 - sta));
		}
	}

	for(int i = 0; i < 10; ++i) /// each col = x
	{
		bool on{false};
		int sta = 0;

		for(int j = 0; j < 10; ++j)
		{
			if(crossword[j][i] == dephis && !on) { on = true; sta = j; }
			if(crossword[j][i] != dephis && on)
			{
				on = false;
				if(j - sta > 1)
				{
					res.push_back(place(i, sta, place::orientationType::vertical, j - sta));
				}
			}
		}
		if(on && 10 - sta > 1) /// place ends on the edge
		{
			res.push_back(place(i, sta, place::orientationType::vertical, 10 - sta));
		}
	}
	return res;
}


std::vector<std::string> toWords(const std::string & words)
{
	std::vector<std::string> res{};
	int sta = 0;
	for(int i = 0; i < words.size(); ++i)
	{
		if(words[i] == ';')
		{
			res.push_back(words.substr(sta, i - sta));
			sta = i + 1;
		}
	}
	res.push_back(words.substr(sta)); /// the last one
	return res;
}

bool recurs(const std::vector<std::string> & words,
			const std::set<int> & indW,
			std::vector<place> & places,
			const std::set<int> & indP)
{
	for(int i : indW)
	{
		for(int j : indP)
		{
			if(places[j].fits(words[i]))
			{
				if(indW.size() == 1 && indP.size() == 1)
				{
					places[j].setStr(words[i]);
					return true;
				}

				std::cout << std::endl;
				places[j].setStr(words[i]);
//				print();

				auto indWnew = indW;
				auto indPnew = indP;
				indWnew.erase(i);
				indPnew.erase(j);


				if(recurs(words, indWnew, places, indPnew)) return true;

				places[j].clearStr();
				print();
			}
		}
	}
	return false;
}

vector<string> answer(std::vector<std::string> crossword, const std::vector<place> & places)
{
	for(const auto & place : places)
	{
		if(place.orientation == place::orientationType::horizontal)
		{
			for(int pos = 0; pos < place.len; ++pos)
			{
				crossword[place.y][place.x + pos] = place.dataString[pos];
			}
		}
		else if(place.orientation == place::orientationType::vertical)
		{
			for(int pos = 0; pos < place.len; ++pos)
			{
				crossword[place.y + pos][place.x] = place.dataString[pos];
			}
		}
	}
	return crossword;
}

vector<string> crosswordPuzzle(const std::vector<std::string> & crossword, string words)
{
	crosswordCopy = crossword;

	std::vector<std::string> wrds = toWords(words);
	std::vector<place> places = readCrossword(crossword);

//	print();
//	for(const auto & in : places)
//	{
//		std::cout << in << std::endl;
//		std::cout << in.fits(wrds[0]) << std::endl;
//	}

//	exit(0);

//	for(const auto & in : places)
//	{
//		std::cout << in << std::endl;
//	}

	std::set<int> indW;
	std::set<int> indP;
	for(int i = 0; i < wrds.size(); ++i)
	{
		indW.emplace(i);
		indP.emplace(i);
	}
//	std::cout << indW << std::endl;
//	std::cout << indP << std::endl;
	bool ans = recurs(wrds, indW, places, indP);

	if(!ans) // whuld never happen
	{
		std::cout << "cant fit" << std::endl;
		return {};
	}

	return answer(crossword, places);
}

int crossword()
{
	const std::string project = "";
	const std::string fileNum = "00";

	std::ofstream fout(prePath + project + fileNum + "out.txt");
	std::ifstream inStr(prePath + project + fileNum + ".txt");

	vector<string> crossword(10);

	for (int i = 0; i < 10; i++) {
		string crossword_item;
		getline(inStr, crossword_item);

		crossword[i] = crossword_item;
	}

	string words;
	getline(inStr, words);

	vector<string> result = crosswordPuzzle(crossword, words);

	for (int i = 0; i < result.size(); i++) {
		fout << result[i];

		if (i != result.size() - 1) {
			fout << "\n";
		}
	}

	fout << "\n";

	fout.close();
	std::cout << areEqualFiles(prePath + project + fileNum + "out.txt",
							   prePath + project + fileNum + "output.txt") << std::endl;

	return 0;
}
