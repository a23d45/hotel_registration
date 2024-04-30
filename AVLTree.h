#pragma once

#include "HotelRoom.h"
#include "TreeNode.h"

class AVLTree
{ 
private:
	TreeNode* root = nullptr;
	TreeNode* rotateRight(TreeNode* y);
	TreeNode* rotateLeft(TreeNode* x);
	static void updateHeight(TreeNode* node);
	static int height(TreeNode* node);
	static int balanceFactor(TreeNode* node);
	TreeNode* balance(TreeNode* node);
	TreeNode* insertNode(TreeNode* node, HotelRoom* value);
	TreeNode* findMin(TreeNode* node);
	TreeNode* removeMin(TreeNode* node);
	TreeNode* removeNode(TreeNode* node, HotelRoom* value);

public:
	void insert(HotelRoom* value);
	void remove(HotelRoom* value);
};

