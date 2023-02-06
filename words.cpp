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

// remove caracteres especiais do final da palavra
string parse_word(string word)
{
    string::iterator it = word.end();
    it--;
    while (it != word.begin() && !isalpha(*it))
    {
        it = word.erase(it);
        it--;
    }
    return word;
}

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

        string parsed_word = parse_word(palavra);

        // Verifica se a palavra tem mais de 2 letras e não possui caracteres especiais
        if (parsed_word.length() > 2 && parsed_word.find_first_of("0123456789.,;:!?*'/'-_@#()[]{}'\"") == string::npos)
        {
            Words *novo = new Words;
            novo->word = parsed_word;
            novo->next = head;
            head = novo;
        }
    }

    arquivo.close();
    return head;
}