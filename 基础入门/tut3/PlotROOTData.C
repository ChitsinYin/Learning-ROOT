#include <iostream>
#include <fstream>
#include "TGraph.h"
#include "TCanvas.h"

// 定义拟合函数
Double_t FitFunc(Double_t* x, Double_t* par) {
    Double_t z = x[0]; // 横轴值（红移 z）
    Double_t CoH = par[0]; // 拟合参数 [0], speed of light over H0

    // 计算 m 的值
    Double_t m = -24.3 + 5 * (log10(CoH * z));
    return m;
}

void PlotROOTData() {
    // 创建 TGraph
    TGraph *gr = new TGraph();
    gr->SetMarkerStyle(2); // 设置数据点样式
    gr->SetMarkerColor(kBlue); // 设置数据点颜色
    gr->SetTitle("SN: Magnitude vs. Redshift; Redshift; Magnitude");

    // 打开ROOT文件、定位并查询 entries
    TFile *input = new TFile("SNdata.root", "read");
    TTree* tree = (TTree*)input->Get("tree");

    double z, m;

    tree->SetBranchAddress("z", &z);
    tree->SetBranchAddress("m", &m);

    int entries = tree->GetEntries();

    std::cout << "Total entries: " << entries << std::endl;


    // 读取数据并填充 TGraph
    int pointCount = 0; // 记录成功读取的数据点数量
    for (int i = 0; i < entries; i++){
        tree->GetEntry(i); //读取第 i 个数据点
        std::cout << "Read point: (" << z << ", " << m << ")" << std::endl;
        gr->SetPoint(gr->GetN(), z, m);
        pointCount++;
    } 

    // 检查是否读取到数据
    if (pointCount == 0) 
    {
        std::cerr << "Error: No valid data points found in the file!" << std::endl;
        return;
    }

    // 创建 TF1 对象
    TF1* fit = new TF1("fit", FitFunc, 0.001, 1.5, 1);
    fit->SetParameter(0, 1e9); // 设置参数 [0] 的初始值（例如 CoH = 1e9）
    fit->SetParName(0, "CoH"); // 设置参数名称
    //fit->SetLineWidth(3) //设置拟合曲线宽度
    //同理可以设置曲线Color, Style

    // 创建 TCanvas 并绘制图形
    TCanvas *c1 = new TCanvas("c1", "SN Data Plot", 800, 600);
    c1->SetTickx();
    c1->SetTicky();
    c1->SetGridx();
    c1->SetGridy();
    gr->Draw("AP"); // "A" 表示绘制坐标轴，"P" 表示绘制数据点
    gr->Fit("fit","R"); // 拟合数据
    
    //添加数据、拟合曲线图例
    TLegend *leg = new TLegend(0.68,0.2,0.87,0.35);
    leg->AddEntry(gr, "Data points", "p");
    leg->AddEntry(fit, "Fit Function", "l");
    leg->Draw();

    //得到拟合参数
    double CoH = fit->GetParameter(0);

    //将估算的宇宙年龄文本插入图片
    // 格式化字符串（使用科学计数法）
    TString text = TString::Format("#splitline{Age of the universe:}{ #approx %.2e years}", 3 * CoH);

    // 创建 TLatex 对象
    TLatex *t = new TLatex(1.2,18.7,text);
    t->SetTextSize(0.033); // 设置文本大小
    t->SetTextAlign(22);  // 设置文本对齐方式（居中）
    //t->SetTextFont(42);    // 设置字体为标准字体
    t->Draw();

    // 保存图像（可选）
    c1->SaveAs("SN_Data_Fit.png");

    // 关闭文件
    input->Close();
}


    