#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool isLowerCase(const string& str) {
    for (char c : str) {
        if (!islower(c)) {
            return false; // If any non-lowercase character is found, return false
        }
    }
    return true; // All characters are lowercase
}

bool contain_all_alphabets(const string& str) {
    bool letters[26] = {false};

    for (char c : str) {
        if (isalpha(c)) {
            letters[tolower(c) - 'a'] = true;
        }
    }

    for (bool letter : letters) {
            if (!letter) {
                return false;
            }
        }

        return true;
}

string encriptionString(const string& text, const string& key) {
    string encriptedText;

    for (char c : text) {
        char encryptedChar = key[c - 'a'];
        encriptedText += encryptedChar;
    }
    return encriptedText;
}

int main()
{
    string key = "";
    string::size_type temp = 0;

    cout << "Enter the encryption key: ";
    getline(cin, key);

    temp = key.length();
    if (temp != 26) {
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return EXIT_FAILURE;
    } else if (!isLowerCase(key)) {
        cout << "Error! The encryption key must contain only lower case characters." << endl;
        return EXIT_FAILURE;
    }  else if (!contain_all_alphabets(key)) {
        cout << "Error! The encryption key must contain all alphabets a-z." << endl;
        return EXIT_FAILURE;
    } else {
        cout << "Enter the text to be encrypted: ";
        string text = "";
        getline(cin, text);
        if (!isLowerCase(text)) {
        cout << "Error! The text to be encrypted must contain only lower case characters." << endl;
        return EXIT_FAILURE;

        } else {
            cout << "Encrypted text: " << encriptionString(text, key) << endl;
    }
}
}
