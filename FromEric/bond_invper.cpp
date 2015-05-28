#include <map>
#include <set>
#include <iostream>
#include <stdlib.h>

typedef std::pair<int, int> Pos;
typedef std::set<Pos> ExistenceMap;
typedef std::multimap<double, std::pair<Pos, unsigned int> > LocMap;

ExistenceMap    pos_exists;
LocMap          loc_world;

Pos get_pos(Pos start_pos, unsigned int direction) {
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

// Returns true if the site attached through this bond has already been invaded
bool invade_bond(Pos start_site, unsigned int direction) {
    double      new_val;
    Pos         invasion_site;
    
    invasion_site = get_pos(start_site, direction);
    if (pos_exists.count(invasion_site) > 0) return true;
    pos_exists.insert(invasion_site);
    
    for (unsigned int dir=0;dir<4;++dir) {
        // Set the bonds in each direction from the current site
        new_val = drand48();
        loc_world.insert(std::make_pair(new_val, std::make_pair(invasion_site, dir)));
    }
    
    return false;
}

void print_site_header(void) {
    std::cout << "x y dir val\n";
}

void print_site_data(Pos site, double val, unsigned int bond_dir) {
    std::cout << site.first << " " << site.second << " " << bond_dir << " " << val << "\n";
}

int main(int argc, char **argv) {
    Pos             bond_loc;
    double          bond_val;
	unsigned int	i, num_steps, bond_dir;
    bool            already_invaded;

    num_steps = atoi(argv[1]);
    if (num_steps < 1) std::cerr << "Num steps must be greater than 0" << std::endl;
    
    srand48(time(NULL));
    
    bond_loc = std::make_pair(0,0);
    pos_exists.insert(bond_loc);
    for (bond_dir=0;bond_dir<4;++bond_dir)
        loc_world.insert(std::make_pair(drand48(), std::make_pair(bond_loc, bond_dir)));
    print_site_header();
    
	for (i=0;i<num_steps;) {
        LocMap::iterator    it;
        it = loc_world.begin();
		bond_val = it->first;
        bond_loc = it->second.first;
        bond_dir = it->second.second;
        loc_world.erase(it);
        already_invaded = invade_bond(bond_loc, bond_dir);
        if (!already_invaded) {
            print_site_data(bond_loc, bond_val, bond_dir);
            i++;
        }
	}
}

