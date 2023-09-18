#include <iostream>
#include <vector>

using namespace std;

struct skyline{
    int x{};
    int lower_y{};
    int upper_y{};
};

struct pos{
    float x; float y;
};

struct candidatePos{
    pos position;

    bool left_wall;
    bool lower_corner;
};

struct box{
    int width{};
    int height{};
    bool packed {false};
    pos packed_center_pos{};
};

struct config{
    vector<skyline> left_sky_lines{};
    vector<skyline> right_sky_lines{};
    vector<box> packed_boxes{};
};

class Packer {
private:
    config cfg;

public:
    Packer(int W, int H){
        skyline left_wall{0, 0, H};
        skyline right_wall{W, 0, H};

        cfg.left_sky_lines.push_back(left_wall);
        cfg.right_sky_lines.push_back(right_wall);

        cfg.packed_boxes.clear();
    }
    config getCFG() { return cfg; }

    void packingBox(box target_box, candidatePos CP){

        // transform CP to center position
        if(CP.left_wall)    target_box.packed_center_pos.x = CP.position.x + float(target_box.width)/2;
        else                target_box.packed_center_pos.x = CP.position.x - float(target_box.width)/2;
        if(CP.lower_corner) target_box.packed_center_pos.y = CP.position.y + float(target_box.height)/2;
        else                target_box.packed_center_pos.y = CP.position.y - float(target_box.height)/2;

        // update packed state
        target_box.packed = true;

        // add target box to cfg
        cfg.packed_boxes.push_back(target_box);

        // update skyline
        updateSkyline(target_box, CP);
    }

    void updateSkyline(box target_box, candidatePos CP){


    }



};
