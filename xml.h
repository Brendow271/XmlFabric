#pragma once
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <functional>

class TreeNode {
public:
    std::string tag;
    std::string value;
    std::vector<std::unique_ptr<TreeNode>> children;

    TreeNode(std::string t, std::string v) : tag(std::move(t)), value(std::move(v)) {}
    void addChild(std::unique_ptr<TreeNode> v) {children.push_back(std::move(v));}
    std::string toString(int depth);
    void forEach(std::function <void (TreeNode*)>  callback);
    std::vector<TreeNode*> getChilds();

    class iterator {
    public:
        explicit iterator(TreeNode* node);

        iterator& operator ++ ();
        iterator operator ++ (int);
        iterator& operator += (int n);
        TreeNode* operator * () const;

    private:
        std::vector<TreeNode*> nodes;
        int indCurNode;
    };

};

class  xmlForest {
public:

    xmlForest() = default;
    std:: string toStringForest(){return rootNode->toString(0);}
    void save(const std::string& filename);
    void print();
    void load(const std::string& path);
    void parse(const std::string& line);
    void forEachForest(std::function <void (TreeNode*)>  callback);

private:
    std::unique_ptr<TreeNode> rootNode;
    std::string readFile(const std::string& path);
    std:: string getTag(const std::string& line, int& pos);
    std:: string getValue(const std::string& line, int& pos);
    std::unique_ptr<TreeNode> loadNode(const std::string& line, int& pos);

};

