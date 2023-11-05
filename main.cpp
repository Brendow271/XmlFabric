#include "xml.h"
#include "XMLResource.h"

int main() {
    std::unique_ptr<XMLResource> resource = XMLResource::create("testTree.xml");

    return 0;
}
