#include <windows.h>
#include "BST.h"
#include "DirectedGraph.h"
#include "algorithm"
#include "queue"
#include "utility"


// class for draw something
class DrawWorker {
public:
    COORD coord;
    void drawStraightLineByOX(int x_start, int x_end, int y, char lineSign) {
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
        setCursorPosition(x_start, y);
        while (coord.X < x_end) {
            std::cout << lineSign;
            coord.X++;
        }
    }
    void drawStraightLineByOY(int y_start, int y_end, int x, char lineSign) {
        // this function drawing line wich will parallel with OY and have height X above OY
        /*
        *                   ^ OY
        *                   |
        *                   |
        *                   |
        *          y_end    -     |
        *                   |     |
        *                   |     |
        *                   |     |
        *                   |     |
        *                   |     |
        *           y_start -     |
        *                   |-----|------------------------------>
        *                   |     x                    
        */
        setCursorPosition(x, y_start);
        while (coord.Y < y_end) {
            std::cout << lineSign;
            coord.Y++;
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
    template<typename T>
    void drawLineUnderDegree(int start_x, int start_y, int lineLength, int degree, T lineSign) {
        /*
        * This function will drawing line under degree:
        * x = x0+l*cos(degree)
        * y = y0+l*sin(degree)
        *
        *
        *                   ^ OY                  \
        *                   |                      \
        *                   |                       \
        *                   |     (start_x,start_x)->*
        *                   |                         \
        *                   |                          \
        *                   |                           \
        *                   |---------------------------|--------->
        *                   |                         end_x       OX
        *                   |
        *
        */
        int x_end = static_cast<int>(start_x/ + lineLength * std::cos(degree));
        int y_end = static_cast<int>(start_y + lineLength * std::sin(degree));
        if (x_end < 0) start_x *= -1;
        if (y_end < 0) start_y *= -1;
        while (coord.X != x_end || coord.Y != y_end) {
            setCursorPosition(coord.X, coord.Y);
            std::cout << lineSign;
            if (coord.X != x_end) {
                coord.X += 1;
            }
            if (coord.Y != y_end) {
                coord.Y += 1;
            }
        }
    }
    void displayBinaryTree(Node* root, int y = 0, int startScreenBlock = 0, int middleScreenBlockPosition = 60, int endScreenBlock = 120) {
        _displayBinaryTree(root, y, startScreenBlock, middleScreenBlockPosition,endScreenBlock);
        setCursorPosition(0,20);
    }
    void displayDirectedGraph(DirectedGraph* g) {
        _displayDirectedGraph(g);
    }
private:
    
    void _displayBinaryTree(Node* root, int y = 0, int startScreenBlock = 0, int middleScreenBlockPosition = 60, int endScreenBlock = 120) {
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

            drawStraightLineByOX((startScreenBlock + middleScreenBlockPosition) / 2, middleScreenBlockPosition, y, '_');
            drawStraightLineByOX(middleScreenBlockPosition + 1, (middleScreenBlockPosition + endScreenBlock) / 2, y, '_');
            y++;
        }
        // draw next nodes
        displayBinaryTree(root->left, y, startScreenBlock, (startScreenBlock + middleScreenBlockPosition) / 2, middleScreenBlockPosition);
        displayBinaryTree(root->right, y, middleScreenBlockPosition, (middleScreenBlockPosition + endScreenBlock) / 2, endScreenBlock);
    }
    void _displayDirectedGraph(DirectedGraph* graph) {
        std::cout << "Матрица весов" << std::endl;
        graph->displayWeightMatrix();
    }
    
};
int main()
{   
    setlocale(LC_ALL, "");
    DrawWorker* d = new DrawWorker();
    std::vector<std::vector<int>> wM = {
        {0,0,2,5,5,0,0,0},
        {1,0,2,2,0,3,0,0},
        {6,0,0,0,3,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,5,0},
        {0,5,0,0,0,0,4,4},
        {0,0,0,0,6,6,0,6},
        {0,0,0,0,0,0,0,0}
    };
    DirectedGraph* g = new DirectedGraph(wM);
    std::vector<std::stack<int>> pathes = g->dijkstrasAlgorithm(1);
    for (std::stack<int> path : pathes) {
        std::cout << std::endl;
        while (!path.empty()) {
            std::cout <<std::setw(3)<<path.top();
            path.pop();
        }
    }
    std::cout << std::endl;
    std::cout << g->findPathesByLength(1, 6, 3);
}