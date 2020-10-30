#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include "carrinho.hpp"
using namespace std;


int main(){
    queue<int> fila;
    for(int i=0;i<100;i++)
    {
        fila.push(i);
    }
    Carrinho car(10);
    car.loop(fila);
}