#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <stack>
#include <cstddef>


using namespace std;

typedef int64_t ll;
const int64_t SIZE = 2e5 + 7;
const long double EPS = 1e-12;

vector <pair <char, float>> v;
stack <int> st;

struct Stack {
    char info;
    double num;
    Stack* next;
};

Stack* top1 = nullptr;
Stack* top2 = nullptr;
void push(Stack*& t, char elem, double ch) {
    Stack* p = new (Stack);
    p->info = elem;
    p->num = ch;
    p->next = t;
    t = p;
}

Stack* del(Stack*& t) {
    t = (*t).next;
    return t;
}

int pri(char ch) {
    if (ch == '(') {
        return 0;
    } else if (ch == '+' || ch == '-') {
        return 1;
    } else if (ch == '*' || ch == '/') {
        return 2;
    } else if (ch == '^' || ch == 'q') {
        return 3;
    } else if (ch == 's' || ch == 'c' ||
               ch == 't' || ch == 'l') {
        return 4;
    }
    return 0;
}

int err(string s) {
    int sk = 0;
    for (int i = 0; i < s.size(); i++) {
        if ((i == 0) &&
            (s[i] == '+' || s[i] == '*' || s[i] == '/' || s[i] == '^')) {
            return 11;
        }
        if ((i != s.size() - 1) &&
            (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^') &&
            (s[i + 1] == '+' || s[i + 1] == '-' || s[i + 1] == '*'
             || s[i + 1] == '/' || s[i + 1] == '^')) {
            return 11;
        }
        if (i == s.size() - 1 && (s[i] == '*' || s[i] == '+' || s[i] == '/' || s[i] == '-')) {
            return 11;
        }
        if (i < s.size() - 1 &&
            (s[i] == '*' || s[i] == '-' || s[i] == '+' || s[i] == '/' || s[i] == '^')
            && s[i + 1] == ')') {
            return 11;
        }
        if (i != 0 && s[i - 1] == '(' && s[i] == ')') {
            return 11;
        }
        if (s[i] == '(') {
            sk += 1;
        } else if (s[i] == ')') {
            sk -= 1;
        }
        if (sk < 0) {
            return 11;
        }
    }
    if (sk != 0) {
        return 11;
    }
    return 0;
}
int pr = 0;
int apply1() {
    double ch2 = (*top1).num;
    del(top1);
    double ch1 = (*top1).num;
    del(top1);
    char zn = (*top2).info;
    del(top2);
    if (zn == '+') {
        push(top1, '@', ch1 + ch2);
    } else if (zn == '-') {
        push(top1, '@', ch1 - ch2);
    } else if (zn == '*') {
        push(top1, '@', ch1 * ch2);
    } else if (zn == '^') {
        push(top1, '@', pow(ch1, ch2));
    } else if (zn == '/' && ch2 == 0) {
        return -1;
    } else if (zn == '/') {
        push(top1, '@', ch1 / ch2);
    }
    return 0;
}

int apply2() {
    double ch = (*top1).num;
    del(top1);
    char zn = (*top2).info;
    del(top2);
    if (zn == 't' && ch == 90) {
        return -1;
    }
    if (zn == 'l' && ch < EPS) {
        return -1;
    }
    if (zn == 'q' && ch < -EPS) {
        return -1;
    }
    if (zn == 's') {
        push(top1, '@', sin(ch));
    } else if (zn == 'c') {
        push(top1, '@', cos(ch));
    } else if (zn == 'q') {
        push(top1, '@', sqrt(ch));
    } else if (zn == 't') {
        push(top1, '@', tan(ch));
    } else if (zn == 'l') {
        push(top1, '@', log(ch));
    }
    return 0;
}
int calc(string s, double &ans) {
    s += "+0";
    int cnt = 0, cntdot = 0, flag = 0;
    if (err(s) == 11) {
        return -1;
    }
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ' ') {
            continue;
        }
        if ((s[i] >= 48 && s[i] <= 57) || s[i] == '.') {
            if (s[i] == '.') {
                flag = 1;
            }
            if (flag == 1) {
                cntdot += 1;
            }
            cnt += 1;
            if ((i == s.size() - 1 && s[i+ 1] != '.') || (s[i + 1] < 48 && s[i + 1] != '.') ||( s[i + 1] > 57 && s[i + 1] != '.')) {
                double ch = 0;
                int cnt2 = cnt;
                if (flag == 1) {
                    cnt2 = cnt - cntdot;
                }
                for (int j = i - cnt + 1; j <= i - cntdot; j++) {
                    cnt2 -= 1;
                    ch += pow(10, cnt2) * (s[j] - '0');
                }
                if (flag == 1) {
                    cnt2 = 0;
                    for (int j = i - cntdot + 2; j <= i; j++) {
                        cnt2 += 1;
                        ch += pow(0.1, cnt2) * (s[j] - '0');
                    }
                }
                push(top1, '@', ch);
                cnt = 0;
                cntdot = 0;
                flag = 0;
            }
            continue;
        }
        int skip = 0;
        if (i < s.size() - 3 &&
            s[i] == 's' && s[i + 1] == 'q'
            && s[i + 2] == 'r' && s[i + 3] == 't') {
            i += 1;
            skip = 3;
        } else if (i < s.size() - 2 &&
                   s[i] == 's' && s[i + 1] == 'i' && s[i + 2] == 'n') {
            skip = 3;
        } else if (i < s.size() - 1 &&
                   s[i] == 'l' && s[i + 1] == 'n') {
            skip = 2;
        } else if (i < s.size() - 2 &&
                   s[i] == 'c' && s[i + 1] == 'o' && s[i + 2] == 's') {
            skip = 3;
        } else if (i < s.size() - 2 &&
                   s[i] == 't' && s[i + 1] == 'g') {
            skip = 2;
        } else if (s[i] >= 'a' && s[i] <= 'z') {
            return -1;
        }
        if (s[i] == '(') {
            push(top2, s[i], 0.0);
            continue;
        }
        if (s[i] == ')') {
            while (top2 != nullptr && (*top2).info != '(') {
                if ((*top2).info == 's' || (*top2).info == 'q' || (*top2).info == 't'
                    || (*top2).info == 'l' || (*top2).info == 'c') {
                    int prove = apply2();
                    if (prove == -1) {
                        return -1;
                    }
                } else {
                    int prove = apply1();
                    if (prove == -1) {
                        return -1;
                    }
                }
            }
            del(top2);
        } else if (top2 == nullptr || pri((*top2).info) < pri(s[i])) {
            if ((s[i] == '-' && s[i - 1] == '(') || (s[i] == '-' && i == 0)) {
                push(top1, '@', 0.0);
            }
            push(top2, s[i], 0.0);
        } else if (top2 != nullptr && pri((*top2).info) >= pri(s[i])) {
            while (top2 != nullptr && pri((*top2).info) >= pri(s[i])) {
                if ((*top2).info == 's' || (*top2).info == 'q' || (*top2).info == 't'
                    || (*top2).info == 'l' || (*top2).info == 'c') {
                    int prove = apply2();
                    if (prove == -1) {
                        return -1;
                    }
                } else {
                    int prove = apply1();
                    if (prove == -1) {
                        return -1;
                    }
                }
            }
            push(top2, s[i], 0.0);
        }
        if (skip != 0) {
            i += skip - 1;
        }
    }
    while (top2 != nullptr) {
        if ((*top2).info == 's' || (*top2).info == 'q' || (*top2).info == 't'
            || (*top2).info == 'l' || (*top2).info == 'c') {
            int prove = apply2();
            if (prove == -1) {
                return -1;
            }
        } else {
            int prove = apply1();
            if (prove == -1) {
                return -1;
            }
        }
    }
    if (pr == 11) {
        return 0;
    }

    ans = (*top1).num;
    return -1;
}

