#pragma once
#include "xml.h"


class XMLResource {
public:
    static std::unique_ptr<XMLResource> create(const std::string& path);

    using iterator = TreeNode::iterator;

    void save(const std::string &filename);

    void print();

    void load(const std::string &path);

    void parse(const std::string &line);

    void forEachForest(std::function<void(TreeNode *)> callback);

    TreeNode::iterator begin();

    TreeNode::iterator end();

    TreeNode::iterator findByTag(const std::string &tag);

    TreeNode::iterator findByValue(const std::string &value);

    TreeNode::iterator add(std::string tag, std::string value, TreeNode::iterator iterPlace);

    bool erase(TreeNode::iterator it);

private:
    std::unique_ptr<xmlForest> xmlTree;
    XMLResource(const std::string &path);
};

