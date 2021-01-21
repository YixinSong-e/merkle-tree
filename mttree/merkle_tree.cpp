#include <iostream>
#include <iomanip>
#include "merkle_tree.h"
#include "myFile.h"
#include <sstream>
#include <fstream>

void MerkleTree::deleteNode(string index, vector<string>files)
{
	//int l = root->l; int r = root->r;
	Node *p = root;
	int judgeLorR = 0; // 1 - left, 2 - right
	while (1)
	{
		if ( p->l == p->r) break;
		//int mid = (l + r) >> 1;
		if (index <= p->left->r)
		{
			p = p->left;
			judgeLorR = 1;
			continue;
		}
		else
		{
		//	l = mid + 1;
			p = p->right;
			judgeLorR = 2;
			continue;
		}
	}
//	updateInsert(p->parent, judgeLorR);
	if (judgeLorR == 1)
	{
		p->parent->left = nullptr;
		p->parent->l = p->parent->r;
		p->parent->hash = p->parent->right->hash ;
		Node *dele = p->parent->right;
		p->parent->right = nullptr;
		delete dele;
		Node *par = p->parent;
		while (1)
		{
			par = par->parent;
			par->l = par->left->l;
			par->hash = hash_sha256(par->left->hash + par->right->hash);
			if (par->parent == par) break;
		}
		delete p;
	}
	else if (judgeLorR == 2)
	{
		p->parent->right = nullptr;
		p->parent->r = p->parent->l;
		p->parent->hash = p->parent->left->hash;
		Node *dele = p->parent->left;
		p->parent->left = nullptr;
		delete dele;
		Node *par = p->parent;
		while (1)
		{
			par = par->parent;
			par->r = par->right->r;
			par->hash = hash_sha256(par->left->hash + par->right->hash);
			if (par->parent == par) break;
		}
		delete p;
	}
}
void MerkleTree::insertTree(string index, vector<string>files)
{
	ifstream ifs(index, ios::in);
	stringstream buffer;
	buffer << ifs.rdbuf();
	string k;
	k += buffer.str();
//	cout << k << endl;
	Node* newNode = new Node(hash_sha256(k));
	newNode->left = newNode->right = nullptr;
	newNode->l = newNode->r = index;
	//int l = root->l; int r = root->r;
	Node *p = root;
	int judgeLorR = 0; // 1 - left, 2 - right
	while (1)
	{
		if (p->l == p->r) break;
		//int mid = (l + r) >> 1;
		if (index <= p->left->r)
		{
			//r = mid;
			p = p->left;
			judgeLorR = 1;
			continue;
		}
		else
		{
			//l = mid + 1;
			p = p->right;
			judgeLorR = 2;
			continue;
		}
	}
	Node *newTaken = new Node(hash_sha256( newNode->hash + p->hash) );
	newTaken->left = newNode;
	newTaken->right = p;
	newTaken->l = newTaken->left->l;
	newTaken->r = newTaken->right->r;
	newTaken->parent = p->parent;
	//newNode->l = newNode->r = index;
	//updateInsert(newTaken,judgeLorR);
	if (judgeLorR == 1)
	{
		p->parent->left = newTaken;
		p->parent = newTaken;
	//	p->parent->hash = hash_sha256(p->parent->left->hash + p->parent->right -> hash);
	}
	else if (judgeLorR == 2)
	{
		p->parent->right = newTaken;
		p->parent = newTaken;
	//	p->parent->hash = hash_sha256(p->parent->left->hash + p->parent->right->hash);
	}
	Node *par = newTaken->parent;
	while (1)
	{
		par->l = par->left->l;
		par->r = par->right->r;
		par->hash = hash_sha256(par->left->hash + par->right->hash);
		par = par->parent;
		if (par->parent == par) break;
	}
	par->hash = hash_sha256(par->left->hash + par->right->hash);
}
MerkleTree::MerkleTree(std::vector<Node*> blocks) {
	std::vector<Node*> nodes;
	while (blocks.size() != 1) {
	//	printNodeHashes(blocks);
		for (unsigned int l = 0, n = 0; l < blocks.size(); l = l + 2, n++) {
			if (l != blocks.size() - 1) { // checks for adjacent block
				//if (l == 14)
				//{
				//	cout << "test" << endl;
				//	cout << blocks[l]->hash << endl;
				//	cout << blocks[l + 1]->hash << endl;
				//	cout << hash_sha256(blocks[l]->hash + blocks[l + 1]->hash) << endl;
				//}
				nodes.push_back(new Node(hash_sha256(blocks[l]->hash + blocks[l + 1]->hash))); // combine and hash adjacent blocks
				nodes[n]->left = blocks[l]; // assign children
				nodes[n]->right = blocks[l + 1];
				nodes[n]->l = blocks[l]->l;
				nodes[n]->r = blocks[l + 1]->r;
				blocks[l + 1]->parent = blocks[l]->parent = nodes[n];
			}
			else {
				nodes.push_back(new Node(hash_sha256(blocks[l]->hash)));
				nodes[n]->l = blocks[l]->l;
				nodes[n]->r = blocks[l]->r;
				nodes[n]->left = blocks[l]; // assign children
				nodes[n]->right = nullptr;
				blocks[l]->parent = nodes[n];
			}
		}
		std::cout << "\n";
		blocks = nodes;
		nodes.clear();

	}
	this->root = blocks[0];
	this->root->parent = blocks[0];
}

MerkleTree::~MerkleTree() {
	deleteTree(root);
	std::cout << "Tree deleted" << std::endl;
}
void MerkleTree::printTree(Node* n)
{
	static int depth = 0;
	if (n == nullptr)
		depth = 0;
	else {
		if (n->left) {
			depth++;
			printTree(n->left);
			depth--;
			for (int i = 0; i < depth; i++)
				std::cout << "====";
			std::cout << "|" << std::endl;
		}
		for (int k = 0; k < depth; k++)
			std::cout << "====";
		std::cout << n->hash << std::endl;
		if (n->right) {
			for (int i = 0; i < depth; i++)
				std::cout << "====";
			std::cout << "|" << std::endl;
			depth++;
			printTree(n->right);
			depth--;
		}
	}
}
//void MerkleTree::printTree(Node* n, int indent) {
//	if (n) {
//		if (n->left) {
//			printTree(n->left, indent + 4);
//		}
//		if (n->right) {
//			printTree(n->right, indent + 4);
//		}
//		if (indent) {
//			std::cout << std::setw(indent) << ' ';
//		}
//		std::cout << n->hash << "\n";
//	}
//}

void MerkleTree::deleteTree(Node* n) {
	if (n) {
		if(n->left != nullptr)deleteTree(n->left);
		if (n->right != nullptr)deleteTree(n->right);
		//n = NULL;
		delete n;
	}
}