#include<iostream>
using namespace std;

int RandomNumber(int lowerBound, int upperBound) {
    srand((unsigned)time(NULL));
    return lowerBound + (rand() % upperBound);
}

int GetIntInput(const char* PROMPT_MESSAGE) {

    int input;
    int failure;

    do {
        failure = false;
        cout << (PROMPT_MESSAGE ? PROMPT_MESSAGE : "ENTER AN INTEGER VALUE") << endl;
        cin >> input;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "INCORRECT INPUT!! PLEASE TRY AGAIN" << endl;
            failure = true;
        }
    } while (failure);

    return input;
}

char GetCharInput(const char* PROMPT_MESSAGE, char validInputs[], int length) {
    
    char input;
    int failure;

    do {
        failure = false;
        cout << PROMPT_MESSAGE << endl;
        cin >> input;
        if (cin.fail()) {
            cout << "INCORRECT INPUT!! PLEASE TRY AGAIN" << endl;
            failure = true;
        }
        else if (!isalnum(input)) {
            cout << "INCORRECT INPUT!! PLEASE TRY AGAIN" << endl;
            failure = true;
        }
        else if (isdigit(input)) {
            cout << "INCORRECT INPUT!! PLEASE TRY AGAIN" << endl;
            failure = true;
        }
        else if (length > 0) {
            bool valid_input = false;
            for (int i = 0; i < length; i++) {
                if (input == validInputs[i]) {
                    valid_input = true;
                    break;
                }
            }
            if (!valid_input) {
                cout << "INCORRECT INPUT!! PLEASE TRY AGAIN" << endl;
                failure = true;
            }

        }

        // clear input buffer 
        cin.clear();
        cin.ignore(256, '\n');

    } while (failure);

    return input;
}

void clearScreen() {
    system("cls"); // specific to windows
}