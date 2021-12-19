#include <iostream>
#include <string>
#include "ExpressionTree.h"

using namespace std;

bool isOperator(char c);
double evaluatePrefix(string& prefix);
int operatorPriority(char c);

int main()
{
    setlocale(LC_ALL, "Russian");
    ExpressionTree tree;
    
    string infix;
    cout << "Input infix expression: ";
    getline(cin, infix);

    tree.buildFromInfix(infix);
    cout << "Your infix expression: ";
    tree.inOrder();
    cout << endl;

    cout << "\nPrinting expression tree:";
    cout << endl;
    tree.print2D();

    cout << endl;
    cout << "Prefix form:" << endl;
    string prefix = tree.getPrefix();
    cout << prefix;

    cout << endl;
    cout << "evaluate expression tree: " << tree.evaluate();

    cout << endl;
    cout << "Evaluate prefix form: " << evaluatePrefix(prefix);

}

bool isOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/')
    {
        return true;
    }
    return false;
}

/*
Returns 1 for + and -
Returns 2 for * and /
*/
int operatorPriority(char c)
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

double evaluatePrefix(string& prefix)
{
    stack<double> s;
    string t = "";
    for (int j = prefix.size() - 1; j >= 0; j--)
    {
        // Push operand to Stack to convert prefix[j] to digit subtract '0' from prefix[j].
        if (!isOperator(prefix[j]))
        {
            s.push(prefix[j] - '0');
        }
        else
        {
            // Operator encountered pop two elements from Stack
            double o1 = s.top();
            s.pop();
            double o2 = s.top();
            s.pop();

            // Use switch case to operate on o1 and o2 and perform o1 O o2.
            switch (prefix[j]) {
            case '+':
                s.push(o1 + o2);
                break;
            case '-':
                s.push(o1 - o2);
                break;
            case '*':
                s.push(o1 * o2);
                break;
            case '/':
                s.push(o1 / o2);
                break;
            }
        }
    }
    
    return s.top();
}


