#include <iostream>
#include <thread>

/* scoped_thread and example usage */
/* scoped_thread is to ensure that threads are completed before a scope is exited */
class scoped_thread
{
  std::thread t;
public:
  explicit scoped_thread(std::thread t_) : t(std::move(t_))
  {
    if(!t.joinable())
      throw std::logic_error("No thread");
  }
  ~scoped_thread()
  {
    t.join();
  }
  scoped_thread(scoped_thread const&)=delete;
  scoped_thread& operator=(scoped_thread const&)=delete;
};

void do_something(int &i)
{
  ++i;
}

struct func
{
  int &i;

  func(int &i_):i(i_){}

  void operator()()
  {
    for(unsigned j=0;j<10000;++j) {
      do_something(i);
    }
  }
};

void do_something_in_current_thread() {}
void f()
{
  int some_local_state;
  scoped_thread t{std::thread(func(some_local_state))};

  do_something_in_current_thread();
}

int main () {
  f ();
}
