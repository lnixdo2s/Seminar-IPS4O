#include <iostream>
#include <algorithm>
#include <atomic>
#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <chrono> 
#include <ctime> 
#include <string>


#include "../extern/ips4o/include/ips4o/ips4o.hpp"

using namespace std;

class Sorting {
    public:
        vector<double> generateVector(int size);
        vector<double> generateVectorNormal(int size);
        vector<double> generateVectorPois(int size);
        vector<double> generateVectorBin(int size);
        vector<double> generateVectorChiSqr(int size);
        void sort(vector<double> v, int th, string s);
        void sortQuick(vector<double> v, string s);
        void sortQuickParallel(vector<double> v, int th, string s);
        void sortRun1();
        void sortRun2();
        void sortRun3();
        void sortRun4();
        void sortRun5();
};

class CSV {
    public:
        void initCSV();
        void writeToCSV(string a, string b, string c, string d);
};

vector<double> Sorting::generateVector(int size) {
    random_device r;
    default_random_engine gen(r());
    uniform_real_distribution<double> dist;
    vector<double> v(size);
    for (auto& e : v) {
        e = dist(gen);
    }
    return v;
}
vector<double> Sorting::generateVectorNormal(int size) {
    random_device r;
    default_random_engine gen(r());
    normal_distribution<double> dist;
    vector<double> v(size);
    for (auto& e : v) {
        e = dist(gen);
    }
    return v;
}
vector<double> Sorting::generateVectorPois(int size) {
    random_device r;
    default_random_engine gen(r());
    poisson_distribution<int> dist;
    vector<double> v(size);
    for (auto& e : v) {
        e = dist(gen);
    }
    return v;
}
vector<double> Sorting::generateVectorBin(int size) {
    random_device r;
    default_random_engine gen(r());
    binomial_distribution<int> dist;
    vector<double> v(size);
    for (auto& e : v) {
        e = dist(gen);
    }
    return v;
}
vector<double> Sorting::generateVectorChiSqr(int size) {
    random_device r;
    default_random_engine gen(r());
    chi_squared_distribution<double> dist;
    vector<double> v(size);
    for (auto& e : v) {
        e = dist(gen);
    }
    return v;
}
/**
 * @brief 
 * 
 * @param v 
 */
