#ifndef ITERATOR_H
#define ITERATOR_H

template <typename> class List;   // required forward declaration

template <typename T>
class ListIterator
{
    
    friend class List<T>;
    
public:
    ListIterator();
    bool hasNext() const;
    bool hasPrevious() const;
    T & next() throw ( NoSuchObject );
    T & previous() throw ( NoSuchObject );
    void printInternal() const;
    
private:
    Node<T> * current;
    bool before;
    
};

template <typename T>
ListIterator<T>::ListIterator(){
    current = 0;
    before = true;
}

template <typename T>
T & ListIterator<T>::next() throw ( NoSuchObject ){
    
    if( hasNext() == 0 ){
        throw NoSuchObject("ListIterator:next: No such object");
    }
    else if( before == true ){
        before = false;
    }
    else{
        current = current -> getNextPtr();
    }
    
    return current->getObject();
    
}

template <typename T>
T & ListIterator<T>::previous() throw ( NoSuchObject ){
    
    
    if( hasPrevious() == 0 ){
        throw NoSuchObject("ListIterator:previous: No such object");
    }
    else if( before == false ){
        before = true;
    }
    else{
        current = current -> getPrevPtr();
    }
    
    return current->getObject();

}

template <typename T>
bool ListIterator<T>::hasNext() const {
    
    return (current->getNextPtr() != 0);
    
}

template <typename T>
bool ListIterator<T>::hasPrevious() const {
    
    return (current->getPrevPtr() != 0);
    
}

template <typename T>
void ListIterator<T>::printInternal() const
{
    if ( before == true ){
        cout << "Object at current: " << current->getObject();
        cout << "          address: " << current << endl;
        cout << "           before: " << before << endl;
        cout << "         has next: " << current->hasNext() << endl;
        cout << "     has previous: " << current->hasPrevious() << endl;
    }
    
}

#endif // ITERATOR_H
