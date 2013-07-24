#include <patriciaTrie.hpp>

PatriciaTrie::PatriciaTrie(std::string f) : filename (f)
{
}

PatriciaTrie::~PatriciaTrie()
{
}

node::node(int index, int freq, int length, char c)
{
    this.index = index;
    this.freq = freq;
    this.length = length;
    this.c = c;
}

int PatriciaTrie::add(std::string word, int freq, node* t)
{
    int pos = -1;
    node* n;

    if (isalpha(word[0]))
        pos = word[0] - 'a';
    else if (isdigit(word[0]))
        pos = word[0] - '0';
    else
        std::cerr << "Error: Character \"" << word[0] << "\" not handled." << std::endl;

    n = t.sons[pos];

    if (n != nullptr) // If prefix letter exists
    {
        int i = 0;
        // Look in suffixes if the tail of the word is already registered
        while (i < n.length && (i + 1) < word.length() &&
                suffixes[n.index + i] == word[i + 1])
            ++i;
        
        // TODO
        if (i == word.length) // word is fully registered
        {
            // "Tester" was there and we add "test". Now the node is "test" and
            // node below is "er" contiguous in suffixes.
            if (i < n.length) // burst Down (it is not that easy, recursive burst possible)
            {
                // TODO burstdown, we don't add anything, date already exists.
                // Just updating is needed.
                burstDown(n.index + i, n.freq, n);
                n.length = i;
                n.freq = freq;
            }
            // Else it is a duplicate, do nothing.
        }
        else
        {
            // "Test" was there and we add "tester". Now the node is stil "test" and
            // node below is "er" (not contiguous in memory).
            add(word.substr(word.begin + i + 1, word.end), freq, n);
        }
    }
    else // We create a leaf.
    {
        n = new node(suffixes.size(), freq, word.length() - 1,
                word[0]);
        for (std::string::iterator it = word.begin + 1; it != word.end; it++)
            suffixes.push_back(*it);
    }
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

            line >> word >> freq;
            add(tolower(word), freq, root);
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
