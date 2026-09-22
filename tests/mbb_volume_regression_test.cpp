#include <fstream>
#include <iostream>
#include <vector>

#include "mbb.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Expected path to tetrahedron.obj\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input) {
        std::cerr << "Cannot open " << argv[1] << '\n';
        return 1;
    }

    std::vector<pt3> points(4);
    for (int i = 0; i < 4; i++) {
        char recordType;
        pt3 point;
        input >> recordType >> point.x >> point.y >> point.z;
        if (!input || recordType != 'v') {
            std::cerr << "Cannot read tetrahedron vertices\n";
            return 1;
        }
        points[i] = point;
    }

    std::vector<pt3> lowerBase(4);
    std::vector<pt3> upperBase(4);
    ftype volume = mbbApproximation(points, lowerBase, upperBase);

    if (volume <= 0 || volume > 8.000001L) {
        std::cerr << "Expected MBB volume <= 8, got " << volume << '\n';
        return 1;
    }

    return 0;
}
