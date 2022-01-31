#include <list>
#include <mutex>
#include <algorithm>
#include <thread>
#include <iostream>
#include <condition_variable>

std::list<int> some_list;
std::mutex m;
std::condition_variable cv;
static const int range = 1000;
int last_element;

void add_to_list(int val)
{
  std::unique_lock<std::mutex> guard(m);
  std::cout << "adding" << val << std::endl;
  some_list.push_back(val);
  cv.notify_one();
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
    std::unique_lock<std::mutex> guard(m);
    cv.wait(guard, [i]{return ( !some_list.empty() && some_list.back() >= i);});
    std::cout << "Checking" << i << std::endl;
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
