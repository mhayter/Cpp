#include <iostream>
#include <memory>
#include <algorithm>
#include <cstring>
#include <ctime>
using namespace std;

/*
Results: on 10 000 000 raw pointers outperformed unique_ptr 32s vs 39s roughly 20%


now I make a standard file: 10 000 000 digits 
looks like 20% difference in favor of raw
*/

class Tree {
public:
	virtual void inOrderTraversal() = 0;
	virtual void insert(int d) = 0;
	virtual ~Tree()
};

struct RawNode {
	RawNode (int data, RawNode* left, RawNode* right) {
		this->data = data;
		this->left = left;
		this->right = right;
	}
	int data;
	RawNode *left;
	RawNode *right;
};

class RawBST : public Tree{
public:
	RawBST() {
		head = nullptr;
	}
	void insert(int d) {
		insertHelper(&head,d);
	}
	void inOrderTraversal() {
		inOrderHelper(head);
	}
private:
	void inOrderHelper(RawNode *curNode) {
		if (curNode == nullptr) return;
		inOrderHelper(curNode->left);
		cout << curNode->data << " ";
		inOrderHelper(curNode->right);
	}
	void insertHelper(RawNode **curNode, int d) {
		//cerr << "insertHelper called " << endl;
		if (*curNode == nullptr) {
			//cerr << "new INsert" << d << endl;
			*curNode = new RawNode(d,nullptr, nullptr);
		} else {
			if (d < (*curNode)->data) { //go left
				insertHelper(&((*curNode)->left),d);
			}else {
				insertHelper(&((*curNode)->right),d);
			}
		}
	}
	RawNode *head;
};

struct Node {
	Node (int data, unique_ptr<Node> left, unique_ptr<Node> right) {
		this->data = move(data);
		this->left = move(left);
		this->right = move(right);
	}
	int data;
	unique_ptr<Node> left;
	unique_ptr<Node> right;
};

class BST : public Tree{
public:
	BST() {
		head = nullptr;
	}
	void insert(int d) {
		insertHelper(&head,d);
	}
	void inOrderTraversal() {
		inOrderHelper(move(head));
	}
private:
	void inOrderHelper(unique_ptr<Node> &&curNode) {
		if (curNode == nullptr) return;
		inOrderHelper(move(curNode->left));
		cout << curNode->data << " ";
		inOrderHelper(move(curNode->right));
	}
	void insertHelper(unique_ptr<Node> *curNode, int d) {
		if (*curNode == nullptr) {
			*curNode = make_unique<Node>(Node(d,nullptr, nullptr));
		} else {
			if (d < (*curNode)->data) { //go left
				insertHelper(&((*curNode)->left),d);
			}else {
				insertHelper(&((*curNode)->right),d);
			}
		}
	}
	unique_ptr<Node> head;
};

class myBST : public Tree{
public:
	myBST() {
		head = nullptr;
	}
	void insert(int d) {
		insertHelper(move(head),d);
	}
	void inOrderTraversal() {
		inOrderHelper(move(head));
	}
private:
	void inOrderHelper(unique_ptr<Node> &&curNode) {
		if (curNode == nullptr) return;
		inOrderHelper(move(curNode->left));
		cout << curNode->data << " ";
		inOrderHelper(move(curNode->right));
	}
	void insertHelper(unique_ptr<Node> &&curNode, int d) {
		if (curNode == nullptr) {
			curNode = make_unique<Node>(Node(d,nullptr, nullptr));
		} else {
			if (d < (curNode)->data) { //go left
				insertHelper(move((curNode)->left),d);
			}else {
				insertHelper(move((curNode)->right),d);
			}
		}
	}
	unique_ptr<Node> head;
};
const int SIZE = 10000000;
int a[SIZE];

int main(int argc, char *argv[]) {
	// your code goes here
	Tree *treePtr;

	int nElements = atoi(argv[2]);
	for(int i=0;i<nElements;i++) {
		a[i] = i;
	}
	random_shuffle(a,a+nElements);
	cerr << "argv[1] " << argv[1] << endl;

	int start = clock();
	if (strcmp(argv[1],"-m")==0) {
		cerr << "myBST" << endl;
		treePtr = new myBST();
	} else if (strcmp(argv[1],"-b") == 0) {
		cerr <<"BST" << endl;
		treePtr = new BST();
	} else {
		cerr << "RawBST" << endl;
		treePtr = new RawBST();
	}

	for(int i=0;i<nElements;i++) {
		treePtr->insert(a[i]);
	}
	treePtr->inOrderTraversal();
	cerr << clock() - start << endl;
	return 0;
}