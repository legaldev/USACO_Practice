/*
ID: luglian1
PROG: runround
LANG: C++
*/

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#define INPUT_FILE "runround.in"
#define OUTPUT_FILE "runround.out"

using namespace std;

void NextNumber(std::vector<int>& number, int Digits) {
    number[Digits - 1]++;
    for (int i = Digits - 1; i >= 0; i--) {
        if (number[i] == 10) {
            number[i] = 1;
            if (i == 0) {
                number.insert (number.begin(),1);
                return;
            } else 
                number[i - 1]++;
        }
    }
    return;
}

bool CheckElement(std::vector<int>::iterator first,
    std::vector<int>::iterator last, int val) {
    while (first < last) {
        if (*first == val) 
            return true;
        ++first;
    }
    return false;
}

void NextUniqueNumber(std::vector<int>& number) {
    std::vector<int> old = number;
    for (int i = 1; i < number.size(); ++i) {
        if (number[i] == 0) number[i]++;
        while (CheckElement (number.begin(),number.begin() + i,number[i])) {
            number[i]++;
            if (number[i] == 10) {
                number[i] = 1;
                NextNumber (number,i);
                i = 1;
                continue;
            }
        }
    }
    return;
}

bool IsRoundNumber(std::vector<int>& number) {
    std::vector<bool> used(10,false);
    for (int i = 0, pos = 0, val = number[0]; i < number.size(); i++) {
        pos = (pos + val) % number.size();
        val = number[pos];
        if (used[pos] == true) return false;
        used[pos] = true;
    }
    return true;
}

unsigned int NextRoundNumber(unsigned int number) {
    std::vector<int> digits;
    for (int i = 0, tens = 1; i <= 10; ++i, tens *= 10) {
        int partial = number / tens;
        if (partial == 0) break;
        partial %= 10;
        digits.push_back(partial);
    }
    std::reverse (digits.begin(),digits.end());
    NextNumber (digits,digits.size());
    NextUniqueNumber (digits);
    while (!IsRoundNumber(digits)) {
        NextNumber (digits,digits.size());
        NextUniqueNumber (digits);
    }
    number = 0;
    for (int i = 0; i < digits.size(); i++) 
        number = 10 * number + digits[i];
    return number;
}

int main(int argc, char *argv[]) {
    ifstream FileInput (INPUT_FILE);
    ofstream FileOutput (OUTPUT_FILE);
    unsigned int Number;
    FileInput >> Number;
    FileOutput << NextRoundNumber(Number) << "\n";
    return 0;
}