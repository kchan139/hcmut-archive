#include "sub.cpp"

int main ()
{
    try
    {
        // PROBLEM 1
        string expression;
        cout << "Enter a arithmetic expression: ";
        getline(cin, expression);
        string postfix = Infix2Postfix(expression);
        string prefix  = Infix2Prefix(expression);

        cout << "Postfix: "    << postfix << endl;
        cout << "Prefix: "     << prefix << endl;
        cout << "Postfix Evaluation: " << PostfixPrefixCalculator(postfix) << endl;
        cout << "Prefix Evaluation: " << PostfixPrefixCalculator(prefix) << endl << endl;


        // PROBLEM 2
        string logic_expression;
        cout << "Enter a logic expression: ";
        getline(cin, logic_expression);

        // Infix to Postfix and Prefix
        string logic_postfix = LogicInfix2Postfix(logic_expression);
        string logic_prefix  = LogicInfix2Prefix(logic_expression);
        cout << "Postfix: "    << logic_postfix << endl;
        cout << "Prefix: "     << logic_prefix << endl;

        // Postfix and Prefix Evaluation
        string var_values;
        cout << "Enter values for variables: ";
        getline(cin, var_values);
        cout << "Postfix Evaluation: " << LogicPostfixPrefixCalculator(logic_postfix, var_values) << endl;
        cout << "Prefix Evaluation: " << LogicPostfixPrefixCalculator(logic_prefix, var_values) << endl << endl;
        
    }
    catch (const runtime_error & error) 
    { cout << "Error: " << error.what() << endl; }

    return 0;
}