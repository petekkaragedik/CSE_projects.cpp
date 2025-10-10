#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <string>

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

                array[currentPosition] = {obj, ACTIVE};
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
                hashVal = 37 * hashVal + character;
            }
            hashVal %= array.size();
            //handling the case where hashVal is negative
            if(hashVal < 0) {
                hashVal += array.size();
            }
            return hashVal;
        }
};
#endif