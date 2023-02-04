#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "words.cpp"
#include "hash.cpp"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Uso: " << argv[0] << " <nome_arquivo>" << endl;
        return 1;
    }

    Words *words = formatter(argv);

    if (words == NULL)
        return 1;

    // Imprime a lista de palavras
    Words *aux = words;
    while (aux != NULL)
    {
        cout << aux->word << endl;
        aux = aux->next;
    }

    int pos = hash_function("acb");

    cout << "Posição da palavra abc: " << pos << endl;

    return 0;
}
