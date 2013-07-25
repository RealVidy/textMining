#include "patriciaTrie.hpp"

PatriciaTrie::PatriciaTrie(std::string f) : filename (f)
{
}

PatriciaTrie::~PatriciaTrie()
{
}

node::node(int index, int freq, int length, char c)
{
    this->index = index;
    this->freq = freq;
    this->length = length;
    this->c = c;
}

node* PatriciaTrie::burstDown(size_t index, size_t i, unsigned short freq, node* n)
{
    size_t pos = -1;
    char c = this->suffixes[index + i];
    node* newNode = nullptr;
    
    newNode = new node(index, freq, i, this->suffixes[index]);

    n->length -= i + 1;
    n->c = c;

    if (isalpha(c))
        pos = c - 'a';
    else
        pos = c - '0';
    
    newNode->sons[pos] = n;

    return newNode;
}

int PatriciaTrie::add(std::string word, int freq, node* t)
{
    size_t pos = -1;
    node* n;

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
        
        if (i == word.length()) // word is fully registered
        {
            // "Tester" was there and we add "test". Now the node is "test" and
            // node below is "er" contiguous in suffixes.
            if (i < n->length) // burst Down (it is not that easy, recursive burst possible)
            {
                // TODO burstdown, we don't add anything, date already exists.
                // Just updating is needed.
                node* tmp;
                if ((tmp = burstDown(n->index, i, freq, n)) != nullptr)
                n = tmp;             
            }
            // Else it is a duplicate, do nothing.
        }
        else
        {
            // "Test" was there and we add "tester". Now the node is stil "test" and
            // node below is "er" (not contiguous in memory).
            add(word.substr(i + 1, n->length - (i + 1)), freq, n);
        }
    }
    else // We create a leaf.
    {
        n = new node(suffixes.size(), freq, word.length() - 1,
                word[0]);
        
        for (std::string::const_iterator it = word.begin() + 1; it != word.end(); ++it)
            suffixes.push_back(*it);
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

            ss >> word >> freq;
            std::cout << word << std::endl;
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
