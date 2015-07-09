#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
 
using namespace std;
 
static mutex theLock;
 
void produce(int* data) {
  for (int i = 1 ; i <= 5 ; ++i) {
    {
      lock_guard<mutex> lock(theLock);
      *data = i;
    }
    //this_thread::sleep_for(chrono::milliseconds(500));
  }
}
 
int main() {
  int data = 0;
  int val = 0;
 
  // Start thread
  thread t(produce, &data);
 
  // Loop through the data until
  do {
    {
      lock_guard<mutex> lock(theLock);
      if (data != 5) {
        data += 12;
      }
      val = data;
    }
    cout<< "My current value " << val << endl;
  } while (val != 5);
 
  // Cleanup
  t.join();
 
  return 0;
}