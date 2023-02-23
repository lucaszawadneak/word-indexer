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

struct InsertResult
{
    int total_elements;
    int element_count;
};

struct WordToTableResult
{
    int size;
    HashTable *hash_table;
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
InsertResult insert(HashTable *hash_table, string key, int size, int n, int default_count = 1)
{
    int pos = hash_function(key, size), total_elements = n;
    HashTable *aux = &hash_table[pos];

    // cout << "pos = " << pos << endl;
    // cout << "key = " << key << endl;

    // se posição da tabela hash estiver vazia insere a palavra
    if (aux->key == "")
    {
        aux->key = key;
        aux->count = default_count;
        aux->next = NULL;
        return InsertResult{total_elements + 1, default_count};
    }

    // se houver colisão, insere na lista
    while (aux->next != NULL)
    {
        if (aux->key == key)
        {
            aux->count++;
            return InsertResult{total_elements, aux->count};
        }
        aux = aux->next;
    }

    // se a palavra já existir na lista, incrementa o contador
    if (aux->key == key)
    {
        aux->count++;
        return InsertResult{total_elements, aux->count};
    }

    // se não existir, insere no final da lista
    HashTable *novo = new HashTable;
    novo->key = key;
    novo->count = default_count;
    novo->next = NULL;
    aux->next = novo;
    return InsertResult{total_elements + 1, default_count};
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

string parse_word(string word)
{
    auto it = remove_if(word.begin(), word.end(), [](char const &c)
                        { return !std::isalnum(c); });

    word.erase(it, word.end());

    return word;
}

WordToTableResult *word_to_table(char *argv[], int file = 3)
{
    int total_elements = 0, size = 97;
    HashTable *head = new HashTable[97];
    ifstream arquivo(argv[file]);
    if (!arquivo.is_open())
    {
        cout << "Erro ao abrir arquivo" << endl;
        return NULL;
    }

    string palavra;
    while (arquivo >> palavra)
    {
        // Transforma a palavra para lower case

        transform(palavra.begin(), palavra.end(), palavra.begin(), ::tolower);

        string parsed_word = parse_word(palavra);

        // cout << "parsed_word = " << parsed_word << endl;

        // Verifica se a palavra tem mais de 2 letras e não possui caracteres especiais
        if (parsed_word.length() > 2 && parsed_word.find_first_of("0123456789.,;:!?*'/'-_@#()[]{}'\"") == string::npos)
        {
            InsertResult result = insert(head, parsed_word, size, total_elements);
            total_elements = result.total_elements;
            if (total_elements / size >= 8)
            {
                size = size * 2;
                cout << "Resizing table " << size * 2 << endl;
                head = resize(head, size / 2, size);
            }
        }
    }

    WordToTableResult *word_result = new WordToTableResult;

    word_result->size = size;
    word_result->hash_table = head;

    arquivo.close();
    return word_result;
}