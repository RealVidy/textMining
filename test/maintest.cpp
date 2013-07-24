# include "../bloomfilter/bloomfilter.hpp"

# include <iostream>

int main(int argc, char *argv[])
{
  BloomFilter Filter = BloomFilter();

  Filter.reset();
  
  Filter.add("test");
  Filter.add("test2");
  Filter.add("testQSD");
  Filter.add("teQSDFQSDFst");
  Filter.add("tessdt");
  Filter.add("tesfsdfsdfsdfst");
  Filter.add("t65df5sdf5sdfest");
  Filter.add("tes s5df s56fezrst");
  Filter.add("tesefze eze 56tw");

  std::cout << "Word: 'test' is present ? " << Filter.isPresent("test") << std::endl;
  std::cout << "Word: 'test6' is present ? " << Filter.isPresent("test6") << std::endl;
  std::cout << "Word: 'tesefze eze 56tw' is present ? " << Filter.isPresent("tesefze eze 56tw")  << std::endl;

  return 0;
}
