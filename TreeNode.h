#pragma once

#include "HotelRoom.h"
struct TreeNode
{
    HotelRoom* key;
    int height;
    TreeNode* left;
    TreeNode* right;

    TreeNode(HotelRoom* k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

