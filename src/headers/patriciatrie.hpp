/**
 * \file patriciatrie.hpp
 * \brief Structures pour le Patricia Trie
 * \author Florian Thommains, Victor Degliame
 * \date 31/07/2013
 */

#ifndef PATRICIA_TRIE_HPP
# define PATRICIA_TRIE_HPP

# define CHUNK (16384)
# define BLOCK_SIZE (16)

# include "includes.hpp"

/**
 * \struct Node
 * \brief Noeud d'un Patricia Trie   
 */
struct Node
{
typedef std::map<char, Node*> nodeMap;

    nodeMap sons;
    size_t index;
    size_t freq;
    unsigned short length;
    char c;
    bool isWord;

    void print(void);
    Node(size_t index, size_t freq, unsigned short length, char c);
    Node(void);
    ~Node(void);
};

/**
 * \class ParticiaTrie
 * \brief Class qui va créer 
 */
class PatriciaTrie
{
private:
    std::string filename;

private:
    void drawTree(Node * n);

 
public:
    /*
     * \brief Constructeur qui va sauvgarder le dico
     * \param f: emplacement du dico
     */
    PatriciaTrie(std::string f);
    /**
     * \brief Constructeur
     */
    PatriciaTrie(void);
    /*
     * \brief Destructeur
     *
     */
    ~PatriciaTrie(void);

private:
    /*
     * \brief Ajoute un élément dans l'arbre
     */
    int add(std::string word, int freq, Node* n);
    /*
     * \brief Utilisé dans la fonction add, elle permet l'eclatement d'un noeud.
     */ 
    Node* burstDown(size_t index, size_t i, size_t freq, Node* n);
    /*
     * \brief Permet de cerhcer dans l'arbre.
     */
    void browse(std::string word, Node* n);

public:
    /*
     *\brief Permet de créer le dico serializé.
     */
    void compile(std::string filename);
    void print(void);
    Node* root = nullptr;
    std::vector<char> suffixes;

private:
    std::vector<std::pair<std::vector<int>, std::pair<unsigned int, Node*>>> new_trie;
    void deepthFirstSearch(Node *n, int father);
    void printVector();
};

#endif
