#include "xml.h"

std::string TreeNode:: toString() {
    std::string str = "<" + tag + " " + value + ">";
    for (const auto &child: children) {
        str += child->toString();
    }
    str += "</" + tag + ">";
    return str;
}

void xmlForest:: save(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << toStringForest();
        file.close();
    }
}

void xmlForest:: print() {
    printNode(root, 0);
}

void xmlForest:: load(const std::string& path) {
    const std::string line = read_file(path);
    parse(line);
};

void xmlForest:: parse(const std::string& line) {
    int pos = 0;
    root_node = loadNode(line, pos);
};

std::string xmlForest:: read_file(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("File not found");
    }
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
};

std:: string xmlForest:: getTag(const std::string& line, int& pos)
{
    int end = 0;
    pos = line.find("<", pos) + 1;
    if (line[pos] == '/')
        end = line.find(">", pos);
    else
        end = line.find(" ", pos);
    std::string tag = line.substr(pos, end - pos);
    pos = end + 1;
    return tag;
}

std:: string xmlForest:: getValue(const std::string& line, int& pos)
{
    size_t startValue = line.find("\"") + 1;
    size_t endValue = line.find("\"", startValue);
    return line.substr(startValue, endValue - startValue);
}

std::unique_ptr<TreeNode> xmlForest:: loadNode(const std::string& line, int& pos) {

    std::string tag = getTag(line, pos);
    std::string value = getValue(line, pos);
    auto node = std::make_unique<TreeNode>(tag, value);
    std::string next_tag = getTag(line, pos);

    while ((next_tag != ("/" + tag)) && pos < line.size()) {
        pos -= next_tag.size() + 2;
        node->addChild(loadNode(line, pos));
        next_tag = getTag(line, pos);
    }
    return node;
}

void xmlForest:: printNode(const std::unique_ptr<TreeNode>& node, int depth) {
    for (int i = 0; i < depth; ++i) {
        std::cout << "\t";
    }
    std::cout << "<" + node->tag + " value=" + node->value + ">" << std::endl;
    for (const auto& child : node->children) {
        printNode(child, depth + 1);
    }
}
