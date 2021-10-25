#ifndef NODE_H
#define NODE_H

using namespace std;

template <typename T>
class Node
{
    
    public:
        Node( const T & = T() );
        void setObject( const T & );
        T & getObject();
        void setNextPtr( Node<T> * );
        Node<T> *getNextPtr() const;
        void setPrevPtr( Node<T> *);
        Node<T> *getPrevPtr() const;
    
    private:
        T object;
        Node<T> * nextPtr;
        Node<T> * prevPtr;
    
};

template <typename T>
Node<T>::Node( const T & object )
{
    this->object = object;
    this->nextPtr = 0;
    this->prevPtr = 0;
}

template <typename T>
void Node<T>::setObject( const T & object )
{
    this->object = object;
}

template <typename T>
T & Node<T>::getObject()
{
    return object;
}

template <typename T>
void Node<T>::setNextPtr( Node<T> * nextPtr)
{
    this->nextPtr = nextPtr;
}

template <typename T>
Node<T> * Node<T>::getNextPtr() const
{
    return nextPtr;
}

template <typename T>
void Node<T>::setPrevPtr( Node<T> * prevPtr )
{
    this->prevPtr = prevPtr;
}

template <typename T>
Node<T> * Node<T>::getPrevPtr() const
{
    return prevPtr;
}

#endif // NODE_H
