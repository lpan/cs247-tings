#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <iostream>

namespace Template {
  using std::string;

  template <typename T>
  T add1(T a, T b) {
    return a + b;
  }

  void testAdd1() {
    std::cout << add1(1, 2) << std::endl;

    // will not work
    // std::cout << add(1.1, 2) << std::endl;

    // compiler can't deduce, we need to help it out
    std::cout << add1<string>("hello", " world") << std::endl;

    // also works
    std::cout << add1(static_cast<string>("hello"),
                     static_cast<string>(" world")) << std::endl;
  }

  template <typename T1, typename T2, typename T3>
  T1 add3(T2 a, T3 b) {
    return a + b;
  }

  void testAdd3() {
    // won't work, impossible to infer return type if diff from param type!
    // std::cout << add3(1, 2) << std::endl;

    std::cout << add3<float>(1, 2) << std::endl;
  }

  template <typename Printable>
  void print(const Printable& arg) {
    std::cout << arg;
  }

  // https://en.cppreference.com/w/cpp/language/parameter_pack
  template <typename Printable, typename ... Printables>
  void print(const Printable& arg, const Printables& ... args) {
    print(arg);

    // unpacking template params
    print(args ...);
  }

  void testVariadic() {
    print("Hello", 5, "goodbye", 25.5, 'a');
    std::cout << std::endl;
  }

  void test() {
    testAdd1();
    testAdd3();
    testVariadic();

    // omitted.
    // testClass();
    // some gotchas
    // 1. have to put template definition must be in header file (h/hpp)
    // 2. if you want to put T in an array, make sure they are
    //   - copy assignable, default constructable
  }

};

#endif
