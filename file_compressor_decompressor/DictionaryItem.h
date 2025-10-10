#ifndef DICTIONARYITEM_H
#define DICTIONARYITEM_H

#include <string>
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

#endif