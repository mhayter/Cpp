#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

string pre,in;
int d;

//unordered_map<char, int> myMap;

int myMap[130];

struct Node {
	Node () {
		c = '#';
		left = right = 0;
	}
	char c;
	Node *left;
	Node *right;
};

void recurseFast(int start, int end, Node **node) {
	//get left root
	char root = pre[d];
	//find where it is in  in 
	int place = myMap[root];
	
	if (place>=start && place<=end) {
		++d;
		*node = new Node;
		(*node)->c = root;
		recurseFast(start,place-1,&((*node)->left));
		recurseFast(place+1,end, &((*node)->right));
	}
}

void recurse(string s, Node **node) {
	//get left root
	char root = pre[d];

	//find where it is in  in 
	int place = -1;
	for(int i=0;i<(int)s.size();i++) {
		if (s[i] == root) {
			place = i; break;
		}
	}

	if (place != -1) {
		++d;
		*node = new Node;
		(*node)->c = root;
		recurse(s.substr(0,place), &((*node)->left));
		recurse(s.substr(place+1), &((*node)->right));
	}
}

void postOrder(Node *node) {
	if (!node) return;
	postOrder(node->left);
	postOrder(node->right);
	cout << node->c;
}


int main() {
	ios_base::sync_with_stdio(false);
	while (cin >> pre >> in) {
		for(int i=0;i<(int)in.size();i++) myMap[(int)in[i]] = i;
		d=0;
		Node *head = new Node;
		recurseFast(0, in.size()-1, &head);
		postOrder(head);
		cout <<endl;
	}
	return 0;
}