#include "Calculator.h"

int main()
{
    string exprsn;
    while(true)
    {
        cout << ">> ";
        getline(cin, exprsn);
        if(exprsn == "q") break;
        Calc cc;
        cc.readExpression(exprsn);

        cc.calculate();

        cc.printAnswer();
    }
    return 0;
}