#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TGraph.h"
#include "TCanvas.h"


void ListPlotRoot() {
    // 清理 ROOT 环境
    gROOT->Reset();

    // 定义存储数据的数组
    std::vector<double> f;    // 存储第一列数据
    std::vector<double> Omega; // 存储第二列数据

    // 打开 CSV 文件
    std::ifstream file("BBO.csv");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file!" << std::endl;
        return;
    }

    // 逐行读取文件
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;

        // 读取第一列数据
        if (std::getline(ss, token, ',')) {
            f.push_back(std::stod(token)); // 将字符串转换为 double
        }

        // 读取第二列数据
        if (std::getline(ss, token, ',')) {
            Omega.push_back(std::stod(token)); // 将字符串转换为 double
        }
    }

    // 关闭文件
    file.close();

    // 检查数据是否读取成功
    if (f.empty() || Omega.empty()) {
        std::cerr << "Error: No data read from file!" << std::endl;
        return;
    }

    // 创建 TGraph
    int npoints = f.size();
    TGraph *graph = new TGraph(npoints, f.data(), Omega.data());

    // 设置图形属性
    graph->SetTitle("Omega(f); f / Hz ; Omega"); // 设置标题和坐标轴标签
    graph->SetMarkerStyle(20); // 设置数据点样式
    graph->SetMarkerColor(kRed); // 设置数据点颜色
    graph->SetLineColor(kBlue); // 设置连线颜色

    // 绘制图形
    TCanvas *c1 = new TCanvas("c1", "f vs Omega", 800, 600);

    c1-> SetLogx( );
    c1-> SetLogy( );

    graph->Draw("APC"); // "A" 表示绘制坐标轴，"P" 表示绘制数据点，"C"给出插值曲线(可替换"L" 表示绘制连线)

    // 保存图像
    c1->SaveAs("Omega(f).png");
}
