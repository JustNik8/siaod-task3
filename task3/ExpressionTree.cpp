#include "ExpressionTree.h"

bool ExpressionTree::isOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
	{
		return true;
	}
	return false;
}

void ExpressionTree::inOrderUtil(Node* node)
{
	if (node) {
		inOrderUtil(node->left);
		printf("%c", node->data);
		inOrderUtil(node->right);
	}
}

int ExpressionTree::evaluateUtil(Node *root)
{
	if (!root)
	{
		return 0;
	}

	if (!root->left && !root->right)
	{
		return root->data - '0';
	}

	int leftValue = evaluateUtil(root->left);

	int rightValue = evaluateUtil(root->right);

	if (root->data == '+')
	{
		return leftValue + rightValue;
	}
	if (root->data == '-')
	{
		return leftValue - rightValue;
	}
	if (root->data == '*')
	{
		return leftValue * rightValue;
	}
	return leftValue / rightValue;
}

int ExpressionTree::evaluate()
{
	return evaluateUtil(getHead());
}

void ExpressionTree::inOrder()
{
	inOrderUtil(getHead());
}

ExpressionTree::Node* ExpressionTree::getHead()
{
	return this->head;
}


ExpressionTree::Node* ExpressionTree::newNode(char c)
{
	Node* n = new Node;
	n->data = c;
	n->left = n->right = nullptr;
	return n;
}

string ExpressionTree::fromInfixToPostfix(string infix)
{
	string postfix = "";
	stack<char> opers;

	for (char ch : infix)
	{
		if (!isOperator(ch))
		{
			postfix += ch;
		} 
		else if (opers.empty() ||
			operatorPriority(ch) > operatorPriority(opers.top()))
		{
			opers.push(ch);
		} 
		else
		{
			postfix += opers.top();
			opers.pop();
			opers.push(ch);
		}
	}

	while (!opers.empty())
	{
		postfix += opers.top();
		opers.pop();
	}

	return postfix;
}

/*
Returns 1 for + and -
Returns 2 for * and /
*/
int ExpressionTree::operatorPriority(char c)
{
	if (c == '+' || c == '-')
	{
		return 1;
	}
	else if (c == '*' || c == '/')
	{
		return 2;
	}
	return 0;
}

void ExpressionTree::print2DUtil(Node* root, int space)
{
	// Base case
	if (root == nullptr)
	{
		return;
	}

	// Increase distance between levels
	space += COUNT;

	// Process right child first
	print2DUtil(root->right, space);

	// Print current node after space count
	cout << endl;
	for (int i = COUNT; i < space; i++)
	{
		cout << " ";
	}
	cout << root->data << "\n";

	// Process left child
	print2DUtil(root->left, space);
}

void ExpressionTree::print2D()
{
	// Pass initial space count as 0
	print2DUtil(getHead(), 0);
}


void ExpressionTree::getPrefixUtil(Node* root, string& prefix)
{
	if (root == nullptr)
	{
		return;
	}
	prefix += root->data;
	getPrefixUtil(root->left, prefix);
	getPrefixUtil(root->right, prefix);
}

string ExpressionTree::getPrefix()
{
	string prefix = "";
	getPrefixUtil(head, prefix);
	return prefix;
}


ExpressionTree::ExpressionTree()
{
	head = nullptr;
}

void ExpressionTree::buildFromInfix(string infix)
{
	std::string::iterator end_pos = std::remove(infix.begin(), infix.end(), ' ');
	infix.erase(end_pos, infix.end());

	string postfix = fromInfixToPostfix(infix);
	stack<Node*> nodeStack;

	Node* t, * t1, * t2;

	for (int i = 0; i < postfix.length(); i++)
	{
		// If operand, simply push into stack
		if (!isOperator(postfix[i]))
		{
			t = newNode(postfix[i]);
			nodeStack.push(t);
		}
		else //opertor 
		{
			t = newNode(postfix[i]);

			// Pop two top nodes
			t1 = nodeStack.top();
			nodeStack.pop();
			t2 = nodeStack.top();
			nodeStack.pop();

			//  make them children
			t->right = t1;
			t->left = t2;

			// Add this subexpression to stack
			nodeStack.push(t);
		}
	}

	//  only element will be root of expression tree
	this->head = nodeStack.top();
	nodeStack.pop();

}
