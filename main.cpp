#include "xml.h"
#include "XMLResource.h"

int main() {
    std::unique_ptr<XMLResource> xmlRes = XMLResource::create("..\\testTreeInput.xml");
    xmlRes->print();

    std::cout << std::endl;

    for (XMLResource::iterator iter = xmlRes->begin(); iter != xmlRes->end(); iter += 1) {
        std::cout << "tag: " << iter->getTag() << ", value: " << iter->getValue() << std::endl;
    }

    std::cout << std::endl;
    
    XMLResource::iterator iter1 = xmlRes->findByTag("age");
    std::cout << "The age is: " << iter1->getValue() << " value" << std::endl;

    XMLResource::iterator iter2 = xmlRes->findByValue("Igor");
    std::cout << "The Igor is: " << iter2->getTag() << " tag" << std::endl;

    XMLResource::iterator iter3 = xmlRes->findByTag("MeowVolume");
    xmlRes->add( "eyeColor", "Blue", iter3);

    XMLResource::iterator iter4 = xmlRes->findByTag("FirstName");
    xmlRes->erase(iter4);

    xmlRes->save("..\\testTreeOutput.xml");
    return 0;
}
