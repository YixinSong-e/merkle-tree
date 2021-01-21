#pragma once
#ifndef NODE_H
#define NODE_H

#include <string>

struct Node {
	std::string hash;
	std::string l, r;
	Node *left;
	Node *right;
	Node *parent;
	Node(std::string data);
};

#endif /* NODE_H */