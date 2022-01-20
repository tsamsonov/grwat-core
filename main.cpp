//
// Created by Timofey Samsonov on 25.06.2020.
//

#include "csv.h"
#include "grwat_core.cpp"
using namespace std;

void read_inputs(string infilehydro, string infilemeteo,
                 vector<int> &Day1,  vector<int> &Mon1,  vector<int> &Year1, vector<double> &Qin1,
                 vector<double> &Tin1, vector<double> &Pin1) {
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

void read_input(string infile,
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

//    double size = 3;

    read_input("/Volumes/Work/_grwat/2022/grwat_bug/input.txt",
                Day, Mon, Year, Qin, Tin, Pin);

    grwat::parameters p;

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

    for (auto value : Qgr) {
        cout << value << ' ';
    }

}
