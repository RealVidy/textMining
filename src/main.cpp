#include "patriciaTrie/patriciaTrie.hpp"

int main(int, char**)
{
    PatriciaTrie* p = new PatriciaTrie("wTest.txt");

    p->compile();

    return 0;
}
