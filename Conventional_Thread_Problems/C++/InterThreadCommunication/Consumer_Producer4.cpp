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
    int k  ;
    Sharedobject(){

        __data_ready = false ;
        __data_value = 0 ; k = 0 ;
    } 
    
    void produce(int n) ;
    int consume() ;
    bool state(){return __data_ready ;}
    
} ;
void Sharedobject::produce(int __data_value) {
  //while(true){
    //cout <<__data_ready<<endl;
    unique_lock<mutex> ul(__data_mutex);
    this->__data_value = __data_value ;
    cout<<"Toriqe Produces : "<< __data_value <<endl;
    __data_ready = true;
    ul.unlock();
    while (__data_ready) {
      // sleep for 1 second
      try{
        this_thread::sleep_for (chrono::seconds(1));
      }catch(exception& e) {
          //statement
      }
    }
  //}
}

// consume thread function
int Sharedobject::consume() {
  //while(true){
    while (!__data_ready) {
      // sleep for 1 second
      try{
        this_thread::sleep_for (chrono::seconds(1));
      }catch(exception& e) {
          //statement
      }
    }
    //cout<<__data_ready<<endl ;
    unique_lock<mutex> ul(__data_mutex) ;
    
    cout<<"Lamiya gets : "<< __data_value << endl ;
    __data_ready = false ;
    return __data_value ;
  //}
}

class producerThread{
    Sharedobject* object ;
    thread p ;
public:

    producerThread(Sharedobject& object){
        this->object = &object ;
        p = thread(&producerThread::run , this) ;
    }
    void run(){
        int i = 0 ;
        while(i<10)
            object->produce(i++) ;
    }
    Sharedobject* get(){
        return object ;
    }
   void terminate(){
        try{
            p.join() ;
        }catch(exception& e){
            //statement
        }
    }
    
} ;

class consumerThread{
    Sharedobject* object ;
    thread c ;
public:
    consumerThread(Sharedobject& object){
        this->object = &object ;
        c = thread(&consumerThread::run, this) ;
    }
    void run(){
        while(true){
            object->consume() ;
            if(object->consume() == 9){
                break ; 
            }
        }
    }
    Sharedobject* get(){
        return object ;
    }
    void terminate(){
        try{
            c.join() ;
        }catch(exception& e) {
            //statement
        }
    }
} ;

int main() {
    Sharedobject obj ;
    consumerThread Lamiya(obj) ;
    producerThread Toriqe(obj) ;
    /*
    thread con(&consumerThread::run, Lamiya) ;
    thread pro(&producerThread::run, Toriqe) ;
    con.join() ;
    pro.join() ;
    */
    Lamiya.terminate() ;
    Toriqe.terminate() ;
    obj.k = 0 ;
    Toriqe.get()->k = 87 ;
    cout<<obj.k<<endl;
    cout<<Lamiya.get()->k<<endl ;
    
    cout<<"Ending"<<endl ;
    //cout<<&(Toriqe.get())<<" "<<&(Lamiya.get())<<endl; 
    
    return 0 ;
}