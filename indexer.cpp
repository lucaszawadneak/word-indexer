#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <vector>

#include "hash.cpp"

using namespace std;

// TODO: freq-word
// TODO: search

void print_how_to_use()
{
    cout << "Parametros incorretos" << endl;
    cout << "Primeiro parametro: freq ou freq-word ou search" << endl;
    cout << "Verifique ESPECIFICACAO.md para mais detalhes" << endl;
}

struct HashValue
{
    string word;
    int count;
};

void find_n_max(HashTable *hash_table, int size, int n)
{
    cout << "Inserindo valores no vetor...\n";
    vector<HashValue> values;
    HashTable *aux;
    for (int i = 0; i < size; i++)
    {
        aux = &hash_table[i];
        while (aux != NULL)
        {
            // push back
            HashValue value;
            value.word = aux->key;
            value.count = aux->count;
            values.push_back(value);

            aux = aux->next;
        }
    }

    cout << "size = " << values.size() << endl;
    // merge sort values
    for (int i = 0; i < values.size(); i++)
    {
        for (int j = i + 1; j < values.size(); j++)
        {
            if (values[i].count < values[j].count)
            {
                HashValue aux = values[i];
                values[i] = values[j];
                values[j] = aux;
            }
        }
    }

    cout << "Os " << n << " maiores valores são: ";
    for (int i = 0; i < n; i++)
    {
        cout << values[i].word << " (" << values[i].count << ") \n";
    }
}

// função main que recebe parametros de linha de comando
int main(int argc, char *argv[])
{
    HashTable *hash_table;

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
    cout << "Formatando arquivo...\n";

    WordToTableResult *result = word_to_table(argv);

    hash_table = result->hash_table;
    int size = result->size;

    // print_table(hash_table, size);

    if (mode == "--freq-word")
    {
        cout << "Palavra: " << searchKey << endl;
        cout << "Frequencia: " << search(hash_table, searchKey, size) << " ocorrências" << endl;
        return 1;
    }
    if (mode == "--freq")
    {
        cout << "Buscando as " << searchKey << " palavras mais frequentes" << endl;
        find_n_max(hash_table, size, stoi(searchKey));
        return 1;
    }

    return 0;
}
