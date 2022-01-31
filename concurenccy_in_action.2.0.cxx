#include <iostream>
#include <thread>

// launching thread with class

class background_task
{
public:
  void operator()() const
  {
    printA();
    printB();
  }

  void printA() const { std::cout << "A" << std::endl; }
  void printB() const { std::cout << "B" << std::endl; }
};

int main(void)
{
  background_task bg_task;
  std::thread my_thread(bg_task);

  my_thread.join();
}
