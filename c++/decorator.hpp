#ifndef DECORATOR_H
#define DECORATOR_H

#include <string>

using std::string;

// enhance/overwrite the way an object behaves at runtime
class Pizza {
public:
  virtual float price() const = 0;
  virtual string text() const = 0;
  virtual ~Pizza() {}
};

// concrete components
class NormalCrust : public Pizza {
  float price() const override { return 3; }
  string text() const override { return "pizza"; }
};

class ThinCrust : public Pizza {
  float price() const override { return 2; }
  std::string text() const override { return "thin crust pizza"; }
};

// decorator base
class Decorator : public Pizza {
  // gotta keep track of the decoratee
  // could be an ownership as well. it is like a linked list
  Pizza *component_;
protected:
  Pizza& getComponent() const {
    return *component_;
  }

public:
  Decorator(Pizza *p) : component_{p} {}
  ~Decorator() { delete component_; }
};

class Topping : public Decorator {
  string name_;
  float price_;

public:
  Topping(string name, float price, Pizza *p)
    : Decorator{p}, name_{name}, price_{price} {}

  float price() const override {
    return getComponent().price() + price_;
  }

  std::string text() const override {
    return getComponent().text() + " with " + name_;
  }
};

#endif
