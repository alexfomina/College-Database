#ifndef LAZYBST_H
#define LAZYBST_H
#include "TreeNode.h"
#include <iostream>
using namespace std;

template <typename T>
class LazyBST{
    public:
        LazyBST();
        virtual ~LazyBST();
        int getSize();
        void insert(T data);
        void remove(T data);
        bool contains(T data);
        void printTreeInOrder();
        void printTreePostOrder();
        void restructure();
        TreeNode<T>* getRoot();
        T getMin();
        T getMax();
        void extractValuesInOrder(TreeNode<T>* subTreeRoot, T* sortedValues, int& index);
        T* getSortedValues();
        TreeNode<T>* findElement(int id);

    private:
        TreeNode<T>* m_root;
        int m_size;
        void insertHelper(TreeNode<T>*& subTreeRoot, TreeNode<T>* newNode);
        bool containsHelper(TreeNode<T>* subTreeRoot, T data);
        void printTreeInOrderHelper(TreeNode<T>* subTreeRoot);
        void printTreePostOrderHelper(TreeNode<T>* subTreeRoot);
        T getMinHelper(TreeNode<T>* subTreeRoot);
        T getMaxHelper(TreeNode<T>* subTreeRoot);
        void findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent);
        TreeNode<T>* getSuccessor(TreeNode<T>* rightChild);
        void rebuildTree(T* values, int start, int end, TreeNode<T>*& subTreeRoot);
        int calculateImbalance(TreeNode<T>* subTreeRoot);
        TreeNode<T>* findElementHelper(TreeNode<T>* subTreeRoot, int id);
        int calculateDepth(TreeNode<T>* subTreeRoot);
};

template <typename T>
LazyBST<T>::LazyBST(){
    m_root = NULL;
    m_size = 0;
}
template <typename T>
LazyBST<T>::~LazyBST(){
    delete m_root;
    //free memory
}

template <typename T>
int LazyBST<T>::getSize(){
    return m_size;
}

template <typename T>
TreeNode<T>* LazyBST<T>::getRoot()
{
    return m_root;
}
template <typename T>
void LazyBST<T>::insert(T data){
    TreeNode<T>* newNode = new TreeNode<T>(data);
    insertHelper(m_root, newNode);
    ++m_size;
    restructure();
}

template <typename T>
void LazyBST<T>::insertHelper(TreeNode<T>*& subTreeRoot, TreeNode<T>* newNode){
    if(subTreeRoot == NULL){
        subTreeRoot = newNode; //pointer swap
    }
    else if(newNode->getData()->getID() < subTreeRoot->getData()->getID()){
        insertHelper(subTreeRoot->m_left, newNode);
    }
    else if(newNode->getData()->getID() >subTreeRoot->getData()->getID()){
        insertHelper(subTreeRoot->m_right, newNode);
    }
}

template <typename T>
bool LazyBST<T>::contains(T data){
    return containsHelper(m_root, data);
}

template <typename T>
bool LazyBST<T>::containsHelper(TreeNode<T>* subTreeRoot, T data){
    if(subTreeRoot == NULL){
        return false;
    }
    else if(data == subTreeRoot->getData()){
        return true;
    }
    else if(data < subTreeRoot->getData()){
        return containsHelper(subTreeRoot->m_left, data);
    }
    else{
        return containsHelper(subTreeRoot->m_right, data);
    }
}

template <typename T>
void LazyBST<T>::printTreeInOrder(){
    printTreeInOrderHelper(m_root);
}

template <typename T>
void LazyBST<T>::printTreeInOrderHelper(TreeNode<T>* subTreeRoot){
    if(subTreeRoot != NULL){
        printTreeInOrderHelper(subTreeRoot->m_left);
        subTreeRoot->getData()->printInfo();
        printTreeInOrderHelper(subTreeRoot->m_right);
    }
}

template <typename T>
void LazyBST<T>::printTreePostOrder(){
    printTreePostOrderHelper(m_root);
}

template <typename T>
void LazyBST<T>::printTreePostOrderHelper(TreeNode<T>* subTreeRoot){
    if(subTreeRoot != NULL){
        printTreePostOrderHelper(subTreeRoot->m_left);
        printTreePostOrderHelper(subTreeRoot->m_right);
        cout << subTreeRoot->m_data << endl;
    }
}

template <typename T>
T LazyBST<T>::getMin(){
    //check if empty
    if (getSize() == 0)
    {
        return nullptr;
    }
    else
    {
        return getMinHelper(m_root);
    }
}

template <typename T>
T LazyBST<T>::getMinHelper(TreeNode<T>* subTreeRoot){
    if(subTreeRoot->m_left == NULL){
        return subTreeRoot->m_data;
    }
    else{
        return getMinHelper(subTreeRoot->m_left);
    }
}

template <typename T>
T LazyBST<T>::getMax(){
    if (getSize() ==0)
    {
        return nullptr;
    }
    //check if empty
    else
    {
        return getMaxHelper(m_root);
    }
}

template <typename T>
T LazyBST<T>::getMaxHelper(TreeNode<T>* subTreeRoot){
    if(subTreeRoot->m_right == NULL){
        return subTreeRoot->m_data;
    }
    else{
        return getMaxHelper(subTreeRoot->m_right);
    }
}

