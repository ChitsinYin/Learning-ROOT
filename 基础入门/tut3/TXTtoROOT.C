void TXTtoROOT() {
    // 打开 CSV 文件
    std::ifstream file("SNdata.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file SNdata.csv!" << std::endl;
        return;
    }
    else {
        std::cout << "File opened successfully!" << std::endl;
    }

    // 跳过第一行（标题行）
    std::string header;
    std::getline(file, header);
    std::cout << "Header: " << header << std::endl;

    // 读取数据并填充 TGraph
    double z, m;

    TFile *output = new TFile("SNdata.root", "RECREATE");
    TTree *tree = new TTree("tree", "tree");

    tree->Branch("z", &z, "z/D");
    tree->Branch("m", &m, "m/D");

    int pointCount = 0; // 记录成功读取的数据点数量
    while (1) {
        file >> z >> m;

        if (file.eof()) break;

        tree->Fill();
        
        pointCount++;
    }

    // 检查是否读取到数据
    if (pointCount == 0) {
        std::cerr << "Error: No valid data points found in the file!" << std::endl;
        return;
    }

    //写入output 文件，并关闭两个文件
    output->Write( );
    output->Close( );

    file.close( );

    std::cout << pointCount << " data points written to SNdata.root." << std::endl;
}