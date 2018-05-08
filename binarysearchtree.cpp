
#include "BSTree.h"
#include "show9.cpp"

using namespace std;

//Constructor
template <typename DataType, class KeyType>
BSTree<DataType, KeyType>::BSTreeNode::BSTreeNode(const DataType &nodeDataItem, BSTreeNode *leftPtr, BSTreeNode *rightPtr)
{
    dataItem = nodeDataItem;
    left = leftPtr;
    right = rightPtr;
}

//Default
template <typename DataType, class KeyType>
BSTree<DataType, KeyType>::BSTree()
{
    root = NULL;
    
}


template <typename DataType, class KeyType>
BSTree<DataType, KeyType>::BSTree(const BSTree<DataType,KeyType>& other)
{
    *this = other;
}

template <typename DataType, class KeyType>
BSTree<DataType, KeyType>& BSTree<DataType, KeyType>::operator= (const BSTree<DataType,KeyType>& other)
{
    if (this != other)
    {
        clear();
        root = showHelper(root);
    }
    return *this;
}

// Destructor
template <typename DataType, class KeyType>
BSTree<DataType, KeyType>::~BSTree()
{
    clear();
    root = NULL;
}

template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::insert(const DataType& newDataItem)
{
    insertHelper(newDataItem, root);
}

template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::retrieve(const KeyType& searchKey, DataType& searchDataItem) const
{
    return retrieveHelper(searchKey, searchDataItem, root);
}

template <typename DataType, class KeyType>
bool BSTree<DataType, KeyType>::remove(const KeyType& deleteKey)
{
    return removeHelper(deleteKey, root);
}


template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::writeKeys() const
{
    if (isEmpty())
    {
        cout << "Empty tree!" << endl;
    }
    else
    {
        writeKeysHelper(root);
    }
}

template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::writeKeysHelper(BSTreeNode *node) const
{
    if (node != NULL)
    {
        writeKeysHelper(node->left);
        cout << node->dataItem.getKey() << endl;
        writeKeysHelper(node->right);
    }
}
// void writeLessThan ( const KeyType& searchKey ) const;
template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::writeLessThan(const KeyType& searchKey) const
{
    if (isEmpty())
    {
        cout << "The tree is empty" << endl;
    }
    else
    {
        writeLTHelper(root, searchKey);
    }
}
// void writeLTHelper   ( BSTreeNode *p, const KeyType& searchKey ) const;
template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::writeLTHelper(const KeyType& searchKey, BSTreeNode* p) const
{
    if (p == NULL)
    {
        return;
    }
    else  {if (p->dataItem.getKey() >= searchKey)
    {
        writeLTHelper(p->left, searchKey);
    }
    else
    {
        p = p->left;
        cout << p->dataItem.getKey() << endl;
        writeLTHelper(p->right, searchKey);
    }
    }
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::clear()
{
    clearHelper(root);
}

template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::isEmpty() const
{
    return (root == NULL);
}

template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>::getCount () const
{
    return(getCountHelper(root));
}

template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>::getHeight() const
{
    return(getHeightHelper(root));
}

// BSTreeNode *&p, const BSTreeNode *otherPtr );
template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::copyHelper(BSTreeNode*& p, BSTreeNode* otherPtr)
{
    if( p != NULL )
    {
        otherPtr = new BSTreeNode( p->dataItem, NULL, NULL );
        
        copyHelper( otherPtr->left, p->left );
        copyHelper( otherPtr->right, p->right );
    }
}


// void clearHelper ( BSTreeNode *p );
template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::clearHelper(BSTreeNode*& p)
{
    if( p != NULL )
    {
        clearHelper( p->left );
        clearHelper( p->right );
        
        delete p;
        p = NULL;
    }
}


template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::insertHelper(const DataType& newDataItem, BSTreeNode* &p)
{
    if( p == NULL )
    {
        p = new BSTreeNode( newDataItem, NULL, NULL );
    }
    else if( newDataItem.getKey() < p->dataItem.getKey() )
    {
        insertHelper(newDataItem,  p->left);
    }
    else if( newDataItem.getKey() > p->dataItem.getKey() )
    {
        insertHelper(newDataItem,  p->right );
    }
    else
    {
        p->dataItem = newDataItem;
    }
}


template < typename DataType, typename KeyType >
bool BSTree<DataType, KeyType>::retrieveHelper(const KeyType& searchKey, DataType& searchDataItem, BSTreeNode* p) const
{
    if( p == NULL )
    {
        return false;
    }
    else if( searchKey < p->dataItem.getKey() )
    {
        return( retrieveHelper(searchKey, searchDataItem,  p->left ));
    }
    else if( searchKey > p->dataItem.getKey() )
    {
        return( retrieveHelper(searchKey, searchDataItem,  p->right ));
    }
    else
    {
        searchDataItem = p->dataItem;
        return true;
    }
}

//bool removeHelper    ( BSTreeNode *&p, const KeyType& deleteKey );
template < typename DataType, typename KeyType >
bool BSTree<DataType, KeyType>::removeHelper(const KeyType& deleteKey, BSTreeNode*& p)
{
    BSTreeNode* temp;
    if( p == NULL )
    {
        return false;
    }
    else if( deleteKey < p->dataItem.getKey() )
    {
        return( removeHelper(deleteKey,p->left) );
    }
    else if( deleteKey > p->dataItem.getKey() )
    {
        return( removeHelper(deleteKey, p->right) );
    }
    else
    {
        if( p->left == NULL && p->right == NULL )
        {
            delete p;
            p = NULL;
            return true;
        }
        else if( p->left != NULL && p->right == NULL )
        {
            temp = p;
            p = p->left;
            delete temp;
            return true;
        }
        else if( p->left == NULL && p->right != NULL )
        {
            temp = p;
            p = p->right;
            delete temp;
            return true;
        }
        else
        {
            temp = p->left;
            while( temp->right != NULL )
            {
                temp = temp->right;
            }
            
            p->dataItem = temp->dataItem;
            
            
        }
        return removeHelper(temp->dataItem.getKey(), p->left);
    }
}


template < typename DataType, typename KeyType >
int BSTree<DataType, KeyType>::getCountHelper(BSTreeNode* p) const
{
    if( p == NULL )
    {
        return 0;
    }
    else
    {
        return( 1 + getCountHelper( p->left ) + getCountHelper( p->right ) );
    }
}

template < typename DataType, typename KeyType >
int BSTree<DataType, KeyType>::getHeightHelper(BSTreeNode* p, int currentLevel) const
{
    static int maxLevel = 0;
    //If the node is null, then check the current level with the max level
    if(p == NULL)
    {
        if(currentLevel > maxLevel)
            maxLevel = currentLevel;
    }
    //Continue left and right
    else
    {
        getHeightHelper(p->left, currentLevel + 1);
        getHeightHelper(p->right, currentLevel + 1);
    }
    return maxLevel;
}