template <typename T>
void LazyBST<T>::findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent){
    while(target != NULL && target->m_data != key){
        parent = target;
        if(key < target->m_data){
            target = target->m_left;
        }
        else{
            target = target->m_right;
        }
    }
}

template <typename T>
TreeNode<T>* LazyBST<T>::getSuccessor(TreeNode<T>* rightChild){
    while(rightChild->m_left != NULL){
        rightChild = rightChild->m_left;
    }
    return rightChild;
}

template <typename T>
void LazyBST<T>::remove(T d){
    if(getSize() == 0)
    {
        return;
    }
    else
    {
        TreeNode<T>* target = NULL;
        TreeNode<T>* parent = NULL;
        target = m_root;
        findTarget(d,target, parent);
        if(target == NULL){ //not in the tree, nothing to do
            return;
        }
        if(target->m_left == NULL && target->m_right == NULL){ //no children, it's a
    //leaf
            if(target == m_root){
                m_root = NULL;
            }
            else{ //it's not the root
                if(target == parent->m_left){
                    parent->m_left = NULL;
                }
                else{
                    parent->m_right = NULL;
                }
            }
        delete target; //free the memory
        }
        else if(target->m_left != NULL && target->m_right !=NULL){ // 2 child case
            TreeNode<T>* suc = getSuccessor(target->m_right);
            T value = suc->m_data;
            remove(value);
            target->m_data = value;
            }
        else{ // 1 child case
            TreeNode<T>* child;
            if(target->m_left != NULL){
                child = target->m_left;
            }
            else{
                child = target->m_right;
            }
            if(target == m_root){
                m_root = child;
            }
            else{
                if(target == parent->m_left){
                    parent->m_left = child;
                }
                else{
                    parent->m_right = child;
                }
            }
            delete target; //free memory
        }
    --m_size;
    }
}

template <typename T>
void LazyBST<T>::restructure()
{
    int imbalance = calculateImbalance(m_root);
    if (imbalance > 1.5)
    {
        //counting num nodes in the tree
        int numNodes = getSize();
        //creating an array to store values
        T* sortedValues = new T[numNodes];
        //extract values in sorted order
        int index = 0;
        extractValuesInOrder(m_root, sortedValues, index);
        //rebuild the tree
        rebuildTree(sortedValues, 0, numNodes - 1, m_root);
        //free memory
        delete[] sortedValues;
    }
}

template <typename T>
int LazyBST<T>::calculateImbalance(TreeNode<T>* subTreeRoot)
{
    if (subTreeRoot == NULL)
    {
        return 0;
    }
    int leftDepth = calculateDepth(subTreeRoot->m_left);
    int rightDepth = calculateDepth(subTreeRoot->m_right);
    return abs(leftDepth - rightDepth);
}

template <typename T>
int LazyBST<T>::calculateDepth(TreeNode<T>* subTreeRoot)
{
    if (subTreeRoot == NULL)
    {
        return 0;
    }
    int leftDepth = calculateDepth(subTreeRoot->m_left);
    int rightDepth = calculateDepth(subTreeRoot->m_right);
    return max(leftDepth, rightDepth) + 1;
}
template <typename T>
void LazyBST<T>::rebuildTree(T* values, int start, int end, TreeNode<T>*& subTreeRoot)
{
    //base case, if the start is > than end, subTreeRoot is NULL
    if (start > end)
    {
        subTreeRoot = NULL;
        return;
    }

    //find median index and create new root
    int medianIndex = (start + end) /2;
    subTreeRoot = new TreeNode<T>(values[medianIndex]);

    //recursivly rebuild left & right subtrees
    rebuildTree(values, start, medianIndex - 1, subTreeRoot->m_left);
    rebuildTree(values, medianIndex + 1, end, subTreeRoot->m_right);

}



template<typename T>
void  LazyBST<T>::extractValuesInOrder(TreeNode<T>* subTreeRoot, T* sortedValues, int& index)
{
    if (subTreeRoot != NULL)
    {
        extractValuesInOrder(subTreeRoot->m_left, sortedValues, index);
        sortedValues[index++] = subTreeRoot->m_data;
        extractValuesInOrder(subTreeRoot->m_right, sortedValues, index);
    }
}

template<typename T>
TreeNode<T>* LazyBST<T>::findElementHelper(TreeNode<T>* subTreeRoot, int id)
{
    if (subTreeRoot == nullptr || subTreeRoot->m_data->getID() == id)
    {
        return subTreeRoot;
    }

    if (id < subTreeRoot->m_data->getID())
    {
        return findElementHelper(subTreeRoot->m_left, id);
    }
    else{
        return findElementHelper(subTreeRoot->m_right, id);
    }
}

template <typename T>
TreeNode<T>* LazyBST<T>::findElement(int id)
{
    TreeNode<T>* result = findElementHelper(m_root, id);
    return result;
}

template <typename T>
T* LazyBST<T>::getSortedValues()
{
    int numNodes = getSize();
    T* sortedValues = new T[numNodes];
    int index = 0;
    extractValuesInOrder(m_root, sortedValues, index);
    return sortedValues;
}

#endif