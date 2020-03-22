#include <vector>
#include <map>
#include <set>
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
                i += k;
            }
            i++;
        }

        // Initialize vectors

        set<int> years(Year.begin(), Year.end());
        auto nyears = years.size();

        vector<int> iy(nyears, -99); // indices of water resource years ends
        vector<int> ny(nyears, 0);
        vector<int> YGaps(nyears, 0);
        vector<int> donep(4, -1); // four criteria of seasonal discharge beginning
        map<int, int> NumGapsY;
        auto NumGaps = 0;
        auto y = Year[0];
        auto ng = 1; // number of the first year
        auto iy1 = 0;

        donep[4] = y;

        auto w = Qin.size();
        for (auto l = 0; l < w; l++){ // 177

            if (Qin[l] == p.FlagGaps) { // 185
                if (Year[l] != y) {
                    NumGapsY[y] = NumGaps;
                    y = Year[l];
                }
                NumGaps++;
            }

            if (Year[l] > donep[4]) { // 190
                if (NumGapsY[Year[l] - 1] >=30) {
                    if (ng > 1) {
                        iy[ng - 1] = -99;
                    }

                    YGaps[ng] = 1;
                    YGaps[ng - 1] = 1;
                    ng = ng + 1;
                    NumGaps = 0;
                    donep[4] = Year[l];
                } else {
                    auto hh = 0;
                    while (iy[ng - hh] < 0) {
                        hh++;
                    }

                    auto begin = iy[ng - hh] + 300;
                    auto lengthcrop = l - begin + 1;
                    auto end = begin + lengthcrop - 1;
                    vector<float> Qcrop(Qin.begin() + begin, Qin.begin() + end);
                    vector<float> Yearcrop(Year.begin() + begin, Year.begin() + end);
                    vector<float> Moncrop(Mon.begin() + begin, Mon.begin() + end);
                    vector<float> Daycrop(Day.begin() + begin, Day.begin() + end);

                    // POLFINDER

                }
            }

            if (Year[l] == donep[4]) { //221
                if (Mon[l] >= p.polmon1 and Mon[l] <= p.polmon2 and Qin[l] != p.FlagGaps) { //223
                    auto dQ = 0;
                    auto proceed = true;
                    for (auto ff = 1; ff <= p.polkol1; ff++) {
                        if (Qin[l + ff] == p.FlagGaps or Qin[l + ff - 1] == p.FlagGaps) { // goto 8787
                            if (donep[1] == 1 and donep[2] == 1 and donep[3] == 1) {
                                if (ng > 1) {
                                    iy[ng - 1] = l - 1;
                                } else {
                                    iy1 = l - 1;
                                }
                                donep[4] = Year[l] + 1; // search next seasona flood in the next year
                                if (l > 1 and NumGaps > 0) {
                                    YGaps[ng - 1] = 1;
                                    NumGaps = 0;
                                }
                                ng = ng + 1; // number of years
                            }
                            proceed = false;
                            break;
                        } else {
                            dQ = dQ + (Qin[l + ff - 1] - Qin[l + ff]) / (100 * Qin[l + ff - 1] * p.polkol1);
                        }
                    }

                    if (proceed) {

                    }
                }
            }
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

