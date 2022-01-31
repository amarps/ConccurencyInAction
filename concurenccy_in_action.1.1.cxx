#include <iostream>
#include <thread>

void hello()
{
  std::cout << "Hello concurrent world\n";
}

int main(void)
{
  std::thread t(hello);  
  t.join();
}
