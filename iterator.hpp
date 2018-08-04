#ifndef ITERATOR_H
#define ITERATOR_H

#include <iostream>

namespace Iterator {

  class MyList {
    class Node {
    public:
      int value_;
      Node* next_;
      Node(int val, Node *next) : value_{val}, next_{next} {}
    };

    Node *head_;

  public:
    MyList() {
      head_ = new Node(1, new Node(2, new Node(3, nullptr)));
    }

    class iter {
      // so MyList can access its private constructor
      friend class MyList;

      Node *current_;

      explicit iter(Node *head) : current_{head} {}

    public:
      iter& operator++() {
        current_ = current_->next_;
        return *this;
      }

      bool operator!=(const iter &other) {
        return current_ != other.current_;
      }

      bool operator==(const iter &other) {
        return current_ == other.current_;
      }

      int& operator*() {
        return current_->value_;
      }
    };

    iter begin() {
      return iter{head_};
    }

    iter end() {
      return iter{nullptr};
    }
  };

  void test() {
    MyList ml;
    for (auto el : ml) {
      std::cout << el << std::endl;
    }
  }

};


#endif
