#include "XMLResource.h"

std::unique_ptr<XMLResource> XMLResource::create(const std::string& path){
    try {
        return std::unique_ptr<XMLResource>(new XMLResource(path));
    }
    catch (...){
        std :: cout << "Failed to create" << std :: endl << "Create default tree" << std :: endl;
    }
};

XMLResource::XMLResource(const std::string& path): xmlTree(std::make_unique<xmlForest>(path)) {};

void XMLResource::parse(const std::string &xml) {
    try{
        return xmlTree->parse(xml);
    }
    catch (...){
        std :: cout << "Failed to parse" << std :: endl;
    }
};
void XMLResource::load(const std::string &path) {
    try{
        return xmlTree->load(path);
    }
    catch (...){
        std :: cout << "Failed to load" << std:: endl;
    }

};
void XMLResource::save(const std::string &path) {
    try{
        return xmlTree->save(path);
    }
    catch (...){
        std:: cout << "Failed to save" << std :: endl;
    }

};
void XMLResource::print() {
    return xmlTree->print();
};
void XMLResource::forEachForest(std::function<void(TreeNode *)> callback) {
    auto& saveTree = xmlTree;
    try {
        xmlTree->forEachForest(callback);
    }
    catch (...){
        std:: cout << "Something brake" << std:: endl;
        xmlTree.reset(saveTree.get());
    }
};
TreeNode::iterator XMLResource::begin() {
    return xmlTree->begin();
};
TreeNode::iterator XMLResource::end() {
    return xmlTree->end();
};
TreeNode::iterator XMLResource::findByTag(const std::string& tag) {
    try{
        return xmlTree->findByTag(tag);
    }
    catch (...){
        std:: cout << "Failed to find element by tag" << std:: endl;
    }
    return xmlTree->end();
};
TreeNode::iterator XMLResource::findByValue(const std::string& value) {
    try{
        return xmlTree->findByValue(value);
    }
    catch (...){
        std:: cout << "Failed to find element by value" << std:: endl;
        return xmlTree->end();
    }
};
TreeNode::iterator XMLResource::add(std::string tag, std::string value, TreeNode::iterator iterPlace) {
    try{
        return xmlTree->add(tag, value, iterPlace);
    }
    catch (...){
        std::cout << "Failed to add new element in tree! " << std::endl;
        return xmlTree->end();
    }

};
bool XMLResource::erase(TreeNode::iterator it) {
    try{
        return xmlTree->erase(it);
    }
    catch (...){
        std:: cout << "Failed to erase element in tree! " << std::endl;
        return false;
    }

};

