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
