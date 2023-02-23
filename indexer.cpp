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

struct TermFrequency
{
    string filename;
    float frequency;
    TermFrequency *next;
};

struct TF_IDF
{
    string filename;
    float tf_idf;
    TF_IDF *next;
};

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

void insert_in_vetor(TermFrequency *vector, TermFrequency *term)
{
    if (!vector)
    {
        vector = term;
    }
    else
    {
        TermFrequency *aux = vector;
        while (!aux->next)
        {
            aux = aux->next;
        }
        aux->next = term;
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

    if (mode == "--search")
    {
        // TODO: pegar número de documentos e criar hashes
        // TODO: calcular tf-idf
        int documents = argc - 3;

        cout << "Documentos a serem analisados: " << documents << endl;
        cout << "Termo a ser buscado: " << searchKey << endl;

        TermFrequency *frequency_vector = NULL;
        int is_in_documents = 0;

        for (int i = 3; i < argc; i++)
        {
            cout << argv[i] << endl;

            HashTable *fileHashTable;

            WordToTableResult *wordToTableResult = word_to_table(argv, i);

            fileHashTable = wordToTableResult->hash_table;
            int fileSize = wordToTableResult->size;

            int occurrences = search(fileHashTable, searchKey, fileSize);

            if (occurrences > 0)
            {
                is_in_documents++;
            }
            else
            {
                TermFrequency *new_frequency = new TermFrequency;
                new_frequency->filename = argv[i];
                new_frequency->frequency = 0;

                if (!frequency_vector)
                {
                    frequency_vector = new_frequency;
                }
                else
                {
                    TermFrequency *aux = frequency_vector;
                    while (!aux->next)
                    {
                        aux = aux->next;
                    }
                    aux->next = new_frequency;
                }
                continue;
            }

            float termFrequency = occurrences / (float)fileSize;

            TermFrequency *new_frequency = new TermFrequency;
            new_frequency->filename = argv[i];
            new_frequency->frequency = termFrequency;

            if (!frequency_vector)
            {
                frequency_vector = new_frequency;
            }
            else
            {
                TermFrequency *aux = frequency_vector;
                while (!aux->next)
                {
                    aux = aux->next;
                }
                aux->next = new_frequency;
            }

            // float inverseDocumentFrequency = log10(documents / is_in_documents);

            // float tf_idf = termFrequency * inverseDocumentFrequency;

            // cout << "Palavra: " << searchKey << endl;
            // cout << "Documentos: " << documents << " documentos" << endl;
            // cout << "Em quantos documentos a palavra aparece: " << is_in_documents << " documentos" << endl;
            // cout << "Ocorrencias: " << occurrences << " ocorrências" << endl;
            // cout << "Frequencia: " << termFrequency << " ocorrências" << endl;
            // cout << "Frequencia inversa: " << inverseDocumentFrequency << " ocorrências" << endl;
            // cout << "TF-IDF: " << tf_idf << endl;

            // TF_IDF *new_tf_idf = new TF_IDF;
            // new_tf_idf->filename = argv[i];
            // new_tf_idf->tf_idf = tf_idf;
        }

        // print term frequency vector
        TermFrequency *printAux = frequency_vector;

        TF_IDF *tf_idf_vector = NULL;

        while (printAux)
        {

            cout << "Arquivo: " << printAux->filename << endl;
            cout << "Frequencia: " << printAux->frequency << endl;

            // float inverseDocumentFrequency = log10(documents / is_in_documents);

            // float tf_idf = printAux->frequency * inverseDocumentFrequency;

            // TF_IDF *new_tf_idf = new TF_IDF;
            // new_tf_idf->filename = printAux->filename;
            // new_tf_idf->tf_idf = tf_idf;

            // if (!tf_idf_vector)
            // {
            //     tf_idf_vector = new_tf_idf;
            // }
            // else
            // {
            //     TF_IDF *aux = tf_idf_vector;
            //     while (!aux->next)
            //     {
            //         aux = aux->next;
            //     }
            //     aux->next = new_tf_idf;
            // }

            printAux = printAux->next;
        }

        cout << "teste" << endl;

        return 0;
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
