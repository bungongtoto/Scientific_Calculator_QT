#ifndef CALCULATE
#define CALCULATE

#include <iostream>
#include <stack>
#include <string>
#include <cmath>
using namespace std;

/**
 * @class Calculate
 * @brief brief description object is used to evaluate infix expressions
 * @param Operant used to store operands during calculation
 * @param Expression  holds the postfix expression of infix expression to be evaluaed
 * @param result holds the result of the evaluation
 */
class Calculate{
    private:
    static int const max = 50;
    stack <char> Pstack;
    stack <string> Operant;
    string postfix;
    const string operators{"x - + ^ /"};
    string Expression[max];
    string result;


    bool isOperator(char toCheck);
    int precedence(char toCheck);
    bool contains(string str , string tocheck);
    int len(string str);
    void split_postfix(string str, const char seperator);
    static void removeTrailingCharacters(std::string &str, const char charToRemove);


    public:
    void convert_infix_to_postfix(string infix);
    void Evaluate_postfix();
    string get_answer();

};
/**
 * @fn convert_infix_to_postfix(string infix) @brief converts enter infix expression to postfix
 * @fn Evaluate_postfix() @brief evaluates the derived postfix expression
 * @fn get_answer() @brief returns the answer of the evaluation.
 * 
 */
#endif
