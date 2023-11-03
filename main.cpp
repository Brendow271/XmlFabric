#include "xml.h"

int main() {
    xmlForest forestLoad;
    forestLoad.load("testTree.xml");
    forestLoad.forEachForest([](TreeNode* node) {std:: cout << node->tag << std:: endl;});
    forestLoad.print();
    forestLoad.save("test.xml");
    return 0;
}
