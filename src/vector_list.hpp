#include <iostream>
#include <stdexcept>

#include "../include/vector_list.hpp"

template <class T>
VectorList<T>::VectorList(size_t capacity) 
  : data{new T[capacity]},_size{0},_capacity{capacity} {
    std::cout<<"criando lista\n";
  }

template  <class T>
VectorList<T>::~VectorList() {
  delete[] data;
   std::cout<<"deletando lista\n";
}

template <class T>
size_t VectorList<T>::capacity() const {
    return _capacity;
}

template <class T>
size_t VectorList<T>::size() const {
  return _size;
}

template <class T>
void VectorList<T>::push_back(const T& value){
    if(size()>=capacity()){
        throw std::length_error("lista cheia");
    }
    data[size()] = value;
    _size++;
}

template <class T> 
bool VectorList<T>::empty() const {
    return size() == 0;
}

template <class T>
void VectorList<T>::pop_back()  {
    if(empty()){
        throw std::out_of_range("lista vazia");
    }
    _size--;
}

template <class T>
void VectorList<T>::print() const {
    for(size_t i = 0; i < size(); i++){
        std::cout << data[i] << " ";
    }
    std::cout << "\n";
}

template <class T>
void VectorList<T>::insert(size_t index,const T& value) {
    if(size() >= capacity()){
        throw std::length_error("lista cheia");
    } else if (index > size()){
        throw std::out_of_range("posição inválida");
    }
    if(index == size()){
        return push_back(value);
    }
    for(size_t i = size(); i > index ;i--){
        data[i] = data[i-1];
    }
    data[index] = value;
    _size++;
}

template <class T>
void VectorList<T>::remove(size_t index) {
    if(index >= size()){
        throw std::out_of_range("posição inválida");
    }
    if(index == size()-1){
        return pop_back();
    }
    for (size_t i = index; i < size()-1; i++) {
        data[i] = data[i+1];
    }
    _size--;
}

template <class T> 
T* find_item_in_data(T* data, size_t size, const T& item) {
    for (size_t i = 0; i < size; i++) {
        if (data[i] == item) {
            return &data[i];
        }
    }
    return nullptr;
}

template <class T>
T& VectorList<T>::find(const T& item){
    auto elemento = find_item_in_data(data, size(), item);
    if(elemento == nullptr){
        throw std::out_of_range("item não encontrado");
    }
    return *elemento;
}

template <class T>
const T& VectorList<T>::find(const T& item) const {
    auto elemento = find_item_in_data(data, size(), item);
    if(elemento == nullptr){
        throw std::out_of_range("item não encontrado");
    }
    return *elemento;
}

template <class T>
bool VectorList<T>::contains(const T& item) const {
    auto elemento = find_item_in_data(data, size(), item);
    return elemento != nullptr;
}

template <class T>
void VectorList<T>::clear() {
    _size = 0;
}

template <class T>
VectorList<T>::VectorList(const VectorList &list) 
    : data{new T[list._capacity]}, _size{list._size}, _capacity{list._capacity} {
    for (size_t i = 0; i < list._size; i++) {
        data[i] = list.data[i];
    }
}

template <class T>
VectorList<T> &VectorList<T>::operator=(const VectorList &list) {
    if (this != &list) {
        delete[] data;
        _capacity = list._capacity;
        _size = list._size;
        data = new T[_capacity];
        for (size_t i = 0; i < _size; i++) {
            data[i] = list.data[i];
        }
    }
    return *this;
}

template <class T>
T &VectorList<T>::operator[](size_t index) {
    if (index >= _size) {
        throw std::out_of_range("índice inválido");
    }
    return data[index];
}

template <class T>
const T &VectorList<T>::operator[](size_t index) const {
    if (index >= _size) {
        throw std::out_of_range("índice inválido");
    }
    return data[index];
}
