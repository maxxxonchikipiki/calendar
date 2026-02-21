#include <iostream>
#include <cstdlib>
#include <cctype>

namespace Calendar {
    const char* M_NAMES[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    
    const char* Q_HEADERS[] = {
        "January               February              March",
        "April                 May                   June",
        "July                  August                September",
        "October               November              December"
    };

    int calc_wd(int d, int m, int y) {
        int a = (14 - m) / 12;
        int y2 = y + 4800 - a;
        int m2 = m + 12 * a - 3;
        int j = d + (153 * m2 + 2)/5 + 365*y2 + y2/4 - y2/100 + y2/400 - 32045;
        return j % 7;
    }

    int month_len(int mi, int yv) {
        if (mi == 1 || mi == 3 || mi == 5 || 
            mi == 7 || mi == 8 || mi == 10 || mi == 12) {
            return 31;
        }
        if (mi == 2) {
            if ((yv % 400 == 0) || (yv % 4 == 0 && yv % 100 != 0)) {
                return 29;
            }
            return 28;
        }
        return 30;
    }

    void show_num(int cd, int md = 31) {
        if (cd > md) {
            std::cout << "  ";
        } else if (cd < 10) {
            std::cout << ' ' << cd;
        } else {
            std::cout << cd;
        }
    }

    void show_one(int mn, int yn) {
        std::cout << yn << '\n';
        std::cout << M_NAMES[mn - 1] << '\n';
        std::cout << "Su Mo Tu We Th Fr Sa\n";
        
        int so = (calc_wd(1, mn, yn) + 1) % 7;
        for (int i = 0; i < 3 * so; ++i) {
            std::cout << ' ';
        }
        
        int td = month_len(mn, yn);
        int cp = so;
        
        for (int dc = 1; dc <= td; ++dc) {
            show_num(dc);
            if (cp == 6) {
                std::cout << '\n';
                cp = 0;
            } else if (cp != 6 && dc != td) {
                std::cout << ' ';
                ++cp;
            } else if (cp != 6 && dc == td) {
                ++cp;
            }
        }
        
        if (cp != 0) {
            std::cout << '\n';
        }
    }

    void show_three(int qi, int yv, bool add_nl = false) {
        std::cout << Q_HEADERS[qi] << '\n';
        std::cout << "Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa\n";
        
        int m1 = 3 * qi + 1;
        int m2 = m1 + 1;
        int m3 = m2 + 1;
        
        int d1 = 1;
        int d2 = 1;
        int d3 = 1;
        int s1 = (calc_wd(1, m1, yv) + 1) % 7;
        int s2 = (calc_wd(1, m2, yv) + 1) % 7;
        int s3 = (calc_wd(1, m3, yv) + 1) % 7;
        
        int dim1 = month_len(m1, yv);
        int dim2 = month_len(m2, yv);
        int dim3 = month_len(m3, yv);
        
        for (int c = 0; c < 7; ++c) {
            if (c < s1) {
                std::cout << "   ";
            } else {
                show_num(d1, dim1);
                d1++;
                if (c != 6) {
                    std::cout << ' ';
                }
            }
        }
        
        std::cout << "  ";
        
        for (int c = 0; c < 7; ++c) {
            if (c < s2) {
                std::cout << "   ";
            } else {
                show_num(d2, dim2);
                d2++;
                if (c != 6) {
                    std::cout << ' ';
                }
            }
        }
        
        std::cout << "  ";
        
        for (int c = 0; c < 7; ++c) {
            if (c < s3) {
                std::cout << "   ";
            } else {
                show_num(d3, dim3);
                d3++;
                if (c != 6) {
                    std::cout << ' ';
                }
            }
        }
        
        std::cout << '\n';
        
        int cm = 1;
        int cdow = 1;
        
        while (d1 <= dim1 || d2 <= dim2 || d3 <= dim3) {
            if (cdow == 7 && cm == 3) {
                if (d3 <= dim3) {
                    show_num(d3, dim3);
                }
                d3++;
                std::cout << '\n';
                cm = 1;
                cdow = 1;
            } else if (cdow == 7) {
                if (cm == 1) {
                    show_num(d1, dim1);
                    d1++;
                } else {
                    show_num(d2, dim2);
                    d2++;
                }
                cdow = 1;
                cm++;
                std::cout << "  ";
            } else if (cm == 1 && d1 > dim1) {
                for (int i = 0; i < ((8 - cdow) * 3) + 1; ++i) {
                    std::cout << ' ';
                }
                cm++;
                cdow = 1;
            } else if (cm == 2 && d2 > dim2) {
                for (int i = 0; i < ((8 - cdow) * 3) + 1; ++i) {
                    std::cout << ' ';
                }
                cm++;
                cdow = 1;
            } else if (cm == 3 && d3 > dim3) {
                std::cout << '\n';
                cm = 1;
                cdow = 1;
            } else {
                if (cm == 1) {
                    show_num(d1, dim1);
                    if (!(d1 == dim1 && (d2 > dim2 || d3 > dim3))) {
                        std::cout << ' ';
                    }
                    cdow++;
                    d1++;
                } else if (cm == 2) {
                    show_num(d2, dim2);
                    if (!(d2 == dim2 && (d1 > dim1 && d3 > dim3))) {
                        std::cout << ' ';
                    }
                    cdow++;
                    d2++;
                } else if (cm == 3) {
                    show_num(d3, dim3);
                    if (d3 != dim3) {
                        std::cout << ' ';
                    }
                    cdow++;
                    d3++;
                }
            }
        }
        
        if (!(cm == 1 && cdow == 1)) {
            std::cout << '\n';
        }
        
        if (add_nl) {
            std::cout << '\n';
        }
    }
}

int main(int argc, char* argv[]) {
    using namespace Calendar;
    
    if (argc == 2) {
        int yi = std::atoi(argv[1]);
        std::cout << yi << '\n';
        show_three(0, yi, true);
        show_three(1, yi, true);
        show_three(2, yi, true);
        show_three(3, yi, false);
    } else if (argc == 3) {
        int mi = std::atoi(argv[1]);
        int yi = std::atoi(argv[2]);
        show_one(mi, yi);
    }
    
    return 0;
}

