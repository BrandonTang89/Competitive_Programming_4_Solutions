/**Kattis - logo2
 * I hate computational geometry. This took damn long, intially i didn't want to brute force
 * the angles, but doing that proved to be less prone to bugs and what not. Also i had to 
 * adjust the EPS to 1e-8 rather than 1e-9, which was a bit of a pain to debug.
 * 
 * In the case of the query being a distance, we just run through everything, and skip the query
 * command. Then we find the length of the resulting vector. This works because addition of vectors
 * is commutative. Ie a + b + c + .. + q + .. + e + f = a + b + c + .. + e + f + q. We move the vector
 * of the query to the end of the sum and end with q = -(a + b + c + .. + e + f). 
 * 
 * In the case of the query being an angle, we just brute force try all angles...
 * 
 * Time: O(n*360), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
const ld EPS = 1e-8;

struct point {
    ld x, y;
    point() { x = y = 0; }
    point(ld _x, ld _y) : x(_x), y(_y) {}
};

// Vector Struct
struct vec {
    ld x, y;
    vec(ld _x, ld _y) : x(_x), y(_y) {}
    vec(point p1, point p2) : x(p2.x - p1.x), y(p2.y - p1.y) {}

    // Vector Operations
    vec operator+(const vec &v) const { return vec(x + v.x, y + v.y); }
    vec operator-(const vec &v) const { return vec(x - v.x, y - v.y); }
    vec operator*(const ld &r) const { return vec(x * r, y * r); }
    vec operator/(const ld &r) const { return vec(x / r, y / r); }

    // Length
    ld length() { return hypot(x, y); }

    // Length Square
    ld length_sq() { return x * x + y * y; }
};

// Counter Clockwise Rotation about Pivot which defaults to origin
ld DEG_to_RAD(ld d) { return d * M_PI / 180; }
ld RAD_to_DEG(ld r) { return r * 180 / M_PI; }

vec rotate(ld rad, vec v) {
    ld x = v.x;
    ld y = v.y;
    ld nx = x * cos(rad) - y * sin(rad);
    ld ny = x * sin(rad) + y * cos(rad);
    return vec(nx, ny);
}

int num_tc, n, query_type = 0;
string s;
string x;
vector<pair<string, string>> commands;
int main() {
    cin >> num_tc;

    for (int tc = 0; tc < num_tc; tc++) {
        cin >> n;
        commands.clear();
        for (int i = 0; i < n; i++) {
            cin >> s >> x;
            commands.push_back(make_pair(s, x));
            if (x == "?") {
                if (s == "lt") {
                    query_type = 3;
                } else if (s == "rt") {
                    query_type = 4;
                } else if (s == "fd") {
                    query_type = 1;
                } else if (s == "bk") {
                    query_type = 2;
                }
            }
        }

        if (query_type == 1 || query_type == 2) {
            vec direction = vec(point(0, 0), point(0, 1));  // toward positive y
            vec cur_vec = vec(point(0, 0), point(0, 0));
            for (int index = 0; index < n; index++) {
                if (commands[index].second == "?") {
                    continue;
                }
                if (commands[index].first == "lt") {
                    direction = rotate(DEG_to_RAD(stoi(commands[index].second) % 360), direction);
                    direction = direction / direction.length();
                } else if (commands[index].first == "rt") {
                    direction =
                        rotate(DEG_to_RAD(-(stoi(commands[index].second) % 360)), direction);
                    direction = direction / direction.length();
                } else if (commands[index].first == "fd") {
                    cur_vec = cur_vec + direction * stoi(commands[index].second);
                } else if (commands[index].first == "bk") {
                    cur_vec = cur_vec - direction * stoi(commands[index].second);
                }
            }
            cout << int(roundl(cur_vec.length())) << endl;

        } else {
            for (int theta = 0; theta < 360; theta++) {
                vec direction = vec(point(0, 0), point(0, 1));  // toward positive y
                vec cur_vec = vec(point(0, 0), point(0, 0));
                for (int index = 0; index < n; index++) {
                    if (commands[index].second == "?") {
                        if (commands[index].first == "lt") {
                            direction = rotate(DEG_to_RAD(theta), direction);
                            direction = direction / direction.length();
                        } else if (commands[index].first == "rt") {
                            direction = rotate(DEG_to_RAD(360 - theta), direction);
                            direction = direction / direction.length();
                        }
                        continue;
                    }

                    if (commands[index].first == "lt") {
                        direction =
                            rotate(DEG_to_RAD(stoi(commands[index].second) % 360), direction);
                        direction = direction / direction.length();
                    } else if (commands[index].first == "rt") {
                        direction =
                            rotate(DEG_to_RAD(-(stoi(commands[index].second) % 360)), direction);
                        direction = direction / direction.length();
                    } else if (commands[index].first == "fd") {
                        cur_vec = cur_vec + direction * stoi(commands[index].second);
                    } else if (commands[index].first == "bk") {
                        cur_vec = cur_vec - direction * stoi(commands[index].second);
                    }
                }
                // cout << cur_vec.x << " " << cur_vec.y << endl;
                if (fabs(cur_vec.x) < EPS && fabs(cur_vec.y) < EPS) {
                    cout << theta << endl;
                    break;
                }
            }
        }
    }

    return 0;
}