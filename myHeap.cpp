#include <iostream>
#include <cstdlib>
using namespace std;


struct Heap {
	const static int HEAP_SIZE = 50010;
	pair<int,int> heap[HEAP_SIZE];
	int hpsize=0;
	int min, minInd, left, right,place;
	#define LEFT(x) (2*(x)+1)
	#define RIGHT(x) (2*(x)+2)
	#define PARENT(x) (((x)-1)/2)

	void reset() {
		hpsize = 0;
	}
	void insert(pair<int,int> a) {
		//min head parent < place
		heap[hpsize] = a;
		int place = hpsize;
		while (heap[PARENT(place)]>heap[place]) {
			swap(heap[PARENT(place)],heap[place]);
			place = PARENT(place);
		}
		++hpsize;
	}
	int size() {
		return hpsize;
	}
	pair<int,int> extract() {
		pair<int,int> ans = heap[0];
		heap[0] = heap[--hpsize];
		place = 0;
		while (true) {
			this->min = heap[place].first;
			minInd = place;
			left = LEFT(place);
			right = RIGHT(place);

			if (left < hpsize && this->min > heap[left].first){
				minInd = left;
				this->min = heap[minInd].first;
			} //bad
			if (right < hpsize && this->min > heap[right].first){
				minInd = right;
				this->min = heap[minInd].first;
			}
			if (minInd != place) {
				swap(heap[place],heap[minInd]);
				place = minInd;
			} else break;
		}
		return ans;
	}
};

int main() {
	//vector<pair<int,int>> a;
	Heap heap;
	for(int i=0;i<10;i++) {
		heap.insert(make_pair(rand(),5));
	} 
	for(int i=0;i<16;i++) {
		if (heap.heap[i].first) cout << "i = " << i << " " << heap.heap[i].first << endl;
	}
	cout << "Extracting ... " << endl;
	int hs = heap.size();
	for (int j=0;j<hs; j++) {
		cout << heap.extract().first << endl;
		for(int i=0;i<heap.size();i++) {
		if (heap.heap[i].first) cout << "i = " << i << " " << heap.heap[i].first << endl;
	}
	}
	return 0;
}