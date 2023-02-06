#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "words.cpp"
#include "hash.cpp"
#include "sort_tree.cpp"

using namespace std;

// TODO: argumentos freq freq-word search

void print_how_to_use()
{
    cout << "Parametros incorretos" << endl;
    cout << "Primeiro parametro: freq ou freq-word ou search" << endl;
    cout << "Verifique ESPECIFICACAO.md para mais detalhes" << endl;
}

// função main que recebe parametros de linha de comando
int main(int argc, char *argv[])
{
    int total_elements = 0, size = 97;
    HashTable *hash_table;
    OrderList *order_list;

    cout << "Indexador de palavras" << endl;

    string mode = argv[1];
    string searchKey = argv[2];

    cout << "Modo: " << mode << endl;

    if (argv[3] == NULL)
    {
        cout << "Arquivo inválido" << endl;
        return 1;
    }

    // quebra todas as palavras do arquivo, transforma para lower case e verifica
    // se é válida (não possui acentos)
    Words *words = formatter(argv);

    if (words == NULL)
        return 1;

    // cout << "size = " << size << endl;

    hash_table = new HashTable[size];
    order_list = new OrderList;

    // insere as palavras na tabela hash
    while (words != NULL)
    {
        InsertResult result = insert(hash_table, words->word, size, total_elements);
        total_elements = result.total_elements;

        if (mode == "--freq")
        {
            // parsed search key
            int parsedSearchKey = stoi(searchKey);

            order_list = insert_in_order_list(order_list, words->word, result.element_count, parsedSearchKey);
        }

        // verifica se a tabela hash precisa ser redimensionada
        if (total_elements / size >= 8)
        {
            size = size * 2;
            cout << "Resizing table " << size * 2 << endl;
            hash_table = resize(hash_table, size / 2, size);
        }
        words = words->next;
    }

    delete words;

    // print_table(hash_table, size);

    if (mode == "--freq-word")
    {
        cout << "Palavra: " << searchKey << endl;
        cout << "Frequencia: " << search(hash_table, searchKey, size) << " ocorrências" << endl;
        return 1;
    }

    if (mode == "--freq")
    {
        print_ordered_list(order_list);
        return 1;
    }

    return 0;
}
