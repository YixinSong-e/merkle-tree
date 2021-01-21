#include <iostream>
#include "merkle_tree.h"
#include "myFile.h"
#include <algorithm>
#include <filesystem>
#include <sstream>
#include <fstream>
string compare(vector<string> newfiles, vector<string> files)
{
	int size1 = newfiles.size();
	int size2 = files.size();
	int flag1 = 0;
	if (size1 < size2) flag1 = 1; else flag1 = 2;
	for (int i = 0; i < size1; i++)
	{
		if (newfiles[i] != files[i])
			if (flag1 == 1) return files[i];
			else return newfiles[i];
	}
	if (size1 < size2)
	{
		cout << files[size1] << endl;
		return files[size1];
	}
	return "0";
}
std::vector<Node*> leaves;
vector<string> files;
vector<Node *> initLeaves(vector<string>files,const char *filePath)
{
	vector<Node*> leaves;
	getFiles1(filePath, files);
	for (int i = 0; i < files.size(); i++)
	{
		//std::cout << files[i] << std::endl;
		ifstream ifs(files[i], ios::in);
		stringstream buffer;
		buffer << ifs.rdbuf();
		string k;
		k += buffer.str();
		leaves.push_back(new Node(hash_sha256(k)));
	}
	for (unsigned int i = 0; i < leaves.size(); i++) {
		leaves[i]->left = nullptr;
		leaves[i]->right = nullptr;
		leaves[i]->l = leaves[i]->r = files[i];
	}
	return leaves;
}
int main() {
	
	const char * filePath = "F:\\lab3\\first";
	const char * filePath2 = "F:\\lab3\\second";
	leaves = initLeaves(files, filePath);
	getFiles1(filePath, files);
	// 建树
	MerkleTree *hashTree = new MerkleTree(leaves);
	std::cout << hashTree->root->hash << std::endl;
	//遍历
	hashTree->printTree(hashTree->root);
	while (1)
	{
		int control = 0;
		cout << "输入2则做实验4,输入其它则做检查增删实验" << endl;
		scanf_s("%d", &control);
		if (control == 0) exit(0);
		if (control == 2)
		{
			vector<Node *>leaves;
			vector<string>files2;
			leaves = initLeaves(files2, filePath2);
			MerkleTree *hashTree2 = new MerkleTree(leaves);
			std::cout << hashTree2->root->hash << std::endl;
			hashTree2->printTree(hashTree2->root);
			Node *p1 = hashTree->root;
			Node *p2 = hashTree2->root;
			while (1)
			{
				if (p1->l == p1->r) break;
				if (p1->left->hash != p2->left->hash)
				{
					p1 = p1->left;
					p2 = p2->left;
				}
				else if (p1->right->hash != p2->right->hash)
				{
					p1 = p1->right;
					p2 = p2->right;
				}
				else break;
			}
			if (p1->l == p1->r) cout << "不同的文件名为:" << p1->l << endl;
			else cout << "不存在不同的文件名" << endl;
			delete hashTree2;
			continue;
		}
		vector<string> newFiles;
		getFiles1(filePath, newFiles);
		string flag = "";
		flag = compare(newFiles, files);
		if (flag != "0")
		{
			if (newFiles.size() > files.size())
			{
				hashTree->insertTree(flag, newFiles);
				hashTree->printTree(hashTree->root);
				cout << "增加了文件：" << flag << endl;
			}
			else
			{
				hashTree->deleteNode(flag, files);
				hashTree->printTree(hashTree->root);
				cout << "删除了文件：" << flag << endl;
			}
			files = newFiles;
		}
		else
		{
			printf("No change in the dictory\n");
		}
	}
	
	delete hashTree;

	return 0;
}