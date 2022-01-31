#include <iostream>
#include <thread>
#include <unistd.h>

/* a function that returns while a thread still has access to local variables */

struct Func
{
  int &i;
  Func(int &i_) : i(i_) {}

  void operator()() {
    CauseError();
  }

  void CauseError() {
    for (int j = 0; j < 100000; j++) {
      std::cout << i << std::endl; // potential accesing dangling refrence
    }
  }
};

void duh()
{
  int a = 2;
  Func my_func(a);
  std::thread my_thread(my_func);
  my_thread.detach(); // dont wait for my thread

} // my thread might be still running

int main()
{
  duh();
  usleep(1000);
}
