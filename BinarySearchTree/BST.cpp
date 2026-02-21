#include "BST.h"

void Node::display()const { std::cout << value; }

Node::Node(int v) { value = v; }

BinarySearchTree::BinarySearchTree(std::vector<int>* values) { this->createTree(values); }
void BinarySearchTree::createTree(std::vector<int>* values) {
    this->root = new Node((*values)[0]);
    int i = 1;
    std::size_t size = (*values).size();
    while (i < size) {
        this->_insert(this->root, new Node((*values)[i]));
        i++;
    }
    this->root = root;
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
    std::string answer = _search(this->root, value) ? "Founded" : "Not founded";
    std::cout << answer;
}

void BinarySearchTree::deleteNode(int value) {
    _delete(this->root, value);

}

void BinarySearchTree::calculateProductElementsOfTree() {
    float result = 1;
    _calculateProductElementsOfTree(this->root, &result);
    std::cout<<"Произвдение всех элементов дерева: " << result;
}

void BinarySearchTree::_postorder_traversal(Node* root) {
    // see https://neon1ks.github.io/c/22/2208.htm
    // Симметричный
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
    // Обратный
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
                if (!node->right)height++;
            }
            else {
                this->_insert(node->left, insertedNode);
            }
        }
        else if (node->value < insertedNode->value) {
            if (!node->right) {
                node->right = insertedNode;
                if (!node->left)height++;
            }
            else {
                this->_insert(node->right, insertedNode);
            }
        }
    }

}

void BinarySearchTree::_delete_node_without_children(Node* parentNode, Node* deletedNode) {
    /*
    *  proccess node without children:
    *  Delete node with value 1:
    *
    *  1)    parentNode -> 2
    *                     / \
    *   deletedNode ->   1   null
    *
    *  2)               2                   2
    *                  / \        ->       / \
    *     delete ->   1   null          null  null
    */
    if (parentNode->value > deletedNode->value) parentNode->left = nullptr;
    else parentNode->right = nullptr;
    delete deletedNode;
}

void BinarySearchTree::_delete_node_with_one_child(Node* parentNode) {
    /*
    *  proccess node with one child(left or right):
    *  Delete node with value 4:
    *
    *  1)           1
    *              / \
    *          null   4 <- parentNode
    *                  \
    *                   5
    *
    *  2)           1
    *              / \
    *          null   5
    *                  \
    *                   5
    *  3)           1
    *              / \
    *          null   5
    *                  \
    *                   null
    */
    if (parentNode->left && !parentNode->right) {
        parentNode->value = parentNode->left->value;
        delete parentNode->left;
        parentNode->left = nullptr;

    }
    else if (parentNode->right && !parentNode->left) {
        parentNode->value = parentNode->right->value;
        delete parentNode->right;
        parentNode->right = nullptr;
    }
}

void BinarySearchTree::_delete_node_with_two_children(Node* deletedNode) {
    /*
    * proccess node with two children:
    * for more info see https://www.techiedelight.com/deletion-from-bst/
    * Delete node with value 40:
    * Example:
    *           35
    *          /  \
    *        12    60
    *             /  \
    *           40   null
    *          /  \
    *        39    58
    *             /  \
    *           57    59
    *
    *
    *  1)       35
    *          /  \
    *        12    60
    *             /  \
    *           40   null
    *          /  \
    *        39    58 <- _findMinNode will return this node
    *             /  \
    *     min-> 57    59
    *
    *
    *  2)       35                              35
    *          /  \                            /  \
    *         12   60                        12   60
    *             /  \                           /  \
    * assign -> 40   null         ->            57  null
    *          /  \                            /  \
    *        39    58                         39  58
    *             /  \                           /  \
    *   delete-> 57   59                      null   59
    */
    int minValue = _findMinValueInTree(deletedNode->right);
    Node* parentNodeWithMinValue = _findParentNodeByValue(this->root, minValue);
    _delete(parentNodeWithMinValue, minValue);
    deletedNode->value = minValue;
}

void BinarySearchTree::_delete(Node* node, int value) {
    if (!node)return;
    else if (node->left && node->left->value == value && (!node->left->left && !node->left->right)) {
        _delete_node_without_children(node, node->left);
    }
    else if (node->right && node->right->value == value && (!node->right->left && !node->right->right)) {
        _delete_node_without_children(node, node->right);
    }
    else if (node->value == value && ((node->right && !node->left) || node->left && !node->right)) {
        _delete_node_with_one_child(node);
    }
    else if (node->value == value && node->right && node->left) {
        _delete_node_with_two_children(node);
    }
    else {
        if (node->value > value) _delete(node->left, value);
        else _delete(node->right, value);
    }
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
void _dijkstrasAlgorithm(int vertex) {

}