// Implemeting the code for the Tax Ledger System with the Help of a Binary Search Tree 
// Muhammad Obaidullah (24L-0509)

// A tax Ledger system is a system that efficently manages taxpayer information using templated BinarySearch Tree 

#include<iostream>
using namespace std; 
#include<queue> 
#include<cmath> // for abs()
#include<algorithm> // for max()

// This class represents a single tax payer here 
class TaxPayer{ 
    public: 
      int taxId; 
      string name; 
      float taxamountowned; 

    TaxPayer(int id=0, string n = "", float amount = 0.0): taxId(id), name(n), taxamountowned(amount) {}

    //Comparison operators to help BST organize by taxId 
    bool operator<(const TaxPayer&other ) const {return taxId < other.taxId; }
    bool operator>(const TaxPayer&other ) const {return taxId > other.taxId; }
    bool operator==(const TaxPayer&other ) const {return taxId == other.taxId;}

    void display() const{
        cout << "Tax ID: " << taxId << endl; 
        cout << "Name:   " << name << endl; 
        cout << "Tax Amount Owed: " << taxamountowned << endl; 
    }
}; 

// A generalized BST based tree with the implementation of all the functions here 

template <class T>
class BST {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(const T& d) : data(d), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // This is the implementation of all the functions that are going to be utilized in this entire expression. 
    Node* insert(Node* node, const T& value) {
        if (!node) return new Node(value);
        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);
        return node;
    }

    Node* search(Node* node, const T& key) {
        if (!node || node->data == key)
            return node;
        if (key < node->data)
            return search(node->left, key);
        else
            return search(node->right, key);
    }

    Node* findMin(Node* node) {
        while (node && node->left)
            node = node->left;
        return node;
    }

    Node* remove(Node* node, const T& key) {
        if (!node) return nullptr;
        if (key < node->data)
            node->left = remove(node->left, key);
        else if (key > node->data)
            node->right = remove(node->right, key);
        else {
            // Node found
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* minNode = findMin(node->right);
            node->data = minNode->data;
            node->right = remove(node->right, minNode->data);
        }
        return node;
    }

    void inorder(Node* node) const {
        if (!node) return;
        inorder(node->left);
        node->data.display();
        inorder(node->right);
    }

    void preorder(Node* node) const {
        if (!node) return;
        node->data.display();
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) const {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        node->data.display();
    }

    int height(Node* node) const {
        if (!node) return 0;
        return 1 + max(height(node->left), height(node->right));
    }

    int countNodes(Node* node) const {
        if (!node) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    int countLeafNodes(Node* node) const {
        if (!node) return 0;
        if (!node->left && !node->right) return 1;
        return countLeafNodes(node->left) + countLeafNodes(node->right);
    }

    void clear(Node*& node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
        node = nullptr;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    void insert(const T& value) { root = insert(root, value); }
    void remove(const T& key) { root = remove(root, key); }

    T* search(const T& key) {
        Node* result = search(root, key);
        return result ? &(result->data) : nullptr;
    }

    void inorder() const { inorder(root); }
    void preorder() const { preorder(root); }
    void postorder() const { postorder(root); }

    void levelOrder() const {
        if (!root) return;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();
            curr->data.display();
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }

    int getHeight() const { return height(root); }
    int getTotalNodes() const { return countNodes(root); }
    int getLeafCount() const { return countLeafNodes(root); }

    bool isBalanced(Node* node) const {
        if (!node) return true;
        int lh = height(node->left);
        int rh = height(node->right);
        return abs(lh - rh) <= 1 && isBalanced(node->left) && isBalanced(node->right);
    }
    bool isBalanced() const { return isBalanced(root); }

    void clear() { clear(root); }
};


//Implementing the Ledger System that helps us to create a Tax Ledger System Wrapper. 

class TaxLedgerSystem {
private:
    BST<TaxPayer> ledger; //

public:
    void registerTaxpayer() {
        int id;
        string name;
        float amount;
        cout << "Enter Tax ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Tax Amount Owed: ";
        cin >> amount;

        TaxPayer t(id, name, amount); 
        ledger.insert(t);
        cout << " Taxpayer added successfully!\n";
    }

    void removeTaxpayer() {
        int id;
        cout << "Enter Tax ID to remove: ";
        cin >> id;
        ledger.remove(TaxPayer(id)); 
        cout << "🗑️ Taxpayer removed.\n";
    }

    void searchTaxpayer() {
        int id;
        cout << "Enter Tax ID to search: ";
        cin >> id;
        TaxPayer key(id); 
        TaxPayer* result = ledger.search(key);
        if (result)
            result->display();
        else
            cout << " Taxpayer not found.\n";
    }

    void displayAll() {
        cout << "\n--- Taxpayers (InOrder Sorted by Tax ID) ---\n";
        ledger.inorder();
    }

    void menu() {
        int choice;
        do {
            cout << "\n\n====== TAX LEDGER MENU ======\n";
            cout << "1. Register New Taxpayer\n";
            cout << "2. Remove Taxpayer\n";
            cout << "3. Search Taxpayer\n";
            cout << "4. Display InOrder\n";
            cout << "5. Display PreOrder\n";
            cout << "6. Display PostOrder\n";
            cout << "7. Display Level Order\n";
            cout << "8. Ledger Depth\n";
            cout << "9. Total Taxpayer Count\n";
            cout << "10. Count Leaf Taxpayers\n";
            cout << "11. Balance Check\n";
            cout << "0. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1: registerTaxpayer(); break;
                case 2: removeTaxpayer(); break;
                case 3: searchTaxpayer(); break;
                case 4: ledger.inorder(); break;
                case 5: ledger.preorder(); break;
                case 6: ledger.postorder(); break;
                case 7: ledger.levelOrder(); break;
                case 8: cout << "Height: " << ledger.getHeight() << endl; break;
                case 9: cout << "Total Taxpayers: " << ledger.getTotalNodes() << endl; break;
                case 10: cout << "Leaf Nodes: " << ledger.getLeafCount() << endl; break;
                case 11: cout << (ledger.isBalanced() ? "Balanced" : "Not Balanced") << endl; break;
            }
        } while (choice != 0);
    }
};


int main(){ 
    TaxLedgerSystem system; 
    system.menu(); 
    return 0; 
}

