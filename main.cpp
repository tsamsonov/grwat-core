//
// Created by Timofey Samsonov on 25.06.2020.
//

#include "csv.h"
#include "grwat_core.cpp"
using namespace std;

void read_input(const string& infile,
                vector<int> &Day1,  vector<int> &Mon1,  vector<int> &Year1,
                vector<double> &Qin1, vector<double> &Tin1, vector<double> &Pin1) {

    io::CSVReader<6, io::trim_chars<>, io::no_quote_escape<' '>> input(infile);
    string day, month, year, qin, tin, pin;

    while(input.read_row(day, month, year, qin, tin, pin)){

        try {
            Day1.push_back(stoi(day));
        } catch(...) {
            Day1.push_back(NAN);
        }

        try {
            Mon1.push_back(stoi(month));
        } catch(...) {
            Mon1.push_back(NAN);
        }

        try {
            Year1.push_back(stoi(year));
        } catch(...) {
            Year1.push_back(NAN);
        }

        try {
            Qin1.push_back(stod(qin));
        } catch(...) {
            Qin1.push_back(NAN);
        }

        try {
            Tin1.push_back(stod(tin));
        } catch(...) {
            Tin1.push_back(NAN);
        }

        try {
            Pin1.push_back(stod(pin));
        } catch(...) {
            Pin1.push_back(NAN);
        }
    }
}

int main() {

    vector<int> Day;
    vector<int> Mon;
    vector<int> Year;
    vector<double> Qin;
    vector<double> Tin;
    vector<double> Pin;

    read_input("/Users/tsamsonov/GitHub/grwat/temp/input.txt",
                Day, Mon, Year, Qin, Tin, Pin);

    grwat::parameters p;

    p.mome = 11;
    p.grad = 1.5;
    p.grad1 = 7.0;
    p.kdQgr1 = 500.0;
    p.polmon1 = 3;
    p.polmon2 = 5;
    p.polkol1 = 10;
    p.polkol2 = 15;
    p.polkol3 = 30;
    p.polgrad1 = 4;
    p.polgrad2 = 2;
    p.prodspada = 40;
    p.nPav = 5;
    p.nZam = 5;
    p.nWin = 5;
    p.Pcr = 3;
    p.Tcr1 = 0.0;
    p.Tcr2 = 2.0;
    p.Tzam = -8.0;
    p.Twin = -1.0;
    p.SignDelta = 0.01;
    p.SignDelta1 = 0.0015;
    p.PavRate = 0.001;
    p.FlagGaps = NAN;
    p.InterpolStep = 15;
    p.gradabs = 1000.0;
    p.ModeMountain = false;
    p.pgrad = 2.0;
    p.polkolMount1 = 30;
    p.polkolMount2 = 5;
    p.polgradMount = 1.5;
    p.niter = 100;
    p.a = 0.975;
    p.k = 0.975;
    p.C = 0.05;
    p.aq = -0.5;
    p.padding = 0;
    p.passes = 3;
    p.filter = grwat::KUDELIN;

    auto n = Qin.size();

    vector<double> Qgr(n, 0);
    vector<double> Quick(n, 0);
    vector<double> Qpol(n, 0);
    vector<double> Qpav(n, 0);
    vector<double> Qthaw(n, 0);
    vector<double> Qpb(n, 0);
    vector<int> Type(n, 0);
    vector<int> Hyear(n, 0);

    grwat::separate(Year, Mon, Day, Qin, Tin, Pin, Qgr, Quick, Qpol, Qpav, Qthaw, Qpb, Type, Hyear, p);

}
