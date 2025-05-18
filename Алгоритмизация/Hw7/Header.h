#pragma once

class TreeNode {
public:
    int val;            // �������� ����
    TreeNode* left;     // ��������� �� ����� �������� ����
    TreeNode* right;    // ��������� �� ������ �������� ����

    // ����������� ������
    // ��������� �������� ���� � ��������� �� ����� � ������ ���� (�� ��������� nullptr, ��� ������ None)
    TreeNode(int val = 0, TreeNode* left = nullptr, TreeNode* right = nullptr)
        : val(val), left(left), right(right) {
    } // ������������� ������ ������
};

