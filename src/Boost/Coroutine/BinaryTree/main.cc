//
// Created by Will Lee on 2021/10/1.
//

#include <boost/coroutine2/all.hpp>
#include <iostream>
#include <iterator>

struct node {
  typedef std::shared_ptr<node> ptr_t;

  // Each tree node has an optional left subtree,
  // an optional right subtree and a value of its own.
  // The value is considered to be between the left
  // subtree and the right.
  ptr_t left, right;
  std::string value;

  // construct leaf
  node(const std::string &v) : left(), right(), value(v) {}

  // construct nonleaf
  node(ptr_t l, const std::string &v, ptr_t r) : left(l), right(r), value(v) {}

  static ptr_t create(const std::string &v) {
    return ptr_t(new node(v));
  }

  static ptr_t create(ptr_t l, const std::string &v, ptr_t r) {
    return ptr_t(new node(l, v, r));
  }
};

node::ptr_t create_left_tree_from(const std::string &root) {
  /* --------
       root
       / \
      b   e
     / \
    a   c
   -------- */
  return node::create(node::create(node::create("a"), "b", node::create("c")), root, node::create("e"));
}

node::ptr_t create_right_tree_from(const std::string &root) {
  /* --------
       root
       / \
      a   d
         / \
        c   e
     -------- */
  return node::create(node::create("a"), root, node::create(node::create("c"), "d", node::create("e")));
}

typedef boost::coroutines2::coroutine<std::string> coro_t;

// recursively walk the tree, delivering values in order
void traverse(node::ptr_t n, coro_t::push_type &out) {
  if (n->left) traverse(n->left, out);
  out(n->value);
  if (n->right) traverse(n->right, out);
}

// evaluation
int main() {

  {
    node::ptr_t left_d(create_left_tree_from("d"));
    coro_t::pull_type left_d_reader([&](coro_t::push_type &out) {
      traverse(left_d, out);
    });

    node::ptr_t right_b(create_right_tree_from("b"));
    coro_t::pull_type right_b_reader([&](coro_t::push_type &out) {
      traverse(right_b, out);
    });

    std::cout << "left tree from d == right tree from b? " << std::boolalpha
              << std::equal(std::begin(left_d_reader), std::end(left_d_reader), std::begin(right_b_reader))
              << std::endl;
  }

  {
    node::ptr_t left_d(create_left_tree_from("d"));
    coro_t::pull_type left_d_reader([&](coro_t::push_type &out) {
      traverse(left_d, out);
    });

    node::ptr_t right_x(create_right_tree_from("x"));
    coro_t::pull_type right_x_reader([&](coro_t::push_type &out) {
      traverse(right_x, out);
    });

    std::cout << "left tree from d == right tree from x? " << std::boolalpha
              << std::equal(std::begin(left_d_reader), std::end(left_d_reader), std::begin(right_x_reader))
              << std::endl;
  }
  std::cout << "Done" << std::endl;
}