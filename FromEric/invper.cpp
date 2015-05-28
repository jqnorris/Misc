#include <map>
#include <set>
#include <iostream>
#include <stdlib.h>

typedef std::pair<int, int> Pos;
typedef std::set<Pos> ExistenceMap;
typedef std::multimap<double, Pos> LocMap;

ExistenceMap    pos_exists;
LocMap          loc_world;

Pos get_pos(Pos start_pos, int direction) {
	switch (direction) {
		case 0: // up
            return std::make_pair(start_pos.first, start_pos.second+1);
		case 1: // down
            return std::make_pair(start_pos.first, start_pos.second-1);
		case 2: // left
            return std::make_pair(start_pos.first-1, start_pos.second);
		case 3: // right
            return std::make_pair(start_pos.first+1, start_pos.second);
    }
}

void invade_site(Pos invasion_site) {
    double      new_val;
    Pos         new_pos;
    
    for (unsigned int dir=0;dir<4;++dir) {
        // Check the sites in each direction from the current site
        new_pos = get_pos(invasion_site, dir);
        if (pos_exists.count(new_pos) == 0) {
            new_val = drand48();
            pos_exists.insert(new_pos);
            loc_world.insert(std::make_pair(new_val, new_pos));
        }
    }
}

void print_site_header(void) {
    std::cout << "x y val\n";
}

void print_site_data(Pos site, double val) {
    std::cout << site.first << " " << site.second << " " << val << "\n";
}

int main(int argc, char **argv) {
    Pos             site_loc;
    double          site_val;
	unsigned int	i, num_steps;

    num_steps = atoi(argv[1]);
    if (num_steps < 1) std::cerr << "Num steps must be greater than 0" << std::endl;
    
    srand48(time(NULL));
    
    site_loc = std::make_pair(0,0);
    invade_site(site_loc);
    print_site_header();
    print_site_data(site_loc, 0);
    
	for (i=0;i<num_steps;++i) {
        LocMap::iterator    it;
        it = loc_world.begin();
		site_val = it->first;
        site_loc = it->second;
        loc_world.erase(it);
        invade_site(site_loc);
        print_site_data(site_loc, site_val);
	}
}

