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

  for (auto &i : lista) 
  {
    std::cout << i << ",";
  }
  std::cout << '\n';

  lista.insert(lista.begin(), 15);

  lista.print();

  lista[4];
  lista[5];

  auto pos = lista.begin();
  std::cout<<"Primeiro da lista = "<<*pos<<'\n';
  ++pos;
  std::cout<<"Segundo da lista = "<<*pos<<'\n';
  --pos;
  std::cout<<"Primeiro da lista = "<<*pos<<'\n';

  pos = lista.begin() + 4;

  lista.insert(pos,55);

  lista.print();

  return 0;
}
