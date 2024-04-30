#include "AVLTree.h"

TreeNode* AVLTree::rotateRight(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

TreeNode* AVLTree::rotateLeft(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

void AVLTree::updateHeight(TreeNode* node)
{
    node->height = 1 + std::max(height(node->left), height(node->right));
}

int AVLTree::height(TreeNode* node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return node->height;
}

int AVLTree::balanceFactor(TreeNode* node)
{
    if (node == nullptr) {
        return 0;
    }
    return height(node->right) - height(node->left);
}

TreeNode* AVLTree::balance(TreeNode* node) {
    updateHeight(node);

    int bf = balanceFactor(node);

    if (bf > 1) {
        if (balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }
    if (bf < -1) {
        if (balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }

    return node;
}

TreeNode* AVLTree::insertNode(TreeNode* node, HotelRoom* value)
{
    if (node == nullptr) 
    {
        return new TreeNode(value);
    }

    if (value < node->key) 
    {
        node->left = insertNode(node->left, value);
    }
    else if (value > node->key) 
    {
        node->right = insertNode(node->right, value);
    }
    else 
    {
        return node;
    }

    return balance(node);
}

TreeNode* AVLTree::findMin(TreeNode* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    return node->left ? findMin(node->left) : node;
}

TreeNode* AVLTree::removeMin(TreeNode* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    if (node->left)
    {
        return node->right;
    }
    node->left = removeMin(node->left);
    return balance(node);
}

TreeNode* AVLTree::removeNode(TreeNode* node, HotelRoom* value)
{
    if (node == nullptr)
    {
        return 0;
    }
    if (value < node->key)
    {
        node->left = removeNode(node->left, value);
    }
    else if (value > node->key)
    {
        node->right = removeNode(node->right, value);
    } 
    else
    {
        TreeNode* left_subtree = node->left;
        TreeNode* right_subtree = node->right;
        delete node;
        if (right_subtree == nullptr)
        {
            return left_subtree;
        }
        TreeNode* min = findMin(right_subtree);
        min->right = removeMin(right_subtree);
        min->left = left_subtree;
        return balance(min);
    }
    return balance(node);
}

void AVLTree::insert(HotelRoom* value)
{
    root = insertNode(root, value);
}

void AVLTree::remove(HotelRoom* value)
{
    root = removeNode(root, value);
}
