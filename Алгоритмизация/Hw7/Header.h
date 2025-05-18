#pragma once

class TreeNode {
public:
    int val;            // Значение узла
    TreeNode* left;     // Указатель на левый дочерний узел
    TreeNode* right;    // Указатель на правый дочерний узел

    // Конструктор класса
    // Принимает значение узла и указатели на левый и правый узлы (по умолчанию nullptr, что аналог None)
    TreeNode(int val = 0, TreeNode* left = nullptr, TreeNode* right = nullptr)
        : val(val), left(left), right(right) {
    } // Инициализация членов класса
};

