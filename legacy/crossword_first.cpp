#include <bits/stdc++.h>
#include <header.h>

using namespace std;

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
		: x{x_}, y{y_}, orientation{o_}, len{len_}, dataString{std::string(len_, ' ')} {}
	int contains(int x_, int y_) const
	{
		if(orientation == orientationType::horizontal)
		{
			if(y_ == y && x_ >= x && x_ - x < len) return x_ - x;
		}
		else if(orientation == orientationType::vertical)
		{
			if(x_ == x && y_ >= y && y_ - y < len) return y_ - y;
		}
		return -1;
	}


	bool fits(const std::string & in) const
	{
		if(occupied) return false;
		if(len != in.size()) return false;

		for(int i = 0; i < len; ++i)
		{
			if(dataString[i] != ' ' && dataString[i] != in[i]) return false;
		}
		return true;
	}

	void setStr(const std::string & in)
	{
		backupString = dataString;
		dataString = in;
		occupied = true;
	}

	void clearStr()
	{
		dataString = backupString;
		occupied = false;
	}
};

std::vector<place> readCrossword(const std::vector<std::string> & crossword)
{
	std::vector<place> res{};
	for(int i = 0; i < 10; ++i) /// each row
	{
		int j = 0;
		bool on{false};
		int sta = 0;

		while (j < 10)
		{
			if(crossword[i][j] == '-' && !on) { on = true; sta = j;}
			if(crossword[i][j] != '-' && on)
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

	for(int i = 0; i < 10; ++i) /// each col
	{
		bool on{false};
		int sta = 0;

		for(int j = 0; j < 10; ++j)
		{
			if(crossword[j][i] == '-' && !on) { on = true; sta = j; }
			if(crossword[j][i] != '-' && on)
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
			std::set<int> indW,
			std::vector<place> & places,
			std::set<int> indP)
{
	for(int i : indW)
	{
		for(int j : indP)
		{
			if(places[j].fits(words[i]))
			{
				places[j].setStr(words[i]);

				indW.erase(i);
				indP.erase(j);

				if(recurs(words, indW, places, indP)) return true;

				places[j].clearStr();
				indW.insert(i);
				indP.insert(j);

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
	std::vector<std::string> wrds = toWords(words);
	std::vector<place> places = readCrossword(crossword);
	std::set<int> indW;
	std::set<int> indP;
	for(int i = 0; i < wrds.size(); ++i)
	{
		indW.emplace(i);
		indP.emplace(i);
	}
	std::cout << indW << std::endl;
	std::cout << indP << std::endl;
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
