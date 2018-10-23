#include <bits/stdc++.h>
#include <header.h>

using namespace std;


// Complete the minTime function below.
long minTime(vector<long> machines, long goal)
{
	long mx = *std::max_element(std::begin(machines), std::end(machines));
	double speed = std::accumulate(std::begin(machines), std::end(machines), 0., [](double res, long in){ return res + 1. / in; });
	long fir = std::floor(goal / speed);
	std::cout << fir << std::endl;
	long prod = std::accumulate(std::begin(machines), std::end(machines), 0, [fir](long res, long in){ return res + fir / in; });
	int rest = goal - prod;
	std::cout << rest << std::endl;

	if(rest <= 0) return fir;

	std::map<int, int> mp{}; /// days to next toy, num of machines
	for(auto in : machines)
	{
		for(int a = in - fir % in; a < mx; a += in)
		{
			mp[a] += 1;
		}
	}

	int addDays = 0;
	for(auto in : mp)
	{
		rest -= in.second;
		addDays = in.first;
		if(rest <= 0) { break; }
	}
	return fir + addDays;
}

int production()
{
	const std::string project = "prod";
	const std::string fileNum = "02";

	std::ofstream fout(prePath + project + fileNum + "out.txt");
	std::ifstream inStr(prePath + project + fileNum + ".txt");

	string nGoal_temp;
	getline(inStr, nGoal_temp);

	vector<string> nGoal = split(nGoal_temp);

	int n = stoi(nGoal[0]);

	long goal = stol(nGoal[1]);

	string machines_temp_temp;
	getline(inStr, machines_temp_temp);

	vector<string> machines_temp = split(machines_temp_temp);

	vector<long> machines(n);

	for (int i = 0; i < n; i++) {
		long machines_item = stol(machines_temp[i]);

		machines[i] = machines_item;
	}

	long ans = minTime(machines, goal);

	fout << ans << "\n";

	fout.close();


	std::cout << areEqualFiles(prePath + project + fileNum + "out.txt",
							   prePath + project + fileNum + "output.txt") << std::endl;

	return 0;
}

