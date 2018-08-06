#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace Composite {

  using std::string;
  using std::unique_ptr;

  /*
   * What is it for?
   * - deals with compound objects (something that represents a composition of
   *   heterogeneous, recursive, component objects) by exposing an uniform
   *   interface
   * - encapsulates the structure of a complex (composite) data structure
   * - iterator pattern on steroids
   */

  class Component {
    string name_;
  public:
    Component(string n) : name_{n} {}

    virtual ~Component() {};

    virtual string name() const {
      return name_;
    }

    virtual int salary() const = 0;

    // --------------------
    // iterator stuffs
    class Iter {
    protected:
      // reference to the Component being visited
      Component* component_;

    public:
      Iter(Component* cp) : component_{cp} {}
      virtual ~Iter() {}

      // reset iterator to initial (points to the first element) state
      virtual void first() = 0;

      virtual bool hasNext() const = 0;

      virtual Component* next() = 0;
    };

    virtual Iter* createIterator() = 0;
  };

  class Leaf : public Component {
    int salary_;
  public:
    Leaf(string n, int s) : Component{n}, salary_{s} {}

    int salary() const override {
      return salary_;
    }

    // -------------------
    // Iterator things

    class LeafIter : public Iter {
      // we can also implement the cursor in other ways
      // btw, the following way, the cursor is just a binary flag
      //
      // for example, like the star war example, we can make cursor to have
      // type Component* and then set it to nullptr after it is being iterated
      bool isDone_;
    public:
      LeafIter(Leaf* h) : Iter{h}, isDone_{false} {}

      // reset cursor to init value
      void first() override {
        isDone_ = false;
      }

      bool hasNext() const override {
        return !isDone_;
      }

      Component* next() override {
        isDone_ = true;
        return component_;
      }
    };

    LeafIter* createIterator() override {
      return new LeafIter{this};
    }
  };

  class Container : public Component {
    std::vector<unique_ptr<Component>> members_;
  public:
    Container(string n) : Component{n} {}

    void add(Component* hn) {
      members_.push_back(unique_ptr<Component>(hn));
    }

    int salary() const override {
      int total = 0;
      for (auto& it : members_) {
        total += it->salary();
      }

      return total;
    }

    unsigned int size() const {
      return members_.size();
    }

    Component* get(unsigned int i) const {
      return members_.at(i).get();
    }

    class ContainerIter : public Iter {
      int cursor_;
      std::vector<Iter*> iters_;

    public:
      ContainerIter(Container* ct) : Iter{ct}, cursor_{-1} {
        for (unsigned int i = 0; i < ct->size(); ++i) {
          iters_.emplace_back(ct->get(i)->createIterator());
        }
      }

      ~ContainerIter() {
        for (auto it : iters_) {
          delete it;
        }
      }

      void first() override {
        cursor_ = -1;
        for (auto& it : iters_) {
          it->first();
        }
      }

      bool hasNext() const override {
        if (cursor_ == -1) {
          return true;
        }

        for (unsigned int i = cursor_; i < iters_.size(); ++i) {
          if (iters_.at(i)->hasNext()) {
            return true;
          }
        }

        return false;
      }

      Component* next() override {
        if (cursor_ == -1) {
          cursor_ ++;
          return component_;
        }

        while (static_cast<unsigned int>(cursor_) < iters_.size() && !iters_.at(cursor_)->hasNext()) {
          cursor_++;
        }

        if (static_cast<unsigned int>(cursor_) == iters_.size()) {
          return nullptr;
        }

        return iters_.at(cursor_)->next();
      }
    };

    ContainerIter* createIterator() override {
      return new ContainerIter{this};
    }
  };

  void test() {
    Container *avengers = new Container("Avengers");
    avengers->add(new Leaf("Iron Man", 1000000000));
    avengers->add(new Leaf("Black Widow", 100000));
    avengers->add(new Leaf("Hulk", 100000));
    avengers->add(new Leaf("Thor", 100000));

    Container *spidermen = new Container("Spider-Men");
    spidermen->add(new Leaf("Miles Morales", 0));
    spidermen->add(new Leaf("Peter Parker", 0));
    spidermen->add(new Leaf("Tobey Maguire", 4000000));

    Container *mcu = new Container("MCU");
    mcu->add(avengers);
    mcu->add(new Leaf("Captain America",100000));
    mcu->add(new Leaf("Doctor Strange", 100000));
    mcu->add(new Leaf ("Black Panther", 100000));

    Container myHeroes("Heroes");
    myHeroes.add(mcu);
    myHeroes.add(spidermen);
    myHeroes.add(new Leaf("Squirrel Girl", 50));

    auto yeet = myHeroes.createIterator();
    while (yeet->hasNext()) {
      Component* c = yeet->next();
      std::cout << c->name() << " : " << c->salary() << std::endl;
    }

    delete yeet;
  }
}

#endif
