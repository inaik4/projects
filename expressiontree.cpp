#include "ExpressionTree.h"
#include <iostream>
#include <ctype.h>

using namespace std;

template<typename DataType>
ExprTree<DataType>::ExprTreeNode::ExprTreeNode(char elem, ExprTreeNode *leftPtr,
                                               ExprTreeNode *rightPtr)
{
    dataItem = elem;
    left = leftPtr;
    right = rightPtr;
}

 //Default constructor to make empty expression tree
template<typename DataType>
ExprTree<DataType>::ExprTree()
{
    root = NULL;
}

//Copy constructor to initialize ExprTree
template<typename DataType>
ExprTree<DataType>::ExprTree(const ExprTree& source)
{
    *this = source;
}

//Set ExprTree equal to the other one
template<typename DataType>
ExprTree<DataType>& ExprTree<DataType>::operator=(const ExprTree<DataType>&
                                                  source)
{
    if(this == &source)
        return *this;
    
    copyHelper(root);
    return *this;
}

//Recursively call left and right using copyHelper
template<typename DataType>
void ExprTree<DataType>::copyHelper(ExprTreeNode *&p)
{
    if(p != NULL)
    {
        ExprTreeNode *left = NULL;
        ExprTreeNode *right = NULL;
        
        //recursive calls
        copyHelper(left);
        copyHelper(right);
        
        p = new ExprTreeNode(p->dataItem, left, right);
    }
}

//Destructor to deallocate memory
template<typename DataType>
ExprTree<DataType>::~ExprTree()
{
    clear();
}

template<typename DataType>
void ExprTree<DataType>::build()
{
    buildHelper(root);
}

//Helper function for build()
template<typename DataType>
void ExprTree<DataType>::buildHelper(ExprTreeNode *&p)
{
    char c;
    cin >> c;
    
    p = new ExprTreeNode(c, NULL, NULL);
    
    if(c == '+' || c == '-' || c == '*' || c == '/')
    {
        //recursive calls
        buildHelper(p->left);
        buildHelper(p->right);
    }
}

//Infix form
template<typename DataType>
void ExprTree<DataType>::expression() const
{
    exprHelper(root);
}

template<typename DataType>
void ExprTree<DataType>::exprHelper(ExprTreeNode *p) const
{

    if(isdigit(p->dataItem))
    {
        cout << p->dataItem;
        return;
    }
    cout << '(';
    
    //recursive call
    exprHelper(p->left);
    cout << p->dataItem;
    //recursive call
    exprHelper(p->right);
    cout << ')';
}

template<typename DataType>
DataType ExprTree<DataType>::evaluate() const throw (logic_error)
{
    if(root == NULL)
        throw("The tree is empty!");
    
    return evalHelper(root);
}

//Helper function for evaluate()
template<typename DataType>
DataType ExprTree<DataType>::evalHelper(ExprTreeNode *p) const
{

    switch(p->dataItem)
    {
        case '+':
            return (evalHelper(p->left) + evalHelper(p->right));
            break;
        case '-':
            return (evalHelper(p->left) - evalHelper(p->right));
            break;
        case '*':
            return (evalHelper(p->left) * evalHelper(p->right));
            break;
        case '/':
            return (evalHelper(p->left) / evalHelper(p->right));
            break;
        default:
            return (p->dataItem - '0');
            break;
    }
}

//Clear all data items in the tree
template<typename DataType>
void ExprTree<DataType>::clear()
{
    clearHelper(root);
}

//Helper for clear()
template <typename DataType>
void ExprTree<DataType>::clearHelper(ExprTreeNode *p)
{
    if(p != NULL)
    {
        //recursive calls
        clearHelper(p->left);
        clearHelper(p->right);
        delete p;
        
        p = NULL;
    }
}

template<typename DataType>
void ExprTree<DataType>::commute()
{
    commuteHelper(root);
}

//Helper for commute()
template<typename DataType>
void ExprTree<DataType>::commuteHelper(ExprTreeNode *p)
{
    if(p == NULL)
        return;
    
    if(!isdigit(p->dataItem))
    {
        ExprTreeNode* temp = p->left;
        p->left = p->right;
        p->right = temp;
    }
    
    //recursive calls
    commuteHelper(p->left);
    commuteHelper(p->right);
}

template<typename DataType>
bool ExprTree<DataType>::isEquivalent(const ExprTree& source) const
{
    return isEquivalentHelper(root, source.root);
}

//Helper for isEquivalent()
template <typename DataType>
bool ExprTree<DataType>::isEquivalentHelper(const ExprTreeNode* x,
                                            const ExprTreeNode* y) const
{
    //Set condition for equivalence
    if(x == NULL && y == NULL)
        return true;
    //If nodes are not empty...
    else if (x != NULL && y != NULL)
    {
        if(x->dataItem == y->dataItem)
        {
            if(isEquivalentHelper(x->left, y->left) &&
               isEquivalentHelper(x->right, y->right))
                return true;
            
            //After first check, check if swapped elements are equivalent
            else if (isEquivalentHelper(x->left, y->right) &&
                     isEquivalentHelper(x->right, y->left))
            {
                if(x->dataItem == '+' || x->dataItem == '*')
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
    }
    return false;
}

template <typename DataType>
bool ExprTree<DataType>::isEmpty() const
{
    return false;
}

template<typename DataType>
void ExprTree<DataType>::showStructure() const
{
    // Outputs an expression tree. The tree is output rotated counter-
    // clockwise 90 degrees from its conventional orientation using a
    // "reverse" inorder traversal. This operation is intended for testing
    // and debugging purposes only.
    
    // No isEmpty function in this class. Add a private one if you wish.
    if ( root == NULL )
        cout << "Empty tree" << endl;
    else
    {
        cout << endl;
        showHelper(root,1);
        cout << endl;
    }
}

template<typename DataType>
void ExprTree<DataType>::showHelper(ExprTreeNode *p, int level) const
{
    
    // Recursive helper for the showStructure() function. Outputs the
    // subtree whose root node is pointed to by p. Parameter level is the
    // level of this node within the expression tree.
    
    int j;   // Loop counter
    
    if ( p != 0 )
    {
        // Output right subtree
        showHelper(p->right, level + 1);
        // Tab over to level
        for (j = 0 ; j < level ; j++)
            cout << "\t";
        
        // Output dataItem
        cout << " " << p->dataItem;
        
        // Output "connector"
        if ( ( p->left != 0 ) && ( p->right != 0 ) )
            cout << "<";
        else if ( p->right != 0 )
            cout << "/";
        else if ( p->left != 0 )
            cout << "\\";
        
        cout << endl;
        
        // Output left subtree

        showHelper(p->left,level+1);
    }
}


