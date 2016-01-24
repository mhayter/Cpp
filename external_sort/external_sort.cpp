#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

int minHeap(const pair<string,int> &a,const pair<string,int> &b) {
	return a.first > b.first;
}

const int MAX_FILE_SIZE = 1024*1024*1.5;

string createFileName(int n) {
	char myBuff[20];
	sprintf(myBuff,"%d",n);
	return (string(myBuff) + " intermediate_file.txt"); 
}

int main() {
	//get input
	ios_base::sync_with_stdio(false);
	vector<string> a;
	string s;
	vector<string>fileNames;
	while (cin >> s) {
		a.emplace_back(s);
		if (a.size() >= MAX_FILE_SIZE) {
			//
			string name(createFileName(fileNames.size()));
			fileNames.push_back(name);
			ofstream curStream(name.c_str());

			cerr << "name " << name << endl;
			sort(a.begin(),a.end());
			for(auto &x:a) curStream << x << "\n";
			a.clear();
		}
	}
	if (a.size() ) {
		string name(createFileName(fileNames.size()));
		fileNames.push_back(name);
		ofstream curStream(name.c_str());

		cerr << "name " << name << endl;
		sort(a.begin(),a.end());
		for(auto &x:a) curStream << x << "\n";
		a.clear();
	}
	//merge stuff 

	//for each file 

	pair<string,int> myPair; //curstring, location
	vector<pair<string,int> > myHeap;
	vector<ifstream*> myStreams;
	for(int i=0;i<fileNames.size();i++) {
		myStreams.push_back(new ifstream(fileNames[i]));
		(*myStreams[i]) >> s;
		myHeap.push_back(make_pair(s,i));
		//cerr << s << endl;
	}
	make_heap(myHeap.begin(), myHeap.end(),minHeap);

	/*for(auto &x:myHeap) {
		cerr << x.first << endl;
	}*/

	int ntimes = 0;
	//grab smallest and add new
	while(myHeap.size()) {
		int place = myHeap.front().second;
		cout << myHeap.front().first << "\n";
		//pop heap
		pop_heap(myHeap.begin(),myHeap.end(),minHeap); myHeap.pop_back();
		/*if (ntimes <1) {
			cerr << "******************* AFTER POP **********************" << endl;
			for(auto &x:myHeap) {
				cerr << x.first << endl;
			}
		}
		*/

		//add new element to heap if file isn't empty
		string newElement;
		{// no eof
			string newElement;
			(*myStreams[place]) >> newElement;
			if ((*myStreams[place]).eof()) continue;
			myHeap.push_back(make_pair(newElement,place)); push_heap(myHeap.begin(),myHeap.end(),minHeap);
			/*if (ntimes <1) {
				cerr << "******************* AFTER PUSH **********************" << endl;
				for(auto &x:myHeap) {
					cerr << x.first << endl;
				}
			}*/
		} 
		ntimes++;
	}

	cerr << "intermediate_files generated\n";
	return 0;
}