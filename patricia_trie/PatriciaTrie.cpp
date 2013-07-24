# include <PatriciaTrie.hpp>

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
  if (isalpha(word[0]))
    pos = word[0]  - 'a';
  else
    pos = word[0] - '0';

  if (sons[pos] != nullptr)
    add(word.substr(word.begin + 1, word.end), freq, sons[pos]);
  else // Si on est en feuille
  {
    sons[pos] = new node(suffixes.size(), freq, word.length() - 1,
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
