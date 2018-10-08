#ifndef HEADER_H
#define HEADER_H
#include <QString>
#include <string>
#include <vector>

int queries();
int triplets();

bool areEqualFiles(const QString & path1, const QString & path2);
bool areEqualFiles(const std::string & path1, const std::string & path2);
const std::string prePath{"/home/michael/Projects/hacker/"};

std::string ltrim(const std::string &str);
std::string rtrim(const std::string &str);
std::vector<std::string> split(const std::string &str);

#endif // HEADER_H
