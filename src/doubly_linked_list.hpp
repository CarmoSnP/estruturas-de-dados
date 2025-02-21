#include <iostream>
#include <stdexcept> // Para lançar exceções

#include "../include/doubly_linked_list.hpp"

template <class T>
DoublyLinkedList<T>::Node::Node(const T &value)
    : value{value}, next{nullptr}, prev{nullptr} {}

template <class T>
DoublyLinkedList<T>::Node::~Node() {
    if (next != nullptr){
        delete next;
    }
}

template <class T>
DoublyLinkedList<T>::DoublyLinkedList()
    : head{nullptr}, tail{nullptr}, _size{0} {}

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    if (head != nullptr){
        delete head;
    }
}

template<class T>
size_t DoublyLinkedList<T>::size() const{
    return  _size;
}

template <class T>
bool DoublyLinkedList<T>::empty() const
{
    return _size == 0;
}

template <class T>
void DoublyLinkedList<T>::push_front(const T &value)
{
    Node *new_node = new Node(value);
    if (empty())
    {
        tail = new_node;
    }
    else
    {
        new_node->next = head;
        head->prev = new_node;
    }
    head = new_node;
    _size++;
}

template<class T>
void DoublyLinkedList<T>::print() const 
{

    for (auto& v: *this){
        std :: cout << v << "<->"; 
    }
    std::cout <<'\n';
}


template<class T>
T& DoublyLinkedList<T>::operator[](size_t indece) {
    return *(begin() + indece);
} 

// template <class T>
// void DoublyLinkedList<T>::print() const
// {
//     Node *pos = head;
//     while (pos != nullptr)
//     {
//         std::cout << pos->value << " <-> ";
//         pos = pos->next;
//     }
//     std::cout << "NULL("<< size() <<")\n";
// }


template <class T>
void DoublyLinkedList<T>::push_back(const T &value)
{
    Node *new_node = new Node(value);

    if (empty())
    {
        head = new_node;
    }
    else
    {
        new_node->prev = tail;
        tail->next = new_node;
    }

    tail = new_node;
    _size++;
}

template <class T>
void DoublyLinkedList<T>::pop_front()
{
    if (empty())
    {
        throw std::out_of_range("A lista está vazia");
    }

    Node *tmp = head;
    head = head->next;
    if (head != nullptr)
    {
        head->prev = nullptr;
    }
    tmp -> next = nullptr;

    delete tmp;
    _size--;

    if (empty()){
        tail = nullptr;
    }
}

template <class T>
void DoublyLinkedList<T>::pop_back()
{
    if (empty())
    {
        throw std::out_of_range("A lista está vazia");
    }else if(size() == 1 )
    {
        delete tail;
        head = nullptr;
        tail = nullptr;
    } else 
    {
        auto temp = tail;
        tail = tail ->prev;
        tail -> next = nullptr; 
        delete temp;
    }
   _size--;
}

template <class T>
template <class U>
DoublyLinkedList<T>::Iterator<U>::Iterator(U *ptr, bool end) : node{ptr}, end{end} {}

template <class T>
template <class U>
auto &DoublyLinkedList<T>::Iterator<U>::operator*() const
{
    return node->value;
}

template <class T>
template <class U>
typename DoublyLinkedList<T>::template Iterator<U> &DoublyLinkedList<T>::Iterator<U>::operator++()
{
    if (node->next == nullptr){
        end = true;
    }
    else{

    if (node != nullptr)
    {
        node = node->next;
    }
    }
    return *this;
}

template <class T>
template <class U>
typename DoublyLinkedList<T>::template Iterator<U> &DoublyLinkedList<T>::Iterator<U>::operator--()
{

    if (end){
        end = false;
    }
    else{
    if (node != nullptr)
    {
        node = node->prev;
    }
    }
    return *this;
}

template <class T>
template <class U>
bool DoublyLinkedList<T>::Iterator<U>::operator==(const Iterator<U> &other) const
{
    return node == other.node and  end == other.end;
}

template <class T>
template <class U>
bool DoublyLinkedList<T>::Iterator<U>::operator!=(const Iterator<U> &other) const
{
    return not(*this == other);
}

template<class T>
auto DoublyLinkedList<T>::begin() const -> const_iterator {
    return const_iterator(head, empty());
}

template<class T>
auto DoublyLinkedList<T>::begin() -> iterator {
    return iterator(head, empty());
}

template<class T>
auto DoublyLinkedList<T>::end() const -> const_iterator {
    return const_iterator(tail, true);
}

template<class T>
auto DoublyLinkedList<T>::end() -> iterator {
    return iterator(tail, true);
}

template <class T>
template <class U>
typename DoublyLinkedList<T>::template Iterator<U> DoublyLinkedList<T>::Iterator<U>::operator+(size_t offset) const
{
    Iterator<U> it = *this;
    for (size_t i = 0; i < offset && it.node != nullptr; ++i)
    {
        ++it;
    }
    return it;
}

template <class T>
template <class U>
typename DoublyLinkedList<T>::template Iterator<U> DoublyLinkedList<T>::Iterator<U>::operator-(size_t offset) const
{
    Iterator<U> it = *this;
    for (size_t i = 0; i < offset && it.node != nullptr; ++i)
    {
        --it;
    }
    return it;
}

template<class T>
void DoublyLinkedList<T>::insert(iterator pos, const T& value){
    if(pos == begin())
    {
       return push_front(value);
    }   
    else if (pos == end())
    {
        return push_back(value);
    }

    auto node_pos = pos.node;
    auto node_prev = (--pos).node;

    auto new_node = new Node(value);

    node_prev->next = new_node;
    new_node->next = node_pos;

    new_node->prev = node_prev;
    node_pos->prev = new_node;

    _size++;
}
