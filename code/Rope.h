#ifndef ROPE_H__
#define ROPE_H__

#include <string>
#include <memory>
#include <vector>

using namespace std;

// rope_node is the binary search tree node structure for the rope class
  struct rope_node {
    bool is_leaf;
    int length;
    int weight;
    string input;
    shared_ptr<rope_node> left;
    shared_ptr<rope_node> right;
    shared_ptr<rope_node> parent;
  };

  // Rope Data Structure:
  //
  // From any subtree node t, the left subtree's data values must be
  // less than t's data value. The right subtree's data values must be
  // greater than or equal to t's data value.
class Rope{
public:

  // constructor, initialize class variables and pointers here if need.
  // Initially set root_ptr_ to a null shared_ptr of node
  Rope();

  // deconstructor, if you are using shared_pointers you don't need to keep track of
  // freeing memory and you can leave this blank
  ~Rope();

  // init_node initializes a new bst_node from the heap using the given
  // data, and two NULL children, and returns a pointer to it.
  shared_ptr<rope_node> InitNode(string text);

  // insert places the new_node in a proper location in the tree
  // while obeying the invariant. On return, root_ptr_
  // points to the root of the tree.
  //void Insert(shared_ptr<rope_node> new_node);

  shared_ptr<rope_node> MakeTree(shared_ptr<rope_node> root_ptr, string input);

  // This function concatenates two rope nodes together and updates
  // the weight value based on the invariant - weighe of left node(s)
  shared_ptr<rope_node> Concatenate(shared_ptr<rope_node> a, shared_ptr<rope_node> b);

  //This function locates the string stored in the node based on the
  //integer provided 
  void Index_string(shared_ptr<rope_node> root_ptr, int i, string& output);

  //This function updates the shared pointer to the node to the leaf
  //holding the place string location based on the int number
  void Index_location(shared_ptr<rope_node>& root_ptr, int i);

  //Takes in a root node and splits the rope node into 2 new nodes 
  //returning the new root and updating the old based on int i location
  shared_ptr<rope_node> Split(shared_ptr<rope_node>& root_ptr, int i);

  // Returns the root pointer
  shared_ptr<rope_node> GetRoot();

  // This function sets a given pointer as the top pointer
  void SetRoot(shared_ptr<rope_node> root_ptr);

    
private:
  int Rope_count;

  // this pointer always will point to root of the tree
  shared_ptr<rope_node> root_ptr_;
};

#endif // ROPE_H__