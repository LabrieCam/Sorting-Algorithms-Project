
#include <fstream>
#include <iostream>
#include <bitset>
#include <functional>
#include <vector>

class BSTree {
private:

    //defines node in BST
    struct Node {
        int data;
        Node* right;
        Node* left;
        Node(int num) : data(num), right(nullptr), left(nullptr) {}
    };

    //defines root node of tree
    Node* root;

//inorder traversal of BST
    void inorder(Node* node, std::ostream& os) const {
        if (node != nullptr) {
            inorder(node->left, os);
            os << node->data << " ";
            inorder(node->right, os);
        }
    }
//inorder traversal of BST
    void inorder(Node* node, std::vector<int>& arr) const {
        if (node != nullptr) {
            inorder(node->left, arr);
            arr.push_back(node->data);
            inorder(node->right, arr);
        }
    }


        //insert new value into BST
    void insert(Node*& node, int num) {
        if (node == nullptr) {
            node = new Node(num);
        } else if (num > node->data) {
            insert(node->right, num);
        } else {
            insert(node->left, num);
        }
    }


        //postorder traversal of BST
    void postorder(Node* node, std::ostream& os) const {
        if (node != nullptr) {
            postorder(node->left, os);
            postorder(node->right, os);
            os << node->data << " ";
        }
    }

       // preorder traversal of BST
    void preorder(Node* node, std::ostream& os) const {
        if (node != nullptr) {
            os << node->data << " ";
            preorder(node->left, os);
            preorder(node->right, os);


        }
    }


    //deallocates the memory used by each tree node
    void destroyTree(Node* node) {
        if (node != nullptr) {
            destroyTree(node->right);
            destroyTree(node->left);

            delete node;
        }
    }


    //calculates height of the BST
    int height(Node* node) const {
        if (node != nullptr) {
            int rightHeight = height(node->right);
            int leftHeight = height(node->left);

            return std::max(leftHeight, rightHeight) + 1;
        } else {
            return -1;
        }
    }


   
    
public:

    //default constructor
    BSTree() : root(nullptr) {}

    //destructor
    ~BSTree() {
        destroyTree(root);
    }
        //outputs node values from the inorder traversal
    void inorder(std::ostream& os = std::cout) const {
        inorder(root, os);
        os << std::endl;
    }


    //public version of insert to insert values from the root of the tree
    void insert(int num) {
        insert(root, num);
    }

    
    //outputs node values from the postorder traversal
    void postorder(std::ostream& os = std::cout) const {
        postorder(root, os);
        os << std::endl;
    }


    //outputs node values from the preorder traversal
    void preorder(std::ostream& os = std::cout) const {
        preorder(root, os);
        os << std::endl;
    }


    //public version of destroy to deallocate node memory from the root
    void destroy() {
        destroyTree(root);
        root = nullptr;
    }


    
    //calculates BST height from the root
    int height() const {
        return height(root);
    }



    
 //main treesort function
    void treeSort(std::vector<int> & arr){ 

        BSTree tree;
        for(int num : arr ){

            tree.insert(num);
        }
        arr.clear();
        tree.inorder(root, arr);


    }

    
};

