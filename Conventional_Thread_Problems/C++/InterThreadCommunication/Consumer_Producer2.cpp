#include<cstdlib>
#include<iostream>
#include<mutex>
#include<thread>
#include<chrono>
using namespace std;

mutex __data_mutex ;
bool __data_ready ;
int __data_value ;


void produce() {
  while(true){
    //cout <<__data_ready<<endl;
    __data_value = rand()%10 ;
    cout<<"Toriqe Produces : "<<__data_value <<endl;
    unique_lock<mutex> ul(__data_mutex);
    __data_ready = true;
    ul.unlock();
    while (__data_ready) {
      // sleep for 1 second
      this_thread::sleep_for (chrono::seconds(1));
    }
  }
}

// consume thread function
void consume() {
  while(true){
    while (!__data_ready) {
      // sleep for 1 second
      this_thread::sleep_for (chrono::seconds(1));
    }
    //cout<<__data_ready<<endl ;
    unique_lock<mutex> ul(__data_mutex) ;
    
    cout<<"Lamiya gets : "<< __data_value << endl ;
    __data_ready = false ;
  }
}

void producerThread(){
    produce() ;
}

void consumerThread(){
    consume() ;
}

int main() {
    thread consumer(consumerThread) ;
    thread producer(producerThread) ;
    consumer.join() ;
    producer.join() ;
    
    return 0 ;
}