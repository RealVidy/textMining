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

/*
unsigned int BloomFilter::murmur3_32(const void* key, int len, unsigned int seed)
{
  unsigned int c1 = 0xcc9e2d51;
  unsigned int c2 = 0x1b873593;
  unsigned int r1 = 15;
  unsigned int r2 = 13;
  unsigned int m = 5;
  unsigned int n = 0xe6546b64;
  unsigned int len2 = len;

  unsigned int hash = seed;
  
  unsigned char *data = (unsigned char *) key;
  unsigned int k = 0;

  std::cout << static_cast<const char*>(key) << std::endl;
  std::cout << "Seed: " << seed << std::endl;

  while (len >= 4)
  {
    k = *(unsigned int *) data;

    k *= c1;
    k = (k << r1) or (k >> (32 - r1));
    k *= c2;

    hash ^= k;
    hash = (hash << r2) or (hash >> (32 - r2));
    hash = hash * m + n;

    data += 4;
    len -= 4;
  }

  // Remaining bytes
  k = *(unsigned int *) data;
  
  k *= c1;
  k = (k << r1) or (k >> (32 - r1));
  k *= c2;

  hash ^= k;
  
  hash ^= len;
  hash = hash ^ (hash >> 16);
  hash *= 0x85ebca6b;
  hash = hash ^ (hash >> 13);
  hash = hash * 0xc2b2ae35;
  hash = hash ^ (hash >> 16);

  return hash;
}
*/

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

