#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <math.h>
using namespace std;

//constants
const double PI = atan(1)*4;

//calculator tree
struct Node
{
    string tk;
    Node* left;
    Node* right;

    Node(string str = "", Node* l = nullptr, Node* r = nullptr) :
        tk(str), left(l), right(r) {}
};

//calculator class
class Calc 
{
    private:
       Node *root;
       double answer;

    public:
        //input
        Calc() : root(nullptr), answer(0) {}
        void readExpression(string tk);
        void calculate();
        void printAnswer(); 
};

stack<string> parseExpression(string exprsn);
Node* buildTree(stack<string> token); 
double inorder(Node* nd);
void attachOperator(stack<Node*>& treeNodes, stack<Node*>& ops);

bool isOperator(char c);
bool isOperator(string s);
bool isParenthesis(char c);
bool isFunction(string s);
int priority(string s);

#endif