#include <iostream>
#include <string>
#include <cctype>
#include <fstream>



using std::cout;
using std::string;
using std::cin;


int main() {

    string input = "C:\\Users\\Jaron L\\Desktop\\Freizeit\\AdventOfCode\\Day3\\input.txt";
   

    std::ifstream file(input);
    if (!file.is_open()) {
        std::cerr << "Fehler beim Öffnen der Datei." << std::endl;
        return 1;
    }



    enum State { START, M, MU, MUL,  D, DO, DON, DON_APOSTROPHE, DONT, OPEN_PAREN, READ_X, COMMA, READ_Y, CLOSE_PAREN, DO_OPEN_PAREN, DO_CLOSE_PAREN,
    DONT_OPEN_PAREN, DONT_CLOSE_PAREN };
    State currentState = START;
    int total = 0;
    int x = 0, y = 0;
    int digitCountX = 0, digitCountY = 0;
    char c;
    bool isEnabled = true;

    while(file.get(c)) {
        switch(currentState) {

            case START:
                x = y = 0;
                digitCountX = digitCountY = 0;
                if(c == 'm') currentState = M;
                if(c == 'd') currentState = D;
                break;
            case M:
                if(c == 'u') currentState = MU;
                else currentState = START;
                break;
            case MU:
                if(c == 'l') currentState = MUL;
                else currentState = START;
                break;
            case MUL:
                if(c == '(') currentState = OPEN_PAREN;
                else currentState = START;
                break;

            //do und don't
            case D:
                if(c == 'o') currentState = DO;
                else currentState = START;
                break;
            case DO:
                if(c == '(') currentState = DO_OPEN_PAREN;
                else if(c == 'n') currentState = DON;
                else  currentState = START;
                break;
            case DON:
                if(c == '\'') currentState = DON_APOSTROPHE;
                else currentState = START;
                break;
            case DON_APOSTROPHE:
                if(c == 't') currentState = DONT;
                else currentState = START;
                break;
            case DONT:
                if(c == '(') currentState = DONT_OPEN_PAREN;
                else currentState = START;
                break;
            
            //'do()'
            case DO_OPEN_PAREN:
                if(c == ')') {
                    isEnabled = true;
                    currentState = DO_CLOSE_PAREN;
                } else currentState = START;
                break;
            case DO_CLOSE_PAREN:
                if(c == 'm') currentState = M;
                else if(c == 'd') currentState = D;
                break;

            // 'don't()'
            case DONT_OPEN_PAREN:
                if(c == ')') {
                    isEnabled = false;
                    currentState = DONT_CLOSE_PAREN;
                } else currentState = START;
                break;
            case DONT_CLOSE_PAREN:
                if(c == 'm') currentState = M;
                else if(c == 'd') currentState = D;
                break;

            case OPEN_PAREN:
                if(std::isdigit(c)) {
                    x = c - '0';                                  // '5' - '0' = 5 (int) 
                    digitCountX = 1;
                    currentState = READ_X;
                } else  currentState = START;
                break;
            case READ_X:
                if(std::isdigit(c) && digitCountX < 3) {
                    x = x * 10 + (c - '0');
                    digitCountX++;
                } else if(c == ','  && digitCountX > 0) {
                    currentState = COMMA;
                } else currentState = START;
                break;
            case COMMA:
                if(isdigit(c)) {
                    y = c - '0';
                    digitCountY = 1;
                    currentState = READ_Y;
                } else currentState = START;
                break;
            case READ_Y:
                if(isdigit(c) && digitCountY < 3) {
                    y = y * 10 + (c - '0');
                    digitCountY++;
                } else if(c == ')' && digitCountY > 0) {
                    currentState = CLOSE_PAREN;
                } else currentState = START;
                break;
            case CLOSE_PAREN:
                if(isEnabled) {
                    total += x * y;
                }
                currentState = START;
                if(c == 'm') currentState = M;
                else if(c == 'd') currentState = D;
                break;
        }
    }
    cout << total;
    return 0;
}