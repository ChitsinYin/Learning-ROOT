#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TKey.h>
#include <iostream>

void inspect_root_file(const char* file_path) {
    // 打开 ROOT 文件
    TFile* root_file = TFile::Open(file_path);
    if (!root_file || root_file->IsZombie()) {
        std::cerr << "Error: Unable to open file " << file_path << std::endl;
        return;
    }

    std::cout << "Inspecting file: " << file_path << "\n\n";

    // 获取文件中的所有键（Keys）
    TIter next(root_file->GetListOfKeys());
    TKey* key;
    while ((key = (TKey*)next())) {
        TObject* obj = key->ReadObj();
        if (obj->IsA() == TTree::Class()) {  // 检查对象是否为 TTree
            TTree* tree = (TTree*)obj;
            std::cout << "Found TTree: " << tree->GetName() << std::endl;
            std::cout << "----------------------------------------" << std::endl;

            // 获取树的所有分支
            TObjArray* branches = tree->GetListOfBranches();
            for (int i = 0; i < branches->GetEntries(); ++i) {
                TBranch* branch = (TBranch*)branches->At(i);
                const char* branch_name = branch->GetName();
                const char* branch_type = branch->GetClassName();  // 获取分支的数据类型

                // 处理基本数据类型
                if (!branch_type) {
                    TLeaf* leaf = branch->GetLeaf(branch_name);
                    if (leaf) {
                        branch_type = leaf->GetTypeName();  // 获取基本数据类型的名称
                    }
                    else {
                        branch_type = "unknown";
                    }
                }

                std::cout << "Branch: " << branch_name << " | Type: " << branch_type << std::endl;
            }
            std::cout << "\n";
        }
    }

    // 关闭文件
    root_file->Close();
}

// 主函数
void inspect_root() {
    const char* root_file_path = "data_A.4lep.root";  // 替换为你的 .root 文件路径
    inspect_root_file(root_file_path);
}