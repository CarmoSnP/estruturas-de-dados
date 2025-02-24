#include <iostream>
#include "../include/vector_list.hpp"

int main() {
    VectorList<int> lista(10);
    
    std::cout << "tamanho inicial: " << lista.size() << "\n";
    std::cout << "capacidade: " << lista.capacity() << "\n";

    lista.push_back(5);
    lista.push_back(10);
    lista.push_back(15);
    
    std::cout << "elementos apos push_back: ";
    lista.print();

    lista.insert(1, 7);
    std::cout << "apos insert(1, 7): ";
    lista.print();

    lista.remove(2);
    std::cout << "apos remove(2): ";
    lista.print();

    std::cout << "encontrando 10: " << lista.find(10) << "\n";
    std::cout << "lista contem 5? " << (lista.contains(5) ? "sim" : "nao") << "\n";
    
    lista.pop_back();
    std::cout << "apos pop_back: ";
    lista.print();
    
    std::cout << "acessando por []: " << lista[0] << "\n";
    lista[0] = 42;
    std::cout << "apos modificar por []: ";
    lista.print();

    lista.clear();
    std::cout << "apos clear, tamanho: " << lista.size() << "\n";
    return 0;
}
