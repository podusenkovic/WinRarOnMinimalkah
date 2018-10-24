#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <bitset>
#include <time.h>
#include <string>

using namespace std;

class Node {
	bool last;
	char value;
	Node *nextA, *nextB;
public:
	Node(bool _last = true, char _value = 0, Node *_nextA = nullptr, Node *_nextB = nullptr) :
		last(_last), value(_value), nextA(_nextA), nextB(_nextB) {};

	bool isLast() {
		return last;
	}
	char getValue() {
		return value;
	}
	void setValues(char val) {
		value = val;
	}
	~Node() {
		delete nextA, nextB;
	}

	friend map<char, string> getTreeData(Node*, string);
};

struct arrNode {
	char first;
	int second;
	Node *third;
};

bool cmpArrNode(const arrNode &a, const arrNode &b)
{
	return a.second > b.second;
}


map<char, string> getTreeData(Node *a, string prev) {
	static map<char, string> temp;
	if (a->last) {
		cout << a->value << " " << prev << endl;
		temp[a->value] = prev;
	}
	else {
		getTreeData(a->nextA, prev + "1");
		getTreeData(a->nextB, prev + "0");
	}
	return temp;
}


int main() {

	/*srand(time(NULL));
	ofstream file("output.txt");

	for (int i = 0; i < 102400; i++)
	file << char(rand() % 255 + 1);//((rand() % 30) ? char(rand() % 26 + 65) : char(32)); // THE SYMBOL '/0' IS A SPECIAL DONT USE IT, YOU IDIOT
	*/


	ifstream file("output.txt");
	//ifstream file("test.txt");
	map<char, int> simbolsCount;

	while (!file.eof()) {
		char a;
		file.get(a);
		if (simbolsCount.find(a) == simbolsCount.end())
			simbolsCount[a] = 1;
		else simbolsCount[a]++;
	}


	//vector<arrNode> simbVec(simbolsCount.begin(), simbolsCount.end());
	vector<arrNode> simbVec;
	for (auto p : simbolsCount) {
		simbVec.push_back({ p.first, p.second, nullptr });
	}


	// CREATING TREE
	Node *topNode = nullptr;
	while (simbVec.size() != 1) {
		sort(simbVec.begin(), simbVec.end(), cmpArrNode);
		int n = simbVec.size();
		Node *nodeA = nullptr, *nodeB = nullptr;

		if (simbVec[n - 1].first != char(0))
			nodeA = new Node(true, simbVec[n - 1].first);
		else nodeA = simbVec[n - 1].third;

		if (simbVec[n - 2].first != char(0))
			nodeB = new Node(true, simbVec[n - 2].first);
		else nodeB = simbVec[n - 2].third;


		topNode = new Node(false, char(0), nodeA, nodeB);

		int nFreq = simbVec[n - 1].second + simbVec[n - 2].second;

		simbVec.pop_back();
		simbVec[simbVec.size() - 1] = arrNode{ char(0), nFreq , topNode };
	}

	// GETTING TREE DATA IN MAP TYPE
	map<char, string> treeData = getTreeData(topNode, "");

	file.close();

	
	/*auto it = treeData.begin();
	string dictString = "";
	while (it != treeData.end()) {
		dictString.push_back(it->first);

		it++;
	}*/
	
	// TRYING CREATE ARCHIVED FILE
	file.open("output.txt");
	ofstream archive("output.sosi_jepy", ios::binary);
	short unsigned int i = 0;
	unsigned char out = char(0);
	char in;
	while (!file.eof()) {
		file.get(in);
		//cout << in << " ";
		for (auto p : treeData[in]) {
			if (i < 7) {
				out |= ((p == '1') ? 1u : 0u);
				out <<= 1;
				i++;
			}
			else {
				out |= ((p == '1') ? 1u : 0u);
				//cout << bitset<8>(out) << " ";
				archive << out;
				out = char(0);
				i = 0;
			}
		}
	}

	delete topNode;

	archive.close();

	/* Create a 100 MB file
	for (int i = 0; i < 104857600; i++) {
	file << char(rand() % 23 + 65);
	}*/


	file.close();
	cout << endl;
	system("pause");
	return 0;
}