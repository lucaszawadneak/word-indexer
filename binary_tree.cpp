#include <iostream>

using namespace std;

struct BinaryNode
{
    string word;
    int count;
    BinaryNode *left = NULL;
    BinaryNode *right = NULL;
};

void insert_in_bin_tree(BinaryNode **root, HashTable *item)
{
    if (!(*root))
    {
        *root = new BinaryNode{
            item->key,
            item->count,
        };
        return;
    }

    if (item->count <= (*root)->count)
    {
        insert_in_bin_tree(&(*root)->left, item);
    }

    if (item->count > (*root)->count)
    {
        insert_in_bin_tree(&(*root)->right, item);
    }
}

void assign_to_array(BinaryNode *root, HashTable *array, int *index)
{
    if (root == NULL)
    {
        return;
    }

    assign_to_array(root->left, array, index);

    array[*index] = HashTable{
        root->word,
        root->count,
    };

    *index = *index + 1;

    assign_to_array(root->right, array, index);
}

// função que printa os
int print_n_max(BinaryNode *root, int n)
{
    if (root == NULL)
    {
        return 0;
    }

    int count = print_n_max(root->right, n);

    if (count < n)
    {
        cout << root->word << " " << root->count << endl;
        count++;
    }

    count += print_n_max(root->left, n - count);

    return count;
}