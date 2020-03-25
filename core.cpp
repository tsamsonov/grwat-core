#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <random>
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

    bool polfinder(const vector<int> &Day, const vector<int> &Mon, const vector<int> &Year,
                   const vector<float> &Qin, vector<int> &donep, int &iyY, int &ng, int lstart, parameters par) {

        auto polgrad1 = par.polgrad1;
        auto polgrad2 = par.polgrad2;
        auto polkol1 = par.polkol1;
        auto polkol2 = par.polkol2;
        auto polkol3 = par.polkol3;

        auto polkolMount1 = par.polkolMount1;
        auto polkolMount2 = par.polkolMount2;
        auto polgradMount = par.polgradMount;

        auto p = Day.size();

        for (int i = 0; i < 100; ++i) { // 1398
            vector<int> Sumdonep(4, 0);
            auto vsebylo = 0;

            for (int l = 0; l < p; ++l) {
                auto polQsum = 0;

                for (int j = 0; j < 3; ++j)
                    donep[j] = -1;

                if (Year[l] == donep[4]) {
                    if (Mon[l] >= par.polmon1 and Mon[l] <= par.polmon2 and Qin[l] != par.FlagGaps) { // 1417
                        auto dQ = 0;
                        for (auto ff = 1; ff <= polkol1; ff++)
                            dQ = dQ + (Qin[l + ff - 1] - Qin[l + ff]) / (100 * Qin[l + ff - 1] * polkol1);

                        if (dQ > -polgrad1)
                            donep[1] = -1;
                        else
                            donep[1] = 1;
                        Sumdonep[1] = Sumdonep[1] + 1;

                        dQ = 0;
                        for (auto ff = 1; ff <= polkol2; ff++)
                            dQ = dQ + (Qin[l + ff - 1] - Qin[l + ff]) / (100 * Qin[l + ff - 1] * polkol2);

                        if (dQ > 0)
                            donep[2] = -1;
                        else {
                            donep[2] = 1;
                            Sumdonep[2] = Sumdonep[2] + 1;
                        }

                        if (par.ModeMountain) {
                            donep[3] = 1;
                            for (auto ff = 1; ff <= polkolMount1; ff++) {
                                for (auto fff = ff; fff <= polkolMount2; fff++)
                                    polQsum = polQsum + Qin[l + fff];
                                if (polQsum / (Qin[l] * polkolMount2) < polgradMount)
                                    donep[3] = -1;
                            }

                            if (donep[3] == 1)
                                Sumdonep[3] = Sumdonep[3] + 1;
                        } else {
                            for (auto ff = 0; ff <= polkol3; ff++)
                                polQsum = polQsum + Qin[l + ff - 1];

                            if (polQsum / (Qin[l] * polkol3) < polgrad2)
                                donep[3] = -1;
                            else {
                                donep[3] = 1;
                                Sumdonep[3] = Sumdonep[3] + 1;
                            }
                        }

                        if (donep[1] == 1 and donep[2] == 1 and donep[3] == 1) {
                            iyY = lstart + l - 1;
                            donep[4] = Year[l] + 1;
                            ng = ng + 1;
                        }
                    }
                    // SEASONAL FLOOD IS FOUND
                    if (donep[1] == 1 and donep[2] == 1 and donep[3] == 1 and donep[4] == Year[p])
                        return true;
                }
            }

            // TODO: check whether this is really neeeded
            if (donep[1] == 1 and donep[2] == 1 and donep[3] == 1 and donep[4] == Year[p])
                return true;

            vsebylo = (Sumdonep[1] > 0 and Sumdonep[2] > 0 and Sumdonep[3] > 0) ? 1 : 0;

            auto Smallestdonep = std::min({Sumdonep[1], Sumdonep[2], Sumdonep[3]});

            std::random_device rdev;
            std::default_random_engine seed(rdev());
            std::uniform_real_distribution<> ran(0, 1);

            if (Sumdonep[1] == 0 or (vsebylo == 1 and Sumdonep[1] == Smallestdonep)) {
                auto choose = ran(seed);
                if (choose <= 0.5)
                    polgrad1 = polgrad1 - 0.1 * polgrad1;
                else if (polkol1 > 2)
                    polkol1 = polkol1 - 1;
                else
                    polgrad1 = polgrad1 - 0.1 * polgrad1;

            }

            if (Sumdonep[2] == 0 or (vsebylo == 1 and Sumdonep[2] == Smallestdonep)) {
                polkol2 = polkol2 - 1;
            }

            if (Sumdonep[3] == 0 or (vsebylo == 1 and Sumdonep[3] == Smallestdonep)) {
                auto choose = ran(seed);
                if (par.ModeMountain) {
                    if (choose <= 0.2) {
                        polkolMount1 = polkolMount1 - 5;
                    } else if (choose > 0.2 and choose <= 0.6) {
                        if (polkolMount2 > 1)
                            polkolMount1 = polkolMount1 - 1;
                        else
                            polgradMount = polgradMount - 0.1 * polgradMount;
                    } else {
                        polgradMount = polgradMount - 0.1 * polgradMount;
                    }
                } else {
                    if (choose <= 0.5) {
                        polgrad2 = polgrad2 - 0.1 * polgrad2;
                    } else if (polkol3 > polkol3 / 2) {
                        polkol3 = polkol3 - 5;
                    } else {
                        polgrad2 = polgrad2 - 0.1 * polgrad2;
                    }
                }
            }

        }

        return false; // SEASONAL FLOOD NOT FOUND

    }

    void separate(vector<int> Day, vector<int> Mon, vector<int> Year,
                  vector<float> Qin, vector<float> Tin, vector<float> Pin,
                  parameters par) {

        // detect gaps in data
        map<int, int> FactGapsin;
        int i = 0;
        for (auto it = Qin.begin(); it != Qin.end(); ++it) {
            if (*it == par.FlagGaps) {
                int k = 0;
                while (it != Qin.end()) {
                    if (*it != par.FlagGaps) break;
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

            if (Qin[l] == par.FlagGaps) { // 185
                if (Year[l] != y) {
                    NumGapsY[y] = NumGaps;
                    y = Year[l];
                }
                NumGaps++;
            }

            if (Year[l] > donep[4]) { // 190
                if (NumGapsY[Year[l] - 1] >=30) {
                    if (ng > 1)
                        iy[ng - 1] = -99;

                    YGaps[ng] = 1;
                    YGaps[ng - 1] = 1;
                    ng = ng + 1;
                    NumGaps = 0;
                    donep[4] = Year[l];
                } else {
                    auto hh = 0;
                    while (iy[ng - hh] < 0)
                        hh++;

                    auto begin = iy[ng - hh] + 300;
                    auto lengthcrop = l - begin + 1;
                    auto end = begin + lengthcrop - 1;
                    vector<float> Qcrop(Qin.begin() + begin, Qin.begin() + end);
                    vector<int> Yearcrop(Year.begin() + begin, Year.begin() + end);
                    vector<int> Moncrop(Mon.begin() + begin, Mon.begin() + end);
                    vector<int> Daycrop(Day.begin() + begin, Day.begin() + end);

                    // POLFINDER
                    polfinder(Daycrop, Moncrop, Yearcrop, Qcrop, donep, iy[ng - 1], ng, iy[ng - hh] + 300, par);

                }
            }

            if (Year[l] == donep[4]) { //221
                if (Mon[l] >= par.polmon1 and Mon[l] <= par.polmon2 and Qin[l] != par.FlagGaps) { //223
                    auto dQ = 0;
                    auto proceed = true;
                    for (auto ff = 1; ff <= par.polkol1; ff++) {
                        if (Qin[l + ff] == par.FlagGaps or Qin[l + ff - 1] == par.FlagGaps) { // goto 8787
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
                            dQ = dQ + (Qin[l + ff - 1] - Qin[l + ff]) / (100 * Qin[l + ff - 1] * par.polkol1);
                        }
                    }

                    if (proceed) {
                        if (dQ > -par.polgrad1)
                            donep[1] = -1;
                        else
                            donep[1] = 1;

                        dQ = 0;
                        for (auto ff = 1; ff <= par.polkol2; ff++)
                            dQ = dQ + (Qin[l + ff - 1] - Qin[l + ff]) / (100 * Qin[l + ff - 1] * par.polkol2);

                        if (dQ > 0)
                            donep[2] = -1;
                        else
                            donep[2] = 1;

                        auto polQsum = 0;

                        if (par.ModeMountain) {
                            donep[3] = 1;
                            for (auto ff = 1; ff <= par.polkolMount1; ff++) {
                                for (auto fff = ff; fff <= par.polkolMount2; fff++)
                                    polQsum = polQsum + Qin[l + fff];
                                if (polQsum / (Qin[l] * par.polkolMount2) < par.polgradMount)
                                    donep[3] = -1;
                            }
                        } else {
                            for (auto ff = 0; ff <= par.polkol3; ff++)
                                polQsum = polQsum + Qin[l + ff - 1];

                            if (polQsum / (Qin[l] * par.polkol3) < par.polgrad2)
                                donep[3] = -1;
                            else
                                donep[3] = 1;
                        }
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

