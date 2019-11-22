#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"
#include "string.h"
#include "vector"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked(bool)),
            this, SLOT(yaochanwanguan()));

    connect(ui->pushButton_2, SIGNAL(clicked(bool)),
            this, SLOT(wulingaoshou()));

    connect(ui->pushButton_3, SIGNAL(clicked(bool)),
            this, SLOT(gangjintiegu()));

    connect(ui->pushButton_4, SIGNAL(clicked(bool)),
            this, SLOT(yishanlanlv()));

    connect(ui->pushButton_5,SIGNAL(clicked(bool)),
            this, SLOT(getFileName()));

    connect(ui->pushButton_6,SIGNAL(clicked(bool)),
            this, SLOT(ChangeFileVal()));
}

QString MainWindow::getVal(int offset,int num=0)
{
    auto nowAdress=(char*)lpMapAddress+offset;
    QString nowVal= QString::number(*(short int*)nowAdress+num,10);
    return nowVal;
}

void MainWindow::ShowVal()
{
    ui->lineEdit_14->setText(getVal(0x244));      //当前等级

    ui->lineEdit_2->setText(getVal(0x268));    //得到当前体力

    ui->lineEdit_3->setText(getVal(0x274));    //得到当前法力

    ui->lineEdit_4->setText(getVal(0x2C8,2));    //武力

    ui->lineEdit_5->setText(getVal(0x2D4));      //灵力

    ui->lineEdit_6->setText(getVal(0x2E0,9));      //防御

    ui->lineEdit_7->setText(getVal(0x2EC,3));      //身法

    ui->lineEdit_8->setText(getVal(0x2F8));      //吉运

    ui->lineEdit_9->setText(getVal(0x250));      //体力上限

    ui->lineEdit_10->setText(getVal(0x25C));      //法力上限

    auto nowMoneyAdress=(char*)lpMapAddress+0x28;          //金钱4bit，用不了那个函数
    QString nowMoney= QString::number(*(int*)nowMoneyAdress,10);
    ui->lineEdit_11->setText(nowMoney);

    /*auto nowNumAdress=(char*)lpMapAddress+0x6C2;          //物品数量1bit，用不了那个函数
    QString nowNum= QString::number(*(char*)nowNumAdress,10);
    ui->lineEdit_13->setText(nowNum);*/
}

void MainWindow::getFileName()
{
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Open rpg file"), "", tr("XianJian file (*.rpg)"));

    ui->lineEdit->setText(fileName);

    if(ui->lineEdit->text()=="")
    {
        return;
    }
    MapFile();
    ShowVal();
}

void MainWindow::MapFile()
{
    HANDLE hFile;
    hFile = CreateFileA(ui->lineEdit->text().toStdString().c_str(), //将选择的文件转为特定格式
        GENERIC_READ | GENERIC_WRITE, // open for reading
        FILE_SHARE_READ, // share for reading
        NULL, // no security
        OPEN_EXISTING, // existing file only
        FILE_ATTRIBUTE_NORMAL, // normal file
        NULL); // no attr. template
    //根据hFile，创建一个文件映射对象hMapFile
    HANDLE hMapFile;
    hMapFile = CreateFileMapping(hFile, // Current file handle.
        NULL, // Default security.
        PAGE_READWRITE, // Read/write permission.
        0, // Max. object size.
        0, // Size of hFile.
        NULL); // Name of mapping object.

    //根据hMapFile，获取到内存中的有效地址，该地址与文件直接关联

    lpMapAddress = MapViewOfFile(hMapFile, // Handle to mapping object.
        FILE_MAP_ALL_ACCESS, // Read/write permission
        0, // Max. object size.
        0, // Size of hFile.
        0);

    //操作内存内容，就是操作文件内容

    //lpMapAddress = (char*)lpMapAddress + 0x0000010;
    //*(char*)lpMapAddress = 0x99;
}

void MainWindow::yaochanwanguan()
{
    if(ui->lineEdit->text()=="")
    {
        return;
    }
    auto nowMoneyAdress=(int*)((char*)lpMapAddress+0x28);          //金钱4bit
    int n=999999;

    *nowMoneyAdress= (*nowMoneyAdress&0)|n;

    ShowVal();
}

