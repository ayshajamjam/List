#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <new>
#include "node.h"
#include "nosuchobject.h"
#include "iterator.h"

template <typename T>
class List;

template <typename T>
ostream & operator<<( ostream &, const List<T> & );

template <typename T>
class List {
    
    friend ostream & operator<< <>( ostream &, const List<T> & );
    
public:
    List();
    List( const List<T> & ) throw ( bad_alloc );
    ~List();
    void add( unsigned, const T & ) throw ( bad_alloc, out_of_range );
    void addAll( const List<T> & ) throw ( bad_alloc );
    void addAll( unsigned, const List<T> & ) throw ( bad_alloc, out_of_range );
    void addFirst( const T & ) throw ( bad_alloc );
    void addLast( const T & ) throw ( bad_alloc );
    void clear();
    bool contains( const T & ) const;
    bool empty() const;
    int indexOf( const T & ) const;
    T &get( unsigned ) const throw ( out_of_range ); // specify a position; returns reference to object at that position
    T &getFirst() const throw ( NoSuchObject );
    T &getLast() const throw ( NoSuchObject );
    ListIterator<T> listIterator();
    ListIterator<T> listIterator( unsigned ) throw ( out_of_range );
    T remove( unsigned ) throw ( out_of_range );
    T removeFirst() throw ( NoSuchObject );
    T removeFirstOccurrence( const T & ) throw ( NoSuchObject );
    T removeLast() throw ( NoSuchObject );
    T removeLastOccurrence( const T & ) throw ( NoSuchObject );
    T set( unsigned, const T & ) throw ( out_of_range );
    unsigned size() const;
    T * toArray() const throw ( bad_alloc );
    const List<T> &operator=( const List<T> & ) throw ( bad_alloc );
    void printInternal( ostream & = cout );
    
private:
    Node<T> * frontPtr;
    Node<T> * backPtr;
    unsigned sz;
    
    void add( Node<T> *, const T & ) throw ( bad_alloc );
    void initialize();
    Node<T> * getIthNode( unsigned ) const throw ( out_of_range );
    T remove( Node<T> * );
    
}; // List class

template <typename T>
ListIterator<T> List<T>::listIterator(){
    
    ListIterator<T> li;
    li.current = frontPtr;
    li.before = true;
    
    return li;
    
}

template <typename T>
ListIterator<T> List<T>::listIterator( unsigned index ) throw ( out_of_range ){
    
    if( index < 0 || index >= sz ){
        throw out_of_range("List::listIterator: index is out of range");
    }
    
    ListIterator<T> li;
    li.current = getIthNode(index);
    li.before = true;
    
    return li;
    
}

template <typename T>
void List<T>::addAll( const List<T>& list ) throw ( bad_alloc ){
    
    Node<T> * temp = 0;
    
    if( list.size()!= 0 ){
        temp = list.getIthNode(int(0));
    }
    
    while( temp != 0 ){
        addLast((temp->getObject()));
        temp = temp->getNextPtr();
    }
    
}

template <typename T>
void List<T>::addAll( unsigned index, const List<T>& list ) throw ( bad_alloc, out_of_range ){

    Node<T> * temp = 0;
    
    if( list.size()!= 0 ){
        temp = list.getIthNode(list.size() - 1);
    }
    
    while( temp != 0 ){
        add(index, (temp->getObject()));
        temp = temp->getPrevPtr();
    }
    
}

template <typename T>
ostream & operator<<( ostream & out, const List<T> & list ){
    
    Node<T> * temp = 0;
    
    if(list.size() != 0){
        temp = list.getIthNode(int(0));
    }
    
    cout << "[";
    
    while(temp != 0){
        
        out << temp->getObject();
        temp = temp->getNextPtr();
        
        if (temp != 0){
            out << ", ";
        }
        
    }
    
    cout << "]";

    return out;
    
}

template <typename T>
T List<T>::set( unsigned index, const T & object ) throw ( out_of_range ){
    
    if( index < 0 || index >= sz ){
        throw out_of_range ( "List::getIthNode: index is out of range" );
    }
    
    Node<T> * ptr = getIthNode(index);
    
    T obj = ptr->getObject();
    
    ptr->setObject(object);
    
    return obj;
    
}

