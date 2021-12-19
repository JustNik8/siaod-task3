#pragma once

#include <iostream>
#include <string>
#include <stack>
#include <deque>

using namespace std;

class ExpressionTree
{
private:
	struct Node
	{
		char data;
		Node* left, * right;
	};

	Node* head;
	const int COUNT = 5;

	bool isOperator(char c);
	Node* newNode(char c);
	string fromInfixToPostfix(string infix);
	int operatorPriority(char c);
	void print2DUtil(Node* root, int space);
	void getPrefixUtil(Node* root, string& prefix);
	void inOrderUtil(Node* node);
	int evaluateUtil(Node *root);

public:
	ExpressionTree();

	void buildFromInfix(string infix);
	void inOrder();
	Node* getHead();
	void print2D();
	string getPrefix();
	int evaluate();
};

