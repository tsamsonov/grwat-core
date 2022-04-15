//bool minus_found = false;

// search for upwards thaws

//            for (auto p = nmax-2; p > startPol[i]; --p) {
//                unsigned FlexPrev = start;
//                if (p < Bend1) {
//                    if ((deltaQ[p] <= -Qin[nmax] * par.SignDelta) or ((deltaQ[p] + deltaQ[p-1]) <= -Qin[nmax] * par.SignDelta)) {
//                        for (auto pp = p; pp < nmax-2; ++pp) {
//                            if (deltaQ[pp] > 0) {
//                                Flex1 = pp;
//                                break;
//                            }
//                        }
//                    }
//
//                    if (Flex1 >= start) {
//                        for (auto u = Flex1; u > startPol[i]; --u) { // 602
//                            if ((deltaQ[u] <= (-Qin[nmax] * par.SignDelta * 0.5)) or ((deltaQ[u] + deltaQ[u - 1]) <= (-Qin[nmax] * par.SignDelta * 0.5))) {
//                                for (auto pp = u; pp < Flex1-1; ++pp) {
//                                    if (deltaQ[pp] > 0) {
//                                        FlexPrev = pp;
//                                    }
//                                }
//                            }
//                        } // 611
//
//                        if (FlexPrev > start) {
//                            LocMax1 = std::distance(Qin.begin() + FlexPrev, max_element(Qin.begin() + FlexPrev, Qin.begin() + Flex1)) + FlexPrev - 1;
//                        } else {
//                            LocMax1 = std::distance(Qin.begin() + start, max_element(Qin.begin() + start, Qin.begin() + Flex1)) + start;
//                        } // 617
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
//                    }
//
//                }
//
//                if (minus_found)
//                    break;
//            }
