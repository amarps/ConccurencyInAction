#include <iostream>
#include <thread>

int main()
{
  std::thread t([](){
    std::cout << std::this_thread::get_id() << std::endl;
  });
  std::thread t1([](){
    std::cout << std::this_thread::get_id() << std::endl;
  });

  std::cout << std::this_thread::get_id() << std::endl;
  std::cout << std::this_thread::get_id() << std::endl;

  t.join();
  t1.join();
}
