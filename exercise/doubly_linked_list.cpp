#include "../include/doubly_linked_list.hpp"
#include <iostream>

int main() {
    DoublyLinkedList<int> lista;

    std::cout << "Inserindo elementos no início e no fim da lista...\n";
    lista.push_front(10);
    lista.push_front(20);
    lista.push_front(30);

    lista.push_back(5);
    lista.push_back(6);
    lista.push_back(7);

    lista.print();

    std::cout << "Removendo o primeiro elemento...\n";
    lista.pop_front();
    lista.print();

    std::cout << "Removendo o último elemento...\n";
    lista.pop_back();
    lista.print();

    std::cout << "Iterando sobre os elementos da lista:\n";
    for (auto &i : lista) {
        std::cout << i << " ";
    }
    std::cout << '\n';

    std::cout << "Inserindo 15 no início da lista usando insert...\n";
    lista.insert(lista.begin(), 15);
    lista.print();

    std::cout << "Acessando elementos por índice usando operator[]:\n";
    for (size_t i = 0; i < lista.size(); ++i) {
        std::cout << "lista[" << i << "] = " << lista[i] << '\n';
    }

    std::cout << "Testando operador de iteração (++ e --):\n";
    auto pos = lista.begin();
    std::cout << "Primeiro da lista = " << *pos << '\n';
    ++pos;
    std::cout << "Segundo da lista = " << *pos << '\n';
    --pos;
    std::cout << "Voltando para o primeiro da lista = " << *pos << '\n';

    std::cout << "Inserindo 55 na posição 4...\n";
    pos = lista.begin() + 4;
    lista.insert(pos, 55);
    lista.print();

    std::cout << "Testando find() e contains():\n";
    int busca = 15;
    if (lista.contains(busca)) {
        std::cout << "O elemento " << busca << " está na lista.\n";
    } else {
        std::cout << "O elemento " << busca << " não foi encontrado.\n";
    }

    std::cout << "Removendo um intervalo de elementos...\n";
    lista.erase(lista.begin(), lista.begin() + 2);
    lista.print();

    std::cout << "Limpando a lista completamente...\n";
    lista.clear();
    
    if (lista.empty()) {
        std::cout << "A lista está vazia!\n";
    } else {
        lista.print();
    }

    return 0;
}
