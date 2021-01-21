//
//#include<openssl\ssl.h>
//#include <string>
//#include "node.h"
//#pragma comment(lib,"libssl.lib")
//#pragma comment(lib,"libcrypto.lib")
//using namespace std;
//
//string sha256(const string str)
//{
//	char buf[20];
//	unsigned char hash[SHA256_DIGEST_LENGTH];
//	SHA256_CTX sha256;
//	SHA256_Init(&sha256);
//	SHA256_Update(&sha256, str.c_str(), str.size());
//	SHA256_Final(hash, &sha256);
//	std::string NewString = "";
//	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
//	{
//		sprintf_s(buf, "%02x", hash[i]);
//		NewString = NewString + buf;
//	}
//	return NewString;
//}
//Node** initalize_leaf(char *path)
//{
//	Node** lst;
//	
//
//	return lst;
//}
//bool compare(Node **node, Node **oldnode)
//{
//	return true;
//}
//int main(int argc, char *argv[]) {
//	if (argc == 1 || argc > 3) {
//		puts("error parameters");
//		return 0;
//	}
//
//	//含程序自身参数，总参数数为2时，第2个参数为用于构建默克尔树的目录
//	//含程序自身参数，总参数数为3时，第2个参数为用于构建默克尔树的目录，第3个参数为用于构建默克尔树和比较一致性的目录，
//	//相关逻辑自行补充
//
//	Node ** oldnode = NULL;
//
//	while(1) //整体实验大循环，完成实验3-1至3-4
//	{
//		//初始化创建叶子节点，注意根据目录下文件数分配空间
//		//initalize_leaf函数，输出Node类型的数组，每个叶子节点的key可使用文件名，哈希值为文件所有数据的哈希，叶子节点初始化时，父节点、左右子节点为空，数据结构参考前述数据结构。未初始化时，key值可以设成-1.
//		//hash函数可以是MD5，也可以是SHA-256，或自行设计哈希函数
//
//		Node ** node = initalize_leaf(argv[1]);
//		if (compare(node, oldnode) == 0)  //比较路径下是否有文件更新或删除，如果没有更新则不重建默克尔树
//		{
//			printf("No change in the directory.");
//			continue;
//		}
//		if(oldnode == NULL)
//			oldnode = node;
//
//		//构建哈希树
//		//Node * root = malloc(sizeof(Node));
//		//MtTree * mt = malloc(sizeof(MtTree));
//
//		//哈希树叶子节点构建，自行设计迭代实现整体默克尔树构建
//		//for (int i = 0; *node[i]->key != -1; i += 2)
//		//{
//			//root = build_tree(mt, *node[i], *node[i + 1]);
//		//}
//
//		//Showtree(root);
//
//		oldnode = node;
//	} //结束大循环
//
//}