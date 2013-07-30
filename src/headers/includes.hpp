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

# include <assert.h>
# include <zlib.h>
# include <stdio.h>

# include <sys/mman.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include <boost/archive/binary_iarchive.hpp>
# include <boost/archive/binary_oarchive.hpp>
# include <boost/serialization/map.hpp>
# include <boost/serialization/vector.hpp> 

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

struct dataNode
{
    size_t index;
    size_t freq;
    unsigned short length;
    char c;
    bool isWord;
    size_t nbSons;
} __attribute__((packed));

#endif
