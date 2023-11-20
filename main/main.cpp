#include <iostream>
#include <vector>
#include <random>

using namespace std;

void initial_condition(vector<int>& ring, int num, mt19937& gen, uniform_int_distribution<int> ran_pos){
    for (int i = 0; i < num; i++)
    {
        ring[ran_pos(gen)] = 1;
    }
    
}

int main(){
    const int SIZE = 10;
    const double ALPHA = 0.2;
    const double BETA = 0.2;
    const int NUM_ILLNESS = 2;
    const int STEPS = 5000;

    mt19937 gen(random_device{}());
	uniform_int_distribution<int> ran_pos(0, SIZE-1); //Get any random integer
	uniform_real_distribution<double> ran_u(0.0, 1.0); //Our uniform variable generator

    vector<int> ring(SIZE, 0);
    initial_condition(ring, NUM_ILLNESS, gen, ran_pos);
    //initial state
    for (size_t i = 0; i < ring.size(); i++){
        cout<<ring[i];        
    }
    cout << endl;

    for (int t = 0; t < STEPS; t++){
        vector<int> illness_index;
        for (size_t i = 0; i < ring.size(); i++){
            if (ring[i] == 1){
                illness_index.push_back(i);
            }
        }
        for (const auto i :illness_index){
            if (ran_u(gen) < ALPHA){
                if (ring[(i+1) % SIZE] != 2){
                    ring[(i+1) % SIZE] = 1;  
                }
                
            }
            if (ran_u(gen) < ALPHA){
                if (ring[(i-1+SIZE) % SIZE] != 2){
                ring[(i-1+SIZE) % SIZE] = 1;
                }
            }
            if (ran_u(gen) < BETA){
                ring[i] = 2;
            }
            
        }
    }
    for (size_t i = 0; i < ring.size(); i++){
        cout<<ring[i];        
        }
    return 0;
}

