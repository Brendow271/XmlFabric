#include "xml.h"

#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

struct TreeNode {
    std::string value;
    std::vector<std::shared_ptr<TreeNode>> children;

    TreeNode(const std::string& v) : value(v) {}

    void addChild(const std::string& v) {
        children.push_back(std::make_shared<TreeNode>(v));
    }
};

class XmlForest {
public:
    std::shared_ptr<TreeNode> root; //unique

    XmlForest() {
        root = std::make_shared<TreeNode>("ROOT");
    }

    void save(const std::string& filename) {
        std::ofstream file(filename);
        if (file.is_open()) {
            saveNode(file, root);
            file.close();
        }
    }

    void load(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            root = loadNode(file);
            file.close();
        }
    }

    void print() {
        printNode(root, 0);
    }

private:

    void saveNode(std::ostream& out, const std::shared_ptr<TreeNode>& node) {
        out << "<HEAD value=\"" << node->value << "\">" << std::endl;
        for (const auto& child : node->children) {
            saveNode(out, child);
        }
        out << "</HEAD>" << std::endl;
    }


    std::shared_ptr<TreeNode> loadNode(std::istream& in) {
        std::string line;
        std::getline(in, line); // Read <HEAD value="...">

        size_t start = line.find("\"") + 1;
        size_t end = line.find("\"", start);
        std::string value = line.substr(start, end - start);

        auto node = std::make_shared<TreeNode>(value);

        while (std::getline(in, line)) {
            if (line.find("</HEAD>") != std::string::npos) {
                return node;
            }
            else {
                node->children.push_back(loadNode(in));
            }
        }

        return node;
    }


    void printNode(const std::shared_ptr<TreeNode>& node, int depth) {
        for (int i = 0; i < depth; ++i) {
            std::cout << "  ";
        }
        std::cout << node->value << std::endl;
        for (const auto& child : node->children) {
            printNode(child, depth + 1);
        }
    }
};

int main() {
    XmlForest forestLoad;
    forestLoad.load("lab2.xml");
    forestLoad.print();

    XmlForest forest;

    // Add data to the forest
    forest.root->addChild("1");
    forest.print();
    forest.root->addChild("2");
    forest.print();
    forest.root->children[0]->addChild("11");
    forest.print();
    forest.root->children[1]->addChild("12");


    forest.save("lab3.xml");

    XmlForest forestLoad2;
    forestLoad2.load("lab2.xml");
    forestLoad2.print();



    return 0;
}