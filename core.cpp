#include <vector>
#include <map>
#include <iostream>
#include "csv.h"
using namespace std;

namespace grwat {
    struct parameters {
        int mome = 11;
        double grad = 1.0;
        double grad1 = 13.0;
        double kdQgr1 = 1500.0;
        int polmon1 = 1;
        int polmon2 = 5;
        int polkol1 = 5;
        int polkol2 = 15;
        int polkol3 = 25;
        double polgrad1 = 10;
        double polgrad2 = 6;
        int prodspada = 90;
        int nPav = 2;
        int nZam = 5;
        int nWin = 5;
        double Pcr = 0.2;
        double Tcr1 = 0.0;
        double Tcr2 = 2.0;
        double Tzam = -5.0;
        double Twin = -1.0;
        double SignDelta = 0.01;
        double SignDelta1 = 0.0015;
        double PavRate = 0.001;
        float FlagGaps = -999.0;
        int InterpolStep = 15;
        double gradabs = 1000.0;
        bool ModeMountain = false;
        double pgrad = 2.0;
        int polkolMount1 = 30;
        int polkolMount2 = 30;
        double polgradMount = 1.5;
    };

    void separate(vector<int> Day, vector<int> Mon, vector<int> Year,
                  vector<float> Qin, vector<float> Tin, vector<float> Pin,
                  parameters p) {

        // Initialize vectors
        vector<int> iy;
        vector<int> ny;
        vector<int> Ygaps;
        vector<int> NumGapsY;

        vector<int> donep(4, -1); // four criteria of seasonal discharge beginning

        // detect gaps in data
        map<int, int> FactGapsin;
        int i = 0;
        for (auto it = Qin.begin(); it != Qin.end(); ++it) {
            if (*it == p.FlagGaps) {
                int k = 0;
                while (it != Qin.end()) {
                    if (*it != p.FlagGaps) break;
                    k++;
                    it++;
                }
                FactGapsin[i] = k;

                cout << i << endl;
                cout << FactGapsin[i] << endl;

                i += k;
            }
            i++;
        }




    }

    void read_inputs(string infilehydro, string infilemeteo,
                     vector<int> &Day1,  vector<int> &Mon1,  vector<int> &Year1, vector<float> &Qin1,
                     vector<float> &Tin1, vector<float> &Pin1) {
        io::CSVReader<4, io::trim_chars<>, io::no_quote_escape<' '>> inhydro(infilehydro);
        int day, month, year;
        double qin;
        while(inhydro.read_row(day, month, year, qin)){
            Day1.push_back(day);
            Mon1.push_back(month);
            Year1.push_back(year);
            Qin1.push_back(qin);
        }

        io::CSVReader<2, io::trim_chars<>, io::no_quote_escape<' '>> inmeteo(infilemeteo);
        double tin, pin;
        while(inmeteo.read_row(tin, pin)){
            Tin1.push_back(tin);
            Pin1.push_back(pin);
        }
    }
}

int main() {
    cout << "Mamba Huyamba\n";

    vector<int> Day;
    vector<int> Mon;
    vector<int> Year;
    vector<float> Qin;
    vector<float> Tin;
    vector<float> Pin;

    grwat::read_inputs("in.txt", "inmeteo.txt", Day, Mon, Year, Qin, Tin, Pin);

    grwat::parameters p;

    grwat::separate(Day, Mon, Year, Qin, Tin, Pin, p);

}

