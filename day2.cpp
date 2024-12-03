#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <sstream>


using std::cout;
using std::string;
using std::cin;
using std::vector;

void readAndSplit(string& filename, vector<int>& a) {

    std::stringstream ss(filename);
    int num;
    while (ss >> num) {
        a.push_back(num);
    }
}


int safeReports(vector<int>& a) {
    if (a.size() < 2) {
        return 0; 
    }

    bool isAscending = true;
    bool isDescending = true;

    for(size_t i = 1; i < a.size(); i++) {
        int diff = a[i] - a[i-1];
        if(abs(diff) < 1 || abs(diff) > 3) {
            return 0;
        }

        if(diff < 0) {
            isAscending = false;
        }

        if(diff > 0) {
            isDescending = false;
        }
    }

     if (!isAscending && !isDescending) {
        return 0;
    }

   return 1;
}

int safeReportsAdvanced(vector<int>& a) {
    if(safeReports(a)) {
        return 1;
    }

    for(size_t i = 0; i < a.size(); i++) {
        vector<int> aReduced;
        for(size_t j = 0; j < a.size(); j++) {
            if(j != i) {
                aReduced.push_back(a[j]);
            }
        }

        if (safeReports(aReduced)) {
            return 1; 
        }
    } 
    return 0; 
}


int main() {

    string input = "C:\\Users\\Jaron L\\Desktop\\Freizeit\\AdventOfCode\\Day2\\input.txt";
    std::fstream file(input);

    if (!file.is_open()) {
        std::cerr << "Fehler: Datei konnte nicht geöffnet werden." << std::endl;
        return 1;
    }

    string line;
    int sumSafeReports = 0;

     while (std::getline(file, line)) {
        vector<int> numbers; // Vektor für die aktuelle Zeile
        readAndSplit(line, numbers);

        /* Debug-Ausgabe: Zahlen der aktuellen Zeile
        cout << "Zahlen in der Zeile: ";
        for (const int& num : numbers) {
            cout << num << " ";
        }
        cout << std::endl;
    	*/
        // Safe Reports für diese Zeile berechnen
        //sumSafeReports += safeReports(numbers);
        sumSafeReports += safeReportsAdvanced(numbers);
    }

    file.close();

    cout << "Gesamtanzahl der sicheren Berichte: " << sumSafeReports << std::endl;
}
