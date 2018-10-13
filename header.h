#ifndef HEADER_H
#define HEADER_H
#include <QString>
#include <string>
#include <vector>
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

bool areEqualFiles(const QString & path1, const QString & path2);
bool areEqualFiles(const std::string & path1, const std::string & path2);
const std::string prePath{"/home/michael/Projects/hacker/"};

std::string ltrim(const std::string &str);
std::string rtrim(const std::string &str);
std::vector<std::string> split(const std::string &str);

inline std::ostream & operator<< (std::ostream & os, const std::vector<int> & in)
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


#endif // HEADER_H
