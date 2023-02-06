#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

// struct lista encadeada que armazena as palavras

struct Words
{
    string word;
    Words *next;
};

Words *formatter(char *argv[])
{

    ifstream arquivo(argv[3]);
    if (!arquivo.is_open())
    {
        cout << "Erro ao abrir arquivo" << endl;
        return NULL;
    }
    Words *head = NULL;

    string palavra;
    while (arquivo >> palavra)
    {
        // Transforma a palavra para lower case
        transform(palavra.begin(), palavra.end(), palavra.begin(), ::tolower);

        // Verifica se a palavra tem mais de 2 letras
        if (palavra.length() > 2 && palavra.find_first_of("0123456789.,;:!?*'/'-()[]{}'\"") == string::npos)
        {
            Words *novo = new Words;
            novo->word = palavra;
            novo->next = head;
            head = novo;
        }
    }

    arquivo.close();
    return head;
}