#include <iostream>
#include "./Header.h"


// Функция для нахождения максимального значения в дереве
int findMaxBrightness(TreeNode* root) {
    if (root == nullptr) {
        // Возвращаем минимальное значение int, если дерево пустое
        // Это исключительный случай, так как по условию дерево не пустое
        return INT_MIN;
    }

    // Находим максимальное значение в левом поддереве
    int leftMax = findMaxBrightness(root->left);
    // Находим максимальное значение в правом поддереве
    int rightMax = findMaxBrightness(root->right);

    // Возвращаем максимальное из трех значений: текущего узла, левого и правого поддеревьев
    return std::max(root->val, std::max(leftMax, rightMax));
}

//пост - ордерный обход(левый → правый → корень), 
// чтобы сначала удалить дочерние узлы, а затем сам узел.
void deleteTree(TreeNode* root) {
    if (root == nullptr) {
        return; // Базовый случай: дерево пустое
    }

    // Рекурсивно удаляем левое поддерево
    deleteTree(root->left);
    // Рекурсивно удаляем правое поддерево
    deleteTree(root->right);
    // Удаляем текущий узел
    delete root;
}

int main1() {
    setlocale(LC_ALL, "Russian");
    // Создаем корневой узел дерева со значением 1.
    TreeNode* root = new TreeNode(1);

    // Создаем левый дочерний узел от корневого узла
    root->left = new TreeNode(3);

    // Создаем правый дочерний узел от корневого узла
    root->right = new TreeNode(5);

    root->left->left = new TreeNode(8);
    root->left->right = new TreeNode(10);

    root->right->right = new TreeNode(6);
    root->right->left = new TreeNode(2);

    root->right->right->left = new TreeNode(0);
    root->right->right->right = new TreeNode(1);

    root->left->left->left = new TreeNode(14);
    root->left->left->right = new TreeNode(15);
    root->left->right->right = new TreeNode(3);

    int maxBrightness = findMaxBrightness(root);
    std::cout << "Max brightness: " << maxBrightness << std::endl; // 15

    // Освобождаем память, чтобы избежать утечек памяти.
    deleteTree(root);
    root = nullptr; // Хорошая практика — обнулять указатель после удаления

    return 0;
}