#include <bits/stdc++.h>
#include <header.h>

using namespace std;

struct place
{
	enum class ori{h, v};
	int x{0};
	int y{0};
	ori o;
	int len{0};
	std::string dt;
	std::string bc;
	bool occ{false};

	place(int x_, int y_, ori o_, int len_)
		: x{x_}, y{y_}, o{o_}, len{len_}, dt{std::string(len_, ' ')} {}
	int contains(int x_, int y_) const
	{
		if(o == ori::h)
		{
			if(y_ == y && x_ >= x && x_ - x < len) return x_ - x;
		}
		else if(o == ori::v)
		{
			if(x_ == x && y_ >= y && y_ - y < len) return y_ - y;
		}
		return -1;
	}


	bool fits(const std::string & in) const
	{
		if(occ) return false;
		if(len != in.size()) return false;

		for(int i = 0; i < len; ++i)
		{
			if(dt[i] != ' ' && dt[i] != in[i]) return false;
		}
		return true;
	}

	void setStr(const std::string & in)
	{
		bc = dt;
		dt = in;
		occ = true;
	}

	void clearStr()
	{
		dt = bc;
		occ = false;
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
					res.push_back(place(sta, i, place::ori::h, j - sta));
				}
			}
			++j;
		}
		if(on && 10 - sta > 1) /// place ends on the edge
		{
			res.push_back(place(sta, i, place::ori::h, 10 - sta));
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
					res.push_back(place(i, sta, place::ori::v, j - sta));
				}
			}
		}
		if(on && 10 - sta > 1) /// place ends on the edge
		{
			res.push_back(place(i, sta, place::ori::v, 10 - sta));
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
	return res;
}

bool recurs(const std::vector<std::string> & words, int staW,
					  std::vector<place> & places, int staP)
{
	for(int i = staW; i < words.size(); ++i)
	{
		for(int j = staP; j < places.size(); ++j)
		{
			if(places[j].fits(words[i]))
			{
				places[j].setStr(words[i]);
				if(recurs(words, staW + 1, places, staP + 1)) return true;
				places[j].clearStr();
			}
		}
	}
}

vector<string> crosswordPuzzle(const std::vector<std::string> & crossword, string words)
{
	std::vector<std::string> wrds = toWords(words);
	std::vector<place> places = readCrossword(crossword);

}

int crossword()
{
	const std::string project = "abbr";
	const std::string fileNum = "14";

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