void Sorting::sort(vector<double> v, int th, string s) {
    CSV csv;
    // Using time point and system_clock 
    chrono::time_point<std::chrono::system_clock> start, end; 
  
    start = chrono::system_clock::now(); 

    ips4o::parallel::sort(v.begin(), v.end(), less<>{}, th);

    end = std::chrono::system_clock::now(); 
  
    chrono::duration<double> elapsed_seconds = end - start; 
    time_t end_time = std::chrono::system_clock::to_time_t(end); 
  
    csv.writeToCSV(s, to_string(th), to_string(v.size()), to_string(elapsed_seconds.count()));
}
void Sorting::sortQuick(vector<double> v, string s) {
    CSV csv;
    // Using time point and system_clock 
    chrono::time_point<std::chrono::system_clock> start, end; 
  
    start = chrono::system_clock::now(); 

    std::sort(v.begin(), v.end());

    end = std::chrono::system_clock::now(); 
  
    chrono::duration<double> elapsed_seconds = end - start; 
    time_t end_time = std::chrono::system_clock::to_time_t(end); 
  
    csv.writeToCSV(s, "1", to_string(v.size()), to_string(elapsed_seconds.count()));
}
void Sorting::sortRun1() {
    cout << "SortRun1 wird gestartet" << std::endl;
    Sorting s;
    cout << "[SR1] Feld wird erstellt" << std::endl;
    vector<double> v = s.generateVector(10000000);
    for (size_t i = 1; i <= 12; i++)
    {
        cout << "[SR1] Feld wird kopiert" << std::endl;
        vector<double> v1(v);
        cout << "[SR1] Feld wird sortiert" << std::endl;
        s.sort(v1, i, "ips4o - sweep threadnum");
    }
}
void Sorting::sortRun2() {
    cout << "SortRun2 wird gestartet" << std::endl;
    Sorting s;
    for (size_t i = 0; i < 25; i++)
    {
        cout << "[SR2] Feld wird erstellt" << std::endl;
        vector<double> v = s.generateVector(i * 1000000);
        cout << "[SR2] Feld wird sortiert" << std::endl;
        s.sort(v, 12, "ips4o - vector size");
    }
}
void Sorting::sortRun3() {
    cout << "[SR3] SortRun3 wird gestartet" << std::endl;
    Sorting s;
    for (size_t i = 1; i <= 12; i++)
    {
        cout << "[SR3] Feld wird erstellt" << std::endl;
        vector<double> v = s.generateVector(10000000);
        cout << "[SR3] Feld wird sortiert" << std::endl;
        s.sort(v, i, "ips4o - sweep threadnum sanity check");
    }
}
void Sorting::sortRun4() {
    cout << "[SR4] SortRun3 wird gestartet" << std::endl;
    Sorting s;

    for (size_t i = 1; i <= 10; i++)
    {
        cout << "[SR4] Feld wird erstellt" << std::endl;
        vector<double> v = s.generateVector(1000000);
        cout << "[SR4] Feld wird sortiert" << std::endl;
        s.sort(v, 1, "ips4o - distribution uniform");
    }
    for (size_t i = 1; i <= 10; i++)
    {
        cout << "[SR4] Feld wird erstellt" << std::endl;
        vector<double> v = s.generateVectorNormal(1000000);
        cout << "[SR4] Feld wird sortiert" << std::endl;
        s.sort(v, 1, "ips4o - distribution normal");
    }
        for (size_t i = 1; i <= 10; i++)
    {
        cout << "[SR4] Feld wird erstellt" << std::endl;
        vector<double> v = s.generateVectorChiSqr(1000000);
        cout << "[SR4] Feld wird sortiert" << std::endl;
        s.sort(v, 1, "ips4o - distribution chi squared");
    }
    /*
    for (size_t i = 1; i <= 10; i++)
    {
        cout << "[SR4] Feld wird erstellt" << std::endl;
        vector<double> v = s.generateVectorPois(1000000);
        cout << "[SR4] Feld wird sortiert" << std::endl;
        s.sort(v, 12, "ips4o - distribution poisson");
    }
    for (size_t i = 1; i <= 10; i++)
    {
        cout << "[SR4] Feld wird erstellt" << std::endl;
        vector<double> v = s.generateVectorBin(1000000);
        cout << "[SR4] Feld wird sortiert" << std::endl;
        s.sort(v, 12, "ips4o - distribution binomial");
    }
    */
}
void Sorting::sortRun5() {
    cout << "[SR5] SortRun5 wird gestartet" << std::endl;
    Sorting s;
    for (size_t i = 1; i <= 5; i++)
    {
        cout << "[SR5] Feld wird erstellt" << std::endl;
        vector<double> v = s.generateVector(25000000 * i);
        cout << "[SR5] Feld wird kopiert" << std::endl;
        vector<double> v2;
        copy(v.begin(), v.end(), back_inserter(v2));
        cout << "[SR5] Feld wird sortiert" << std::endl;
        s.sort(v, 1, "ips4o - seq");
        cout << "[SR5] Feld wird sortiert" << std::endl;
        s.sortQuick(v2, "quicksort - seq");
    }
}
void CSV::initCSV() {
    ofstream outputFile;
    remove("output.csv");
    outputFile.open("output.csv", ios_base::app);
    
    // write the file headers
    outputFile << "Algorithmus" << "Threads" << "Vektorgroeße" << "Zeit" << std::endl;
   
    // close the output file
    outputFile.close();
}
void CSV::writeToCSV(string a, string b, string c, string d) {
    ofstream outputFile;
    string filename = "output.csv";
    outputFile.open(filename, ios_base::app);
    
    // write the file headers
    outputFile << a << "," << b << "," << c << "," << d << std::endl;
   
    // close the output file
    outputFile.close();
}

int main(int argc, char** argv) {

    cout << "Starting.." << std::endl;
    CSV csv;
    csv.initCSV();
    Sorting s;

    s.sortRun1();

    //s.sortRun2();

    //s.sortRun3();

    //s.sortRun4();

    //s.sortRun5();
    cout << "Finished.." << std::endl;
    return 0;
}