#include <iostream>
#include <string>

using namespace std;

class Calculator{
private:
string signs = "+-*/=()";
protected:
    string number (string n) {
        if (n.find('.') == string::npos) {
            n += '.';
        }
        for (int i = 0; i < n.size(); i++){
            if (n[n.size()-i-1] != '0') {
                n.erase(n.size()-i, i+1);
                break;
            }
        }
        if (n[n.size()-1] == '.') {
            n.erase(n.size()-1, 1);
        }
        return n;
    }

    string expression (string n) {
        double list[2];
        int i;

        for (i = 1; i < n.size(); i++) {
            if (n[i] == '+' || n[i] == '-' || n[i] == '*' || n[i] == '/') {
                list[0] = stod(n.substr(0, i));
                list[1] = stod(n.substr(i+1, n.size()+1));
                break;
            }
        }

        switch (n[i])
        {
        case '+':
            return to_string(list[0]+list[1]);
        case '-':
            return to_string(list[0]-list[1]);
        case '*':
            return to_string(list[0]*list[1]);
        case '/':
            return to_string(list[0]/list[1]);
        }

        return "Error";
    }

    string all_expressions (string x){
        string n;
        int count = 0, i = 0, id[] = {0, 0, 0}, priority;

        while (true) {
            for (i = id[2]; count < 3; i++) {
                    if ((this->signs.find(x[i]) != string::npos) && (this->signs.find(x[i-1]) == string::npos)) {
                        id[count] = i;
                        count += 1;
                    }
                }
            if (((x.find("+") == string::npos) && (x.find("-") == string::npos) && (x.find("*") == string::npos) && (x.find("/") == string::npos)) || ((this->signs.find(x[1]) != string::npos) && (id[1] == x.size()-1))) {
                return number(x.substr(1, x.size()-2));
            } else {
                priority = (x.find("*") != string::npos) || (x.find("/") != string::npos);
                if (priority == 1 && (x[id[1]] != '*' && x[id[1]] != '/')) {
                    id[0] = id[1];
                    count = 1;
                    continue;
                }
            }
            n = number(expression(x.substr(id[0]+1, id[2]-id[0]-1)));
            x.erase(id[0]+1, id[2]-id[0]-1);
            x = x.insert(id[0]+1, n);
            count = 0;
            id[0] = 0;
            id[1] = 0;
            id[2] = 0;
        }
    }

    string brackets (string x){
        string n;
        int count = 0, i = 0, id[] = {0, 0};

        while (true) {
            if ((x.find("(") != string::npos) && (x.find(")") != string::npos)){
                for (i = 0; count < 1; i++) {
                        if (x[i] == '(') {
                            id[0] = i;
                        } if (x[i] == ')') {
                            id[1] = i;
                            count = 1;
                        }
                    }
                    n = all_expressions(x.substr(id[0], id[1]-id[0]+1));
                    x.erase(id[0], id[1]-id[0]+1);
                    x = x.insert(id[0], n);
                    count = 0;
                    id[0] = 0;
                    id[1] = 0;
            } else if ((x.find("(") != string::npos) || (x.find(")") != string::npos)){ 
                return "Error: the code must contain an odd number of parentheses="; 
            } else {
                return all_expressions(x);
            }
        }
    }

public:
    Calculator (){
        cout << "start" << endl;
    }

    void clear () {
        for (int i = 0; i < 50; i++) {
            cout << endl;
        }
    }
    
    string start (string x){
        if (x == "=clear=") {
            clear();
            return "";
        } else {
            return "="+brackets(x);
        }
    }

    ~Calculator () {
        cout << "end" << endl;
    }
};

class Sett : public Calculator {
public:
    string sett_number (string n) {
        return number (n);
    }
};

int main() {
    Calculator C;
    string enter;
    C.clear();


    while (enter != "0") {
        cin >> enter;
        cout << endl << C.start("="+enter+"=") << endl << endl;
    }
    return 0;
}