#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <ctgmath>

#include "hash.cpp"
#include "binary_tree.cpp"

using namespace std;

// TODO: freq-word
// TODO: search

void print_how_to_use()
{
    cout << "Parametros incorretos" << endl;
    cout << "Primeiro parametro: freq ou freq-word ou search" << endl;
    cout << "Verifique ESPECIFICACAO.md para mais detalhes" << endl;
}

void find_n_max(HashTable *hash_table, int size, int n)
{
    cout << "Inserindo valores no vetor...\n";

    HashTable *aux;
    BinaryNode *tree = NULL;
    for (int i = 0; i < size; i++)
    {
        aux = &hash_table[i];

        while (aux != NULL)
        {

            insert_in_bin_tree(&tree, aux);

            aux = aux->next;
        }
    }

    cout << "Tamanho do vetor: " << size << endl;

    cout << "Os " << n << " maiores valores são: \n";

    print_n_max(tree, n);
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

    if (mode == "--search")
    {
        int documents = 2;

        int occurrences = search(hash_table, searchKey, size);
        int is_in_documents = occurrences != 0 ? 1 : 0;
        float termFrequency = occurrences / (float)size;
        float inverseDocumentFrequency = log10(documents / is_in_documents);

        float tf_idf = termFrequency * inverseDocumentFrequency;

        cout << "Palavra: " << searchKey << endl;
        cout << "Documentos: " << documents << " documentos" << endl;
        cout << "Em quantos documentos a palavra aparece: " << is_in_documents << " documentos" << endl;
        cout << "Ocorrencias: " << occurrences << " ocorrências" << endl;
        cout << "Frequencia: " << termFrequency << " ocorrências" << endl;
        cout << "Frequencia inversa: " << inverseDocumentFrequency << " ocorrências" << endl;
        cout << "TF-IDF: " << tf_idf << endl;
    }

    return 0;
}
