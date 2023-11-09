#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>

using namespace std;

const int MAXPOPULATION = 100;
const int MAXGENERATIONS = 1000;
const double MUTATIONRATE = 0.1;

struct Item
{
    int itemweight;
    int itemvalue;
};

int allowedweight;
vector<Item> items;

vector<bool> Randomsolution()
{
    vector<bool> solution;
    for (int i = 0; i < items.size(); i++)
    {
        solution.push_back(rand() % 2);
    }
    return solution;
}

int Fitnessevaluation(const vector<bool>& solution, int& TW)
{
    int TV = 0;
    TW = 0;
    for (int i = 0; i < items.size(); i++)
    {
        if (solution[i])
        {
            TW = TW + items[i].itemweight;
            TV = TV + items[i].itemvalue;
        }
    }
    if (TW > allowedweight)
    {
        TV = 0;
    }
    return TV;
}

vector<bool> OnePC(const vector<bool>& Fparent, const vector<bool>& Secparent)
{
    vector<bool> newchild = Fparent;
    int Cpoint = rand() % items.size();
    for (int i = Cpoint; i < items.size(); i++)
    {
        newchild[i] = Secparent[i];
    }
    return newchild;
}

void Mutation(vector<bool>& solution)
{
    for (int i = 0; i < items.size(); i++)
    {
        if (rand() / (double)RAND_MAX < MUTATIONRATE)
        {
            solution[i] = !solution[i];
        }
    }
}

int main()
{
    srand(time(0));

    ifstream infile("knapsack_input.txt");

    int Testcount;
    infile>>Testcount;

    for (int t = 1; t <= Testcount; t++)
    {
        infile>>allowedweight;
        int Itemscount;
        infile>>Itemscount;
        items.resize(Itemscount);

        for (int i = 0; i < Itemscount; i++)
        {
            infile>>items[i].itemweight>>items[i].itemvalue;
        }

        vector<bool> bestSol;
        int bestV = 0;
        int bestW = 0;

        for (int g = 0; g < MAXGENERATIONS; g++)
        {
            vector<bool> solution = Randomsolution();
            int weight = 0;
            int value = Fitnessevaluation(solution, weight);

            if (value > bestV)
            {
                bestV = value;
                bestW = weight;
                bestSol = solution;
            }
        }

        cout<<"Test Case "<<t<<"\n";

        int SItems = 0;
        for (int i = 0; i < items.size(); i++)
        {
            if (bestSol[i])
            {
                SItems++;
            }
        }

        cout<<"Total value = "<<bestV<<"\n";
        cout<<"Total weight = "<<bestW<<"\n";

        cout<<"The number of selected items = "<<SItems<<"\n";
        for (int i = 0; i < items.size(); i++)
        {
            if (bestSol[i])
            {
               cout<<"Item " << i + 1<<": Weight = "<<items[i].itemweight<<" , Value = "<<items[i].itemvalue<<"\n";
            }
        }
        cout<<"\n";
    }

    infile.close();
    return 0;
}
