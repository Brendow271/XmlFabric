#include "xml.h"

std::string TreeNode:: toString(int depth) {
    std:: string tabStr = "";
    for (int i = 0; i < depth; ++i) {
        tabStr += "\t";
    }
    std::string str = tabStr + "<" + tag + " value=\""+ value + "\">\n";
    for (const auto &child: children) {
        str += child->toString(depth + 1);
    }
    str += tabStr + "</" + tag + ">\n";
    return str;
}

void TreeNode:: forEach(std::function <void (TreeNode*)>  callback) {
    for(const auto &child: children)
        child->forEach(callback);
    return callback(this);
}

std::vector<TreeNode*> TreeNode::getChilds() {
    std::vector<TreeNode*> vecChilds = {};
    for (const auto& child : children) {
        vecChilds.push_back(child.get());
        std::vector<TreeNode*> vecChildOfChilds = child->getChilds();
        vecChilds.insert(vecChilds.end(), vecChildOfChilds.begin(), vecChildOfChilds.end());
    }
    return vecChilds;
}

const std::string &TreeNode::getTag() const {
    return tag;
}

const std::string &TreeNode::getValue() const {
    return value;
}

TreeNode::iterator TreeNode::begin() {
    return TreeNode::iterator(this);
}

TreeNode::iterator TreeNode::end() {
    return TreeNode::iterator(nullptr);
}

TreeNode::iterator TreeNode::findByTag(const std::string &Tag) {
    if (this->tag == Tag)
        return begin();
    else{
        for(const auto &child: children)
        {
            iterator isFind(child->findByTag(Tag));
            if (isFind != end())
            {
                return isFind;
            }
        }
    }
    return end();
}

TreeNode::iterator TreeNode::findByValue(const std::string &Value) {
    if (this->value == Value)
        return begin();
    else{
        for(const auto &child: children)
        {
            iterator isFind(child->findByValue(Value));
            if (isFind != end())
            {
                return isFind;
            }
        }
    }
    return end();
}

const std::vector<std::unique_ptr<TreeNode>> &TreeNode::getChildren() const {
    return children;
}

bool TreeNode::erase(TreeNode::iterator iter, TreeNode* nodeParent) {

    for (auto &child: children) {

        if (iter == child.get()->end()) {
            return false;
        }

        if (*iter == child.get()) {
            // перемещение
            for (int i = 0; i < child->children.size(); i++) {
                nodeParent->addChild(std::move(child->children[i]));
            }
            //удаление
            std::vector<std::unique_ptr<TreeNode>> &vecParent = this->children;
            for (int i = 0; i < vecParent.size(); i++)
                if (vecParent[i].get() == child.get()) {
                    vecParent[i].reset();
                    vecParent.erase(vecParent.begin() + i);
                    break;
                }
            return true;
        }
        else
        {
            if (nodeParent == this){
                child->erase(iter, nodeParent);
            }
            else {
                child->erase(iter, child.get());
            }
        };
    }
}

TreeNode::iterator::iterator(TreeNode *node) {
    if (node) {
        nodes = node->getChilds();
        nodes.insert(nodes.begin(), node);
    }
    indCurNode = 0;
}

TreeNode::iterator &TreeNode::iterator::operator++() {
    *this += 1;
    return *this;
}

TreeNode::iterator TreeNode::iterator::operator++(int) {
    iterator temp(*this);
    ++(*this);
    return temp;
}

TreeNode::iterator &TreeNode::iterator::operator+=(int n) {
    indCurNode += n;
    if (indCurNode > nodes.size()) {
        indCurNode = nodes.size();
    }
    return *this;
}

TreeNode* TreeNode:: iterator:: operator*() const {
    if (nodes.empty() || indCurNode == nodes.size()) {
        return nullptr;
    }
    return nodes[indCurNode];
}

bool TreeNode::iterator::operator == (const iterator& other) const {
    return **this == *other;
}

bool TreeNode::iterator::operator != (const iterator& other) const {
    return !(*this == other);
}

TreeNode* TreeNode::iterator::operator -> () const {
    return **this;
};

void xmlForest:: save(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << toStringForest();
        file.close();
    }
}

void xmlForest:: print() {
    std:: cout << toStringForest();
}

void xmlForest:: load(const std::string& path) {
    const std::string line = readFile(path);
    parse(line);
}

void xmlForest:: parse(const std::string& line) {
    int pos = 0;
    rootNode = loadNode(line, pos);
}

void xmlForest:: forEachForest(std::function <void (TreeNode*)>  callback){
    rootNode->forEach(callback);
}

std:: string xmlForest:: readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("File not found");
    }
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

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
    size_t startValue = line.find("\"", pos) + 1;
    size_t endValue = line.find("\"", startValue);
    return line.substr(startValue, endValue - startValue);
}

std:: unique_ptr<TreeNode> xmlForest:: loadNode(const std::string& line, int& pos) {

    std::string tag = getTag(line, pos);
    std::string value = getValue(line, pos);
    auto node = std::make_unique<TreeNode>(tag, value);
    std::string nextTag = getTag(line, pos);

    while ((nextTag != ("/" + tag)) && pos < line.size()) {
        pos -= nextTag.size() + 2;
        node->addChild(loadNode(line, pos));
        nextTag = getTag(line, pos);
    }
    return node;
}
TreeNode::iterator xmlForest::begin() {
    return rootNode->begin();
};
TreeNode::iterator xmlForest::end() {
    return rootNode->end();
}

TreeNode::iterator xmlForest::findByTag(const std::string& tag) {
    return rootNode->findByTag(tag);
};
TreeNode::iterator xmlForest::findByValue(const std::string& value) {
    return rootNode->findByValue(value);
}

TreeNode::iterator xmlForest::add(std::string &tag, std::string &value, TreeNode::iterator iterPlace) {
    std:: unique_ptr<TreeNode> node(new TreeNode(tag,value));
    iterPlace->addChild(std:: move(node));
    return TreeNode:: iterator(node.get());
}

bool xmlForest::erase(TreeNode::iterator iter)
{
    if (*iter == rootNode.get()) {
        return false;
    }
    rootNode->erase(iter, rootNode.get());
}
