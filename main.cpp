#include <fstream>
#include <filesystem>
#include <string>

#include "Packer.h"

namespace fs = std::filesystem;

void txtMaker(const Config& cfg){
    auto left_skylines = cfg.left_sky_lines;
    auto right_skylines = cfg.right_sky_lines;
    auto boxes = cfg.packed_boxes;

    fs::path currentDir = fs::current_path();
    fs::path parentDir = currentDir.parent_path();
    fs::path dataDir = parentDir / "data";

    ofstream file(dataDir / "packed_boxes.txt");
    if(file.is_open()){
        for(auto box: boxes){
            file << box.width << ' ' << box.height << ' '
            << box.packed_center_pos.x << ' ' <<box.packed_center_pos.y << '\n';
        }
    }
    else{
        cout << "Error\n";
    }
}


int main() {
    std::cout << "Hello, World!" << std::endl;

    Packer          packer(40, 100);

    Box             test_box{5, 7};
    CandidatePos    test_cp1{0, 100, true, false};
    CandidatePos    test_cp2{40, 100, false, false};


    packer.packingBox(test_box, test_cp1);
    packer.packingBox(test_box, test_cp2);

    auto cfg = packer.getConfig();
    txtMaker(cfg);

    return 0;
}
