#include <iostream>
#include <cstdlib>
using namespace std;

//myheap 0.000s 4/30/2016

template<typename T>
struct Heap {
	const static int HEAP_SIZE = 50010;
	T heap[HEAP_SIZE];
	int hpsize=0;
	int min, minInd, left, right,place;
	#define LEFT(x) (2*(x)+1)
	#define RIGHT(x) (2*(x)+2)
	#define PARENT(x) (((x)-1)/2)

	Heap(): hpsize(0){
	}
	void reset() {
		hpsize = 0;
	}
	void insert(T &a) {
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
	T extract() {
		T ans = heap[0];
		heap[0] = heap[--hpsize];
		place = 0;
		while (true) {
			this->min = heap[place];
			minInd = place;
			left = LEFT(place);
			right = RIGHT(place);

			if (left < hpsize && this->min > heap[left]){
				minInd = left;
				this->min = heap[minInd];
			} //bad
			if (right < hpsize && this->min > heap[right]){
				minInd = right;
				this->min = heap[minInd];
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
	ios_base::sync_with_stdio(false);
	int n; 
	Heap<int> heap;
	while (true) {
		cin >> n; 
		if (n == 0) break;
		heap.reset();
		while (heap.size()) {}
		for(int i=0;i<n;i++) {
			int num;
			cin >> num;
			heap.insert(num);
		}
		//build heap
		int sum = 0;
		while (heap.size() >= 2) {
			int num1 = heap.extract();
			int num2 = heap.extract();
			int curSum = num1+num2;
			sum += curSum;
			heap.insert(curSum);
		}
		cout << sum << "\n";
	}
	return 0;
}