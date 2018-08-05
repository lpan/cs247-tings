#ifndef VISITOR_H
#define VISITOR_H

#include <iostream>

namespace Visitor {

  /*
   * What is it for?
   * - runtime polymorphism based on TWO objects (instead of one)
   *
   * Summary:
   * - visitee being dispatched first
   * - visitor is capable of visiting all visitees (overloading)
   * - then visitor being dispatched
   *
   * Also, it is easy to add functionality to a class by
   * 1. make the class "visitable"
   * 2. write visitors that visit them
   */

  namespace Example1 {
    /*
     * Example: strike enemy with an weapon
     * - action dispatched based on both
     *   - enemy
     *   - weapon
     */

    class Turtle;
    class Tortoise;

    class Weapon {
    public:
      virtual ~Weapon() {}

      virtual void strike(Turtle&) = 0;
      virtual void strike(Tortoise&) = 0;
    };

    class Stick : public Weapon {
    public:
      void strike(Turtle&) override {
        std::cout << "Strike turtle with a stick!" << std::endl;
      }

      void strike(Tortoise&) override {
        std::cout << "Strike tortoise with a stick!" << std::endl;
      }
    };

    class Enemy {
    public:
      virtual ~Enemy() {}
      virtual void beStruckBy(Weapon&) = 0;
    };

    class Turtle : public Enemy {
      void beStruckBy(Weapon& w) override {
        w.strike(*this);
      }
    };

    class Tortoise : public Enemy {
      void beStruckBy(Weapon& w) override {
        w.strike(*this);
      }
    };

    void test() {
      Enemy *e;
      Weapon *w;

      e = new Turtle;
      w = new Stick;

      // 1. beStruckBy dispatches
      // 2. overloads -> calls struck(turtle)
      // 3. dispatches on w by calling stick.struck
      e->beStruckBy(*w);

      delete e;
      delete w;
    }
  }

  namespace Example2 {
    // things being visited
    class MyClassA;
    class MyClassB;

    class MyClassVisitor {
    public:
      virtual ~MyClassVisitor() {}
      virtual void visit(MyClassA&) = 0;
      virtual void visit(MyClassB&) = 0;
    };

    class LelVisitor : public MyClassVisitor {
      void visit(MyClassA&) {
        std::cout << "lel: visiting class A" << std::endl;
      }

      void visit(MyClassB&) {
        std::cout << "lel: visiting class B" << std::endl;
      }
    };

    class MyClass {
    public:
      virtual ~MyClass() {}
      virtual void accept(MyClassVisitor& v) = 0;
    };

    class MyClassA : public MyClass {
    public:
      void accept(MyClassVisitor& v) {
        std::cout << "dispatch on A" << std::endl;
        v.visit(*this);
      }
    };

    class MyClassB : public MyClass {
    public:
      void accept(MyClassVisitor& v) {
        std::cout << "dispatch on B" << std::endl;
        v.visit(*this);
      }
    };

    void test() {
      MyClass *thing = new MyClassB;
      MyClassVisitor *visitor = new LelVisitor;

      thing->accept(*visitor);

      delete thing;
      delete visitor;
    }

  }

  void test() {
    // Example1::test();
    Example2::test();
  }

};

#endif
