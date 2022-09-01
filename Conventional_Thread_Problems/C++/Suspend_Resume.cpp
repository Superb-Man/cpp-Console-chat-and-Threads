#include<iostream>
#include<string>
#include<thread>
#include<mutex>
#include<condition_variable>

std::mutex _mu;
std::condition_variable cv;

class Mythread{
    
    std::thread _thr ;
    bool _suspendFlag ;
    std::string _thrname ;

public:
    Mythread(std::string _thrname){
        this->_thrname = std::string(_thrname) ;
        _suspendFlag = false ; 
        start() ;
    }
    
    void start() ;
    void run() ;
    void mysuspend() ;
    void myresume() ;
    void terminate() ;
} ;

void Mythread::start(){
    _thr = std::thread(&Mythread::run , this) ; 
}
void Mythread::run(){
    try {
        for(int i = 15; i > 0; i--) {
            std::cout << _thrname <<" : "<< i <<'\n' ;  
            std::this_thread::sleep_for(std::chrono::milliseconds(200)) ;
            
            while(_suspendFlag) {
                std::unique_lock<std::mutex> lck(_mu);
            }
        }
    } catch (std::exception& e) {
        /********Nothing**********/
    }
    std::cout << "Exiting .." <<_thrname << '\n' ;
}
void Mythread::mysuspend(){
    std::lock_guard<std::mutex> lck(_mu);
    _suspendFlag = true;
}
void Mythread::myresume(){
    std::lock_guard<std::mutex> lck(_mu);
    _suspendFlag = false ;
}
void Mythread::terminate(){
    _thr.join() ;
}

int main()
{
    Mythread ob1("One") ;
    Mythread ob2("Two") ;
    try {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)) ;
        ob1.mysuspend();
        std::cout << "Suspending thread One" <<'\n' ;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)) ;
        ob1.myresume();
        std::cout << "Resuming thread One" <<'\n';
        ob2.mysuspend();
        std::cout << "Suspending thread Two" <<'\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)) ;
        ob2.myresume();
        std::cout << "Resuming thread Two" << '\n';
    } catch (std::exception &e) {
        //
    }
    // wait for threads to finish
    try {
        std::cout << "Waiting for threads to finish." <<'\n'; 
        ob1.terminate();
        ob2.terminate();
    } catch (std::exception& e) {
        //
    }
    std::cout << "Main thread exiting." << '\n';
    
    return 0 ;
}
