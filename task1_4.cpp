#include <iostream>
#include <fstream>
#include <set>

struct Entry {
    int a, b, c;
    bool operator<(const Entry& other) const {
        if (a != other.a) return a < other.a;
        if (b != other.b) return b < other.b;
        return c < other.c;
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) return 0;

    std::ifstream file(argv[1]);
    int n;
    file >> n;

    std::set<Entry> s;
    for (int i = 0; i < n; i++) {
        Entry e;
        file >> e.a >> e.b >> e.c;
        s.insert(e);
    }

    std::cout << s.size() << "\n";
    for (const auto& e : s) {
        std::cout << e.a << " " << e.b << " " << e.c << "\n";
    }
}
