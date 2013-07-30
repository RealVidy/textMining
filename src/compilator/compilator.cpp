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

    n->length -= i + 1;
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

            if (leftOver.length() > 0) // Else we had a duplicate.
                add(leftOver, freq, tmp);
        }
    }
    else // We create a leaf.
    {
        t->sons[firstC] = new Node(suffixes.size(), freq, word.length() - 1,
                firstC);
        t->sons[firstC]->isWord = true;

        // t->sons[firstC]->print();

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

/*
int PatriciaTrie::compress(FILE* source, FILE* dest, int level)
{
    int ret, flush;
    unsigned have;
    z_stream strm;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    ret = deflateInit(&strm, level);
    if (ret != Z_OK)
	return ret;

    do {
	strm.avail_in = fread(in, 1, CHUNK, source);
	if (ferror(source))
	{
	    (void) deflateEnd(&strm);
	    return Z_ERRNO;
	}
	flush = feof(source) ? Z_FINISH : Z_NO_FLUSH;
	strm.next_in = in;
	do {
	    strm.avail_out = CHUNK;
	    strm.next_out = out;
	    ret = deflate(&strm, flush);
	    assert(ret != Z_STREAM_ERROR);
	    have = CHUNK - strm.avail_out;
	    if (fwrite(out, 1, have, dest) != have || ferror(dest))
	    {
		(void) deflateEnd(&strm);
		return Z_ERRNO;
	    }
	} while (strm.avail_out == 0);
	assert(strm.avail_in == 0);
    } while (flush != Z_FINISH);
    assert(ret == Z_STREAM_END);

    (void) deflateEnd(&strm);
    return Z_OK;
}
*/

int nodeNum = 0;
void PatriciaTrie::deepthFirstSearch(Node* n, int father)
{
    std::vector<int> tmp;

    if (n != root)
    {
	for (size_t i = 0; i < new_trie[father].first.size(); i++)
	    if (new_trie[father].first[i] == -1)
	    {
		new_trie[father].first[i] = nodeNum;
		break;
	    }
    }

    if (n->sons.size() == 0)
	tmp.push_back(-2);
    else
	for (size_t i = 0; i < n->sons.size(); i++)
	    tmp.push_back(-1);

    new_trie.push_back(std::make_pair(tmp, std::make_pair(nodeNum, n)));
 
    father = nodeNum;
    nodeNum++;

    tmp.clear();
    for (std::map<char, Node*>::iterator it = n->sons.begin();
	 it != n->sons.end(); ++it)
	deepthFirstSearch(it->second, father);

}

void PatriciaTrie::createRawFile(std::string filename)
{
    std::ofstream file(filename);

    // Header
    IntOctets n;
    ShortOctets n2;

    n.i = sizeof(char) * suffixes.size();
    file << n.a[0];
    file << n.a[1];
    file << n.a[2];
    file << n.a[3];

    n.i = 12;
    file << n.a[0];
    file << n.a[1];
    file << n.a[2];
    file << n.a[3];

    n.i = 12 + sizeof(char) * suffixes.size();
    file << n.a[0];
    file << n.a[1];
    file << n.a[2];
    file << n.a[3];

    // Suffixes
    for (std::vector<char>::iterator it = suffixes.begin(); it != suffixes.end(); ++it)
	file << *it;

    // Transform the patricia trie
    deepthFirstSearch(root, -1);
    
    std::cout << new_trie[0].second.second->c << std::endl;

    for (size_t i = 0; i < new_trie.size(); i++)
    {
	n.i = new_trie[i].second.second->index;
	file << n.a[0];
	file << n.a[1];
	file << n.a[2];
	file << n.a[3];

	n.i = new_trie[i].second.second->freq;
	file << n.a[0];
	file << n.a[1];
	file << n.a[2];
	file << n.a[3];

	n.i = new_trie[i].second.second->length;
	file << n.a[0];
	file << n.a[1];
	file << n.a[2];
	file << n.a[3];

	file << new_trie[i].second.second->c;

	file << new_trie[i].second.second->isWord;

	n2.i = new_trie[i].first.size();
	file << n2.a[0];
	file << n2.a[1];

	for (size_t j = 0; j < new_trie[i].first.size(); j++)
	    if (new_trie[i].first[j] != -2)
	    {
		n.i =  new_trie[i].first[j] * BLOCK_SIZE + sizeof(int) * new_trie[i].first.size();
		file << n.a[0];
		file << n.a[1];
		file << n.a[2];
		file << n.a[3];
	    }
    }

    file.close();
/*
    std::string name_compress = filename + "_compress";
 
    FILE* in = fopen(filename.c_str(), "r+");
    FILE* out = fopen(name_compress.c_str(), "a+");

    compress(in, out, 1);

    fclose(in);
    fclose(out);

    rename(name_compress.c_str(), filename.c_str());
*/
}
