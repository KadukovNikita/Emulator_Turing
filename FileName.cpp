#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>

using namespace std;

//Исходные данные в файле info.txt:
//6 3
//ab
//bbbbbbbbbbbbbbbaaba
//-- - -- - -- -
//&L2 aR1 bR1
//-- - aL3 bL3
//-- - aR4 aR5
//& N0 aL4 aL4
//-- - bN0 bN0



class Machine_Turing
{
private:
    int CNT;
    int lines; int countvar, leng;
    vector <vector <string>> table_Var;
    map<char, vector<string>> mapsymb;
    char nothing = '&';
    string str;
    vector <char> band;
    vector <char> alphabet;
public:
    Machine_Turing() {
        CNT = 500;
        Init();
        Emulator();
    }
    pair<int, int> Zone()
    {
        int l, r;
        for (int i = 0; i < band.size(); ++i)
        {
            if (band[i] != nothing) {
                l = i;
                break;
            }
        }
        for (int i = band.size() - 1; i >= 0; --i)
        {
            if (band[i] != nothing) {
                r = i;
                break;
            }
        }
        return { l, r };
    }
    void Init()
    {
        ifstream inputFile("info.txt");
        string data;
        inputFile >> lines; inputFile >> countvar; inputFile >> str;

        for (int i = 0; i < str.size(); ++i)
            alphabet.push_back(str[i]);

        inputFile >> str;
        leng = str.size();

        for (int i = 0; i < CNT; ++i)
            band.push_back('&');
        for (int i = 0; i < str.size(); ++i)
            band.push_back(str[i]);
        for (int i = 0; i < CNT; ++i)
            band.push_back('&');

        table_Var.resize(lines);
        for (int i = 0; i < lines; ++i) table_Var[i].resize(countvar);

        for (int i = 0; i < lines; i++) {
            for (int j = 0; j < countvar; j++) {
                inputFile >> table_Var[i][j];
            }
        }

        for (int j = 0; j < countvar; j++) {
            vector<string>  prom;
            for (int i = 0; i < lines; i++) {
                prom.push_back(table_Var[i][j]);
            }
            if (j == 0) {
                mapsymb[nothing] = prom;
            }
            else {
                mapsymb[alphabet[j - 1]] = prom;
            }

        }
    }

    void Emulator()
    {
        int state = 1;
        int ukaz = 1;

        while (true)
        {

            pair<int, int> p2 = Zone();
            for (int i = min(ukaz + CNT, p2.first); i <= max(ukaz + CNT, p2.second); ++i)
            {
                if (i == ukaz + CNT) cout << " (" << state << ") ";
                cout << band[i];
            }

            cout << endl;

            if (!state) break;

            char ch = band[ukaz + CNT];
            band[ukaz + CNT] = mapsymb[band[ukaz + CNT]][state][0];
            if (mapsymb[band[ukaz + CNT]][state][1] == 'R') ukaz++;
            else if (mapsymb[band[ukaz + CNT]][state][1] == 'L') ukaz--;
            state = mapsymb[ch][state][2] - 48;

        }

        cout << endl << endl << "Результат: ";
        pair<int, int> p = Zone();
        int l = p.first; int r = p.second;

        for (int i = l; i <= r; ++i)
        {
            cout << band[i];
        }
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    new Machine_Turing();
    return 0;
}