#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Skyline{
    int x{};
    int lower_y{};
    int upper_y{};
};

struct Pos{
    float x; float y;
};

struct CandidatePos{
    Pos position;

    bool left_wall;
    bool lower_corner;
};

struct Box{
    int width{};
    int height{};
    bool packed {false};
    Pos packed_center_pos{};
};

struct Config{
    vector<Skyline> left_sky_lines{};
    vector<Skyline> right_sky_lines{};

    vector<CandidatePos> CPs{};

    vector<Box> packed_boxes{};
};

class Packer {
private:
    Config cfg;
    int WIDTH;
    int HEIGHT;

public:
    Packer(int W, int H){
        Skyline left_wall{0, 0, H};
        Skyline right_wall{W, 0, H};

        cfg.left_sky_lines.push_back(left_wall);
        cfg.right_sky_lines.push_back(right_wall);

        cfg.packed_boxes.clear();

        WIDTH = W; HEIGHT = H;
    }
    Config getConfig() { return cfg; }

    void packingBox(Box target_box, CandidatePos CP){

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

    void updateSkyline(Box target_box, CandidatePos CP) {
        bool covered = false;
        vector<Skyline> temp;

        if (CP.left_wall) {
            if (CP.lower_corner) {
                int new_upper_y = int(CP.position.y) + target_box.height;
                int new_lower_y = int(CP.position.y);

                auto new_skyline = Skyline{int(CP.position.x) + target_box.width, new_lower_y, new_upper_y};
                for (auto sl: cfg.left_sky_lines) {

                    if (sl.lower_y == new_lower_y) {
                        temp.push_back(new_skyline);
                        covered = true; // to deal with covered skyline only
                    }
                    if (sl.lower_y >= new_upper_y and covered) covered = false;
                    if (sl.upper_y > new_upper_y and covered) temp.push_back(Skyline{sl.x, new_upper_y, sl.upper_y});// partially covered
                    if (!covered) temp.push_back(sl);
                }
            } else { // CP.upper_corner
                int new_upper_y = int(CP.position.y);
                int new_lower_y = int(CP.position.y) - target_box.height;

                auto new_skyline = Skyline{int(CP.position.x) + target_box.width, new_lower_y, new_upper_y};
                for (auto sl: cfg.left_sky_lines) {
                    if(sl.lower_y <= new_lower_y and new_lower_y < sl.upper_y){
                        covered = true;
                        sl.upper_y = new_lower_y;
                        temp.push_back(sl);
                        temp.push_back(new_skyline);
                    }
                    if(!covered) temp.push_back(sl);
                    if(sl.upper_y == new_upper_y and covered) covered = false;
                }
            }
            cfg.left_sky_lines = temp;
        }
        else{ // CP.right_corner
            if (CP.lower_corner) {
                int new_upper_y = int(CP.position.y) + target_box.height;
                int new_lower_y = int(CP.position.y);

                auto new_skyline = Skyline{int(CP.position.x) - target_box.width, new_lower_y, new_upper_y};
                for (auto sl: cfg.right_sky_lines) {

                    if (sl.lower_y == new_lower_y) {
                        temp.push_back(new_skyline);
                        covered = true; // to deal with covered skyline only
                    }
                    if (sl.lower_y >= new_upper_y and covered) covered = false;
                    if (sl.upper_y > new_upper_y and covered) temp.push_back(Skyline{sl.x, new_upper_y, sl.upper_y});// partially covered
                    if (!covered) temp.push_back(sl);
                }
            } else { // CP.upper_corner
                int new_upper_y = int(CP.position.y);
                int new_lower_y = int(CP.position.y) - target_box.height;

                auto new_skyline = Skyline{int(CP.position.x) - target_box.width, new_lower_y, new_upper_y};
                for (auto sl: cfg.right_sky_lines) {
                    if (sl.lower_y <= new_lower_y and new_lower_y < sl.upper_y) {
                        covered = true;
                        sl.upper_y = new_lower_y;
                        temp.push_back(sl);
                        temp.push_back(new_skyline);
                    }
                    if (!covered) temp.push_back(sl);
                    if (sl.upper_y == new_upper_y and covered) covered = false;
                }
            }
            cfg.right_sky_lines = temp;
        }
    }

    void generateCP(){
        cfg.CPs.clear();
        int prev_x;

        prev_x = WIDTH;
        for(auto sl : cfg.left_sky_lines){
            if(sl.x < prev_x) cfg.CPs.push_back(CandidatePos{
                float(sl.x), float(sl.lower_y), true, true});
            if(sl.x > prev_x) cfg.CPs.push_back(CandidatePos{
                float(prev_x), float(sl.lower_y), true, false});
            prev_x = sl.x;
        }
        cfg.CPs.push_back(CandidatePos{float(prev_x), float(HEIGHT), true, false});

        prev_x = 0;
        for(auto sl : cfg.right_sky_lines){
            if(sl.x > prev_x) cfg.CPs.push_back(CandidatePos{
                        float(sl.x), float(sl.lower_y), false, true});
            if(sl.x < prev_x) cfg.CPs.push_back(CandidatePos{
                        float(prev_x), float(sl.lower_y), false, false});
            prev_x = sl.x;
        }
        cfg.CPs.push_back(CandidatePos{float(prev_x), float(HEIGHT), false, false});

    }

};
