void MassHist() {
    TTree *tree = new TTree("tree", "Hzz");

    const char *filepath="E:\\001Projects\\甲辰 秋\\粒子物理实验\\ROOT\\Tutorial\\tut1\\HzzMcSig.csv";
  \\改为自己电脑上HzzMcSig.csv 的地址

    tree->ReadFile(filepath, "mass/D:totalWeight/D");

    TH1F *hist = new TH1F("hist", "Higgs Mass Distribution;Mass/GeV;Counts", 70, 80, 150);

    tree->Draw("mass>>hist");

    TCanvas *c1 = new TCanvas("c1", "Mass Histogram", 800, 600);
    hist->Draw();

    c1->SaveAs("MCMassHist.png");
}