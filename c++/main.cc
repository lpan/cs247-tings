#include <iostream>

#include "./iterator.hpp"
#include "./decorator.hpp"

void testIter() {
  MyList ml;
  for (auto el : ml) {
    std::cout << el << std::endl;
  }
}

void testDecor() {
  Pizza *p = new NormalCrust;
  std::cout << p->text() << std::endl;
  std::cout << p->price() << std::endl;

  p = new Topping("mushroom", 1, p);
  std::cout << p->text() << std::endl;
  std::cout << p->price() << std::endl;
}

int main() {
  testIter();
  testDecor();
  return 0;
}
