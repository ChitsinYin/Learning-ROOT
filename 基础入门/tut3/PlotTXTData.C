#include <iostream>
#include <fstream>
#include "TGraph.h"
#include "TCanvas.h"

void PlotTXTData() {
    // 创建 TGraph
    TGraph *gr = new TGraph();
    gr->SetMarkerStyle(2); // 设置数据点样式
    //gr->SetLineWidth(2);             // 设置连线宽度
    //gr->SetLineColor(kBlue);         // 设置连线颜色为蓝色
    gr->SetTitle("Magnitude of SN vs. Redshift; Redshift; Magnitude");

    // 打开 CSV 文件
    std::ifstream file("SNdata.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file SNdata.csv!" << std::endl;
        return;
    } else {
        std::cout << "File opened successfully!" << std::endl;
    }

    // 跳过第一行（标题行）
    std::string header;
    std::getline(file, header);
    std::cout << "Header: " << header << std::endl;

    // 读取数据并填充 TGraph
    double x, y;
    int pointCount = 0; // 记录成功读取的数据点数量
    while (file >> x >> y) {
        std::cout << "Read point: (" << x << ", " << y << ")" << std::endl;
        gr->SetPoint(gr->GetN(), x, y);
        pointCount++;
    }

    // 检查是否读取到数据
    if (pointCount == 0) {
        std::cerr << "Error: No valid data points found in the file!" << std::endl;
        return;
    }

    // 关闭文件
    file.close();

    // 创建 TCanvas 并绘制图形
    TCanvas *c1 = new TCanvas("c1", "SN Data Plot", 800, 600);
    gr->Draw("AP"); // "A" 表示绘制坐标轴，"P" 表示绘制数据点

    // 保存图像（可选）
    c1->SaveAs("SN_data_plot.png");
}