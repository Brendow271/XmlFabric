#include "xml.h"

int main() {
    xmlForest forestLoad;
    forestLoad.load("lab3.xml");
    forestLoad.print();

    return 0;
}
