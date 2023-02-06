#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

struct HashTable
{
    string key;
    int count;
    HashTable *next;
};

// função hash que recebe palavra e devolve a posição na tabela hash
int hash_function(string word, int size)
{
    char c;
    int p = 31;
    int hash = 0, p_pow = 1;

    for (int i = 0; i < word.length(); i++)
    {
        c = word[i];
        hash = (hash + (c - 'a' + 1) * p_pow) % size;
        p_pow = (p_pow * p) % size;
    }

    return hash;
}

// inserir na tabela hash e retorna o número de elementos únicos
int insert(HashTable *hash_table, string key, int size, int n, int default_count = 1)
{
    int pos = hash_function(key, size);
    HashTable *aux = &hash_table[pos];
    int total_elements = n;

    // se posição da tabela hash estiver vazia insere a palavra
    if (aux->key == "")
    {
        aux->key = key;
        aux->count = default_count;
        aux->next = NULL;
        // cout << "aux was empty" << aux->key << endl;
        // cout << "pos = " << pos << endl;
        return total_elements + 1;
    }

    // se houver colisão, insere na lista
    while (aux->next != NULL)
    {
        if (aux->key == key)
        {
            aux->count++;
            return total_elements;
        }
        aux = aux->next;
    }

    // se a palavra já existir na lista, incrementa o contador
    if (aux->key == key)
    {
        aux->count++;
        return total_elements;
    }

    // se não existir, insere no final da lista
    HashTable *novo = new HashTable;
    novo->key = key;
    novo->count = default_count;
    novo->next = NULL;
    aux->next = novo;
    return total_elements + 1;
}

// pesquisa na bela hash e na lista
int search(HashTable *hash_table, string key, int size)
{
    int pos = hash_function(key, size);
    // cout << "pos = " << pos << endl;
    HashTable *aux = &hash_table[pos];

    if (aux->key == "")
        return 0;
    else
    {
        while (aux->next != NULL)
        {
            if (aux->key == key)
                return aux->count;
            aux = aux->next;
        }
        if (aux->key == key)
            return aux->count;
    }
    return 0;
}

// remimensionar tabela hash, realocando elementos anteriores
// recebe tabela hash, tamanho antigo e novo
HashTable *resize(HashTable *hash_table, int old_size, int new_size)
{
    HashTable *new_hash_table = new HashTable[new_size];
    HashTable *aux;
    for (int i = 0; i < old_size; i++)
    {
        aux = &hash_table[i];
        if (aux->key != "")
        {
            insert(new_hash_table, aux->key, new_size, 0, aux->count);
            while (aux->next != NULL)
            {
                aux = aux->next;
                insert(new_hash_table, aux->key, new_size, 0, aux->count);
            }
        }
    }

    // libera memória
    delete[] hash_table;

    return new_hash_table;
}

// printa tabela hash
void print_table(HashTable *hash_table, int size)
{
    HashTable *aux;
    for (int i = 0; i < size; i++)
    {
        aux = &hash_table[i];
        if (aux->key != "")
        {
            cout << i << ": " << aux->key << " " << aux->count << endl;
            while (aux->next != NULL)
            {
                aux = aux->next;
                cout << i << ": " << aux->key << " " << aux->count << endl;
            }
        }
    }
}
