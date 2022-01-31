#include <thread>
#include <iostream>
#include <mutex>
#include <queue>
#include <condition_variable>

// Waiting for data to process with std::condition_variable

bool more_data_to_prepare()
{
  return false;
}

struct data_chunk {};

data_chunk prepare_data()
{
  return data_chunk();
}

void process(data_chunk&)
{}

bool is_last_chunk(data_chunk&)
{
  return false;
}

std::mutex mut;
std::queue<data_chunk> data_queue;   // 1
std::condition_variable data_cond;

void data_preparation_thread()
{
  while (more_data_to_prepare())
  {
    data_chunk const data=prepare_data();
    {
      std::lock_guard<std::mutex> lk(mut);
      data_queue.push(data);  // 2
    }
    data_cond.notify_one();  // 3
  }
}

void data_processing_thread()
{
  while(true)
  {
    std::unique_lock<std::mutex> lk(mut);  // 4
    data_cond.wait(lk, []{return !data_queue.empty();});  // 5
    data_chunk data=data_queue.front();
    data_queue.pop();
    lk.unlock();  // 6
    process(data);
    if(is_last_chunk(data))
      break;
  }
}

int main()
{
  std::thread t1(data_preparation_thread);
  std::thread t2(data_processing_thread);

  t1.join();
  t2.join();
}
