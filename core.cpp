#include <vector>
#include <string>
#include <iostream>
#include "csv.h"
using namespace std;

void separate(vector<int> polmon, int ss1, vector<int> polkol, int ss2, int prodspada, int nPav, int nZam, int nWin,
              int FlagGaps, int InterpolStep, double grad, double grad1, double kdQgr1, vector<double> polgrad, int ss3,
              double Pcr, double Tcr1, double Tcr2, double Tzam, double Twin, double SignDelta, double SignDelta1,
              double PavRate, int lenin, int leninmeteo, string outfileAllGrWat,
              string lenallGrWat, string outfileTotal, int lenTotal, string outfileparameters, int lenparameters,
              bool ModeMountain, double pgrad, string outfilepavs, int lenpavs, vector<int> polkolMount, int ss4,
              double polgradMount, double gradabs, int mome) {

    // Initialize vectors
    vector<int> iy(100, -99);
    vector<int> ny(100, 0);
    vector<int> Ygaps(100, 0);


    return;
}

void read_inputs(string infilehydro, string infilemeteo,
                 vector<int> &Day1,  vector<int> &Mon1,  vector<int> &Year1, vector<float> &Qin1,
                 vector<float> &Tin1, vector<float> &Pin1) {
    io::CSVReader<4, io::trim_chars<>, io::no_quote_escape<' '>> in(infilehydro);
//    in.read_header(io::ignore_extra_column, "day", "month", "year", "qin");
    int day, month, year;
    double qin;
    while(in.read_row(day, month, year, qin)){
        Day1.push_back(day);
        Mon1.push_back(month);
        Year1.push_back(year);
        Qin1.push_back(qin);
    }
}

int main() {
    cout << "Mamba Huyamba\n";

    vector<int> Day1;
    vector<int> Mon1;
    vector<int> Year1;
    vector<float> Qin1;
    vector<float> Tin1;
    vector<float> Pin1;

    read_inputs("in.txt", "inmeteo.txt", Day1, Mon1, Year1, Qin1, Tin1, Pin1);

    cout << Year1[0];
}

