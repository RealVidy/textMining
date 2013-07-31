# include "../headers/bloomfilter.hpp"

BloomFilter::BloomFilter()
{
}

BloomFilter::~BloomFilter()
{
}

void BloomFilter::reset()
{
  bitMap.reset();
}

unsigned int BloomFilter::murmur3_32(const void * key, int len, unsigned int seed)
{
  const unsigned int m = 0x5bd1e995;
  const int r = 24;

  unsigned int h = seed ^ len;
  
  const unsigned char * data = (const unsigned char *)key;

  while(len >= 4)
    {
      unsigned int k = *(unsigned int *)data;
      
      k *= m; 
      k ^= k >> r; 
      k *= m; 
      
      h *= m; 
      h ^= k;

      data += 4;
      len -= 4;
    }
	
  switch(len)
    {
    case 3: h ^= data[2] << 16;
    case 2: h ^= data[1] << 8;
    case 1: h ^= data[0];
      h *= m;
    };

  h ^= h >> 13;
  h *= m;
  h ^= h >> 15;

  return h;
}

void BloomFilter::add(std::string word)
{
  unsigned int tmp = 0;

  tmp = murmur3_32(word.c_str(), word.length(), 0x52ed88ff);
  bitMap[tmp % BITSET_SIZE] = 1;

  for (int i = 0; i < NBHASH - 1; i++)
  {
    tmp = murmur3_32(word.c_str(), word.length(), tmp); 
    bitMap[tmp % BITSET_SIZE] = 1;
  }
}

bool BloomFilter::isPresent(std::string word)
{
  unsigned int tmp = 0;
  int sum = 0;

  tmp = murmur3_32(word.c_str(), word.length(), 0x52ed88ff);
  sum =  bitMap[tmp % BITSET_SIZE];

  for (int i = 0; i < NBHASH - 1; i++)
  {
    tmp = murmur3_32(word.c_str(), word.length(), tmp); 
    sum += bitMap[tmp % BITSET_SIZE];
   }

  return (sum == 4);
}

