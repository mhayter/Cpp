#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
public:
	SegmentTree(const vector<int> &b) : a(b.begin(),b.end()) {
		n = a.size();
		segSize = n * 2;
		st = new int[segSize];
		createTree(0,n-1,0);
		printTree();
	}
	~SegmentTree() { delete [] st;}
	int createTree(int start, int end, int place) {
		if (start == end) 
			return st[place] = a[start];
			
		int mid = start + (end-start)/2;
		return st[place] = createTree(start,mid,place*2+1) + createTree(mid+1,end,place*2+2);
	}
	int getSum(int start, int end) const {
		return getSumUtil(start,end,0,n-1,0);
	}
	void update(const int v, const int index) {
		updateUtil(v,index,0,n-1,0);
	}	
	void printTree() const {
		for(int i=0;i<segSize;i++) {
			cout << i << " " <<st[i] << endl;
		}
	}
private:
	int getSumUtil(int start, int end, int istart, int iend, int place) const {
		if (end < istart || start > iend) return 0; // not in interval (no overlap)
		if (start <= istart && end >= iend ) return st[place];
		int mid = istart+(iend-istart)/2;
		return getSumUtil(start,end,istart,mid,place*2+1) + getSumUtil(start,end,mid+1,iend,place*2+2);
	}
	void updateUtil (const int v, const int index, int start,int end, int place) {
		if (index > end || index < start) return;
		
		st[place] = st[place] - a[index] + v;

		if (start == end) {
			if (start == index) a[start] = v;
			st[place] = a[start];
			return;
		}

		int mid = start + (end-start)/2;
		updateUtil(v,index,start,mid,place*2+1);
		updateUtil(v,index,mid+1,end,place*2+2);
	}
	int n;
	int segSize;
	int *st;
	vector<int>a;
};

int main() {
	// your code goes here
	vector<int> array;
	int n; while (cin >> n) array.push_back(n);
	SegmentTree tree(array);
	cout << tree.getSum(0,3) << endl;
	tree.update(7,2);
	cout << tree.getSum(2,2) << " " << tree.getSum(0,3) << " " 
		<< tree.getSum(1,3) << " " << tree.getSum(2,3) << endl;
	return 0;
}
