#include <list>
#include <algorithm>
#include <thread>
#include <iostream>
#include <experimental/random>

std::list<int> some_list;
static const int range = 1000;

void add_to_list(int val)
{
  some_list.push_back(val);
}

bool contain(int val)
{
  bool exist = std::find(some_list.begin(), some_list.end(), val) != some_list.end();
  return exist;
}

void add_in_range()
{
  for (int i=0; i < range; ++i) {
    add_to_list(i);
  }
}

void contains_rand_range()
{
  for (int i =0; i < range; ++i) {
    if(!contain(i)) {
      std::cout << "loss" << i << std::endl;
    }
  }

}

int main()
{
  std::thread t(add_in_range);
  std::thread t1(contains_rand_range);

  t.join();
  t1.join();
}
