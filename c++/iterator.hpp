#ifndef ITERATOR_H
#define ITERATOR_H

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

  class Iterator {
    // so MyList can access its private constructor
    friend class MyList;

    Node *current_;

    explicit Iterator(Node *head) : current_{head} {}

  public:
    Iterator& operator++() {
      current_ = current_->next_;
      return *this;
    }

    bool operator!=(const Iterator &other) {
      return current_ != other.current_;
    }

    bool operator==(const Iterator &other) {
      return current_ == other.current_;
    }

    int& operator*() {
      return current_->value_;
    }
  };

  Iterator begin() {
    return Iterator{head_};
  }

  Iterator end() {
    return Iterator{nullptr};
  }
};

#endif
