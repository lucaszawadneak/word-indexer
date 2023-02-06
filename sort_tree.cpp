#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

struct OrderList
{
    string key;
    int count;
    OrderList *next;
};

OrderList *insert_in_order_list(OrderList *list, string key, int count, int list_size)
{
    OrderList *aux = list;
    OrderList *new_node = new OrderList;
    new_node->key = key;
    new_node->count = count;
    new_node->next = NULL;

    if (aux->key == "")
    {
        aux->key = key;
        aux->count = 1;
        aux->next = NULL;
        return aux;
    }

    if (aux->count >= count)
    {
        new_node->next = aux;
        list = new_node;
        return list;
    }
    if (list_size > 0)
    {
        insert_in_order_list(aux->next, key, count, list_size - 1);
    }

    return list;
}

// printa a lista encadeada
void print_ordered_list(OrderList *list)
{
    OrderList *aux = list;
    while (aux != NULL)
    {
        cout << aux->key << " | Ocorrências: " << aux->count << endl;
        aux = aux->next;
    }
}