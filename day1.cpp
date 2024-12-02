#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>


using std::cout;
using std::string;
using std::cin;
using std::vector;


void readAndSplit(string& filename, vector<int>& a, vector<int>& b) {

    std::ifstream file(filename);

    if(!file.is_open()) {
        std::cerr << "Konnte nicht geöffnet werden";
        return;
    }

    string zeile;
    while(std::getline(file, zeile)) {
        std::stringstream ss(zeile);
        int val_1, val_2;

        if(ss >> val_1 >> val_2) {
            a.push_back(val_1);
            b.push_back(val_2);
            //std::cout << "Added to vector1: " << val_1 << ", vector2: " << val_2 << std::endl;
        } else {
            std::cerr << "Fehler" << std::endl;
        }
    }
    file.close();
}

int findDistance(vector<int> a, vector<int> b) {

std::sort(a.begin(),a.end());
std::sort(b.begin(),b.end());

long long dist = 0;

for(int i = 0; i < a.size(); i++) {
    dist += abs(a[i] - b[i]);
}

return dist;
}

int similarityScore(vector<int> a, vector<int> b) {

    int sum = 0;
    int temp = 0;

    for(int i = 0; i < a.size(); i++) {
        int check = a[i];
        for(int j = 0; j < b.size(); j++) {
            if(check == b[j]) {
                temp++;
            }
            
        }
        sum += check * temp;  
        temp = 0;
    }
return sum;
}

int main() {

string filename = "C:\\Users\\Jaron L\\Desktop\\Freizeit\\AdventOfCode\\Day1\\input.txt";

vector<int> list1;
vector<int> list2;


readAndSplit(filename, list1, list2);
int test = similarityScore(list1, list2);
long long erg = findDistance(list1, list2);

cout << "Task 1: " << erg << '\n';
cout << "Task 2: " << test << '\n';
}
