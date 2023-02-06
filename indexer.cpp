#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "words.cpp"
#include "hash.cpp"

using namespace std;

// TODO: argumentos freq freq-word search
int main(int argc, char *argv[])
{
    int total_elements = 0;
    int size = 97;
    if (argc != 2)
    {
        cout << "Uso: " << argv[0] << " <nome_arquivo>" << endl;
        return 1;
    }

    // quebra todas as palavras do arquivo, transforma para lower case e verifica
    // se é válida (não possui acentos)
    Words *words = formatter(argv);

    if (words == NULL)
        return 1;

    cout << "size = " << size << endl;

    HashTable *hash_table = new HashTable[size];

    // insere as palavras na tabela hash
    while (words != NULL)
    {
        total_elements = insert(hash_table, words->word, size, total_elements);
        words = words->next;

        // verifica se a tabela hash precisa ser redimensionada
        if (total_elements / size >= 8)
        {
            size = size * 2;
            cout << "Resizing table " << size * 2 << endl;
            hash_table = resize(hash_table, size / 2, size);
        }
    }

    delete words;

    cout << "Palavra betray pesquisada: (esperada 775)" << search(hash_table, "betray", size) << endl;

    // print_table(hash_table, size);

    return 0;
}
