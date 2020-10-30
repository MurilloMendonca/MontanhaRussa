#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <chrono>


class Carrinho
{
    int numAssentos;
    std::vector<int> passageirosEmbarcados;
    std::mutex protege;

public:
    Carrinho()
    {
        numAssentos = 0;
    }
    Carrinho(int num)
    {
        numAssentos = num;
    }

    void embarca(std::queue<int>& fila)
    {
        std::vector<std::thread> vec;
        for (int i = 0; i < numAssentos/2; i++)
        {
            vec.push_back(std::thread([](std::vector<int> &assentos, std::queue<int> &fila, std::mutex &mut) {
                mut.lock();
                assentos.push_back(fila.front());
                fila.pop();
                mut.unlock();
            },
                                      std::ref(passageirosEmbarcados),
                                      std::ref(fila),
                                      std::ref(protege)));
        }
        for(auto& x:vec)
        {
            x.join();
        }
        this->mostra();
        vec.clear();
        for (int i = 0; i < numAssentos - numAssentos/2; i++)
        {
            vec.push_back(std::thread([](std::vector<int> &assentos, std::queue<int> &fila, std::mutex &mut) {
                mut.lock();
                assentos.push_back(fila.front());
                fila.pop();
                mut.unlock();
            },
                                      std::ref(passageirosEmbarcados),
                                      std::ref(fila),
                                      std::ref(protege)));
        }
        for(auto& x:vec)
        {
            x.join();
        }
    }
    void desembarca(std::queue<int>& fila)
    {
        std::vector<std::thread> vec;
        for (int i = 0; i < numAssentos; i++)
        {
            vec.push_back(std::thread([](std::vector<int> &assentos, std::queue<int> &fila, std::mutex &mut) {
                mut.lock();
                fila.push(assentos.back());
                assentos.pop_back();
                mut.unlock();
            },
                                      std::ref(passageirosEmbarcados),
                                      std::ref(fila),
                                      std::ref(protege)));
        }
        for(auto& x:vec)
        {
            x.join();
        }
    }
    void mostra(){
        printf("\nNo carrinho:\n|");
        for(int i=0;i<passageirosEmbarcados.size()/2;i++)
            printf(" %i |", passageirosEmbarcados[i]);
        printf("\n|");
        for(int i=passageirosEmbarcados.size()/2;i< passageirosEmbarcados.size();i++)
            printf(" %i |", passageirosEmbarcados[i]);
        printf("\n");
    }

    void viaja(){
        int t = 0;
        bool flag=true;
        while(t>=0){
            system("clear");
        for(int i=0;i<t;i++)
            printf(" ");
        printf("|");
        for(int i=0;i<passageirosEmbarcados.size()/2;i++){
            printf(" %i |", passageirosEmbarcados[i]);
        }
        
        printf("\n");
        for(int i=0;i<t;i++)
            printf(" ");
        printf("|");
        for(int i=passageirosEmbarcados.size()/2;i< passageirosEmbarcados.size();i++)
            printf(" %i |", passageirosEmbarcados[i]);
        printf("\n");
        fflush(stdin);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        
        if(flag && t>35) flag=false;
        t = (flag)?(t+2):(t-2);
        }
        system("clear");
    }
    void loop(std::queue<int>& fila)
    {
       for(;;){
        printf("\nEMBARCANDO\n");
        this->embarca(fila);
        this->mostra();
        this->mostraFila(fila);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        this->viaja();
        printf("\nDESEMBARCANDO\n");
        this->desembarca(fila);
        this->mostra();
        this->mostraFila(fila);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
    void mostraFila(std::queue<int> aux)
    {
        printf("\nNa Fila: ");
        while(!aux.empty()){
            printf("%i ", aux.front());
            aux.pop();
        }
    }
};