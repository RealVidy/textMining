#include "patriciaTrie/patriciaTrie.hpp"

int main(int, char**)
{
    PatriciaTrie* p = new PatriciaTrie("words.txt");

    p->compile();

    return 0;
}
