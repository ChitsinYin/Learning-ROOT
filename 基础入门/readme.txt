tut0: 检视未知root 文件，列出其中的trees, branches (功能类似于 "new TBrowser" ) ，提供两种方法：inspect_root.C 直接运行得到目标文件的内容，需要每次修改文件地址；inspect_root.cpp 将文件作为input parameter, 在 ROOT 解释器里执行代码，而不需要每次修改代码，需要运行：
	root -l
	.L inspect_root.cpp
	inspect_root("data_D.4lep.root");  // 替换成目标文件路径
通过这两种方法可以容易

tut1: 对大约37万行质量数据绘制 histogram, 导入、读取".csv"格式文件、填充histogram 并绘图。

tut2: 绘制两列实验数据的函数关系，实验数据处理有用，读取并存储数据、绘制双对数图、设置绘图格式。

tut3: 原始数据为SNdata.txt 以空格分隔（由Mathematica 转过来），直接对原数据文件绘图(PlotTXTData.C); 将.txt 文件转换为.root 文件，用TTree 存储数据(TXTtoROOT.C); 对转换后用.root 格式存储的数据进行绘图、拟合、添加图例、添加文本(PlotROOTData.C)