#include <iostream>
#include <thread>

/* RAII thread */
class thread_guard
{
  std::thread &t;
public:
  explicit thread_guard(std::thread &t_)
    :t(t_) { }

  ~thread_guard() {
    if(t.joinable()) {
      t.join();
    }
  }
  thread_guard(thread_guard const&)=delete;
  thread_guard& operator=(thread_guard const&)=delete;
};

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
  thread_guard g(t);  // prevent leaving function before thread finish
}

int main(void)
{
  f();
}
