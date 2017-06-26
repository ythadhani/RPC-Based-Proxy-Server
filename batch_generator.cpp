#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
using namespace std;

void write(vector<string> &v, string &s)
{
	ofstream file;
	file.open(s.c_str());
	string formatter="";
	
        for(int i = 0; i < v.size(); i++)
        {
    		file << formatter;
        	file << v[i];
        	formatter = "\n";
	}
        file.close();
}

int main()
{
	string file_name = "urls.txt", batch1 = "Workload1.txt";
	ifstream infile;
	infile.open (file_name.c_str());

	string line;
	vector<string> myLines;
	int reps=0;
	srand(time(NULL));
	while (getline(infile, line))
	{
	   reps = rand()%10+7;
           for(int j=0;j<reps;j++)
	   {
	   	myLines.push_back(line);
	   }
	}
	infile.close();
	
	// Creates a batch of randomly shuffled urls
	random_shuffle(myLines.begin(), myLines.end());
	write(myLines, batch1);

	return 0;
}
