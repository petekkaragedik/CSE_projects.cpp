#include <iostream>
using namespace std;

template <class T>
class Bitter;

template <class T>
class BITerator {
  private:
    const Bitter<T>& bitter;
    int currIndex;

  public:
    BITerator(const Bitter<T>& b) : bitter(b), currIndex(bitter.getSize() - 1) {}  //we should start from the most significant bit

    void init() { 
        currIndex = bitter.getSize() - 1;
    }
    
    bool hasMore() const { 
        return currIndex >= 0;
    }
    
    int current() const {
        if (currIndex < 0) {
            return 0;  // invalid index
        }

        //obtaining the bit at currIndex
        if (bitter.val & (T(1) << currIndex)) {
            return 1;  //if bit is 1 return 1
        } else {
            return 0;
        }
    }

    void next() { 
        currIndex--;  //move towards least significant bit
    }
};

template <class T>
class Bitter {
  private:
    T & val;

  public:
    Bitter(T & valuee): val(valuee) {}

    int getSize() const { return sizeof(T) * 8; }

    int numberOfSetBits() const {
      int count = 0;
      for (int i = 0; i < getSize(); i++) {
        count += (val >> i) & 1;
      }
      return count;
    }

    void flipBit(int bit) { val ^= (T(1) << bit); }

    int setBit(int bit, int state) {
      if (bit < 0 || bit >= getSize()) {
        return -1;
      }
      if (state == 1) {
        val |= (T(1) << bit);
      } else {
        val &= ~(T(1) << bit);
      }
      return 0;
    }

    void negate() { val = ~val; }

    void shiftLeft(int count, int fill) {
        if (fill) {
            val = (val << count) | ((T(1) << count) - 1);
        } else {
            val = (val << count) | 0;
        }
    }


    void shiftRight(int count, int fill) {
        if (count < 0 || count > getSize()) {
            cout << "Invalid shift count" << endl;
            return;
        }
        T value = val;  // Assume 'val' holds the current value
        T mask = (~((T)0)) << (getSize() - count);

        if (fill) {
            val = (value >> count) | mask;
        } else {
        val = (value >> count) & (~mask);
        }

        cout << val << endl;
    }

    friend ostream & operator<<(ostream& os, const Bitter & b) {
      for (int i = b.getSize() - 1; i >= 0; i--) {
        os << ((b.val >> i) & 1);
      }
      return os;
    }

    friend class BITerator<T>;
};


int main() {  
  typedef int C;
  C c = 145960;

  Bitter<C> bitter1(c);
  cout << "bitter1 has value " << bitter1 << endl;
  cout << "bitter1 has " << bitter1.numberOfSetBits() << " set bits inside" << endl << endl;
  
  Bitter<C> bitter2(c);
  cout << "bitter2 is created from the same object" << endl;
  cout << "bitter2 has value " << bitter2 << endl << endl;
  
  cout << "flipping the 0th and 3rd bits of bitter2 " << endl;
  bitter2.flipBit(0);
  bitter2.flipBit(3);
  cout << "bitter1 has value " << bitter1 << endl;
  cout << "bitter2 has value " << bitter2 << endl;
  cout << "bitter2 has " << bitter2.numberOfSetBits() << " set bits inside" << endl << endl;

  cout << "setting the 1st bit of bitter1 to 1 and 3rd bit of bitter2 to 0" << endl;
  bitter1.setBit(1,1);
  bitter2.setBit(3,0);
  cout << "bitter1 has value " << bitter1 << endl;
  cout << "bitter2 has value " << bitter2 << endl << endl;

  
  cout << "setting the 11th bit of bitter1 to 1 " << endl;
  if(bitter1.setBit(11,1) == -1) {
    cout << "you are out of index: 11 >= " << bitter1.getSize() <<  endl;
  } else {
    cout << "set is done successfully " << endl;
    cout << "bitter1 has value " << bitter1 << endl << endl;
  } 

  cout << "negating the bits of bitter1 " << endl;
  bitter1.negate();
  cout << "bitter1 has value " << bitter1 << endl << endl;

  cout << "shifting bitter1 3 to the left and put 1 for the new bits" << endl;
  bitter1.shiftLeft(3,1);
  cout << "bitter1 has value " << bitter1 << endl << endl;

  cout << "shifting bitter2 3 to the right and put 0 for the new bits" << endl;
  bitter2.shiftRight(3,0);
  cout << "bitter2 has value " << bitter2 << endl << endl;


  cout << "we are using an iterator to obtain the decimal value of bitter1 " << endl ;
  BITerator<C> btr(bitter1);
  unsigned long long value;
  value = 0;
  for(btr.init(); btr.hasMore(); ) {
    value += btr.current(); 
    btr.next();
    if(btr.hasMore()) {
      value *= 2;
    }
  }
  cout << "value for " << bitter1 << " is " << value << endl;
  
  bitter2.negate();
  value = 0;
  for(btr.init(); btr.hasMore();) {
    value += btr.current(); 
    btr.next();
    if(btr.hasMore()) {
      value *= 2;
    }
  }
  cout << "value for " << bitter1 << " is " << value << endl << endl;  

  return 0;
}
