#include "BST.h"

void Node::display()const { std::cout << value; }

Node::Node(int v) { value = v; }

BinarySearchTree::BinarySearchTree(std::vector<int>* values) { 
    this->createTree(values); 
}
void BinarySearchTree::createTree(std::vector<int>* values) {
    this->root = new Node((*values)[0]);
    int i = 1;
    std::size_t size = (*values).size();
    while (i < size) {
        this->_insert(this->root, new Node((*values)[i]));
        i++;
    }
   
}
BinarySearchTree::~BinarySearchTree() {
    _deleteTree(root);
}
void BinarySearchTree::insertNode(int value) { this->_insert(this->root, new Node(value)); }

void BinarySearchTree::preorder_traversal() {
    // see https://neon1ks.github.io/c/22/2208.htm
    _preorder_traversal(this->root);
}

void BinarySearchTree::postorder_traversal() {
    // see https://neon1ks.github.io/c/22/2208.htm
    _postorder_traversal(this->root);
}

void BinarySearchTree::inorder_traversal() {
    // see https://neon1ks.github.io/c/22/2208.htm
    _inorder_traversal(this->root);
}

void BinarySearchTree::search(int value) {
    std::string answer = _search(this->root, value) ? "Элемент найден" : "Элемент не найден";
    std::cout << answer;
}

void BinarySearchTree::deleteNode(int value) {
    this->root = _delete(this->root, value);

}

void BinarySearchTree::calculateProductElementsOfTree() {
    float result = 1;
    _calculateProductElementsOfTree(this->root, &result);
    std::cout<<"Произвдение всех элементов дерева: " << result;
}

void BinarySearchTree::_postorder_traversal(Node* root) {
    // see https://neon1ks.github.io/c/22/2208.htm
    // Обратный
    if (!root)return;
    _postorder_traversal(root->left);
    _postorder_traversal(root->right);
    std::cout << root->value << " ";
}

void BinarySearchTree::_preorder_traversal(Node* root) {
    // see https://neon1ks.github.io/c/22/2208.htm
    // Прямой
    if (!root)return;
    std::cout << root->value << " ";
    _preorder_traversal(root->left);
    _preorder_traversal(root->right);

}

void BinarySearchTree::_inorder_traversal(Node* root) {
    // see https://neon1ks.github.io/c/22/2208.htm
    // Симметричный
    if (!root)return;
    _inorder_traversal(root->left);
    std::cout << root->value << " ";
    _inorder_traversal(root->right);
}

bool BinarySearchTree::_search(Node* root, int value) {
    if (!root)return false;
    else if (value == root->value)return true;
    else if (value > root->value) return _search(root->right, value);
    else return _search(root->left, value);
}

void BinarySearchTree::_insert(Node* node, Node* insertedNode) {
    if (node->value != insertedNode->value) {
        if (node->value > insertedNode->value) {
            if (!node->left) {
                node->left = insertedNode;
                insertedNode->parent = node;
                if (!node->right)height++;
            }
            else {
                this->_insert(node->left, insertedNode);
            }
        }
        else if (node->value < insertedNode->value) {
            if (!node->right) {
                node->right = insertedNode;
                insertedNode->parent = node;
                if (!node->left)height++;
            }
            else {
                this->_insert(node->right, insertedNode);
            }
        }
    }

}

Node* BinarySearchTree::_get_successor(Node* curr) {
    curr = curr->right;
    while (curr != nullptr && curr->left != nullptr)
        curr = curr->left;
    return curr;
}

// Delete a node with value x from BST
Node* BinarySearchTree::_delete(Node* root, int x) {
    if (root == nullptr)
        return root;

    if (root->value > x)
        root->left = _delete(root->left, x);
    else if (root->value < x)
        root->right = _delete(root->right, x);
    else {
        // Node with 0 or 1 child
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Node with 2 children
        Node* succ = _get_successor(root);
        root->value = succ->value;
        root->right = _delete(root->right, succ->value);
    }
    return root;
}

Node* BinarySearchTree::_findParentNodeByValue(Node* node, int childValue) {
    // return parent node by childValue
    if (!node) return nullptr;

    if ((node->left && node->left->value == childValue) || (node->right && node->right->value == childValue)) return node;

    if (node->value > childValue) return _findParentNodeByValue(node->left, childValue);
    else return _findParentNodeByValue(node->right, childValue);
}

int BinarySearchTree::_findMinValueInTree(Node* node, int minValue) {
    // returns a node whose child elements have a minimum value
    if (!node) return minValue;

    if (node->value < minValue) {
        minValue = node->value;
    }
    int _minNode = _findMinValueInTree(node->left, minValue);
    return _minNode;
}

void BinarySearchTree::_calculateProductElementsOfTree(Node* root, float* product) {
    if (!root)return;
    *product *= root->value;
    _calculateProductElementsOfTree(root->left, product);
    _calculateProductElementsOfTree(root->right, product);

}


void BinarySearchTree::_deleteTree(Node*node) {
    if (!node) return;
    _deleteTree(node->left);
    _deleteTree(node->right);
    delete node;
}

void ThreadedBinarySearchTree::flash_tree() {
    _set_node_thread_links(this->root);
}


void ThreadedBinarySearchTree::_set_node_thread_links(Node* node) {
    // setup thread links for threading tree
    if (!node)return;
    if (node->left==nullptr) {
        node->left_is_threaded = true;
    }
    if (node->right == nullptr) {
        node->right_is_threaded = true;
    }
    _set_node_thread_links(node->left);
    _set_node_thread_links(node->right);
}
Node* ThreadedBinarySearchTree::_find_the_nearest_node(Node* node) {
    Node* curr = node->parent;
    while (curr->parent && curr->value < curr->parent->value) {
        curr = curr->parent;
    }
    return curr;
}


void ThreadedBinarySearchTree::thread_tree()
{
    _thread_left_subtree(this->root->left);
    _thread_right_subtree(this->root->right);
}

void ThreadedBinarySearchTree::_thread_left_subtree(Node* current) {
    if (!current)return;
    if (current == current->parent->right) {
        current->right_threaded_node =  _find_the_nearest_node(current);
    }
    _thread_left_subtree(current->left);
    _thread_left_subtree(current->right);
}
void ThreadedBinarySearchTree::_thread_right_subtree(Node* current) {
    if (!current)return;
    if (current == current->parent->left) {
        current->left_threaded_node = _find_the_nearest_node(current);
    }
    _thread_left_subtree(current->left);
    _thread_left_subtree(current->right);
}