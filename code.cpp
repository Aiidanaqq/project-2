#include <iostream>
#include <sstream>
#include <cmath>
#include <stack>
using namespace std;

struct Leksema {
    char type;
    double value;
};

bool Maths(stack <Leksema>& Stack_n, stack <Leksema>& Stack_o, Leksema& item) {
    double a, b, c;
    a = Stack_n.top().value;
    Stack_n.pop();
    switch (Stack_o.top().type) {
    case '+':
        b = Stack_n.top().value;
        Stack_n.pop();
        c = a + b;
        item.type = '0';
        item.value = c;
        Stack_n.push(item);
        Stack_o.pop();
        break;
    case '-':
        b = Stack_n.top().value;
        Stack_n.pop();
        c = b - a;
        item.type = '0';
        item.value = c;
        Stack_n.push(item);
        Stack_o.pop();
        break;
    case '^':
        b = Stack_n.top().value;
        Stack_n.pop();
        c = pow(b, a);
        item.type = '0';
        item.value = c;
        Stack_n.push(item);
        Stack_o.pop();
        break;
    case '*':
        b = Stack_n.top().value;
        Stack_n.pop();
        c = a * b;
        item.type = '0';
        item.value = c;
        Stack_n.push(item);
        Stack_o.pop();
        break;
    case '/':
        b = Stack_n.top().value;
        if (a == 0) {
            cerr << "Error! Cannot divide by 0!" << endl;
            return false;
        }
        else {
            Stack_n.pop();
            c = (b / a);
            item.type = '0';
            item.value = c;
            Stack_n.push(item);
            Stack_o.pop();
            break;
        }
    case 'e':
        c = exp(a);
        item.type = '0';
        item.value = c;
        Stack_n.push(item);
        Stack_o.pop();
        break;
    case 's':
        c = sqrt(a);
        item.type = '0';
        item.value = c;
        Stack_n.push(item);
        Stack_o.pop();
        break;
    case 'r':
        c = round(a);
        item.type = '0';
        item.value = c;
        Stack_n.push(item);
        Stack_o.pop();
        break;
    case 'a':
        c = abs(a);
        item.type = '0';
        item.value = c;
        Stack_n.push(item);
        Stack_o.pop();
        break;
    default:
        cerr << "Error!" << endl;
        return false;
    }
    return true;
}

int getRang(char Ch) {
    if (Ch == 'e' || Ch == 's' || Ch == 'r' || Ch == 'a')return 4;
    if (Ch == '^')return 3;
    if (Ch == '+' || Ch == '-')return 1;
    if (Ch == '*' || Ch == '/')return 2;
    else return 0;
}

int main()
{
    cout << "Welcome to the Calculator!" << endl;
    cout << "Please enter your arithmetic expression: ";
    while (true) {
        system("cls");
        std::string str;
        getline(cin, str);
        stringstream sstr{str};

        char Ch;
        double value;
        bool flag = true;
        stack<Leksema> Stack_n;
        stack<Leksema> Stack_o;
        Leksema item;
        while (true) {
            Ch = sstr.peek();
            if (Ch == '\377')break;
            if (Ch == ' ') {
                sstr.ignore();
                continue;
            }
            if (Ch == 'e' || Ch == 'a') {
                char foo[3];
                for (int i = 0; i < 3; i++) {
                    Ch = sstr.peek();
                    foo[i] = Ch;
                    sstr.ignore();
                }
                if (foo[0] == 'e' && foo[1] == 'x' && foo[2] == 'p') {
                    item.type = 'e';
                    item.value = 0;
                    Stack_o.push(item);
                    continue;
                }
                if (foo[0] == 'a' && foo[1] == 'b' && foo[2] == 's') {
                    double operand;
                    sstr >> operand;
                    item.type = 'a';
                    item.value = operand;
                    Stack_n.push(item);
                    continue;
                }
            }
            if (Ch == 's') {
                char foo[4];
                for (int i = 0; i < 4; i++) {
                    Ch = sstr.peek();
                    foo[i] = Ch;
                    sstr.ignore();
                }
                if (foo[0] == 's' && foo[1] == 'q' && foo[2] == 'r' && foo[3] == 't') {
                    item.type = 's';
                    item.value = 0;
                    Stack_o.push(item);
                    continue;
                }
            }
            if (Ch == 'r') {
                char foo[5]; 
                for (int i = 0; i < 5; i++) {
                    Ch = sstr.peek();
                    foo[i] = Ch;
                    sstr.ignore();
                }
                if (foo[0] == 'r' && foo[1] == 'o' && foo[2] == 'u' && foo[3] == 'n' && foo[4] == 'd') {
                    item.type = 'r';
                    item.value = 0;
                    Stack_o.push(item);
                    continue;
                }             
            }    
            if (Ch >= '0' && Ch <= '9' || Ch == '-' && flag == 1) {
                sstr >> value;
                item.type = '0';
                item.value = value;
                Stack_n.push(item);
                flag = 0;
                continue;
            }
            if (Ch == '+' || Ch == '-' && flag == 0 || Ch == '*' || Ch == '/' || Ch == '^') {
                if (Stack_o.size() == 0) {
                    item.type = Ch;
                    item.value = 0;
                    Stack_o.push(item);
                    sstr.ignore();
                    continue;
                }
                if (Stack_o.size() != 0 && getRang(Ch) > getRang(Stack_o.top().type)) {
                    item.type = Ch;
                    item.value = 0;
                    Stack_o.push(item);
                    sstr.ignore();
                    continue;
                }
                if (Stack_o.size() != 0 && getRang(Ch) <= getRang(Stack_o.top().type)) {
                    if (!Maths(Stack_n, Stack_o, item)) {
                        system("pause");
                        return 0;
                    }
                    continue;
                }
            }
            if (Ch == '(') {
                item.type = Ch;
                item.value = 0;
                Stack_o.push(item);
                sstr.ignore();
                continue;
            }
            if (Ch == ')') {
                while (Stack_o.top().type != '(') {
                    if (!Maths(Stack_n, Stack_o, item)) {
                        system("pause");
                        return 0;
                    } else continue;
                }
                Stack_o.pop();
                sstr.ignore();
                continue;
            } else {
                cout << "Expression entered incorrectly!" << endl;
                system("pause");
                return 0;
            }
        }
        while (Stack_o.size() != 0) {
            if (!Maths(Stack_n, Stack_o, item)) {
                system("pause");
                return 0;
            } else continue;
        }
        cout << "Result: " << Stack_n.top().value << endl;
        cout << "Thank you for using the Calculator!" << endl;
        system("pause");
    }
    return 0;
}
