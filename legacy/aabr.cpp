#include <bits/stdc++.h>
#include <header.h>

using namespace std;

char toUpper(char in)
{
	if(in >= 65 && in <= 90) return in;
	return char(in-32);
}

char toLower(char in)
{
	if(in >= 65+32 && in <= 90+32) return in;
	return char(in+32);
}

bool isUpper(char in)
{
	return (in >= 65 && in <= 90);
}

bool isLower(char in)
{
	return (in >= 65+32 && in <= 90+32);
}

int nextUpper(const string & in, int sta)
{
	for(int i = sta; i < in.size(); ++i)
	{
		if(isUpper(in[i])) { return i; }
	}
	return -1;
}

int nextChar(const string & in, int sta, char ch)
{
	for(int i = sta; i < in.size(); ++i)
	{
		if(in[i] == ch) return i;
	}
	return -1;
}

std::vector<int> findLower(const string & in, int sta, int fin, char ch)
{
	std::vector<int> res{};

//	res.push_back(fin);
//	for(int j = fin - 1; j >= sta; --j)
	for(int j = sta; j < fin; ++j)
	{
		if(in[j] == ch) { res.push_back(j); }
	}
	res.push_back(fin);
	return res;
}

int minAlign(const string & a, int staA, int finA, const string & b, int staB, int finB)
{
	int curA = staA;
	int numFound = 0;
	for(int j = staB; j < finB; ++j)
	{
		for(int i = curA; i < finA; ++i)
		{
			if(a[i] == toLower(b[j]))
			{
				++numFound;
				curA = i + 1;
				break;
			}
		}
	}
	if(numFound != finB - staB) return -1;

	return curA;
}


std::unordered_map<int, bool> mp{};
bool findAbbr(const string & a, int staA, const string & b, int staB)
{
	if(staB >= b.size())
	{
		return nextUpper(a, staA) == -1;
	}
	if(staA >= a.size())
	{
		return false;
	}

	if(b.size() > a.size())
	{
		return false;
	}

	if(a[staA] == b[staB])
	{
		int index = staA * b.size() + staB;
		if(mp.count(index) == 0) { mp[index] = findAbbr(a, staA + 1, b, staB + 1); }
		return mp.at(index);
	}


	int nextA = nextUpper(a, staA);
	if(nextA == -1)
	{
		return minAlign(a, staA, a.size(), b, staB, b.size()) != -1;
	}

	int nextB = nextChar(b, staB, a[nextA]);
	if(nextB == -1)
	{
		return false;
	}

	int firstMatch = minAlign(a, staA, nextA, b, staB, nextB);
	if(firstMatch == -1)
	{
		return false;
	}

	std::vector<int> low = findLower(a, firstMatch, nextA, toLower(a[nextA]));

	for(int in : low)
	{
		int index = in * b.size() + nextB;
		if(mp.count(index) == 0) { mp[index] = findAbbr(a, in + 1, b, nextB + 1); }
		if(mp.at(index))
		{
			return true;
		}
	}
	return false;
}

// Complete the abbreviation function below.
string abbreviation(const string & a, const string & b)
{
	return findAbbr(a, 0, b, 0) ? "YES" : "NO";
}


int abbr()
{

	const std::string project = "abbr";
	const std::string fileNum = "14";

	std::ofstream fout(prePath + project + fileNum + "out.txt");
	std::ifstream inStr(prePath + project + fileNum + ".txt");

	int q;
	inStr >> q;
	inStr.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int q_itr = 0; q_itr < q; q_itr++) {
		string a;
		getline(inStr, a);

		string b;
		getline(inStr, b);

		mp.clear();
		string result = abbreviation(a, b);

		fout << result << "\n";
	}

	fout.close();
	std::cout << areEqualFiles(prePath + project + fileNum + "out.txt",
							   prePath + project + fileNum + "output.txt") << std::endl;

	return 0;
}
