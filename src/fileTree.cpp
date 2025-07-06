#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include <Windows.h>

namespace fs = std::filesystem;

class TreeNode {   
    public:
        std::vector<TreeNode*> children;
        std::string value;
        bool isDirectory;

        TreeNode(std::string value, bool isDirectory) {
            this->value = value;
            this->isDirectory = isDirectory;
        }

        ~TreeNode() {
            for(TreeNode* child: children) {
                delete child;
            }
        }

        void addNode(TreeNode* child) {
            this->children.push_back(child);
        }

        void printNodes() {
            for(TreeNode* child: children) {
                std::cout << child->value << std::endl;
            }
        }

        void printTree(const std::string& prefix, bool isLast = true) const {
            std::cout << prefix;
            if(!prefix.empty()) {
                std::cout << (isLast? "└──" : "├──");
            }
            std::cout << this->value << (isDirectory? "\\" : "") << std::endl;
            if(this->isDirectory) {
                for(int i = 0; i < this->children.size(); i++) {
                    std::string new_prefix = prefix + (isLast? "    " : "|   ");
                    this->children.at(i)->printTree(new_prefix, i==(this->children.size() - 1));
                }
            }
        }
};

TreeNode* buildTree(const fs::path& path) {
    TreeNode* node = new TreeNode(path.filename().string(), fs::is_directory(path));
    
    if(fs::is_directory(path)) {
        for(auto& file: fs::directory_iterator(path)) {
            TreeNode* childNode = buildTree(file.path());
            node->addNode(childNode); 
            //std::cout << typeid(file.path()).name() << std::endl;
        }
    }
    return node;
}

int main(int argv, char **argc) {
    SetConsoleOutputCP(CP_UTF8);
    if(argv != 2) {
        std::cout << "Invalid args smh" << std::endl;
        return -1;
    }
    fs::path path(argc[1]);
    if(!fs::exists(path)) {
        std::cout << "Fake path, u fraud" << std::endl;
    }
    TreeNode* root = buildTree(path);
    root->printTree("");
    delete root;
}