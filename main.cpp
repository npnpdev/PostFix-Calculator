#include <iostream>

using namespace std;

#define MAX_SIZE 10
const char operators[] = {'+', '-', '*', '/'};
const char functions[] = {'M', 'N', 'I'};

struct tokenType{
    char data[15];

    void print() const {
        if (data[0] != '\0') {
            cout << data;
        }
    }

    char getCharAt(int index) const {
        int length = 0;
        while (this->data[length] != '\0') {
            length++;
        }

        if (index >= 0 && index < length) {
            return this->data[index];
        } else {
            return '\0';
        }
    }

    tokenType operator+(const tokenType& other) const {
        tokenType result;
        int i = 0;

        // Copy from first element
        for (; data[i] != '\0'; ++i) {
            result.data[i] = data[i];
        }

        // Copy from second element
        for (int j = 0; other.data[j] != '\0'; ++j, ++i) {
            result.data[i] = other.data[j];
        }

        // End of string
        result.data[i] = '\0';

        return result;
    }
};

struct stosElement{
    tokenType data;
    stosElement* next;
};

//add new element to stack
void push(stosElement* &topOfStack, const tokenType &tokenData) {
    stosElement* newTopOfStack = new stosElement;
    newTopOfStack->data = tokenData;
    newTopOfStack->next = topOfStack;

    topOfStack = newTopOfStack;
}

//remove last token from stack
void pop(stosElement* &topOfStack){
    if(topOfStack == nullptr) return;

    stosElement *temp = topOfStack;
    topOfStack = topOfStack->next;

    delete temp;
}

bool isNumber(char token) {
    return token >= '0' && token <= '9';
}

//show stack
void show(stosElement *topOfStack){
    stosElement* temp = topOfStack;

    while(temp != nullptr){
        temp->data.print();
        cout << " ";
        temp = temp->next;
    }
}

tokenType convertToToken(const char *token){
    tokenType newToken;
    int i = 0;

    while (token[i] != '\0') {
        newToken.data[i] = token[i];
        i++;
    }
    newToken.data[i] = '\0';

    return newToken;
}

int countArguments(stosElement* &topOfStack_amount){
    int n_arguments = 0;

    while(topOfStack_amount->data.getCharAt(0) != '('){
        n_arguments++;
        pop(topOfStack_amount);
    }

    //Remove '('
    pop(topOfStack_amount);

    return n_arguments;
}

bool isOperator(char token){
    int numOperators = sizeof(operators) / sizeof(operators[0]);

    for(int i=0; i<numOperators; i++){
        if(token == operators[i]) return true;
    }

    return false;
}

bool isFunction(char token){
    int numFunctions = sizeof(functions) / sizeof(functions[0]);

    for(int i=0; i<numFunctions; i++){
        if(token == functions[i]) return true;
    }

    return false;
}

int operatorPriority(char token){
    if(token == '+' || token == '-') return 1;
    if(token == '*' || token == '/') return 2;
    if(token == '(' || token == ')') return 4;

    return 3;
}

void reverseStack(stosElement* &topOfStack) {
    stosElement* tempStack = nullptr;

    while (topOfStack != nullptr) {
        stosElement* temp = topOfStack;
        topOfStack = topOfStack->next;
        temp->next = tempStack;
        tempStack = temp;
    }

    topOfStack = tempStack;
}

void clearStack(stosElement* &topOfStack) {
    while(topOfStack != nullptr) {
        pop(topOfStack);
    }
}

void addNumberOfArguments(stosElement* &topOfStack_operand, int n_arguments){
    tokenType argumentsToken;
    snprintf(argumentsToken.data, sizeof(argumentsToken.data), "%d", n_arguments);

    //Function + number of arguments
    argumentsToken = topOfStack_operand->data + argumentsToken;

    //Remove old function without arguments
    pop(topOfStack_operand);

    //Add new function with number of arguments
    push(topOfStack_operand, argumentsToken);
}

