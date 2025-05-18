#include "library.h"

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
//<<<<<<<<<<<<<<<<<<<<<<<<<< PROBLEM 1 >>>>>>>>>>>>>>>>>>>>>>>>>>//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//

//================================================================//
//============================== A ===============================//
string Infix2Postfix(const string & expression) 
{
    checkInfixValidity(expression);
    stack <char> operatorStack; string postfix = "";

    for (size_t i = 0; i < expression.length(); i++) 
    {   
        char c = expression[i];
        if (isdigit(c))
        {
            postfix += c;
            while (i+1 < expression.length() && isdigit(expression[i+1])) 
                { postfix += expression[i+1]; i++; }
            postfix += " ";
        } 
        else if (isOperator(c)) 
        {
            while (!operatorStack.empty() && getPrecedence(operatorStack.top()) >= getPrecedence(c)) 
            {
                postfix += operatorStack.top();
                operatorStack.pop();
                postfix += " ";
            }
            operatorStack.push(c);
        }
        else if (c == '(') 
            operatorStack.push(c);
        else if (c == ')') 
        {
            while (!operatorStack.empty() && operatorStack.top() != '(') 
            {
                postfix += operatorStack.top();
                operatorStack.pop();
                postfix += " ";
            }
            if (!operatorStack.empty() && operatorStack.top() == '(')
                operatorStack.pop();
        }
    }
    while (!operatorStack.empty()) 
    {
        postfix += operatorStack.top();
        operatorStack.pop();
        postfix += " ";
    }
    return postfix;
}

//================================================================//
//============================== B ===============================//
string Infix2Prefix(const string & expression) 
{
    checkInfixValidity(expression);

    stack <char> operatorStack;
    string       prefix = "";
    string       reversedExpr = expression;
    reverse (reversedExpr.begin(), reversedExpr.end());

    for (size_t i = 0; i < reversedExpr.length(); i++) 
    {
        char c = reversedExpr[i];
        if (isdigit(c)) 
        {
            prefix += c;
            while (i+1 < reversedExpr.length() && isdigit(reversedExpr[i+1])) 
                { prefix += reversedExpr[i+1]; i++; }
            prefix += " ";
        }
        else if (isOperator(c)) 
        {
            while (!operatorStack.empty() && getPrecedence(operatorStack.top()) > getPrecedence(c)) 
            {
                prefix += operatorStack.top();
                operatorStack.pop();
                prefix += " ";
            }
            operatorStack.push(c);
        }
        else if (c == ')')
            operatorStack.push(c);
        else if (c == '(') 
        {
            while (!operatorStack.empty() && operatorStack.top() != ')') 
            {
                prefix += operatorStack.top();
                operatorStack.pop();
                prefix += " ";
            }
            operatorStack.pop();
        }
    }

    while (!operatorStack.empty()) 
    {
        prefix += operatorStack.top();
        operatorStack.pop();
        prefix += " ";
    }
    reverse(prefix.begin(), prefix.end());
    prefix.erase(prefix.begin());
    
    return prefix;
}

//================================================================//
//============================== C ===============================//
double performOperation(double op1, double op2, char op) 
{
    switch (op) 
    {
        case '+': return op1 + op2;
        case '-': return op1 - op2;
        case '*': return op1 * op2;
        case '/':
            if (op2 == 0)
                throw runtime_error("Divided-by-0");
            return op1 / op2;
        case '^':
            if (op1 == 0 && op2 == 0)
                throw runtime_error("Undefined");
            return pow(op1, op2);
    }
    return -1;
}

double evaluatePostfix(const string & postfix) 
{
    stack <double> operands;
    stringstream   ss(postfix);
    string         token;

    while (ss >> token) 
    {
        if ( isOperator(token[0]) && (!token[1] && !isdigit(token[1])) ) 
        {
            double op2 = operands.top(); operands.pop();
            double op1 = operands.top(); operands.pop();
            double result = performOperation(op1, op2, token[0]);
            operands.push(result);
        } 
        else operands.push(stod(token));
    }
    return operands.top();
}

double evaluatePrefix(const string & prefix) 
{
    stack <double> operands;
    stringstream   ss(prefix);

    istream_iterator <string> begin(ss), end;
    vector           <string> tokens(begin, end);

    for (auto it = tokens.rbegin(); it != tokens.rend(); ++it) 
    {
        if (isOperator((*it)[0]) && !(*it)[1]) 
        {
            double op1 = operands.top(); operands.pop();
            double op2 = operands.top(); operands.pop();
            double result = performOperation(op1, op2, (*it)[0]);
            operands.push(result);
        }
        else operands.push(stod(*it));
    }
    return operands.top();
}


bool isPrefixExpression(const string & expression) {
    for (size_t i = 0; i < expression.size(); i++) 
    {
        if (isspace(expression[i])) 
            continue;
        if (isOperator(expression[i]) && isspace(expression[i+1]))
            return true;
        if (isdigit(expression[i]))
            return false;
    }
    return false;
}

string PostfixPrefixCalculator(string expression) 
{
    double result = isPrefixExpression(expression) ? 
                    evaluatePrefix(expression) : evaluatePostfix(expression);
    stringstream ss;
    ss << fixed << setprecision(4) << result;
    string FinalResult = ss.str();

    for (size_t i = FinalResult.size()-1; i >= 0; i--)
    {
        if (FinalResult[i] != '0' && FinalResult[i] != '.')
            break;
        if (FinalResult[i] == '.')
        {
            FinalResult.pop_back();
            break;
        }
        FinalResult.pop_back();
    }
    return FinalResult;
}




