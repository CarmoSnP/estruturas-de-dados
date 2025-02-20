#include "../include/doubly_linked_list.hpp"
#include <iostream>

int main()
{
  DoublyLinkedList<int> lista;

  lista.push_front(10);
  lista.push_front(20);
  lista.push_front(30);

  lista.push_back(5);
  lista.push_back(6);
  lista.push_back(7);

  std::cout << "removendo o primeiro da lista" << std::endl;
  lista.pop_front();
  std::cout << "removendo o primeiro da lista" << std::endl;
  lista.pop_front();

  lista.print();
  std::cout << "removendo o último da lista" << std::endl;
  lista.pop_back();

  lista.print();

  for (auto &i : lista) // Corrigido erro de declaração
  {
    std::cout << i << ",";
  }
  std::cout << '\n';

  // lista.insert(lista.begin() - 1, 15);

  lista.print();

  // lista[4];
  // lista[5];

  return 0;
}
#include "../include/doubly_linked_list.hpp"
#include <iostream>

int main()
{
  DoublyLinkedList<int> lista;

  lista.push_front(10);
  lista.push_front(20);
  lista.push_front(30);

  lista.push_back(5);
  lista.push_back(6);
  lista.push_back(7);

  std::cout << "removendo o primeiro da lista" << std::endl;
  lista.pop_front();
  std::cout << "removendo o primeiro da lista" << std::endl;
  lista.pop_front();

  lista.print();
  std::cout << "removendo o último da lista" << std::endl;
  lista.pop_back();

  lista.print();

  for (auto &i : lista) // Corrigido erro de declaração
  {
    std::cout << i << ",";
  }
  std::cout << '\n';

  lista.insert(lista.begin() - 1, 15);

  lista.print();

  lista[4];
  lista[5];

  return 0;
}
