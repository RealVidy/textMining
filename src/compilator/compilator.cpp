#include "../headers/patriciatrie.hpp"

PatriciaTrie::PatriciaTrie(std::string f) : filename (f)
{
    root = new Node();
}

PatriciaTrie::PatriciaTrie(void) : filename ("")
{
    root = nullptr;
}

PatriciaTrie::~PatriciaTrie()
{
    delete(root);
}

Node::Node(size_t index, size_t freq, unsigned short length, char c): isWord(false)
{
    this->index = index;
    this->freq = freq;
    this->length = length;
    this->c = c;
}

Node::Node(void): index(0), freq(0), length(0), c(0), isWord(false)
{
}

Node::~Node(void)
{
    for (std::pair<char, Node*> s : this->sons)
        delete(s.second);
}

void Node::print(void)
{
    std::cout << "index " << index << " freq " << freq << " length " << length << " c " << c << std::endl;
}

void PatriciaTrie::browse(std::string word, Node* n)
{
    word += n->c;
    for (size_t i = n->index; i < n->length + n->index; ++i)
        word += this->suffixes[i];

    if (n->isWord)
        std::cout << word << " " << n->freq << std::endl;

    for (Node::nodeMap::iterator it = n->sons.begin(); it != n->sons.end(); ++it)
        browse(word, it->second);
}

void PatriciaTrie::print(void)
{
    std::string word("");

    for (Node::nodeMap::iterator it = this->root->sons.begin();
            it != this->root->sons.end();
            ++it)
        browse(word, it->second);
}

Node* PatriciaTrie::burstDown(size_t index, size_t i, size_t freq, Node* n)
{
    char c = this->suffixes[index + i];
    Node* newNode = nullptr;

    newNode = new Node(index, freq, i, n->c);

    int tmp = (int) n->length - i - 1;
    n->length = (tmp < 0) ? 0 : tmp;
    n->c = c;
    n->index = index + i + 1;

    newNode->sons[c] = n;

    return newNode;
}

int PatriciaTrie::add(std::string word, int freq, Node* t)
{
    Node* n = nullptr;
    char firstC = word[0];

    Node::nodeMap::iterator it = t->sons.find(firstC);
    if (it != t->sons.end())
        n = it->second;

    if (n != nullptr) // If prefix letter exists
    {
        size_t i = 0;
        // Look in suffixes if the tail of the word is already registered
        while (i < n->length && (i + 1) < word.length() &&
                suffixes[n->index + i] == word[i + 1])
            ++i;

        if (i == n->length) // They share the same prefix
        {
            // "Test" was there and we add "tester". Now the node is stil "test" and
            // node below is "er" (not contiguous in memory).
            std::string leftOver = word.substr(i + 1, word.length() - i - 1);

            if (leftOver.length() > 0) // Else we had a duplicate.
                add(leftOver, freq, n);
        }
        else
        {
            // "Tester" was there and we add "test". Now the node is "test" and
            // node below is "er" contiguous in suffixes.
            Node* tmp;
            if ((tmp = burstDown(n->index, i, freq, n)) != nullptr)
                t->sons[firstC] = tmp;

            std::string leftOver = word.substr(i + 1, word.length() - i - 1);
            if (leftOver.length() == 0)
                t->sons[firstC]->isWord = true;

            if (leftOver.length() > 0) // Else we had a duplicate.
                add(leftOver, freq, tmp);
        }
    }
    else // We create a leaf.
    {
        t->sons[firstC] = new Node(suffixes.size(), freq, word.length() == 0 ? 0 : word.length() - 1,
                firstC);
        t->sons[firstC]->isWord = true;

        // t->sons[firstC]->print();

        //std::cout << word << std::endl;
        if (word.begin() != word.end())
            for (std::string::const_iterator it = word.begin() + 1; it != word.end(); ++it)
            {
                //std::cout << *it;
                suffixes.push_back(*it);
            }
        //std::cout << std::endl;
    }

    return 0;
}

int nodeNum = 0;
void PatriciaTrie::deepthFirstSearch(Node* n, int father)
{
    std::vector<int> tmp;

    if (n != root)
    {
        for (size_t i = 0; i < new_trie[father].first.size(); i++)
            if (new_trie[father].first[i] == - 1)
            {
                new_trie[father].first[i] = nodeNum;
                break;
            }
    }

    if (n->sons.size() == 0)
        tmp.push_back(-2);
    else
        for (size_t i = 0; i < n->sons.size(); i++)
            tmp.push_back(- 1);


    new_trie.push_back(std::make_pair(tmp, std::make_pair(nodeNum, n)));

    father = nodeNum;
    nodeNum++;

    tmp.clear();
    for (std::map<char, Node*>::iterator it = n->sons.begin();
            it != n->sons.end(); ++it)
        deepthFirstSearch(it->second, father);

}

