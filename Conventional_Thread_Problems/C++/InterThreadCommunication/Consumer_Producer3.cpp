#include<cstdlib>
#include<iostream>
#include<mutex>
#include<thread>
#include<chrono>
using namespace std;

mutex __data_mutex ;
class Sharedobject{
    //mutex __data_mutex ;
    bool __data_ready ;
    int __data_value ;

public:
    Sharedobject(){
        __data_ready = false ;
        __data_value = 0 ;
    } 
    
    void produce(int n) ;
    int consume() ;
    bool state(){return __data_ready ;}
    
} ;


void Sharedobject::produce(int n) {
  //while(true){
    //cout <<__data_ready<<endl;
    __data_value = n ;
    cout<<"Toriqe Produces : "<<__data_value <<endl;
    unique_lock<mutex> ul(__data_mutex);
    __data_ready = true;
    ul.unlock();
    while (__data_ready) {
      // sleep for 1 second
      this_thread::sleep_for (chrono::seconds(1));
    }
  //}
}

// consume thread function
int Sharedobject:: consume() {
  //while(true){
    while (!__data_ready) {
      // sleep for 1 second
      this_thread::sleep_for (chrono::seconds(1));
    }
    //cout<<__data_ready<<endl ;
    unique_lock<mutex> ul(__data_mutex) ;
    
    cout<<"Lamiya gets : "<< __data_value << endl ;
    __data_ready = false ;
    
    return __data_value ;
  //}
}

void producerThread(Sharedobject& object){
    int i = 0 ;
    while(i<10)
        object.produce(i++) ;
}

void consumerThread(Sharedobject& object){
    while(true){
        object.consume() ;
        if(object.consume() == 9) break ; 
    }
}

int main() {
    Sharedobject obj ;
    thread consumer((consumerThread), ref(obj)) ;
    thread producer((producerThread), ref(obj)) ;
    consumer.join() ;
    producer.join() ;
    
    return 0 ;
}