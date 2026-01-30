#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

//default implementation of tree node
class Node {
public:
    int value;
    Node* left =nullptr;
    Node* right = nullptr;
    
    void display() {
        std::cout << value;
    }
    Node(int v) {
        value = v;
    }
};

// class for draw something
class DrawWorker {
public:
    COORD coord;
    void drawLine(int x_start,int x_end,int y,char lineSign) {
        // this function drawing line wich will parallel with OX and have height Y above OX
        /*
        *                   ^ OY
        *                   |
        *                   |
        *                (y)|     ___________________________
        *                   |
        *                   |
        *                   |-----|-------------------------|----->
        *                   |   x_start                    x_end  OX
        *                   |
        */
        this->setCursorPosition(x_start, y);
        while (this->coord.X < x_end) {
            std::cout << lineSign;
            this->coord.X++;
        }
    }
    void setCursorPosition(int x, int y) {
        // set specific postion for cursor into console
        /*
        *                   ^ OY
        *                   |
        *                   |
        *                (y)|     *
        *                   |
        *                   |
        *                   |-----|------------------------------>
        *                   |    (x)                             OX
        *                   |
        */
        this->coord.X = x;
        this->coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), this->coord);
    }
    void displayBinaryTree(Node* root, int y = 0, int startScreenBlock = 0, int middleScreenBlockPosition = 60, int endScreenBlock = 120) {
        /*
        * this function will display your tree by this algorithm:
        * 1) Each node has WIDTH = 3px and HEIGHT = 2px;
        * 
        * 2) Depend on the screen width ,the space is devided into sectors where the number of sectors = AMOUNT_OF_ELEMENTS_ON_TREE_LEVEL + 1;
        *    2.1) if width is even, the value was printed in first sector, which was equals 59px instead 60px;
        * 
        3) Eache element's value will written in the middle of its own sector;
        * 
        * 4) Before and After each value, the sign "|" is printed;
        *    However, if a node on the bottom level of tree and its left and right children are bouth nullptr, nothing is printed;
        *
        * 5) Each node connected to each other using a line, calculated as follows:
        *    1) for left line: start = (startScreenBlock + middleScreenBlockPosition ) / 2, end = middleScreenBlockPosition;
        *    2) for right line start = middleScreenBlockPosition + 1, end = (middleScreenBlockPosition + endScreenBlock) / 2;
        *
        *
        * 7) For the next level will sectors will divided by next rules:
        *   7.1) for left subtree: start = startScreenBlock, middle = (startScreenBlock + middleScreenBlockPosition) / 2, end = middleScreenBlockPosition;
        *   7.2) for right subtree: start = middleScreenBlockPosition, middle = (middleScreenBlockPosition + endScreenBlock) / 2, end = endScreenBlock;
        * 
        * 6) Nodes with value NULL are not printed;
        *
        * 
        * Example:
        *   Screen width = 120px;
        *   Values for tree: 5,2,6,8,4,13;
        *   
        *   startScreenBlock = 0px, middleScreenBlockPosition = 60px, endScreenBlock = 120px
        * 
        *      NOTE: in the specified limit for the next sector and in parentheses, the length of the string
        *                                           |
        *                              sector(0,60) 5 sector(60,120)
        *                       _______30(30)_______|_______90(30)_______
        *                       |                                       |
        *          sector(0,30) 2 sector(30,60)           sector(60,90) 6 sector(90,120)  
        *           ___15(15)___|___45(15)___               ___75(15)___|___105(15)___
        *                                   |                                         |
        *                                   4                           sector(60,75) 8 sector(105,120)  
        *                                                                  ___67(8)___|___112(7)___      <----- this option is a sector that is not divided into two
        *                                                                                         |              and which is why graph is printed with a collision
        *                                                                                         13
        */  
        //check if node is nullptr
        if (!root)return;
        // draw values of root like that:
        /*
        *   |
        * value
        *   |
        */
        std::string rootValue = !root ? "NULL" : std::to_string(root->value);
        setCursorPosition(middleScreenBlockPosition, y);
        std::cout << "|";
        y++;
        setCursorPosition(middleScreenBlockPosition, y);
        std::cout << rootValue;
        y++;
        setCursorPosition(middleScreenBlockPosition, y);
        std::cout << "|";
        // check if root have left or right node
        if (root->left || root->right) {
            // draw lines for branches
            /*
            *                 |
            *               value
            *    -------------|--------------
            */
            
            drawLine((startScreenBlock + middleScreenBlockPosition) / 2, middleScreenBlockPosition, y, '_');
            drawLine(middleScreenBlockPosition + 1, (middleScreenBlockPosition + endScreenBlock) / 2, y, '_');
            y++;
        }
        // draw next nodes
        displayBinaryTree(root->left, y, startScreenBlock, (startScreenBlock + middleScreenBlockPosition) / 2, middleScreenBlockPosition);
        displayBinaryTree(root->right, y, middleScreenBlockPosition, (middleScreenBlockPosition + endScreenBlock) / 2, endScreenBlock);
    }


};
class BinarySearchTree {
public:
    // create empty root object
    Node* root{};
    // initialize height of tree
    int height = 1;

