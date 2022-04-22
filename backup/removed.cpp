//bool minus_found = false;

// search for upwards thaws
//
//                        // Frosts
//                        for (unsigned pp = LocMax1 - HalfStZ; pp < Flex1; ++pp) {
//                            if (FlagsMinusTemp[pp]) {
//
//                                startPol[i] = Flex1;
//
//                                auto z = -log(Qin[Flex1] / Qin[LocMax1]) / (Flex1 - LocMax1);
//
//                                Qo = Qin[LocMax1]; // exp(-z * LocMax1);
//
//                                for (auto qq = start; qq < Flex1; ++qq) {
//                                        Qthaw[qq] = Qin[qq] - Qbase[qq];
//                                }
//
//                                for (auto qq = Flex1; qq < polend[i]; ++qq) {
//
//                                    if (auto qval = Qo * exp(-z * (qq-LocMax1)); qval >= Qbase[qq] and qval <= Qin[qq]) {
//                                        Qthaw[qq] = qval - Qbase[qq];
//                                    }
//                                    else {
//                                        break;
//                                    }
//
//                                }
//                                minus_found = true;
//                                break;
//                             }
//                        }

//
//static vector<double> pad_vector(const vector<double>& Qin, const int& padding) {
//    vector<double> Q(Qin.begin(), Qin.end()); {
//        Q.insert(Q.begin(), Q.begin() + 1, Q.begin() + padding + 1);
//        Q.insert(Q.end(), Q.end() - padding - 1, Q.end() - 1);
//        std::reverse(Q.begin(), Q.begin() + padding);
//        std::reverse(Q.end() - padding, Q.end());
//    }
//    return Q;
//}
