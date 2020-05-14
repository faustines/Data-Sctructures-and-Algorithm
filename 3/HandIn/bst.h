#ifndef BST_H_
#define BST_H_

#include <algorithm>
#include <iostream>
#include <memory>
#include <utility>
#include <stack>
#include <string>

/*
 * Class definition
 */
template <typename T>
class BST {
  struct Node{
    T key;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
  };
 public:
   int bigNum = 999999999;
   int smallNum = -999999999;
   int Value = 0;
   int kth_smalll = 0;

  /* Return floor key in tree */
  const T& floor(const T &key);
  const T& floor(std::unique_ptr<Node>& n, const T &key);
  /* Return ceil key in tree */
  const T& ceil(const T &key);
  const T& ceil(std::unique_ptr<Node>& n, const T &key);
  /* Return k-th smallest key in tree */
   const T& kth_small(const int k);
   const T& kth_small(std::unique_ptr<Node>& n, const int k);
  // const T& InorderRecur(Node *n, int k);
  const void InorderRecur(Node *n, int k, int& count);

  /* Return whether @key is found in tree */
  bool contains(const T& key);

  /* Return max key in tree */
  const T& max();
  /* Return min key in tree */
  const T& min();

  /* Insert @key in tree */
  void insert(const T &key);
  /* Remove @key from tree */
  void remove(const T &key);

  /* Print tree in-order */
  void print();

 private:

  std::unique_ptr<Node> root;

  /* Useful recursive helper methods */
  void insert(std::unique_ptr<Node> &n, const T &key);
  void remove(std::unique_ptr<Node> &n, const T &key);
  void print(Node *n, int level);
};

/*
* Implementation
*/
template <typename T>
const T& BST<T>::floor(const T &key){
  if (!root) throw std::runtime_error("Empty tree");
  if (floor(root, key) == bigNum){
    std::string error;
    error = "Cannot find floor for key " + std::to_string(key);
    throw std::logic_error(error);
  }

  return(floor(root, key));
}

template <typename T>
const T& BST<T>::floor(std::unique_ptr<Node>& n, const T &key) {

    if (!n)
        return bigNum;

    /* If n->key is equal to key */
    if (key == n.get()->key)
        return n.get()->key;

    /* If n->key is greater than the key */
    if (n.get()->key > key)
        return floor(n.get()->left, key);

    /* Else, the floor may lie in right subtree
      or may be equal to the root*/
    Value = floor(n.get()->right, key);
    return (Value <= key) ? Value : n.get()->key;
}

template <typename T>
const T& BST<T>::ceil(const T &key){
  if (!root) throw std::runtime_error("Empty tree");
  if (ceil(root, key) == smallNum){
    std::string error;
    error = "Cannot find ceil for key " + std::to_string(key);
    throw std::logic_error(error);
  }
  return(ceil(root, key));
}

template <typename T>
const T& BST<T>::ceil(std::unique_ptr<Node>& n, const T &key) {

    if (!n)
        return smallNum;

    /* If n->key is equal to key */
    if (key == n.get()->key)
        return n.get()->key;

    /* If n->key is smaller than the key */
    if (n.get()->key < key)
        return ceil(n.get()->right, key);

    /* Else, the ceil may lie in left subtree
      or may be equal to the root*/
    Value = ceil(n.get()->left, key);
    return (Value >= key) ? Value : n.get()->key;
}

template <typename T>
const T& BST<T>::kth_small(const int k) {
  if (!root) throw std::runtime_error("Empty tree");
  return (kth_small(root,k));
}

template <typename T>
const T& BST<T>::kth_small(std::unique_ptr<Node>& n, const int k) {
  int count =0;
  InorderRecur(n.get(),k,count);
  if (k > count){
    std::string error;
    error = "Cannot find kth_small for key " + std::to_string(k);
    throw std::logic_error(error);
  }
  return(kth_smalll);
}

template <typename T>
const void BST<T>::InorderRecur(Node *n, int k, int& count) {

  if (!n) return;
  InorderRecur(n->left.get(), k,count);
  count ++;
  if (count == k) {
    kth_smalll = n->key;
  }else if (count > k){

  }
  if (k < 0 || k == 0){
    std::string error;
    error = "Cannot find kth_small for key " + std::to_string(k);
    throw std::logic_error(error);
  }
  InorderRecur(n->right.get(), k,count);
}

/*
* @@@ Code below should not be modified @@@
*/
template <typename T>
bool BST<T>::contains(const T &key) {
 Node *n = root.get();

 while (n) {
   if (key == n->key)
     return true;

   if (key < n->key)
     n = n->left.get();
   else
     n = n->right.get();
 }

 return false;
}

template <typename T>
const T& BST<T>::max(void) {
 if (!root) throw std::runtime_error("Empty tree");
 Node *n = root.get();
 while (n->right) n = n->right.get();
 return n->key;
}

template <typename T>
const T& BST<T>::min(void) {
 if (!root) throw std::runtime_error("Empty tree");
 Node *n = root.get();
 while (n->left) n = n->left.get();
   return n->key;
 }

 template <typename T>
 void BST<T>::insert(const T &key) {
   insert(root, key);
 }

 template <typename T>
 void BST<T>::insert(std::unique_ptr<Node> &n, const T &key) {
   if (!n)
     n = std::unique_ptr<Node>(new Node{key});
   else if (key < n->key)
     insert(n->left, key);
   else if (key > n->key)
     insert(n->right, key);
   else
     std::cerr << "Key " << key << " already inserted!\n";
 }

 template <typename T>
 void BST<T>::remove(const T &key) {
   remove(root, key);
 }

 template <typename T>
 void BST<T>::remove(std::unique_ptr<Node> &n, const T &key) {
   /* Key not found */
   if (!n) return;

   if (key < n->key) {
     remove(n->left, key);
   } else if (key > n->key) {
     remove(n->right, key);
   } else {
     /* Found node */
     if (n->left && n->right) {
       /* Two children: replace with min node in right subtree */
       n->key = min(n->right.get())->key;
       remove(n->right, n->key);
     } else {
       /* Replace with only child or with nullptr */
       n = std::move((n->left) ? n->left : n->right);
     }
   }
 }

 template <typename T>
 void BST<T>::print() {
   if (!root) return;
   print(root.get(), 1);
  std::cout << std::endl;
}

template <typename T>
void BST<T>::print(Node *n, int level) {
  if (!n) return;

  print(n->left.get(), level + 1);
  std::cout << n->key
      << " (" << level << ") ";
  print(n->right.get(), level + 1);
}

#endif /* BST_H_ */