void MainWindow::wulingaoshou()
{
    if(ui->lineEdit->text()=="")
    {
        return;
    }

    auto nowMoneyAdress=(short int*)((char*)lpMapAddress+0x2C8); //当前武力max
    *nowMoneyAdress= (*nowMoneyAdress&0)|9997;

    nowMoneyAdress=(short int*)((char*)lpMapAddress+0x2D4); //当前灵力max
    *nowMoneyAdress= (*nowMoneyAdress&0)|9999;

    nowMoneyAdress=(short int*)((char*)lpMapAddress+0x2E0); //当前防御max
    *nowMoneyAdress= (*nowMoneyAdress&0)|9990;

    nowMoneyAdress=(short int*)((char*)lpMapAddress+0x2EC); //当前身法max
    *nowMoneyAdress= (*nowMoneyAdress&0)|9996;

    nowMoneyAdress=(short int*)((char*)lpMapAddress+0x2F8); //当前吉运max
    *nowMoneyAdress= (*nowMoneyAdress&0)|9999;

    ShowVal();
}

void MainWindow::gangjintiegu()
{
    if(ui->lineEdit->text()=="")
    {
        return;
    }

    auto nowMoneyAdress=(short int*)((char*)lpMapAddress+0x244);//等级max
    *nowMoneyAdress= (*nowMoneyAdress&0)|99;

    nowMoneyAdress=(short int*)((char*)lpMapAddress+0x250); //最大血量max
    *nowMoneyAdress= (*nowMoneyAdress&0)|9999;

    nowMoneyAdress=(short int*)((char*)lpMapAddress+0x25C); //最大蓝量max
    *nowMoneyAdress= (*nowMoneyAdress&0)|9999;

    nowMoneyAdress=(short int*)((char*)lpMapAddress+0x268); //当前血量max
    *nowMoneyAdress= (*nowMoneyAdress&0)|9999;

    nowMoneyAdress=(short int*)((char*)lpMapAddress+0x274); //当前蓝量max
    *nowMoneyAdress= (*nowMoneyAdress&0)|9999;

    ShowVal();
}

void MainWindow::yishanlanlv()
{
    if(ui->lineEdit->text()=="")
    {
        return;
    }

    auto MoneyAdress=(int*)((char*)lpMapAddress+0x28);          //金钱4bit
    *MoneyAdress= (*MoneyAdress&0);

    auto nowMoneyAdress=(short int*)((char*)lpMapAddress+0x244);//等级max
    *nowMoneyAdress= (*nowMoneyAdress&0)|1;

    nowMoneyAdress=(short int*)((char*)lpMapAddress+0x250); //最大血量max
    *nowMoneyAdress= (*nowMoneyAdress&0)|100;

    nowMoneyAdress=(short int*)((char*)lpMapAddress+0x25C); //最大蓝量max
    *nowMoneyAdress= (*nowMoneyAdress&0)|25;

    nowMoneyAdress=(short int*)((char*)lpMapAddress+0x268); //当前血量max
    *nowMoneyAdress= (*nowMoneyAdress&0)|100;

    nowMoneyAdress=(short int*)((char*)lpMapAddress+0x274); //当前蓝量max
    *nowMoneyAdress= (*nowMoneyAdress&0)|25;

    nowMoneyAdress=(short int*)((char*)lpMapAddress+0x2C8); //当前武力max
    *nowMoneyAdress= (*nowMoneyAdress&0)|25;

    nowMoneyAdress=(short int*)((char*)lpMapAddress+0x2D4); //当前灵力max
    *nowMoneyAdress= (*nowMoneyAdress&0)|25;

    nowMoneyAdress=(short int*)((char*)lpMapAddress+0x2E0); //当前防御max
    *nowMoneyAdress= (*nowMoneyAdress&0)|25;

    nowMoneyAdress=(short int*)((char*)lpMapAddress+0x2EC); //当前身法max
    *nowMoneyAdress= (*nowMoneyAdress&0)|25;

    nowMoneyAdress=(short int*)((char*)lpMapAddress+0x2F8); //当前吉运max
    *nowMoneyAdress= (*nowMoneyAdress&0)|1;

    ShowVal();
}

