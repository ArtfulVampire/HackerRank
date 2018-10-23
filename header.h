#ifndef HEADER_H
#define HEADER_H
#include <QString>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <iostream>

int queries();
int triplets();
int sherstr();
int substrcont();
int commonchild();
int dsu();
int swapnodes();
int triplesum();
int production();
int abbr();
int arraysum();
int candies();
int revshuf();
int crossword();
int balance();
int cities();
int near();
int bfs();
int brackets();
int merge();
int maxxor();
int subarr();

bool areEqualFiles(const QString & path1, const QString & path2);
bool areEqualFiles(const std::string & path1, const std::string & path2);
const std::string prePath{"/home/michael/Projects/hacker/"};

std::string ltrim(const std::string &str);
std::string rtrim(const std::string &str);
std::vector<std::string> split(const std::string & str);
std::vector<std::string> split_string(const std::string & str);

template <template <class> class Container, class Typ>
inline std::ostream & operator<< (std::ostream & os, const Container<Typ> & in)
{
	for(auto i : in)
	{
		std::cout << i << "\t";
	}
	return os;
}

inline std::ostream & operator<< (std::ostream & os, const std::set<int> & in)
{
	for(auto i : in)
	{
		std::cout << i << "\t";
	}
	return os;
}

inline std::ostream & operator<< (std::ostream & os, const std::list<int> & in)
{
	for(auto i : in)
	{
		std::cout << i << "\t";
	}
	return os;
}


inline std::ostream & operator<< (std::ostream & os, const std::vector<int> & in)
{
	for(auto i : in)
	{
		std::cout << i << "\t";
	}
	return os;
}


inline std::ostream & operator<< (std::ostream & os, const std::map<char, int> & in)
{
	for(auto i : in)
	{
		std::cout << i.first << " " << i.second << "\t";
	}
	return os;
}


#endif // HEADER_H
