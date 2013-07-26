#include "patriciaTrie.hpp"

PatriciaTrie::PatriciaTrie(std::string f) : filename (f)
{
    root = new Node();
}

PatriciaTrie::~PatriciaTrie()
{
}

Node::Node(int index, int freq, int length, char c): nbSons(0)
{
    this->index = index;
    this->freq = freq;
    this->length = length;
    this->c = c;
}

Node::Node(void): index(0), freq(0), length(0), c(0), nbSons(0)
{
}

void Node::print(void)
{
    std::cout << "index " << index << " freq " << freq << " length " << length << " c " << c << std::endl;
}

int Node::addNbSons(int n)
{
    if (this->nbSons + n < 0)
    {
        std::cerr << "Error while incrementing number of sons" << std::endl;
        return -1;
    }

    this->nbSons += n;

    return 0;
}

void PatriciaTrie::browse(std::string word, Node* n)
{
    word += n->c;
   
    for (size_t i = n->index; i < n->length + n->index; ++i)
        word += this->suffixes[i];

    if (n->nbSons == 0)
        std::cout << "Word: " << word << " Freq: " << n->freq << std::endl;
    else
    {
        for (size_t i = 0; i < 36; ++i)
            if (n->sons[i] != nullptr)
                browse(word, n->sons[i]);
    }
}

void PatriciaTrie::print(void)
{
    std::string word("");
    for (size_t i = 0; i < 36; ++i)
        if (this->root->sons[i] != nullptr)
            browse(word, this->root->sons[i]);
}

Node* PatriciaTrie::burstDown(size_t index, size_t i, unsigned short freq, Node* n)
{
    size_t pos = -1;
    char c = this->suffixes[index + i];
    Node* newNode = nullptr;

    newNode = new Node(index, freq, i, this->suffixes[index]);

    n->length -= i + 1;
    n->c = c;

    if (isalpha(c))
        pos = c - 'a';
    else
        pos = c - '0';

    newNode->sons[pos] = n;
    if (newNode->addNbSons(1))
        return nullptr;

    return newNode;
}

int PatriciaTrie::add(std::string word, int freq, Node* t)
{
    size_t pos = -1;
    Node* n;

    if (isalpha(word[0]))
        pos = word[0] - 'a';
    else if (isdigit(word[0]))
        pos = word[0] - '0';
    else
    {
        std::cerr << "Error: Character \"" << word[0] << "\" not handled." << std::endl;

        return -1;
    }

    // Current examined node.
    n = t->sons[pos];

    if (n != nullptr) // If prefix letter exists
    {
        size_t i = 0;
        // Look in suffixes if the tail of the word is already registered
        while (i < n->length && (i + 1) < word.length() &&
                suffixes[n->index + i] == word[i + 1])
            ++i;

        if (i + 2 == word.length()) // word is fully registered
        {
            // "Tester" was there and we add "test". Now the node is "test" and
            // node below is "er" contiguous in suffixes.
            if (i < n->length) // burst Down
            {
                Node* tmp;
                if ((tmp = burstDown(n->index, i, freq, n)) != nullptr)
                    t->sons[pos] = tmp;             
            }
            // Else it is a duplicate, do nothing.
        }
        else
        {
            // "Test" was there and we add "tester". Now the node is stil "test" and
            // node below is "er" (not contiguous in memory).
            add(word.substr(i + 1, n->length - i), freq, n);
        }
    }
    else // We create a leaf.
    {
        t->sons[pos] = new Node(suffixes.size(), freq, word.length() - 1,
                word[0]);

        if (t->addNbSons(1))
            return -1;
        // t->sons[pos]->print();

        //std::cout << word << std::endl;
        for (std::string::const_iterator it = word.begin() + 1; it != word.end(); ++it)
        {
            //std::cout << *it;
            suffixes.push_back(*it);
        }
        //std::cout << std::endl;
    }

    return 0;
}

int PatriciaTrie::compile(void)
{
    std::ifstream file(filename, std::ios::in);

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
        std::cerr << "'" << std::cout;
        return -1;
    }
    return 0;
}
