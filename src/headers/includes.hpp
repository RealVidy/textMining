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

#endif
