#include "main.hpp"

int main( int argc, char **arg ) {

    string comp = "./proc ";
    string passbuf = "./prun ";
    string edit = "./comp+ ";
    string name = arg[1];

    string pythonrun = "./parser "+name;
    edit = edit + name;
    comp = comp + arg[1];
    passbuf = passbuf + name;

    system(pythonrun.c_str());
    system(edit.c_str());
    system(comp.c_str());
    //system(passbuf.c_str());

    return 0;
}