    BinarySearchTree(std::vector<int>* values) {
        this->createTree(values);
    }
    void createTree(std::vector<int>* values){
        this->root = new Node((*values)[0]);
        int i = 1;
        std::size_t size = (*values).size();
        while (i < size) {
            this->_insert(this->root, new Node((*values)[i]));
            i++;
        }
        this->root = root;
    }
    void insertNode(int value) {
        this->_insert(this->root, new Node(value));
    }
    void preorder_traversal() {
        // see https://neon1ks.github.io/c/22/2208.htm
        _preorder_traversal(this->root);
    }
    
    void postorder_traversal() {
        // see https://neon1ks.github.io/c/22/2208.htm
        _postorder_traversal(this->root);
    }
    void inorder_traversal() {
        // see https://neon1ks.github.io/c/22/2208.htm
        _inorder_traversal(this->root);
    }
    void search(int value) {
        std::string answer = _search(this->root, value)?"Founded":"Not founded";
        std::cout << answer;
    }
    void deleteNode(int value) {
        _delete(this->root, value);
        
    }
    void calculateProductElementsOfTree() {
        float result = 1;
        _calculateProductElementsOfTree(this->root, &result);
        std::cout << result;
    }
private:
    void _postorder_traversal(Node* root) {
        // see https://neon1ks.github.io/c/22/2208.htm
        // Симметричный
        if (!root)return;
        _postorder_traversal(root->left);
        _postorder_traversal(root->right);
        std::cout << root->value << "\n";
    }
    void _preorder_traversal(Node* root) {
        // see https://neon1ks.github.io/c/22/2208.htm
        // Прямой
        if (!root)return;
        std::cout << root->value << "\n";
        _preorder_traversal(root->left);
        _preorder_traversal(root->right);

    }
    void _inorder_traversal(Node* root) {
        // see https://neon1ks.github.io/c/22/2208.htm
        // Обратный
        if (!root)return;
        _inorder_traversal(root->left);
        std::cout << root->value << "\n";
        _inorder_traversal(root->right);
    }
    bool _search(Node*root,int value) {
        if (!root)return false;
        else if (value == root->value)return true;
        else if (value > root->value) return _search(root->right, value);
        else return _search(root->left, value);
    }
    void _insert(Node* node, Node* insertedNode) {
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

    void _delete_node_without_children(Node* parentNode, Node* deletedNode) {
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
    void _delete_node_with_one_child(Node* parentNode) {
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
    void _delete_node_with_two_children(Node* deletedNode) {
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
    void _delete(Node* node, int value) {
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
    Node* _findParentNodeByValue(Node* node,int childValue) {
        // return parent node by childValue
        if (!node) return nullptr;
        
        if ((node->left && node->left->value == childValue) || (node->right && node->right->value == childValue)) return node;
        
        if (node->value > childValue) return _findParentNodeByValue(node->left, childValue);
        else return _findParentNodeByValue(node->right, childValue);
    }
    int _findMinValueInTree(Node*node,int minValue = INT_MAX) {
        // returns a node whose child elements have a minimum value
        if (!node) return minValue;
        
        if (node->value < minValue) {
            minValue = node->value;
        }
        int _minNode = _findMinValueInTree(node->left, minValue);
        return _minNode;
    }
    void _calculateProductElementsOfTree(Node* root,float* product) {
        if (!root)return;
        *product*= root->value;
        _calculateProductElementsOfTree(root->left,product);
        _calculateProductElementsOfTree(root->right,product);
        
    }
};
int main()
{   
    std::vector<int>* v = new std::vector<int>{ 54,50,85,3,10,59,2,82,66,42,9,78,22,57,92 };
    BinarySearchTree* t = new BinarySearchTree(v);
    
}