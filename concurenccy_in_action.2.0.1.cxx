#include <iostream>
#include <thread>

// launching thread with lambda

void printA() {
  std::cout << "A" << std::endl;
}

void printB() {
  std::cout << "B" << std::endl;
}

int main(void)
{
  std::thread my_thread([](){
    printA();
    printB();
  });

  my_thread.join();
}