int processIf(stosElement* &topOfStack_operator){
    int operand1 = atoi(topOfStack_operator->data.data);
    pop(topOfStack_operator);

    int operand2 = atoi(topOfStack_operator->data.data);
    pop(topOfStack_operator);

    int operand3 = atoi(topOfStack_operator->data.data);
    pop(topOfStack_operator);

    cout << "IF " << operand1 << " " << operand2 << " " << operand3 << " ";
    show(topOfStack_operator);
    cout << endl;


    if(operand3 > 0){
        return operand2;
    }
    else{
        return operand1;
    }
}

int processN(stosElement* &topOfStack_operand, stosElement* &topOfStack_operator){
    int operand = atoi(topOfStack_operator->data.data);
    pop(topOfStack_operator);

    cout << topOfStack_operand->data.getCharAt(0) << " " << operand << " ";
    show(topOfStack_operator);
    cout << endl;

    return -operand;
}

int processMinMax(stosElement* &topOfStack_operand, stosElement* &topOfStack_operator, char operatorType){
    int n_arguments = topOfStack_operand->data.getCharAt(3) - '0';

    if(operatorType == '>'){
        cout << "MAX" << n_arguments << " ";
    }
    else{
        cout << "MIN" << n_arguments << " ";
    }

    show(topOfStack_operator);
    cout << endl;

    int result = atoi(topOfStack_operator->data.data);
    pop(topOfStack_operator);

    for(int i=0; i<n_arguments - 1; i++){
        if (topOfStack_operator != nullptr){
            if(operatorType == '>'){
                if(atoi(topOfStack_operator->data.data) > result){
                    result = atoi(topOfStack_operator->data.data);
                }
            }
            else{
                if(atoi(topOfStack_operator->data.data) < result){
                    result = atoi(topOfStack_operator->data.data);
                }
            }

            pop(topOfStack_operator);
        }
    }

    return result;
}

bool processOperators(stosElement* &topOfStack_operand, stosElement* &topOfStack_operator, int &result) {
    int operand2 = atoi(topOfStack_operator->data.data);
    pop(topOfStack_operator);

    int operand1 = atoi(topOfStack_operator->data.data);
    pop(topOfStack_operator);

    // Show content of stack
    cout << topOfStack_operand->data.getCharAt(0) << " " << operand2 << " " << operand1 << " ";
    show(topOfStack_operator);
    cout << endl;

    switch (topOfStack_operand->data.getCharAt(0)) {
        case '+':
            result = operand1 + operand2;
            break;
        case '-':
            result = operand1 - operand2;
            break;
        case '*':
            result = operand1 * operand2;
            break;
        case '/':
            if (operand2 != 0) {
                result = operand1 / operand2;
            } else {
                cout << "ERROR" << endl;
                return false;
            }
            break;
        default:
            cout << "Error: Unknown operator." << endl;
            return false;
    }

    return true;
}

void addRestOfOperators(stosElement* &topOfStack_operand, stosElement* &topOfStack_operator, int n_arguments){
    if(topOfStack_operator != nullptr) {
        while (topOfStack_operator != nullptr) {
            push(topOfStack_operand, topOfStack_operator->data);

            if(topOfStack_operator->data.getCharAt(0) == 'M'){
                addNumberOfArguments(topOfStack_operand, n_arguments);
            }

            pop(topOfStack_operator);
        }
    }
}

void processEndOfFunction(stosElement* &topOfStack_operand, stosElement* &topOfStack_operator, stosElement* &topOfStack_amount, const tokenType &newToken) {
    push(topOfStack_amount, newToken);

    if(topOfStack_operator != nullptr && topOfStack_operator->data.getCharAt(0) == '('){
        pop(topOfStack_operator);
        push(topOfStack_operand, topOfStack_operator->data);
        pop(topOfStack_operator);
    }
    else{
        while(topOfStack_operator != nullptr && topOfStack_operator->data.getCharAt(0) != '('){
            push(topOfStack_operand, topOfStack_operator->data);
            pop(topOfStack_operator);
        }
        pop(topOfStack_operator);
    }
}

