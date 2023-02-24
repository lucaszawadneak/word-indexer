#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <ctgmath>
#include <sstream>

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

        while (aux->next)
        {

            if (aux->count == 0)
            {
                aux = aux->next;
                continue;
            }

            insert_in_bin_tree(&tree, aux);

            aux = aux->next;
        }
    }

    cout << "Tamanho do vetor: " << size << endl;

    cout << "Os " << n << " maiores valores são: \n";

    print_n_max(tree, n);
}

void insert_term_frequency(TermFrequency *&head, string filename, float frequency)
{
    TermFrequency *new_node = new TermFrequency;
    new_node->filename = filename;
    new_node->frequency = frequency;
    new_node->next = NULL;

    if (head == NULL)
    {
        head = new_node;
    }
    else
    {
        TermFrequency *curr = head;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = new_node;
    }
}

void calc_and_insert_TF(TF_IDF *&head, TermFrequency *item, float inverseDocumentFrequency)
{
    float termFrequency = item->frequency;
    float tf_idf = termFrequency * inverseDocumentFrequency;

    TF_IDF *new_node = new TF_IDF;
    new_node->filename = item->filename;
    new_node->tf_idf = tf_idf;
    new_node->next = NULL;

    if (head == NULL)
    {
        head = new_node;
    }
    else
    {
        TF_IDF *curr = head;
        if (head->filename == item->filename)
        {
            head->tf_idf = (head->tf_idf + tf_idf) / 2;
            return;
        }
        while (curr->next != NULL)
        {
            if (curr->filename == item->filename)
            {
                curr->tf_idf = (curr->tf_idf + tf_idf) / 2;
                return;
            }
            curr = curr->next;
        }
        if (curr->filename == item->filename)
        {
            curr->tf_idf = (curr->tf_idf + tf_idf) / 2;
            return;
        }
        curr->next = new_node;
    }
}

void sort_tf_idf_list(TF_IDF *&head)
{
    if (!head || !head->next)
    {
        return; // lista vazia ou com apenas um elemento, nada a fazer
    }

    // dividir a lista em duas metades, usando slow/fast pointer
    TF_IDF *slow = head, *fast = head->next;
    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    TF_IDF *mid = slow->next;
    slow->next = nullptr;

    // recursivamente ordenar as duas metades
    sort_tf_idf_list(head);
    sort_tf_idf_list(mid);

    // intercalar as duas listas ordenadas
    TF_IDF *merged = nullptr, *tail = nullptr;
    while (head && mid)
    {
        if (head->tf_idf > mid->tf_idf)
        {
            if (!merged)
            {
                merged = tail = head;
            }
            else
            {
                tail->next = head;
                tail = tail->next;
            }
            head = head->next;
        }
        else
        {
            if (!merged)
            {
                merged = tail = mid;
            }
            else
            {
                tail->next = mid;
                tail = tail->next;
            }
            mid = mid->next;
        }
    }
    // adicionar os restantes, se houver
    if (head)
    {
        tail->next = head;
    }
    else if (mid)
    {
        tail->next = mid;
    }
    // atualizar o ponteiro da cabeça da lista
    head = merged;
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

        stringstream ss(searchKey); // cria um stringstream a partir da string de entrada
        string palavra;
        vector<std::string> palavras;
        TF_IDF *tf_idf_vector = NULL;

        while (ss >> palavra)
        { // lê palavras separadas por espaço
            cout << "Palavra: " << palavra << endl;
            TermFrequency *frequency_vector = NULL;
            int is_in_documents = 0;

            for (int i = 3; i < argc; i++)
            {

                cout << argv[i] << endl;

                HashTable *fileHashTable;

                WordToTableResult *wordToTableResult = word_to_table(argv, i);

                fileHashTable = wordToTableResult->hash_table;
                int fileSize = wordToTableResult->size;

                int occurrences = search(fileHashTable, palavra, fileSize);

                if (occurrences > 0)
                {
                    is_in_documents++;
                }

                float termFrequency = occurrences / (float)fileSize;

                insert_term_frequency(frequency_vector, argv[i], termFrequency);

                free(wordToTableResult);
            }

            // print term frequency vector
            TermFrequency *printAux = frequency_vector;

            float inverseDocumentFrequency = log(documents / (float)is_in_documents) || 0;

            while (printAux)
            {
                calc_and_insert_TF(tf_idf_vector, printAux, inverseDocumentFrequency);

                printAux = printAux->next;
            }
        }
        TF_IDF *tf_print_aux = tf_idf_vector;

        sort_tf_idf_list(tf_print_aux);

        cout << "------------------------" << endl;
        cout << "Ordem TF-IDF:" << endl;

        while (tf_print_aux)
        {
            cout << "Arquivo: " << tf_print_aux->filename << endl;
            cout << "TF-IDF: " << tf_print_aux->tf_idf << endl;

            tf_print_aux = tf_print_aux->next;
        }

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