void MainWindow::ChangeFileVal()
{
    if(ui->lineEdit->text()=="")
    {
        return;
    }

    if(ui->lineEdit_2->text()!=getVal(0x268)) //当前血量
    {
        auto nowMoneyAdress=(short int*)((char*)lpMapAddress+0x268);
        *nowMoneyAdress= (*nowMoneyAdress&0)|ui->lineEdit_2->text().toInt();
    }

    if(ui->lineEdit_3->text()!=getVal(0x274))//当前蓝量
    {
        auto nowMoneyAdress=(short int*)((char*)lpMapAddress+0x274);
        *nowMoneyAdress= (*nowMoneyAdress&0)|ui->lineEdit_3->text().toInt();
    }

    if(ui->lineEdit_9->text()!=getVal(0x250))//体力上限
    {
        auto nowMoneyAdress=(short int*)((char*)lpMapAddress+0x250);
        *nowMoneyAdress= (*nowMoneyAdress&0)|ui->lineEdit_9->text().toInt();
    }

    if(ui->lineEdit_10->text()!=getVal(0x25C))//法力上限
    {
        auto nowMoneyAdress=(short int*)((char*)lpMapAddress+0x25C);
        *nowMoneyAdress= (*nowMoneyAdress&0)|ui->lineEdit_10->text().toInt();
    }

    if(ui->lineEdit_4->text()!=getVal(0x2C8,2))//当前武力
    {
        auto nowMoneyAdress=(short int*)((char*)lpMapAddress+0x2C8);
        *nowMoneyAdress= (*nowMoneyAdress&0)|ui->lineEdit_4->text().toInt()-2;
    }

    if(ui->lineEdit_5->text()!=getVal(0x2D4))//当前灵力
    {
        auto nowMoneyAdress=(short int*)((char*)lpMapAddress+0x2D4);
        *nowMoneyAdress= (*nowMoneyAdress&0)|ui->lineEdit_5->text().toInt();
    }

    if(ui->lineEdit_6->text()!=getVal(0x2E0,9))//当前防御
    {
        auto nowMoneyAdress=(short int*)((char*)lpMapAddress+0x2E0);
        *nowMoneyAdress= (*nowMoneyAdress&0)|ui->lineEdit_6->text().toInt()-9;
    }

    if(ui->lineEdit_7->text()!=getVal(0x2EC,3))//当前身法
    {
        auto nowMoneyAdress=(short int*)((char*)lpMapAddress+0x2EC);
        *nowMoneyAdress= (*nowMoneyAdress&0)|ui->lineEdit_7->text().toInt()-3;
    }

    if(ui->lineEdit_8->text()!=getVal(0x2F8))//当前吉运
    {
        auto nowMoneyAdress=(short int*)((char*)lpMapAddress+0x2F8);
        *nowMoneyAdress= (*nowMoneyAdress&0)|ui->lineEdit_8->text().toInt();
    }

    if(ui->lineEdit_14->text()!=getVal(0x244))//当前等级
    {
        auto nowMoneyAdress=((char*)lpMapAddress+0x244);
        *nowMoneyAdress= (*nowMoneyAdress&0)|ui->lineEdit_14->text().toInt();
    }

    auto MoneyAdress=(char*)lpMapAddress+0x28;          //金钱4bit，用不了那个函数
    QString nowMoney= QString::number(*(int*)MoneyAdress,10);
    if(ui->lineEdit_11->text()!=nowMoney)//当前金钱
    {
        auto nowMoneyAdress=(int*)((char*)lpMapAddress+0x28);
        *nowMoneyAdress= (*nowMoneyAdress&0)|ui->lineEdit_11->text().toInt();
    }

    //添加物品
    auto nowAdress=(short int*)((char*)lpMapAddress+0x6C0);
    if(ui->comboBox->currentIndex()!=0)
    {
        bool nul;
        QString temp="0x003d";
        auto val=temp.toInt(&nul,16);

        while(*nowAdress!=0)
        {
            //注意！！此处没有测试物品栏的最大数目，默认添加在最后一个
            nowAdress=(short int*)nowAdress+3;
        }
        *nowAdress=(*nowAdress&0)|(val+ui->comboBox->currentIndex()-1); //val->003d
    }

    nowAdress=(short int*)nowAdress+1;

    if(ui->lineEdit_13->text()!="")//当前物品数量
    {
        *nowAdress= (*nowAdress&0)|ui->lineEdit_13->text().toInt();
    }

    ShowVal();
}

MainWindow::~MainWindow()
{
    delete ui;
}