void processArgumentsCounting(stosElement *&topOfStack_operand, stosElement *&topOfStack_amount, int &n_arguments) {
    n_arguments = countArguments(topOfStack_amount);

    if(isFunction(topOfStack_operand->data.getCharAt(0))){
        if(topOfStack_operand->data.getCharAt(0) == 'M'){
            addNumberOfArguments(topOfStack_operand, n_arguments);
        }
    }
}

void calculationsONP(stosElement* &topOfStack_operand, stosElement* &topOfStack_operator) {
    int result = 0;

    while (topOfStack_operand != nullptr) {
        if (isNumber(topOfStack_operand->data.getCharAt(0))) {
            push(topOfStack_operator, topOfStack_operand->data);
            pop(topOfStack_operand);
        } else {
            if(isFunction(topOfStack_operand->data.getCharAt(0)) && topOfStack_operator != nullptr) {
                char functionType = topOfStack_operand->data.getCharAt(0);
                if(functionType == 'N' && topOfStack_operator != nullptr)
                    result = processN(topOfStack_operand, topOfStack_operator);
                else if(functionType == 'I' && topOfStack_operator != nullptr && topOfStack_operator->next != nullptr && topOfStack_operator->next->next != nullptr)
                    result = processIf(topOfStack_operator);
                else if(functionType == 'M')
                    result = processMinMax(topOfStack_operand, topOfStack_operator, (topOfStack_operand->data.getCharAt(1) == 'A') ? '>' : '<');
            } else {
                if (topOfStack_operator != nullptr && topOfStack_operator->next != nullptr) {
                    if(!processOperators(topOfStack_operand, topOfStack_operator, result)) return;
                }
            }
            tokenType resultToken;
            snprintf(resultToken.data, sizeof(resultToken.data), "%d", result);
            push(topOfStack_operator, resultToken);
            pop(topOfStack_operand);
        }
    }

    show(topOfStack_operator);
    cout << endl;
}

int main() {
    stosElement *topOfStack_operand = nullptr;
    stosElement *topOfStack_operator = nullptr;
    stosElement *topOfStack_amount = nullptr;

    char token[MAX_SIZE+1];
    int n_arguments = 0;
    int n_formulas = 0;
    cin >> n_formulas;

    for (int i = 0; i < n_formulas; i++) {
        while (scanf("%10s", token) != EOF && token[0]!='.') {
            tokenType newToken = convertToToken(token);
            if(token[0] != ','){
                if(isNumber(token[0])){
                    push(topOfStack_operand, newToken);
                }
                else{
                    if(token[0] == ')'){
                        processEndOfFunction(topOfStack_operand, topOfStack_operator, topOfStack_amount, newToken);
                        processArgumentsCounting(topOfStack_operand, topOfStack_amount, n_arguments);
                    }
                    else{
                        if(token[0] == '('){
                            push(topOfStack_amount, newToken);
                        }
                        //Operators logic
                        if(isOperator(token[0])){
                            while (topOfStack_operator != nullptr && topOfStack_operator->data.getCharAt(0) != '(' &&
                                   operatorPriority(token[0]) <= operatorPriority(topOfStack_operator->data.getCharAt(0))) {
                                push(topOfStack_operand, topOfStack_operator->data);
                                pop(topOfStack_operator);
                            }
                        }
                        push(topOfStack_operator, newToken);
                    }
                }
            }
            else{
                while(topOfStack_operator->data.getCharAt(0) != '('){
                    push(topOfStack_operand, topOfStack_operator->data);
                    pop(topOfStack_operator);
                }

                //Counting ','
                n_arguments++;
                push(topOfStack_amount, newToken);
            }
        }

        //Add rest of operators at the end of RPN (ONP) expression
        addRestOfOperators(topOfStack_operand, topOfStack_operator, n_arguments);

        //ONP expression
        reverseStack(topOfStack_operand);
        show(topOfStack_operand);
        cout << endl;

        //Calculation
        calculationsONP(topOfStack_operand, topOfStack_operator);

        //Prepare stacks for next expression
        clearStack(topOfStack_operand);
        clearStack(topOfStack_operator);
        clearStack(topOfStack_amount);
    }

    delete topOfStack_operator;
    delete topOfStack_operand;
    delete topOfStack_amount;

    return 0;
}