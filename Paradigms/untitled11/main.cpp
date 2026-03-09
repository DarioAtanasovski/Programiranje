#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


string compress(string text) {
    string compressed = "";
    int n = text.length();
    for (int i = 0; i < n; i++) {
        int count = 1;
        while (i < n - 1 && text[i] == text[i + 1]) {
            count++;
            i++;
        }
        compressed += to_string(count) + text[i];
    }
    return compressed;
}

void processFile(string inputPath, string outputPath, int key) {
    ifstream inFile(inputPath);
    if (!inFile.is_open()) {
        cout << "Greshka: Ne mozam da go najdam fajlot na: " << inputPath << endl;
        return;
    }

    string encodedText = "";
    char ch;
    while (inFile.get(ch)) {
        encodedText += (char)(ch + key);
    }
    inFile.close();

    string finalData = compress(encodedText);

    ofstream outFile(outputPath);
    if (outFile.is_open()) {
        outFile << finalData;
        outFile.close();
        cout << "Uspeshno enkodirano i kompresirano!" << endl;
        cout << "Rezultatot e vo: " << outputPath << endl;
    } else {
        cout << "Greshka: Ne mozam da kreiram izlezen fajl!" << endl;
    }
}

int main() {
    system("chcp 65001 > nul");


    string input = "C:\\Users\\user\\Desktop\\anna karenina.txt";
    string output = "C:\\Users\\user\\Desktop\\encoded.txt";

    int userKey;
    cout << "Vnesi kluch za enkodiranje (broj): ";

    if (!(cin >> userKey)) {
        cout << "Greshka: Vnesi samo brojki!" << endl;
        return 1;
    }

    processFile(input, output, userKey);

    return 0;
}