template <typename T>
int List<T>::indexOf( const T & object ) const {
    
    int location = -1;
    
    if ( contains(object) == 0 ){
        return location;
    }
    else{
        
        Node<T> * ptr = frontPtr;
        location = 0;
        
        while(ptr->getObject() != object){
            ptr = ptr->getNextPtr();
            location++;
        }
        
        return location;
        
    }
    
}

template <typename T>
bool List<T>::contains( const T & object ) const{
    
    // Is there another way without having to go through each element?
    
    Node<T> * ptr = frontPtr;
    bool answer = 0;
    
    while(ptr->getObject() != object){
        ptr = ptr->getNextPtr();
        if(ptr == 0){
            return answer;
        }
    }

    answer = 1;
    
    return answer;
    
}


template <typename T>
Node<T> * List<T>::getIthNode(unsigned index) const throw (out_of_range){

    if( index < 0 || index >= sz ){
        throw out_of_range ( "List::getIthNode: index is out of range" );
    }
    
    Node<T> * ptr = frontPtr;
    int location = 0;
    
    while( location != index ){
        ptr = ptr->getNextPtr();
        location++;
    }
    
    return ptr;
    
}

// initialize method
template <typename T>
void List<T>::initialize()
{
    sz = 0;
    frontPtr = 0;
    backPtr = 0;
}

// default constructor
template <typename T>
List<T>::List()
{
    initialize();
}

// explicit constructor
template <typename T>
List<T>::List( const List<T>& d ) throw ( bad_alloc )
{
    initialize();
    *this = d;
}

// empty
template <typename T>
bool List<T>::empty() const
{
    return (sz == 0);
}

// size
template <typename T>
unsigned List<T>::size() const
{
    return sz;
}

template <typename T>
void List<T>::add( unsigned index, const T & object ) throw (bad_alloc, out_of_range){
    
    if ( index == 0 ){
        addFirst(object);
    }
    
    else if ( index == sz - 1 ){
        addLast(object);
     }
    
    else{
        add(getIthNode(index), object);
    }
    
}
    
template <typename T>
void List<T>::add( Node<T> * current, const T & object) throw ( bad_alloc ){
        
    Node<T> * newNode = new Node<T>(object);
        
    Node<T> * temp = (current -> getPrevPtr());
        
    newNode->setNextPtr(current);
    current->setPrevPtr(newNode);
        
    newNode->setPrevPtr(temp);
    temp->setNextPtr(newNode);
        
    sz++;
        
}

// addFirst
template <typename T>
void List<T>::addFirst( const T& object ) throw ( bad_alloc ){
    
    Node<T> * newNode = new Node<T>(object);
    newNode->setNextPtr(frontPtr);
    if ( !empty() )
        frontPtr->setPrevPtr(newNode);
        else{
            backPtr = newNode;
        }
    frontPtr = newNode;
    sz++;
    
}

// addLast
template <typename T>
void List<T>::addLast( const T& object) throw ( bad_alloc ){
    
    Node<T> * newNode = new Node<T>(object);
    if( !empty() ){
        backPtr->setNextPtr(newNode);
        newNode->setPrevPtr(backPtr);
    }
    else{
        frontPtr = newNode;
    }
    backPtr = newNode;
    sz++;
    
}
    
template <typename T>
T List<T>::removeFirstOccurrence(const T & object) throw (NoSuchObject){
    
    int index = 0;
    T obj = 0;
    
    if(empty()){
        throw NoSuchObject( "List::removeFirstOccurrence: list is empty" );
    }
    else if( (contains(object) == 0)){
        throw NoSuchObject("List::removeFirstOccurrence: NoSuchObject");
    }
    else{
        index = indexOf(object);
        obj = remove(index);
    }
    
    return obj;
    
}
    
template <typename T>
T List<T>::removeLastOccurrence(const T & object) throw (NoSuchObject){
    
    int index = sz - 1;
    T obj = 0;
    
    if(empty()){
        throw NoSuchObject( "List::removeLastOccurrence: list is empty" );
    }
    else if( (contains(object) == 0)){
        throw NoSuchObject("List::removeLastOccurrence: NoSuchObject");
    }
    else{
        
        Node<T> * ptr = backPtr;
        
        while(ptr->getObject() != object){
            ptr = ptr->getPrevPtr();
            index--;
        }
        
        obj = remove(index);
        
    }
    
    return obj;
    
    
}
    
