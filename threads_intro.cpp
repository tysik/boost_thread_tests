#include <boost/thread.hpp>
#include <boost/thread/scoped_thread.hpp>
#include <boost/chrono.hpp>

#include <iostream>

void wait(int seconds)
{
  boost::this_thread::sleep_for(boost::chrono::seconds{seconds});
}

void thread()
{
  for (int i = 0; i < 3; ++i)
  {
    wait(1);
    std::cout << i << std::endl;
  }
}

void thread_with_interrupt()
{
  //boost::this_thread::disable_interruption no_interruption; // prevents interruption

  try
  {
    for (int i = 0; i < 3; ++i)
    {
      wait(1);
      std::cout << 10 * i << std::endl;
    }
  }
  catch (boost::thread_interrupted&)
  {
    std::cout << "Interrupted!" << std::endl;
  }
}

int main()
{
  std::cout << boost::this_thread::get_id() << std::endl;

  boost::thread_attributes attrs;
  attrs.set_stack_size(1024);
  boost::thread t1{attrs, thread};
  std::cout << t1.get_id() << std::endl;
  std::cout << boost::thread::hardware_concurrency() << std::endl;

  t1.join();   // join() is blocking - waiting for t to finish

  boost::scoped_thread<> t2{boost::thread{thread_with_interrupt}}; // also blocking
  wait(2);
  t2.interrupt();
}
