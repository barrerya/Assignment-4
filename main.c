// Assignment N4: Template file!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FLUSH stdin=freopen(NULL,"r",stdin)
#define RMN(str) str[strcspn(str,"\n")]=0

#define MAX_LEN 50

typedef struct node BST_node;

struct node {
    short id;
    float gpa;
    BST_node *leftChild;
    BST_node *rightChild;
};

// You must implement all the functions below
BST_node *createBST_node(BST_node *root);   // function to create the BST node
BST_node *createBST();                      // function to create the BST
void displayBST(BST_node *root);            // function to display the BST
void insert_node(BST_node **root, BST_node *node);  // function to insert node into the BST.
void removeBST(BST_node **root);            // function to remove BST
void tree_traversal(BST_node *);             // function used in displayBST() to traverse
BST_node *searchBST(BST_node *, short);      // function to return a node with specific ID
void changeBST(BST_node **);                // function called to change ID in a node in BST
void move_node(BST_node **, short, short);   // function used inside changeBST() to delete node with specific ID and then re-insert it into BST.
int get_id(BST_node *root, short flag); //function to check if id value is valid

// You can declare and implement your own function(s) if needed below:



// Do NOT modify main() function! 
int main() {
    printf("\nCreating List of students:\n\n");

    BST_node *root = createBST();

    displayBST(root);

    if (root != NULL) {
        putchar('\n');
        //changeBST(&root); // Note: comment it out if you don't implement it!
        displayBST(root);
    }

    removeBST(&root);

    return 0;
}


// function to display the BST. No need to change it! 
void displayBST(BST_node *root) {

    printf("\n------------------\n");
    printf(" ID\t  GPA\n");
    printf("------------------\n");

    if (root == NULL) {
        printf("List of students is empty.\n");
    } else {
        tree_traversal(root);
    }
}



// Functions below are declared so template can compile!
// Check all the function prototypes above main() function!


// function to create the BST
BST_node *createBST() {

    BST_node *root = NULL, *newNode = NULL;

    root = createBST_node(NULL);

        do {
            newNode = createBST_node(root);
            if(newNode != NULL) {
                BST_node **rootPTR = &root;
                insert_node(rootPTR, newNode);
            }
        } while (newNode != NULL);


    return root;
}

BST_node *createBST_node(BST_node *root) {
    BST_node *newNode, *head = NULL;
    //tries to insert node

    newNode = NULL;
    char tmp[MAX_LEN] = {0};
    short numID;
    float numGPA = 101;
    int getIDResult;
    char numLen;
    BST_node* node = (BST_node*) malloc(sizeof(BST_node));

    //loop for node
    do {
        //loop to get id
        do {
            printf("Insert student's ID (4 digits): ");
            fgets(tmp, MAX_LEN, stdin);
            FLUSH;
            RMN(tmp);
            numLen = strlen(tmp);

            //skips code if the new id is empty
            if(numLen > 0) {
                numID = (short) strtol(tmp, 0, 10);

                //stores result from get_id to avoid searching the tree multiple times
                getIDResult = get_id(root, numID);
                if (getIDResult > 0) {
                    printf("Incorrect value! Record with id=%d already exists!\n", getIDResult);
                } else if (getIDResult == -1) {
                    printf("Incorrect value! Please try again!\n");
                }
            }else{
                printf("Incorrect value! Please try again!\n");
            }
        } while (getIDResult != -2 && numLen == 0);//breaks loop if id is valid or id is null

        //loop for GPA and assigning values to node
        while(getIDResult == -2 && (numGPA < 0 || numGPA > 100)) {
            printf("Insert student's GPA (0-100): ");
            fgets(tmp, MAX_LEN, stdin);
            FLUSH;
            RMN(tmp);
            numGPA = strtod(tmp, 0);

            if (numGPA < 0 || numGPA > 100) {
                printf("Incorrect value! Please try again!");
            } else {


                if(node == NULL){
                    printf("Cannot allocate memory for the node!");
                    exit(1);
                }
                node->id = numID;
                node->gpa = numGPA;
                node->rightChild = NULL;
                node->leftChild = NULL;
            }
        }

    } while (numLen > 0);

    //free node from memory and return null if the user input nothing into the id otherwise return the new node
    if (numLen == 0){
        free(node);
        return NULL;
    }else {
        return node;
    }
}

//checks if new id is valid
int get_id(BST_node *root, short flag) {
    if(flag >= 1000 && flag <= 9999) {
        if (root != NULL) {
            BST_node *node = searchBST(root, flag);
            if (node->id == flag) {
                return flag;
            }
        }else {
            return -2;
        }
    }else{
        return -1;
    }
}

// function to return a node with specific ID
BST_node *searchBST(BST_node *current, short id) {
    while(current !=NULL && current->id != id) {

        //go to left tree or right!
        current = (current->id > id) ?  current->leftChild : current->rightChild;
    }
    // If not found -> returns NULL!
    return current;

}

void insert_node(BST_node **root, BST_node *node) {
    BST_node *parent, *current;

    current = *root;
    parent = NULL;

    do {
        parent = current;

        //go to left of the tree
        if(node->id < parent->id) {
            current = current->leftChild;

            //insert to the left
            if(current == NULL) {
                parent->leftChild = node;
            }
        }  //go to right of the tree
        else {
            current = current->rightChild;

            //insert to the right
            if(current == NULL) {
                parent->rightChild = node;
            }
        }

    } while (current != NULL);

}


// function called to change ID in a node in BST
//TODO implement changeBST
void changeBST(BST_node **root) {

    // You must implement it!

}


// function used in displayBST() to traverse through nodes!
void tree_traversal(BST_node *root) {

    if(root != NULL) {
        tree_traversal(root->leftChild);
        printf("%d          %.2f",root->id, root->gpa);
        tree_traversal(root->rightChild);
    }
}


// function to remove BST
void removeBST(BST_node **root) {
    if (*root != NULL) {
        removeBST(&(*root)->leftChild);
        removeBST(&(*root)->rightChild);
        free(*root);
    }

}

