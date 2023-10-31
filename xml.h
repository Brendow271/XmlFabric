#ifndef XMLFABRIC_XML_H
#define XMLFABRIC_XML_H
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class TreeNode {
public:
    std::string tag;
    std::string value;
    std::vector<std::unique_ptr<TreeNode>> children;

    TreeNode(std::string t, std::string v) : tag(std::move(t)), value(std::move(v)) {}
    void addChild(std::unique_ptr<TreeNode> v) {children.push_back(std::move(v));}
    std::string toString();
//    const std::string &getTag() const {
//        return tag;
//    }
//
//    const std::string &getValue() const {
//        return value;
//    }
//
//    const std::vector<std::unique_ptr<TreeNode>> &getChildren() const {
//        return children;
//    }
};

class  xmlForest {
public:
    std::unique_ptr<TreeNode> root; //unique
    xmlForest() = default;
    std:: string toStringForest(){return root->toString();}
    void save(const std::string& filename);
    void print();
    void load(const std::string& path);
    void parse(const std::string& line);

private:

    std::unique_ptr<TreeNode> root_node;
    std::string read_file(const std::string& path);
    std:: string getTag(const std::string& line, int& pos);
    std:: string getValue(const std::string& line, int& pos);
    std::unique_ptr<TreeNode> loadNode(const std::string& line, int& pos);
    void printNode(const std::unique_ptr<TreeNode>& node, int depth);
};


#endif //XMLFABRIC_XML_H
