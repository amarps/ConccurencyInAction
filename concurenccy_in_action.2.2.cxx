#include <iostream>
#include <thread>
#include <unistd.h>
#include <stdexcept>

/* waiting for thread to finish */

struct Func
{
  int &i;
  Func(int &i_) : i(i_) {}

  void operator()() {
    CauseError();
  }

  void CauseError() {
    for (int j = 0; j < 100000; j++) {
      if(i == 3) {
	throw std::exception();
      }
      int k = 2 + i;
    }
  }
};

void f()
{
  int some_local_state=0;
  Func my_func(some_local_state);
  std::thread t(my_func);
  try {
    my_func.i = 3;
  } catch(std::exception) {
    std::cout << "@@@@@@called" << std::endl;
    throw std::logic_error("Im called");
    t.join();
  }
  t.join();
}

int main()
{
  f();
  return 0;
}
