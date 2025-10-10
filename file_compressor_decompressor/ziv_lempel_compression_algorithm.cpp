#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class DictionaryItem {
    private:
        string key;
        int code;

    public:
        DictionaryItem(const string & k = "" , int c = -1 ): 
            key(k), code(c){}
        bool operator == (const DictionaryItem& other) const{
            return key == other.key;
        }
        bool operator != (const DictionaryItem& other) const{
            return !(*this == other);
        }
        //since its private, need to extract them with getter functions
        string getKey() const {
            return key;
        }
        int getCode() const{
            return code;
        }
};

template <class HashedObject>
class HashTable{
    public: 
        explicit HashTable(const HashedObject & notfound, int size = 4096):
            ITEM_NOT_FOUND(notfound), array(size) {}
        const HashedObject & find(const HashedObject & elem) const{
            int currentPosition = findPos(elem);
            if( isActive(currentPosition) ){
                return array[currentPosition].element;
            } 
            else {
                return ITEM_NOT_FOUND;
            }
        }
        void insert(const HashedObject & obj){
            int currentPosition = findPos(obj);
            if(!isActive(currentPosition)){
                array[currentPosition].element = obj;
                array[currentPosition].info = ACTIVE;

            }
        }
    private:
        enum EntryType {ACTIVE, EMPTY, DELETED};
        struct HashEntry{
            HashedObject element;
            EntryType info = EMPTY;
        };
        vector <HashEntry> array;
        const HashedObject ITEM_NOT_FOUND;
        bool isActive(int currentPosition) const {
            return array[currentPosition].info == ACTIVE;
        }
        int findPos (const HashedObject& elem) const {
            int currentPosition = hash(elem);
            while(array[currentPosition].info != EMPTY && array[currentPosition].element!= elem){
                currentPosition = (currentPosition + 1) % array.size(); //linear probing
            }
            return currentPosition;
        }
        int hash(const HashedObject& obj) const{
            const string & key = obj.getKey();
            int hashVal = 0;
            /* according to various resources, 37 is commonly used in this polynomial hashing function
            since it is a middle sized prime number as we discussed would be appropritate in the lectures. */
            for(char character : key){
                hashVal = 37 * hashVal + static_cast<unsigned char>(character); //the reason i used static_cast<unsigned char> is because otherwise i got errors
            }
            hashVal %= array.size();
            //handling the case where hashVal is negative
            if(hashVal < 0) {
                hashVal += array.size();
            }
            return hashVal;
        }
};

//the compression algorithm first
string compressionAlgorithm(const string & input){
    //initialization
    HashTable<DictionaryItem> dictionary(DictionaryItem("", -1), 4096);
    string current = "";
    stringstream finalResult;
    int nextCodeTracker = 256; //after the ascii codes we start
    //given ascii initialization
    for(int counter = 0; counter <256; ++counter){
        string ch(1, static_cast<char>(counter)); //this useage is also because of some type handling issues, we're using only the first char, otherwise i got errors
        dictionary.insert( DictionaryItem( ch, counter ) );
    }

    if (!input.empty()) {
        current = input[0];
    }

    for (int i = 1; i < input.length(); i++){
        string next = current + input[i];
        //checking if it already exists in the dictionary 
        //if exists
        if(dictionary.find(DictionaryItem(next)).getCode() != -1){
            current = next;
        }
        //if doesnt exist
        else {
            //output the code for the currentent string we have
            DictionaryItem foundItem = dictionary.find(DictionaryItem(current));
            finalResult << foundItem.getCode() << " ";
            //add the new item if there is any space left
            if(nextCodeTracker < 4096){
                dictionary.insert(DictionaryItem(next, nextCodeTracker++));
            }
            current = string(1, input[i]); //reset to single char
        }
    }
    //printing the final compressed code
    if(!current.empty()){
        finalResult << dictionary.find(DictionaryItem(current)).getCode() << " ";
    }
    return finalResult.str(); // to turn the stringstream object back into string type obj
}

//decompression algorithm
string decompressionAlgorithm(const string & input){
    vector <string> dictionary(4096);
    //initialize the first 256 chars with the ascii
    //using the given notion in the file but modifying for the vector in decompression
    for(int counter = 0; counter <256; ++counter){
        dictionary[counter] = string(1, static_cast<char>(counter)); //converting char to a single character string successfully
    }
    vector <int> codes; //input codes
    stringstream ss(input);
    int code;

    while (ss >> code){
        codes.push_back(code);
    }
    if(codes.empty()){
        return "";
    }
    string finalResult = dictionary[codes[0]];
    string previous = finalResult;
    int nextCodeTracker = 256;

    for (int i = 1; i < codes.size(); i++){
        int curr_code = codes[i];
        string entry; //for the decompressed string

        if(curr_code < nextCodeTracker){
            entry = dictionary[curr_code];
        }
        else if(curr_code == nextCodeTracker){ //currently creating
            entry = previous + previous[0];
        }
        else {  //invalid
            cerr << "Error: Invalid compressed code encountered!" << endl;
            return "";
        }
        finalResult += entry;
        if(nextCodeTracker < 4096) {
            dictionary[nextCodeTracker++] = previous + entry[0];
        }
        previous = entry;
    }
    return finalResult;
}

int main(){
    cout << "To compress a file, press 1. To decompress a file, press 2: ";
    int choice;
    cin >> choice;
    cin.ignore(); //clear newline \n
    if(choice == 1){
        cout << "Enter the input string: ";
        string input;
        getline(cin, input);
        if (input.empty()) {
            cout << "Error: Empty input!" << endl;
            return 0;
        }
        string compressedOutput = compressionAlgorithm(input);
        cout << "Compressed output: " << compressedOutput << endl;
    }
    else if(choice ==2){
        cout << "Enter the compressed string: ";
        string input;
        getline(cin, input);
        if (input.empty()) {
            cout << "Error: Empty input!" << endl;
            return 0;
        }
        string decompressedOutput = decompressionAlgorithm(input);
        cout << "Decompressed string: " << decompressedOutput << endl;
    }
    else{
        cout << "Invalid choice!" <<  endl;
    }
    return 0;
}
