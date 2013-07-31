#ifndef INCLUDE_HPP
# define INCLUDE_HPP


# include <iostream>
# include <fstream>
# include <sstream>

# include <cctype>
# include <string>

# include <vector>
# include <algorithm>
# include <map>
# include <bitset>

# include <climits>

# include <unistd.h>

# include <assert.h>
# include <stdio.h>
# include <fcntl.h>

# include <sys/time.h>
# include <sys/resource.h>
# include <sys/mman.h>
# include <sys/types.h>
# include <sys/stat.h>

# define HEADER_SIZE (16)

union IntOctets
{
    unsigned int i;
    char a[4];
};

union SizeTOctets
{
    unsigned int i;
    char a[4];
};

union ShortOctets
{
    unsigned short i;
    char a[2];
};

struct Header
{
    unsigned int nb_suffixes;
    unsigned int suffixes_offset;
    unsigned int nb_node;
    unsigned int trie_offset;
};

struct dataNode
{
    unsigned int no;
    unsigned int index;
    unsigned int freq;
    unsigned short length;
    //char v1;
    //char v2;
    char c;
    bool isWord;
    int nbSons;
} __attribute__((packed));

#endif
