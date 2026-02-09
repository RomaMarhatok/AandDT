#include <iostream>
#include <vector>
#include <string>
#include <random>

#ifndef BTSNode
#define BTSNode
class Node {
public:
    int value;
    Node* left = nullptr;
    Node* right = nullptr;

    void display() const;
    Node(int v);
};
#endif // !BTSNode

#ifndef BSTTree
#define BST
class BinarySearchTree {
public:
    Node* root{};
    int height = 1;

    BinarySearchTree(std::vector<int>* values);
    void createTree(std::vector<int>* values);
    void insertNode(int value);
    void preorder_traversal();
    void postorder_traversal();
    void inorder_traversal();
    void search(int value);
    void deleteNode(int value);
    void calculateProductElementsOfTree();
    ~BinarySearchTree();
private:
    void _postorder_traversal(Node* root);
    void _preorder_traversal(Node* root);
    void _inorder_traversal(Node* root);
    bool _search(Node* root, int value);
    void _insert(Node* node, Node* insertedNode);

    void _delete_node_without_children(Node* parentNode, Node* deletedNode);
    void _delete_node_with_one_child(Node* parentNode);
    void _delete_node_with_two_children(Node* deletedNode);
    void _delete(Node* node, int value);
    void _deleteTree(Node*root);
    Node* _findParentNodeByValue(Node* node, int childValue);
    int _findMinValueInTree(Node* node, int minValue = INT_MAX);
    void _calculateProductElementsOfTree(Node* root, float* product);
};
#endif // !BSTTree

