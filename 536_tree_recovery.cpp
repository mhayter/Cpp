#include<string>
#include<iostream>
using namespace std;

string pre,in;
int d;

struct Node {
	Node () {
		c = '#';
		left = right = 0;
	}
	char c;
	Node *left;
	Node *right;
};

void recurse(string s, Node **node) {
	//get left root
	char root = pre[d];

	//find where it is in  in 
	int place = -1;
	for(int i=0;i<s.size();i++) {
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
	while (cin >> pre >> in) {
		d=0;
		Node *head = new Node;
		recurse(in, &head);
		postOrder(head);
		cout <<endl;
	}
	return 0;
}