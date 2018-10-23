#include <header.h>
#include <QString>
#include <QFile>
#include <iostream>

bool areEqualFiles(const QString & path1, const QString & path2)
{
	QFile fil1(path1); fil1.open(QIODevice::ReadOnly);
	QFile fil2(path2); fil2.open(QIODevice::ReadOnly);

	int pos = 0;
	int lin = 0;
	while(!fil1.atEnd() || !fil2.atEnd())
	{
		++lin;
		QString a = fil1.readLine();
		QString b = fil2.readLine();
		if(a == b) pos += a.size();
		else
		{
			std::cout
					<< "lin = " << lin << "\t"
//					<< "pos ~= " << pos
					<< std::endl;
			return false;
		}
	}
	return true;
}

bool areEqualFiles(const std::string & path1, const std::string & path2)
{
	return areEqualFiles(QString(path1.c_str()), QString(path2.c_str()));
}

std::string ltrim(const std::string & str)
{
	std::string s(str);

	s.erase(std::begin(s),
			std::find_if(std::begin(s), std::end(s),
						 std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

std::string rtrim(const std::string & str)
{
	std::string s(str);

	s.erase(std::find_if(std::rbegin(s), std::rend(s),
						 std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
			std::end(s));
	return s;
}
std::vector<std::string> split(const std::string & str)
{
	std::vector<std::string> tokens;

	std::string::size_type start = 0;
	std::string::size_type end = 0;

	while ((end = str.find(" ", start)) != std::string::npos) {
		tokens.push_back(str.substr(start, end - start));

		start = end + 1;
	}

	tokens.push_back(str.substr(start));

	return tokens;
}

std::vector<std::string> split_string(const std::string & str)
{
	return split(str);
}
