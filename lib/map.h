
#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;


template <class keyType, class valueType>
struct MapItem
{
  keyType key;
  valueType value;
  MapItem<keyType, valueType> *prev, *next;
};

template <class keyType, class valueType> 
    struct Pair {
     keyType first;
     valueType second;

     Pair (keyType first, valueType second)
     { this->first = first; this->second = second; }
 };


template <class keyType, class valueType>
class Map
{
private:
    MapItem <keyType, valueType> *head, *tail, *traversalIndex;
    int map_size;

public:
    Map ();  // constructor for a new empty map
    Map (const Map<keyType, valueType> & other);   //deep copy constructor
    ~Map (); // destructor
    int size () const; // returns the number of key-value pairs
    void add (keyType key, valueType value); 
    void remove (keyType key);
    valueType get (const keyType & key);
    void merge (const Map<keyType, valueType> & other);
    bool keyExists(keyType key) const;
    bool mergeDuplicate(const Map<keyType, valueType> & other, keyType key, valueType value) const;
    void query(const keyType key);
    void loadFile(string filename);
    void first();
    void next();
    bool hasNext();   //if has item to call next 
    const keyType & getCurrentKey ();
    const keyType & getCurrentValue ();
    void EquateTo (const Map<keyType, valueType> & other);
    vector<keyType> getUnion(const Map<keyType, valueType> & map1, const Map<keyType, valueType> & map2);
    void getIntersection(const Map<keyType, valueType> & map1, const Map<keyType, valueType> & map2);



//template <class keyType, class valueType>
    class Iterator {

         /* add any constructors that you feel will be helpful,
            and choose whether to make them public or private. */
    private: 
        const Map<keyType, valueType> *whoIBelongTo; 
        MapItem<keyType, valueType> *currentItem;
    
        friend class Map<keyType, valueType>;
        Iterator(const Map<keyType, valueType> *m, MapItem<keyType, valueType> *p) { 
        //Iterator() {     
            whoIBelongTo = m; 
            currentItem = p;
        }//end of constructor

        public:
        Pair<keyType, valueType> operator* () const{
        // return the current (key, value) pair the iterator is at 
            Pair<keyType, valueType> currentPair(currentItem->key, currentItem->value);
            return currentPair;
        }//end of *    

        Map<keyType,valueType>::Iterator operator++ (){
        // advances the iterator (pre-increment)
            if (currentItem->next != NULL){
                currentItem = currentItem->next;
            }//end of if
            else{
                currentItem = NULL;
            } 
        }//end of ++    


        Map<keyType,valueType>::Iterator operator= (const Map<keyType,valueType>::Iterator & other){ 
        // assigns the other iterator to this iterator and returns this
            currentItem = other.currentItem;
            return *this;
        }

        bool operator== (const Map<keyType,valueType>::Iterator & other) const{
        // returns whether this iterator is equal to the other iterator
            if(currentItem == other.currentItem && whoIBelongTo == other.whoIBelongTo)
                return true;
            return false;    
        }//end of ==

        bool operator!= (const Map<keyType,valueType>::Iterator & other) const{
        // returns whether this iterator is not equal to the other iterator
            return (!this->operator== (other));
        }//end of !=

    };//end of iterator class

    Map<keyType, valueType>::Iterator begin () const{
        return (Map<keyType, valueType>::Iterator(this, head));
    }//end of begin

    Map<keyType, valueType>::Iterator end () const{
        return Map<keyType, valueType>::Iterator(this, NULL);
    }//end of end

   };
#endif