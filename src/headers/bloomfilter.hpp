#ifndef BLOOM_FILTER_HPP
# define BLOOM_FILTER_HPP

# define NBHASH (4)
# define BITSET_SIZE (4000000)

class BloomFilter
{
private:
  std::bitset<BITSET_SIZE> bitMap;

private:
  unsigned int murmur3_32(const void* key, int len, unsigned int seed);

public:
  BloomFilter();
  ~BloomFilter();

public:
  void add(std::string word);
  void reset();

public:
  bool isPresent(std::string word);

};

#endif /* BLOOM_FILTER8H */