template <typename T>
T List<T>::remove( unsigned index ) throw ( out_of_range ){
    
    T object = 0;
    
    if(index == 0){
        object = removeFirst();
    }
    else if(index == (sz-1)){
        object = removeLast();
    }
    else{
        object = remove(getIthNode(index));
    }
    
    return object;
    
}
    
template <typename T>
T List<T>::remove( Node<T> * current ){
    
    T object = current->getObject();
    
    Node<T> * before = current->getPrevPtr();
    Node<T> * after = current->getNextPtr();
    
    before->setNextPtr(after);
    after->setPrevPtr(before);
    delete current;
    sz--;
    
    return object;
    
}

//removeFirst
template <typename T>
T List<T>::removeFirst() throw ( NoSuchObject ){
    
    if(empty()){
        throw NoSuchObject( "List::removeFirst: list is empty" );
    }
    
    Node<T> * ptr = frontPtr;
    frontPtr = frontPtr->getNextPtr();
    T object = ptr->getObject();
    delete ptr;
    sz--;
    if( !empty() )
        frontPtr->setPrevPtr(0);
        else
            backPtr = frontPtr; // Should point to NULL
            
    return object;
}

template <typename T>
T List<T>::removeLast() throw ( NoSuchObject ){
    
    if(empty()){
        throw NoSuchObject( "List::removeLast: list is empty" );
    }
    
    Node<T> * ptr = backPtr->getPrevPtr();
    T object = backPtr->getObject();
    delete backPtr;
    sz--;
    if( !empty() )
        ptr->setNextPtr(0);
        else
            frontPtr = ptr;
            backPtr = ptr;
            
    return object;
}

template <typename T>
T & List<T>::get( unsigned index ) const throw ( out_of_range ){
    
    if( index < 0 || index >= sz || empty() ){
        throw out_of_range("List::get: index is out of range");
    }
    
    Node<T> * temp = getIthNode(index);
    
    return temp->getObject();
    
}

template <typename T>
T& List<T>::getFirst() const throw ( NoSuchObject )
{
    if(empty())
        throw NoSuchObject( "List::getFirst: list is empty" );
        
    return frontPtr->getObject();
}

template <typename T>
T& List<T>::getLast() const throw ( NoSuchObject )
{
    if(empty())
        throw NoSuchObject( "List::getLast: list is empty" );
        
    return backPtr->getObject();
}


template <typename T>
void List<T>::clear(){
    
    Node<T> * ptr = frontPtr;
    
    while( frontPtr != 0 ){
        frontPtr = frontPtr->getNextPtr();
        delete ptr;
        sz--;
        ptr = frontPtr;
        if( !empty() )
            frontPtr->setPrevPtr(0);
        else
            backPtr = frontPtr; // Both should point to NULL in this case
    }
}

// operator =
template <typename T>
const List<T>& List<T>::operator=( const List<T> &d ) throw (bad_alloc)
{
    
    if( &d != this){
        if( !empty() ){
            clear();
        }
        
        sz = d.sz;
        
        Node<T> * dptr = d.frontPtr;
        Node<T> * last = 0;
        
        while( dptr != 0 ){
            if( last == 0 ){
                frontPtr = backPtr = last = new Node<T>(*dptr);
            }
            else{
                last = new Node<T>(*dptr);
                backPtr->setNextPtr(last);
                last->setPrevPtr(backPtr);
                backPtr = last;
            }
            
            dptr = dptr->getNextPtr();
        }
        
    }
    
    return * this;
    
}
    
template <typename T>
T * List<T>::toArray() const throw (bad_alloc){
    
    T * arr = new T[sz];
    //Node<T> * current = frontPtr;
    
    for(unsigned i = 0; i < size(); i++){
        
        arr[i] = this->get(i);
        
        /*arr[i] = current->getObject();
        current = current->getNextPtr();*/
        
    }
    
    return arr;
        
}

template <typename T>
void List<T>::printInternal(ostream & out)
{
    Node<T> * current = frontPtr;
    int i = 0;
    cout << "top: " << frontPtr << endl;
    while ( current != 0 ){
        out << "Node " << i << endl;
        out << "  address: " << current << endl;
        out << "  object: " << current->getObject() << endl;
        out << "  prev: " << current->getPrevPtr() << endl;
        out << "  next: " << current->getNextPtr() << endl;

        current = current->getNextPtr();
        i++;
    }

}

template <typename T>
List<T>::~List(){
    clear();
}

#endif // LIST_H
