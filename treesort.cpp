#include "treesort.h"
#include <fstream>
#include <sstream>
#include <bitset>
#include <vector>
#include <string>


void print_tree(BSTree* tree, std::bitset<3> mode);

int main(int argc, char* argv[]) {

    std::string dataset = argv[1];

    BSTree* tree = new BSTree();


    //check if dataset file was opened successfully
    std::ifstream data(dataset);
    if (!data.is_open()) {
        std::cerr << "Error opening dataset file: " << "data" << std::endl;
        return 1;
    }

    std::string line;
    // Skip the header line
    std::getline(data, line);

    std::getline(data, line);

    std::vector<int> treeArr;
    while (std::getline(data, line)) {      //read file data
        std::stringstream ss(line);
        std::string objectId, name, obesityStr, shapeArea, shapeLength;
       double obesity;

       //each line is parsed to extract different fields of the data

        std::getline(ss, objectId, ',');
        std::getline(ss, name, ',');
        std::getline(ss, obesityStr, ',');
        std::getline(ss, shapeArea, ',');
        std::getline(ss, shapeLength, ',');
        
        //obesity is converted to a double int
        obesity = std::stod(obesityStr);

        //obesity value is inserted into the BST

        int obesityInt = static_cast<int>(obesity * 10); // Convert to integer for tree insertion
        tree->insert(obesityInt);
        treeArr.push_back(obesityInt);
    }

    data.close();


    
    std::bitset<3> mode("111"); // Preorder, Inorder, and Postorder
    std::cout << "Height: " << tree->height() << std::endl;  //prints the current height of the tree

   

    int num;
    // Insert the numbers


//prints original unsorted array of obesity index values
    std::cout << "Original array of obesity values: ";
    for (int num : treeArr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    tree->treeSort(treeArr);

    //prints sorted array of obesity index values 

    std::cout << "Sorted array of obesity values: ";
    for (int num : treeArr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

   

    // Destroy the tree
    tree->destroy();
    std::cout << "Height after tree is destroyed: " << tree->height() << std::endl;     //prints height of destroyed tree

    delete tree;
    return 0;
}
    //prints the tree based on the traversal
void print_tree(BSTree* tree, std::bitset<3> mode) {
    if (mode[0]) {
        tree->preorder();
    }
    if (mode[1]) {
        tree->inorder();
    }
    if (mode[2]) {
        tree->postorder();
    }
}
