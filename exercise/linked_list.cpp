#include "../include/linked_list.hpp"
#include <iostream>

int main() {
    LinkedList<int> lista;

    std::cout << "inserindo elementos\n";
    lista.push_front(10);
    lista.push_front(20);
    lista.insert(1, 15);
    lista.print();

    std::cout << "removendo elemento na posição 1\n";
    lista.remove(1);
    lista.print();

    std::cout << "verificando se contém 10: " << lista.contains(10) << "\n";
    std::cout << "verificando se contém 30: " << lista.contains(30) << "\n";

    std::cout << "buscando elemento 10\n";
    try {
        std::cout << "encontrado: " << lista.find(10) << "\n";
    } catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }

    std::cout << "removendo todos os elementos\n";
    lista.clear();
    lista.print();

    return 0;
}
