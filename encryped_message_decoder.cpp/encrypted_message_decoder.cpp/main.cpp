#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int decodeNumber(const string& PositionWord);
string reverseWord(const string& word);
string reverseLettersDecode(const string& message);
string caesarCipherShiftDecode(const string& message, int shift);
string findKey(const string& decodedMessage, int position);
string removeLastPunctuation(string key);

int main() {
    
    string message, PositionWord, choice;
    int shift;
    cout << "Enter your encoded message: ";
    getline(cin, message);
    cout << "Choose your decoding strategy:" << endl;
    cout << "1. Reverse Letters" << endl;
    cout << "2. Caesar Cipher Shift" << endl;
    cout << "Enter choice (1 or 2): ";
    cin >> choice;
    
    while(choice != "1" && choice != "2"){
        cout << "Invalid choice. Enter choice (1 or 2): ";
        cin >> choice;
    }
    
    if(choice == "1") {
        
        cout << "Enter the word to find the position of the key word: ";
        cin >> PositionWord;
        string decoded_message = reverseLettersDecode(message);
        cout << "Decoded Message: " << decoded_message << endl;
        cout << "Secret Key: " << findKey(decoded_message, decodeNumber(PositionWord)) << endl;
    }
    
    else if(choice == "2") {
        cout << "Enter Caesar Cipher Shift amount: ";
        cin >> shift;
        cout << "Enter the word to find the position of the key word: ";
        cin >> PositionWord;
        string decoded_message = caesarCipherShiftDecode(message, shift);
        cout << "Decoded Message: " << decoded_message <<  endl;
        cout << "Secret Key: " << findKey(decoded_message, decodeNumber(PositionWord)) << endl;
    }
    
    return 0;
}

int decodeNumber(const string& PositionWord){
    
    int i = 0;
    int num = 0, position = 0;
    
    while(i < PositionWord.length()){
        if ('0' <= PositionWord[i] && PositionWord[i] <= '9'){
            num = PositionWord[i] - '0';
            position += num;
        }
        i += 1;
    }
    return position;
}

string reverseWord(const string& word){
    
    int j = 1;
    string reversed_word;
    while(j <= word.length()){
        reversed_word += word[word.length() - j];
        j += 1;
    }
    return reversed_word;
}

string reverseLettersDecode(const string& message){

    string reversed_message;

    int start = 0, end = 0;
    while (end <= message.length()) {
        if (message[end] == ' ' || end == message.length()) {
            for (int i = end - 1; i >= start; i--) {
                reversed_message += message[i];
            }
            reversed_message += ' ';
            start = end + 1;
        }
        end++;
    }
    reversed_message = reversed_message.substr(0, reversed_message.length() - 1);
    return reversed_message;
}

string caesarCipherShiftDecode(const string& message, int shift) {
    string deciphered = "";

    int p = 0;
    while (p < message.length()) {
        char curr_char = message[p];
        if (isalpha(curr_char)) {
            char base_char;
            if (islower(curr_char)) {
                base_char = 'a';
            } else {
                base_char = 'A';
            }
            int alpha_idx = curr_char - base_char;
            alpha_idx = (alpha_idx - shift + 26) % 26;
            curr_char = base_char + alpha_idx;
        }
        deciphered += curr_char;
        p++;
    }

    return deciphered;
}

string findKey(const string& decodedMessage, int position){
    
    string key, adj;
    unsigned long idx_space, p;
    adj = decodedMessage;
    for(p = 1; p < position; p++){
        idx_space = adj.find(' ');
        adj = adj.substr(idx_space + 1);
    }
    idx_space = adj.find(' ');
    key = adj.substr(0, idx_space);
    key = removeLastPunctuation(key);
    return key;
}


string removeLastPunctuation(string key) {
    string punctuationMarks = ".,;:!?";
    for (int k = 0; k < punctuationMarks.length(); k++) {
        if (key[key.length() - 1] == punctuationMarks[k]) {
            return key.substr(0, key.length() - 1);
        }
    }
    return key;
}
