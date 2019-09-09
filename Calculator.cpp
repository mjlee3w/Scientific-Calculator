#include "Calculator.h"

bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

bool isOperator(string s)
{
    return (s == "+" || s == "-" || s == "*" || s == "/" || s == "^");
}

bool isParenthesis(char c)
{
    return (c == '(' || c == ')');
}

bool isFunction(string s)
{
    return (s == "sin" || s == "cos" || s == "tan" || s == "asin" || s == "acos" || s == "atan"
           || s == "ln" || s == "log" || s == "exp"
           || s == "sqrt");
}

int priority(string s)
{
    if(s == "+" || s == "-") return 1;
    if(s == "*" || s == "/") return 2;
    if(s == "^") return 3;
    return 0;
}

void Calc::readExpression(string exprsn)
{
    //cout << "'" << exprsn  << "'" << endl;
    stack<string> token = parseExpression(exprsn);
    root = buildTree(token);
}

stack<string> parseExpression(string exprsn)
{
    //add space
    string newExprsn;
    for(char c : exprsn)
    {
        if(isOperator(c) || isParenthesis(c))
        {
            newExprsn.push_back(' ');
            newExprsn.push_back(c);
            newExprsn.push_back(' ');
        }
        else 
            newExprsn.push_back(c);
    }

    //read string and push into stack
    string str;
    stack<string> token;
    istringstream iss(newExprsn);
    while(iss >> str)
    {
        //cout << "token: " << str << endl;
        token.push(str);
    } 
 
    return token;
}

Node* buildTree(stack<string> token)
{ 
    stack<Node*> treeNodes;
    stack<Node*> ops;
    
    //read each token from token stack
    string temp;
    while(!token.empty())
    {
        temp = token.top();
        token.pop();

        //check if token is a digit + push into tree stack
        if(isdigit(temp[0])) treeNodes.push(new Node(temp));

        //check if token is ) + push into ops stack
        if(temp == ")") ops.push(new Node(temp));

        //check if token is ( + if it is attach and build tree
        if(temp == "(")
        {
             while(ops.top() -> tk != ")")
            {
                attachOperator(treeNodes, ops);
            }
            ops.pop();
        }

        //check if token is an operator + push into node stack
        if(isOperator(temp))
        {
            //loop until operator is placed in stack
            bool pushed = false;
            while(!pushed)
            {
                //push into ops stack if ops is empty
                if(ops.empty())
                {
                    ops.push(new Node(temp));
                    pushed = true;
                } 
                // push if ops has a close parenthesis
                else if(ops.top() -> tk == ")")
                {
                    ops.push(new Node(temp));
                    pushed = true;
                }
                //check priority and push if greater
                else if(priority(temp) > priority(ops.top() -> tk) || priority(temp) == priority(ops.top() -> tk))
                {
                    ops.push(new Node(temp));
                    pushed = true;
                }
                //else attach to build tree
                else
                {
                    attachOperator(treeNodes, ops);
                } 
            } 
        }

        //if token is a function (sin, cos, etc)
        if(isFunction(temp))
        {
            ops.push(new Node(temp));
            attachOperator(treeNodes, ops);
        }
    }

    //attach everything from stack to tree
    while(!ops.empty())
    {
		attachOperator(treeNodes,ops);
	}

    Node* nd = treeNodes.top();
    treeNodes.pop();
    return nd;
}

void attachOperator(stack<Node*>& treeNodes, stack<Node*>& ops)
{
    //get operator
    Node* opsnd = ops.top();
	ops.pop();

    if(isFunction(opsnd -> tk))
    {
        //cout << "attachOperator for sin" << endl;
        opsnd -> left = treeNodes.top();
        treeNodes.pop();
    }
    else
    {
        //attach tree node left and right
        opsnd->left = treeNodes.top();
        treeNodes.pop();
        opsnd->right = treeNodes.top();
        treeNodes.pop();
    }  

    //push the operator to tree stack
	treeNodes.push(opsnd);
}

void Calc::calculate()
{
    //cout << "root: " << root -> tk << endl;
    answer = inorder(root);
}

double inorder(Node *nd)
{ 
    if(isdigit(nd -> tk[0])) return stod(nd -> tk);
    else
    {
        //double l, r;
        // l = inorder(nd -> left);
        // r = inorder(nd -> right);
        if(nd -> tk == "+") 
            return inorder(nd->left)+inorder(nd->right);
        if(nd -> tk == "-")
            return  inorder(nd->left)-inorder(nd->right);
        if(nd -> tk == "*") 
            return  inorder(nd->left)*inorder(nd->right);
        if(nd -> tk == "/")
            return  inorder(nd->left)/inorder(nd->right);
        if(nd -> tk == "^")
            return pow( inorder(nd->left), inorder(nd->right));

        if(nd -> tk == "sin")
            return sin(inorder(nd->left) * (PI/180));
        if(nd -> tk == "cos")
            return cos(inorder(nd->left) * (PI/180));
        if(nd -> tk == "tan")
            return tan(inorder(nd->left) * (PI/180));
        if(nd -> tk == "asin")
            return asin(inorder(nd->left)) * (180/PI);
        if(nd -> tk == "acos")
            return acos(inorder(nd->left)) * (180/PI);
        if(nd -> tk == "atan")
            return atan(inorder(nd->left)) * (180/PI);
        

        if(nd -> tk == "ln")
            return log(inorder(nd->left)); 
        if(nd -> tk == "log")
            return log10(inorder(nd->left));
        if(nd -> tk == "exp")
            return exp(inorder(nd->left));
        
        if(nd -> tk == "sqrt")
            return sqrt(inorder(nd->left));
    }

    return 0;
}

void Calc::printAnswer()
{
    cout << answer << endl;
}

