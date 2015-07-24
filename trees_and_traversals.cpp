#include <iostream>
#include <queue>
#include <algorithm>
#include <stack>
using namespace std;

class Node {
public:
	Node (int data, Node *next = 0) {
		this->data = data;
		this->next = next;
	}
	int data;
	Node *next;
};
class LinkedList {
public:
	LinkedList() {head = 0;}
	void insert(int data){
		if (head) {
			Node *newNode = new Node(data,head);
			head = newNode;
		} else {
			head = new Node(data);
		}
	}
	int getLength() {
		Node *curNode = head;
		int len = 0;
		while (curNode) {
			len++;
			curNode=curNode->next;
		}
		return len;
	}
	void print() {
		Node *curNode = head;
		while (curNode) {
			cout << curNode->data << endl;
			curNode = curNode->next;
		}
	}
	
	Node *head;
};

class BinaryTree {
	class Node;
public: 
	BinaryTree() {
		root = 0;
	}
	void insert(int d) {
		insertHelper(&root,d);
	}
	bool search(int d) {
		return searchHelper(root,d);
	}
	void print() {
		printHelper(root);
	}
	int getHeight() {
		return getHeightHelper(root);
	}
	void printLevelOrder() {
		cout << "Printing level order..." << endl;
		printLevelOrderHelper(root);
	}
	void printSpiralOrder() {
		cout << "Printing Spiral order" << endl;
		printSpiralOrder(root,0);
	}
	void printRightView() { //view from right
		cout << "Printing Right View" << endl;
		printRightViewHelper(root);
	}
private:
	void printRightViewHelper(Node *curNode) {
		if (curNode==0) cout <<"" << endl;
		queue<pair<Node*,int>>que;
		que.push(make_pair(curNode,0));
		
		int curDepth=-1;
		while(!que.empty()) {
			pair<Node*,int>temp = que.front(); que.pop();
			if (temp.first) {
				if (curDepth!=temp.second) {
					cout << temp.first->data << endl;
					curDepth = temp.second;
				}
				que.push(make_pair(temp.first->right,temp.second+1));
				que.push(make_pair(temp.first->left,temp.second+1));
			}
		}
	}
	void printSpiralOrder(Node *curNode, int depth) {
		if (curNode==0) cout << "" << endl;
		
		queue<pair<Node*,int> >que;
		que.push(make_pair(curNode,depth));
		stack<pair<Node*,int> >sta;
		while (!que.empty() || !sta.empty()){
			while (!que.empty()) {
				pair<Node*, int> temp = que.front(); que.pop();
				if (temp.first) {
					cout << temp.first->data << endl;
					if (temp.second%2 ==0) {// add right frist
						que.push(make_pair(temp.first->right,temp.second+1));
						que.push(make_pair(temp.first->left,temp.second+1));
					} else {
						sta.push(make_pair(temp.first->right,temp.second+1));
						sta.push(make_pair(temp.first->left,temp.second+1));
					}
				}
			}
			while (!sta.empty() ) {
				pair<Node*, int> temp = sta.top(); sta.pop();
				if (temp.first) {
					cout << temp.first->data << endl;
					if (temp.second%2 ==0) {// add right frist
						que.push(make_pair(temp.first->left,temp.second+1));
						que.push(make_pair(temp.first->right,temp.second+1));
					} else {
						sta.push(make_pair(temp.first->left,temp.second+1));
						sta.push(make_pair(temp.first->right,temp.second+1));
					}
				}
			}
		}
	}
	void printLevelOrderHelper(Node *curNode) {
		if (curNode == 0) cout <<"" << endl;
		Node *start = curNode;
		queue<Node*>que;
		que.push(start);
		while (!que.empty()) {
			Node *temp = que.front(); que.pop();
			if (temp) {
				cout << temp->data << endl;
				que.push(temp->left);
				que.push(temp->right);
			}
		}
	}
	int getHeightHelper(Node *curNode) {
		if (curNode==0) return 0;
		int v1=0;
		int v2=0;
		if (curNode->right) v1 = getHeightHelper(curNode->right) + 1;
		if (curNode->left) v2 = getHeightHelper(curNode->left) + 1;
		return max(v1,v2);
		//return max(getHeightHelper(curNode->right) + 1, getHeightHelper(curNode->left) + 1);
	}
	bool searchHelper(Node *curNode, int d) {
		if (curNode) {
			if (d==curNode->data) 
				return true;
			if (d < curNode->data) return searchHelper(curNode->left,d);
			if (d > curNode->data) return searchHelper(curNode->right, d);
		}
		return false;
	}
	void printHelper(Node *curNode) {
		if (curNode) {
			printHelper(curNode->left);
			cout << curNode->data << endl;
			printHelper(curNode->right);
		}
	}
	void insertHelper(Node **curNode, int d) {
		if (*curNode==0) {
			Node *newNode=new Node(d);
			*curNode=newNode;
		} else {
			if (d<=(*curNode)->data)
				insertHelper(&((*curNode)->left),d);
			else insertHelper(&((*curNode)->right),d);
		}
	}
	class Node {
public:
	Node() {}
	Node(int a) {
		data=a;
		right = left = 0;
	}
	int data;
	Node *right;
	Node *left;
};	
	Node *root;
};

int main() {
	// your code goes here
	int n;
	BinaryTree tree;
	LinkedList list;
	while (cin >>n) {
		tree.insert(n);
		//list.insert(n);
	} 
	//tree.print();
	tree.printLevelOrder();
	tree.printSpiralOrder();
	tree.printRightView();
	//list.print();
	//for(int i=1; i<10;i++) { cout << i<<" " <<tree.search(i) << endl;}
	cout << "height of tree " << tree.getHeight() << endl;
	return 0;
}