//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
//<<<<<<<<<<<<<<<<<<<<<<<<<< PROBLEM 2 >>>>>>>>>>>>>>>>>>>>>>>>>>//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//

//================================================================//
//============================== A ===============================//
string LogicInfix2Postfix (string infix)  
{
    checkLogicInfixValidity(infix);
    stack <string> st; string postfix;

    for (size_t i = 0; i < infix.size(); ++i) 
    {
        string op(1, infix[i]);

        if(op == "<")
        {
            op += infix[++i];
            op += infix[++i];
        } 
        if (op == "-") 
            op += infix[++i];
        if (isalpha(op[0]))
            postfix += op;
        else if (op == "(")
            st.push(op);
        else if (op == ")") 
        {
            while (!st.empty() && st.top() != "(") 
            {
                postfix += st.top();
                st.pop();
            }
            if (!st.empty()) st.pop();
        } 
        else 
        {
            if (op != " ")
            {
                while (!st.empty() && getLogicPrecedence(st.top()) >= getLogicPrecedence(op)) 
                {
                    postfix += st.top();
                    st.pop();
                }
            st.push(op);
            }
        }
    }
    while (!st.empty()) 
    {
        postfix += st.top();
        st.pop();
    }
    return postfix;
}

//================================================================//
//============================== B ===============================//
string LogicInfix2Prefix (string infix) 
{
    checkLogicInfixValidity(infix);

    reverse(infix.begin(), infix.end());
    stack <string> st; string prefix;

    for (size_t i = 0; i < infix.size(); ++i) {
        string op(1, infix[i]);

        if (isalpha(op[0]))
            prefix = op + prefix;
        else if (op == ")")
            st.push(op);
        else if (op == "(") 
        {
            while (!st.empty() && st.top() != ")") 
            {
                prefix = st.top() + prefix;
                st.pop();
            }
            if (!st.empty())
                st.pop();
        } 
        else 
        {
            if (op != " ")
            {
                if (infix[i] == '>')
                {
                    if(infix[i+2] && infix[i+2] == '<')
                        { op = "<->"; i += 2; }
                    else 
                        { op = "->"; i++; }
                }
                while (!st.empty() && getLogicPrecedence(st.top()) > getLogicPrecedence(op)) 
                {
                    prefix = st.top() + prefix;
                    st.pop();
                }
                st.push(op);
            }
        }
    }

    while (!st.empty()) 
    {
        prefix = st.top() + prefix;
        st.pop();
    }
    return prefix;
}


//================================================================//
//============================== C ===============================//
bool performLogicOperation (bool op1, bool op2, char op) 
{
    switch (op) 
    {
        case '&': return (op1 && op2);
        case '|': return (op1 || op2);
        case '-': return (!op1 || op2);
        case '<': return ((!op1 || op2) && (!op2 || op1));
    }
    return -1;
}

bool evaluateLogicPostfix (const string & postfix) 
{
    stack <bool> operands;
    for (size_t i = 0; i < postfix.size(); ++i) 
    {
        bool value;
        if (postfix[i] == '1')   value = true;
        if (postfix[i] == '0')   value = false;
        if (postfix[i] == '~') { operands.top() = !operands.top(); continue; }
        if (isLogicOperator(postfix[i])) 
        {
            bool op1 = operands.top(); operands.pop();
            bool op2 = operands.top(); operands.pop();
            bool result = performLogicOperation(op1, op2, postfix[i]);
            if (postfix[i] == '-')  i++;
            if (postfix[i] == '<')  i += 2;
            operands.push(result);
        } 
        else  operands.push(value);
    }
    return operands.top();
}

bool evaluateLogicPrefix (const string & prefix) 
{
    stack<bool> operands;
    
    for (int i = prefix.size()-1; i >= 0 ; i--) 
    {
        bool value;
        if (prefix[i] == '1')   value = true;
        if (prefix[i] == '0')   value = false;
        if (prefix[i] == '~') { operands.top() = !operands.top(); continue; }
        if (isLogicOperator(prefix[i])) 
        {
            if (prefix[i] == '-')
                if (prefix[i-1])
                    if (prefix[i-1] == '<')
                        i--;
            bool op1 = operands.top(); operands.pop();
            bool op2 = operands.top(); operands.pop();
            bool result = performLogicOperation(op2, op1, prefix[i]);
            operands.push(result);
        } 
        else if (prefix[i] != '>')
            operands.push(value);
    }
    return operands.top();
}

bool isLogicPrefixExpression (const string& expression) 
{
    if (expression[0] == '~') return true;
    return isLogicOperator(expression[0]);
}

string assignValue (string expression, string variables)
{
    checkVariablesValidity (expression, variables);

    string s = "";
    int midpoint = variables.size() / 2 + 1;

    for (size_t i = 0; i < expression.size(); ++i)
    {
        if (isalpha(expression[i]))
        {
            for (size_t j = 0; j < variables.size(); ++j)
            {
                if (expression[i] == variables[j])
                {
                    s += variables[midpoint + j];
                    break;
                }
            }
        } else s += expression[i];
    }
    return s;
}

string LogicPostfixPrefixCalculator(string expression, string variables) 
{
    // if the expression is prefix then call evaluateLogicPrefix, otherwise call evaluateLogicPostfix
    bool result   = isLogicPrefixExpression(expression) ? 
        evaluateLogicPrefix ( assignValue(expression, variables) ) : 
        evaluateLogicPostfix( assignValue(expression, variables) );
    
    return (result)? "TRUE" : "FALSE";
}
