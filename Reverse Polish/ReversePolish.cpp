#include <iostream>
#include <sstream>
using namespace std;

class Node
{
public:

    double info;				//data
    class Node *next;	    //link

    Node(double data, Node *ptr = 0)   //constructor
	{
        info = data; 
		next = ptr;
    }
};

class linkStack
{
private:
    Node *top;
public:
    linkStack()
    {
        top = 0;        //initialze top
    }

    bool isEmpty()
    {
        return top == 0;
    }

    void push(double data)
    {
        Node *temp = new Node(data);        //create node

        if(isEmpty())
            top = temp;
        else
        {
            temp->next = top;       //add node to the top of stack
            top = temp;
        }
    }

    double pop()
    {
        if(isEmpty())
            return -999;
        
        double doubleReturn = top->info;

        Node *temp;     //pointer to the top node
        temp = top;

        top = top->next;

        delete temp;        //free up memory

        return doubleReturn;
    }

    float math(double a, double b, string op)       //calculations using top 2 stacks and an operator
    {
        if(op == "+")
            return b+a;
        else if(op == "-")
            return b-a;
        else if(op == "*")
            return b*a;
        else if(op == "/")
        {
            if (a == 0)       
            {
                return -998;    //divide by zero exception
            }
            else return b/a;
        }
        else return -999;
    }

    float ReversePolish(string expression)          //takes in expression and returns the calculated reverse polish
    {
        stringstream input(expression);
        string value;


        int operatorCount = 0;
        int operandCount = 0;
        double a, b;
        while(!input.eof())     //loop until no more inputs
        {
            input >> value;     //insert separated input into value

            stringstream current1(value);
            stringstream current2(value);

            string op;
            double operand;
            current1 >> op;

            if (op == "+"|| op == "-"|| op == "*"|| op == "/")  //Checking if the string is an operator
            {
                a = top->info;      //a becomes the top of the number at the top of the stack
                pop();              //remove the top stack
                b = top->info;      //b is now the top of stack
                pop();
                push(math(a, b, op));       //push the solved expression to the top of stack
                operatorCount++;
            }
            else if (current2 >> operand)       //if it wasn't an operator, push an operand to the top of the stack
            {
                operandCount++;
                push(operand);
            }
        }

        //Operator/Operand Errors
        if (operandCount - 1 > operatorCount)
        {
            return -997;        //too many operands exception
        }
        if (operandCount - 1 < operatorCount)
        {
            return -996;        //too many operands exception
        }
        else
        return top->info;                       //Return the solved expression
    }

    void PrintReversePolish(string expression)
    {
        if (ReversePolish(expression) == -998)          //Print Errors
        {
            cout << "Error: Division by zero";
        }
        else if (ReversePolish(expression) == -997)
        {
            cout << "Error: Too many operands";
        }
        else if (ReversePolish(expression) == -996)
        {
            cout << "Error: Too many operators";
        }
        else                                            //Print solved expression
            cout << top->info;
    }

};

int main()
{
    linkStack stack;

    string expression = "10 15 +";
    cout << expression << " = ";
    stack.PrintReversePolish(expression);

    string expression2 = "10 15 -";
    cout << endl << expression2 << " = ";
    stack.PrintReversePolish(expression2);

    string expression3 = "2.5 3.5 +";
    cout << endl << expression3 << " = ";
    stack.PrintReversePolish(expression3);

    string expression4 = "10 0 /";
    cout << endl << expression4 << " = ";
    stack.PrintReversePolish(expression4);

    string expression5 = "10 20 * /";
    cout << endl << expression5 << " = ";
    stack.PrintReversePolish(expression5);

    string expression6 = "12 20 30 /";
    cout << endl << expression6 << " = ";
    stack.PrintReversePolish(expression6);

    string expression7 = "-10 -30 -";
    cout << endl << expression7 << " = ";
    stack.PrintReversePolish(expression7);

    string expression8 = "100 10 50 25 / * - -2 /";
    cout << endl << expression8 << " = ";
    stack.PrintReversePolish(expression8);

    return 0;
}

// Output:
// 10 15 + = 25
// 10 15 - = -5
// 2.5 3.5 + = 6
// 10 0 / = Error: Division by zero
// 10 20 * / = Error: Too many operators
// 12 20 30 / = Error: Too many operands
// -10 -30 - = 20
// 100 10 50 25 / * - -2 / = -40