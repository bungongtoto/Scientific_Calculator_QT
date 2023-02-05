#include "calculate.h"

bool Calculate::isOperator(char toCheck){
    if(toCheck == '+' ||toCheck == '-' ||toCheck == 'x' ||toCheck == '/' ||toCheck == '^')
    {
        return true;
    }else{
        return false;
    }
}

int Calculate::precedence(char toCheck){
    if (toCheck == '^'){
        return 3;
    }else if (toCheck == 'x' || toCheck == '/'){
        return 2;
    }else if(toCheck == '+' || toCheck == '-'){
        return 1;
    }else{
        return -1;
        }
}

void Calculate::convert_infix_to_postfix(string infix){
    
    for(int i=0; i<infix.length(); i++){
        // first condition:: if the we have an operand 100x(2+12)/14
        if(isdigit(infix[i]) || infix[i] == '.'){
            postfix += infix[i];
        }else if(infix[i] == '(')//2nd condition
        {
            Pstack.push(infix[i]);
        }else if(infix[i] == ')')
        {
            while((Pstack.top() != '(')){
                char temp = Pstack.top();
                postfix =postfix+ " " + temp;
                Pstack.pop();
            }
            if(Pstack.top()=='(')
            {
                Pstack.pop();
            }
        }else if(isOperator(infix[i]))
        {
            postfix += " ";
            if(Pstack.empty()){
                Pstack.push(infix[i]);
            }else
            {
                if (precedence(infix[i]) > precedence(Pstack.top()))
                {
                    Pstack.push(infix[i]);
                }
                else if((precedence(infix[i])==precedence(Pstack.top())) && (infix[i]=='^'))
                {
                    Pstack.push(infix[i]);
                }else{
                    while((!Pstack.empty())&&(precedence(infix[i]) <= precedence(Pstack.top())))
                    {
                        char temp = Pstack.top();
                        postfix = postfix + temp + " ";
                        Pstack.pop();
                    }
                    Pstack.push(infix[i]);
                }
            }
        }
    }
    while(!Pstack.empty())
    {
        postfix = postfix + " " + Pstack.top();
        Pstack.pop();
    }
}

bool Calculate::contains(string str , string tocheck){
    if (str.find(tocheck) != string::npos){
        return true;
    }else{
        return false;
    }
}

int Calculate::len(string str){
    int length = 0;  
    for (int i = 0; str[i] != '\0'; i++)  
    {  
        length++;  
          
    }  
    return length; 
}

void Calculate::split_postfix(string str, const char seperator){
    int currIndex = 0, i = 0;  
    int startIndex = 0, endIndex = 0;  
    while (i <= len(str))  
    {  
        if (str[i] == seperator || i == len(str))  
        {  
            endIndex = i;  
            string subStr = "";  
            subStr.append(str, startIndex, endIndex - startIndex);  
            Expression[currIndex] = subStr;  
            currIndex += 1;  
            startIndex = endIndex + 1;  
        }  
        i++;  
    }
    postfix = "";
}

void Calculate::Evaluate_postfix(){ 
    double ans = 0.0;
    double num1{0.0};
    double num2{0.0};
    split_postfix(postfix,' '); 
    for(int i = 0 ; i < max; i++ ){
        if (Expression[i].empty()){
            break;
        }else{
            if (!contains(operators, Expression[i])){
                Operant.push(Expression[i]);
            }
            else{
                num1 = stod(Operant.top());
                Operant.pop();
                num2 = stod(Operant.top());
                Operant.pop();
                if(Expression[i] == "+"){
                    ans = num2 + num1;
                }else if(Expression[i] == "-"){
                    ans =num2 - num1;
                }else if(Expression[i] == "x"){
                    ans =num2 * num1;
                }else if(Expression[i] == "/"){
                    ans =num2 / num1;
                }else if(Expression[i] == "^"){
                    ans =pow(num2,num1);
                }
                Operant.push(to_string(ans));
            }
        }
    }
    result =Operant.top();
    Operant.pop();
    Expression->clear();
}

void Calculate::removeTrailingCharacters(std::string &str, const char charToRemove) {
    str.erase (str.find_last_not_of(charToRemove) + 1, std::string::npos );
}
string Calculate::get_answer(){
    if(fmod(stod(result),1) == 0.0){
        double holdf = stod(result);
        int holdI = floor(holdf);
        return  to_string(holdI);
    }else{
        removeTrailingCharacters(result,'0');
        return  result;
    }
    result ="";
}
