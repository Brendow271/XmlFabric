

#include "XMLResource.h"

std::unique_ptr<XMLResource> XMLResource::create(const std::string& path){
    return std::unique_ptr<XMLResource>(new XMLResource(path));
};

XMLResource::XMLResource(const std::string& path): xmlTree(std::make_unique<xmlForest>(path)) {};

void XMLResource::parse(const std::string &xml) {
    return xmlTree->parse(xml);
};
void XMLResource::load(const std::string &path) {
    return xmlTree->load(path);
};
void XMLResource::save(const std::string &path) {
    return xmlTree->save(path);
};
void XMLResource::print() {
    return xmlTree->print();
};
void XMLResource::forEachForest(std::function<void(TreeNode *)> callback) {
    return xmlTree->forEachForest(callback);
};
TreeNode::iterator XMLResource::begin() {
    return xmlTree->begin();
};
TreeNode::iterator XMLResource::end() {
    return xmlTree->end();
};
TreeNode::iterator XMLResource::findByTag(const std::string& tag) {
    return xmlTree->findByTag(tag);
};
TreeNode::iterator XMLResource::findByValue(const std::string& tag) {
    return xmlTree->findByValue(tag);
};
TreeNode::iterator XMLResource::add(std::string &tag, std::string &value, TreeNode::iterator iterPlace) {
    return xmlTree->add(tag, value, iterPlace);
};
bool XMLResource::erase(TreeNode::iterator it) {
    return xmlTree->erase(it);
};

