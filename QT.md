# QT学习笔记
## 窗口
```c++
QPushButton* btn = new QPushButton; //创建按钮对象
btn->setParent(this); //设置此按钮的依赖对象
btn->setText("第一个按钮"); //显示文本
QPushButton* btn2 = new QPushButton("第二个按钮",this); //按照控件大小创建按钮
resize(600,400); //重置窗口(按钮)大小
btn2->move(100,200); //移动按钮位置
setWindowTitle("第一个窗口"); //设置窗口名称
setFixedSize(600,400); //设置窗口固定大小
```
## 信号和槽
```c++
//connect(信号的发送者，发送的信号，信号的接收者，处理的槽函数(slot))
//信号:返回void 需要声明不需要实现 可以有参数可以重载
//槽:返回void 需要声明和实现 可以有参数可以重载 写在public中
//触发自定义信号：emit
//当自定义信号和槽出现重载，需要使用函数指针指向函数的地址
connect(btn,&QPushButton::clicked,this,&QWidget::close); //点击btn按钮 实现关闭窗口
//Qstring转为char * 
Qstring str;
str.toutf8().data();
//信号可以链接信号,信号可以链接信号,单个信号可以链接多个槽函数 多个信号可以链接同一个槽函数
```
## 窗口设置
```c++
QMenuBar* bar=menuBar(); //菜单栏创建 最多只能有1个
setMenuBar(bar); //将菜单栏放入窗口中
QMenu* filemenu=bar->addMenu("文件(F)"); //创建菜单
filemenu->addAction("新建"); //创建菜单项
filemenu->addSeparator(); //添加分割线
QAction* addopen= filemenu->addAction("打开");
filemenu->addAction("保存");
QToolBar* toolbar=new QToolBar(this); //工具栏创建 可以有多个
addToolBar(Qt::TopToolBarArea,toolbar); //将工具栏放入窗口中
toolbar->setAllowedAreas(Qt::LeftToolBarArea|Qt::RightToolBarArea); //只允许工具栏左右停靠
toolbar->setFloatable(false); //设置不允许浮动
toolbar->setMovable(false); //设置不允许移动(总开关)
toolbar->addAction("新建"); //添加工具项
toolbar->addAction(addopen);
QPushButton* btn=new QPushButton("view",this); //添加按钮控件
toolbar->addWidget(btn); //按钮控件放在工具栏内
QStatusBar* statusbar=statusBar(); //状态栏创建 最多有一个
setStatusBar(statusbar); //将状态栏放入窗口中
QLabel* label=new QLabel("提示信息",this); //添加标签控件
statusbar->addWidget(label); //标签控件放在状态栏内
QLabel* label1=new QLabel("右侧提示信息",this); //右侧添加标签控件
statusbar->addPermanentWidget(label1);
QPushButton* btn1=new QPushButton("view1",this); //添加按钮控件
statusbar->addWidget(btn1);
QDockWidget* dock=new QDockWidget("浮动",this); //添加铆接部件 可以有多个
addDockWidget(Qt::BottomDockWidgetArea,dock);
QTextEdit* edit=new QTextEdit(this);//设置中心部件 只能有1个
setCentralWidget(edit);
```
## 对话框
```c++
//对话框分为:
//模态对话框(不可以对其他窗口操作)
//非模态对话框(可以对其他窗口操作)
QDialog dlg(this); //模态对话框创建
dlg.resize(400,200);
dlg.exec();
QDialog *dlg2=new QDialog(this); //堆区创建避免一闪而过
dlg2->resize(200,300);
dlg2->show();
dlg2->setAttribute(Qt::WA_DeleteOnClose); //设置关闭此窗口时删除堆区对象
QMessageBox::critical(this,"critical","错误"); //消息对话框-错误对话框
//提问对话框 参数1 父亲 参数2 标题 参数3 提示内容 参数4 按键类型 参数5 默认关联回车按键 返回值为用户选择的按键
QMessageBox::question(this,"ques","提问"); //消息对话框-提问对话框
QMessageBox::warning(this,"warning","警告"); //消息对话框-警告对话框
```