void PatriciaTrie::printVector()
{
    for (size_t i = 0; i < new_trie.size(); i++)
    {
        std::cout << "Node: " << new_trie[i].second.first << std::endl;
        std::cout << "pNode: " << new_trie[i].second.second << std::endl;
        std::cout << "Sons: ";
        for (size_t j = 0; j < new_trie[i].first.size(); j++)
            std::cout << new_trie[i].first[j] << " ";
        std::cout << std::endl << std::endl;
    }
}

void PatriciaTrie::compile(std::string filename)
{
    std::ifstream file(this->filename, std::ios::in);

    if (file)
    {
        std::string line;

        // Read file
        while (std::getline(file, line))
        {
            std::string word;
            int freq;
            std::istringstream ss(line);

            // Get word and frequency for this line
            ss >> word >> freq;
            //std::cout << word << std::endl;

            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            add(word, freq, this->root);
        }

        file.close();
    }
    else
    {
        std::cerr << "Error - Cannot open file: '" << filename;
        std::cerr << "'" << std::endl;
        exit(-1);
    }

    std::string buff;

    // Transform the patricia trie
    deepthFirstSearch(root, -1);

    // Header
    IntOctets n;
    ShortOctets n2;

    n.i = suffixes.size();
    buff.push_back(n.a[0]);
    buff.push_back(n.a[1]);
    buff.push_back(n.a[2]);
    buff.push_back(n.a[3]);

    n.i = sizeof(Header);
    buff.push_back(n.a[0]);
    buff.push_back(n.a[1]);
    buff.push_back(n.a[2]);
    buff.push_back(n.a[3]);

    n.i = new_trie.size();
    buff.push_back(n.a[0]);
    buff.push_back(n.a[1]);
    buff.push_back(n.a[2]);
    buff.push_back(n.a[3]);

    n.i = sizeof(Header) + sizeof(char) * suffixes.size() +
        (suffixes.size() % 4 == 0 ? 0 : (4 - (suffixes.size() % 4)));
    buff.push_back(n.a[0]);
    buff.push_back(n.a[1]);
    buff.push_back(n.a[2]);
    buff.push_back(n.a[3]);

    // Suffixes
    for (std::vector<char>::iterator it = suffixes.begin(); it != suffixes.end(); ++it)
        buff.push_back(*it);

    if (suffixes.size() % 4 != 0)
        for (size_t i = 0; i < 4 - (suffixes.size() % 4); i++)
            buff.push_back((char) 0);

    for (size_t i = 0; i < new_trie.size(); i++)
    {
        n.i = new_trie[i].second.first;
        buff.push_back(n.a[0]);
        buff.push_back(n.a[1]);
        buff.push_back(n.a[2]);
        buff.push_back(n.a[3]);

        n.i = new_trie[i].second.second->index;
        buff.push_back(n.a[0]);
        buff.push_back(n.a[1]);
        buff.push_back(n.a[2]);
        buff.push_back(n.a[3]);

        n.i = new_trie[i].second.second->freq;
        buff.push_back(n.a[0]);
        buff.push_back(n.a[1]);
        buff.push_back(n.a[2]);
        buff.push_back(n.a[3]);

        n.i = new_trie[i].second.second->length;
        buff.push_back(n.a[0]);
        buff.push_back(n.a[1]);
        /*
        buff.push_back(n.a[2]);
        buff.push_back(n.a[3]);
        */
        buff.push_back(new_trie[i].second.second->c);

        buff.push_back(new_trie[i].second.second->isWord);

        if (new_trie[i].first.size() == 1)
        {
            if (new_trie[i].first[0] == (-2))
                n2.i = 0;
            else
                n2.i = 1;
        }
        else
            n2.i = new_trie[i].first.size();
        buff.push_back(n2.a[0]);
        buff.push_back(n2.a[1]);
    }

    // for each node
    for (size_t i = 0; i < new_trie.size(); i++)    
        // Take each son
        for (size_t j = 0; j < new_trie[i].first.size(); j++)
        {
            // ERROR HERE, 1001 is possible for a node
            if (new_trie[i].first[j] != (INT_MAX - 1))
            {
                n.i = new_trie[i].first[j];
                //std::cout << n.i << std::endl;
                buff.push_back(n.a[0]);
                buff.push_back(n.a[1]);
                buff.push_back(n.a[2]);
                buff.push_back(n.a[3]);
            }
        }   

    if (access(filename.c_str(), F_OK) != -1 )
        remove(filename.c_str());

    FILE * fichier = fopen(filename.c_str() , "a+");    

    fwrite(buff.c_str(), sizeof(char), buff.length(), fichier);

    fclose(fichier);
    std::cout << "-- Compilation over" << std::endl;
}
