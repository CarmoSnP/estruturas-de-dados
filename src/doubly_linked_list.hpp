#include <iostream>
#include <stdexcept> // Para lançar exceções

#include "../include/doubly_linked_list.hpp"

template <class T>
DoublyLinkedList<T>::Node::Node(const T &value)
    : value{value}, next{nullptr}, prev{nullptr} {}

// template <class T>
// DoublyLinkedList<T>::Node::~Node() {
//     if (next != nullptr){
//         delete next;
//     }
// }

template <class T>
DoublyLinkedList<T>::Node::~Node(){
    next = nullptr; 
    prev = nullptr;
}

template <class T>
DoublyLinkedList<T>::DoublyLinkedList()
    : head{nullptr}, tail{nullptr}, _size{0} {}

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    while (!empty()) {
        pop_back();
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


// template<class T>
// T& DoublyLinkedList<T>::operator[](size_t indece) {
//     return *(begin() + indece);
// } 

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
auto &DoublyLinkedList<T>::Iterator<U>::operator*() const
{
    return node->value;
}

template <class T>
template <class U>
typename DoublyLinkedList<T>::template Iterator<U>&
DoublyLinkedList<T>::Iterator<U>::operator++() {
    if (node == nullptr || node->next == nullptr) {  
        end = true;
    } else {
        node = node->next;
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

template <class T>
template <class U>
DoublyLinkedList<T>::Iterator<U>::Iterator(U* ptr, bool end)
    : node{ptr}, end{end} {}

// Begin iterator
template <class T>
typename DoublyLinkedList<T>::iterator DoublyLinkedList<T>::begin() {
    return iterator(head, empty());
}

template <class T>
typename DoublyLinkedList<T>::const_iterator DoublyLinkedList<T>::begin() const{
    return const_iterator(head, empty());
}


// End iterator
template <class T>
typename DoublyLinkedList<T>::iterator DoublyLinkedList<T>::end() {
    return iterator(tail, true);
}

template <class T>
typename DoublyLinkedList<T>::const_iterator DoublyLinkedList<T>::end() const{
    return const_iterator(tail, true);
}

template <class T>
template <class U>
typename DoublyLinkedList<T>::template Iterator<U> DoublyLinkedList<T>::Iterator<U>::operator+(size_t offset) const {
    Iterator<U> it = *this;
    for (size_t i = 0; i < offset && it.node != nullptr; ++i) {
        ++it;
    }
    if (it.node == nullptr) {
        it.end = true;
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

template <class T>
void DoublyLinkedList<T>::erase(iterator first, iterator last) {
    if (empty() || first == last) {
        return;
    }

    Node* atual = first.node;
    Node* final = last.end? nullptr: last.node;

    // Se remover do inicio da lista
    if (atual == head) {
        head = final;
    } else if (atual->prev) {
        atual->prev->next = final;
    }

    // Se estamos removendo até o final da lista
    if (final == nullptr || last.end) {
        tail = atual->prev;
        if (tail) {
            tail->next = nullptr;
        }
    } else {
        final->prev = atual->prev;
    }

    // Deletar os nós no intervalo
    while (atual && atual != final) {
        Node* next = atual->next;
        delete atual;
        _size--;
        atual = next;
    }

    // resetar os pontiros
    if (_size == 0) {
        head = nullptr;
        tail = nullptr;
    }
}

template<class T>
template<class U>
size_t DoublyLinkedList<T>::Iterator<U>::operator-(const Iterator<U> other) const {
    auto pos = other;
    size_t count = 0;
    while(pos != *this){
        count++;
        ++pos;
    }
    return count;
}

template<class T>
auto DoublyLinkedList<T>::find(const T& item) -> iterator {
    auto it = begin();
    while(it != end()){
        if(*it == item ) break;
        ++it;
    }
    return it;
}

template<class T>
auto DoublyLinkedList<T>::find(const T& item) const -> const_iterator {
    auto it = begin();
    while(it != end())
    {
        if(*it == item) break;

        ++it;
    }
    return it; 
}

template <class T>
bool DoublyLinkedList<T>::contains(const T& item) const {
    return find(item) != end();
}

template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other)
    : head{nullptr}, tail{nullptr}, _size{0} {
    for (auto& value : other) {
        push_back(value);
    }
}

template <class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other) {
    if (this != &other) {
        clear();
        for (auto& value : other) {
            push_back(value);
        }
    }
    return *this;
}

template <class T>
T& DoublyLinkedList<T>::operator[](size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Índice inválido!!");
    }
    auto it = begin();
    for (size_t i = 0; i < index; ++i) {
        ++it;
    }
    return *it;
}

template <class T>
const T& DoublyLinkedList<T>::operator[](size_t index) const {
    if (index >= _size) {
        throw std::out_of_range("Índice inválido!!");
    }
    auto it = begin();
    for (size_t i = 0; i < index; ++i) {
        ++it;
    }
    return *it;
}

// template <class T>
// void DoublyLinkedList<T>::clear() {
//     while (!empty()) {
//         pop_front();
//     }
// }

template <class T>
void DoublyLinkedList<T>::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    // Após limpar a lista, ajuste os ponteiros corretamente
    tail = nullptr;
    _size = 0;
}