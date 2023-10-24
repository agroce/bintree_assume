#include <deepstate/DeepState.hpp>

using namespace deepstate;

typedef struct node{
  int data;
  struct node *left;
  struct node *right;  
} NODE;

NODE *create_node(int val) {
  NODE *newnode = (NODE*)malloc(sizeof(NODE));
  newnode->data = val;
  newnode->left = NULL;
  newnode->right = NULL;
  return newnode;
}

NODE *random_tree1(unsigned int max_depth, int top_val) {
  if (!DeepState_Bool()) {
    return NULL;
  }
  NODE *top = create_node(top);
  int v_left = DeepState_Int();
  ASSUME(v_left < top_val);
  top->left = random_tree1(max_depth - 1, v_left);
  int v_right = DeepState_Int();
  ASSUME(v_right > top_val);
  top->right = random_tree1(max_depth - 1, v_right);  
  return top;
}

NODE *random_tree2(unsigned int max_depth, int top_val) {
  if (!DeepState_Bool()) {
    return NULL;
  }
  NODE *top = create_node(top);
  int v_left;
  ASSIGN_SATISFYING(v_left, DeepState_Int(), v_left < top_val);  
  top->left = random_tree2(max_depth - 1, v_left);
  int v_right;
  ASSIGN_SATISFYING(v_right, DeepState_Int(), v_right > top_val);   
  top->right = random_tree2(max_depth - 1, v_right);
  return top;
}

unsigned int tree_size(NODE *n) {
  if (n == NULL) {
    return 0;
  } else {
    return 1 + tree_size(n->left) + tree_size(n->right);
  }
}

TEST(Bintree, Count) {
  NODE *t = random_tree1(8, DeepState_Int());
  LOG(TRACE) << "actual size: " << tree_size(t);
}
