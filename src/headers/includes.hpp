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

# include <unistd.h>

# include <assert.h>
# include <zlib.h>
# include <stdio.h>
# include <fcntl.h>

# include <sys/time.h>
# include <sys/resource.h>
# include <sys/mman.h>
# include <sys/types.h>
# include <sys/stat.h>

# include <boost/archive/binary_iarchive.hpp>
# include <boost/archive/binary_oarchive.hpp>
# include <boost/serialization/map.hpp>
# include <boost/serialization/vector.hpp> 

# define HEADER_SIZE (16)

union IntOctets
{
    int i;
    char a[4];
};

union SizeTOctets
{
    size_t i;
    char a[4];
};

union ShortOctets
{
    short i;
    char a[2];
};

struct Header
{
    size_t nb_suffixes;
    size_t suffixes_offset;
    size_t nb_node;
    size_t trie_offset;
};

struct dataNode
{
    size_t no;
    size_t index;
    size_t freq;
    unsigned short length;
    char v1;
    char v2;
    char c;
    bool isWord;
    unsigned short  nbSons;
} __attribute__((packed));

#endif
