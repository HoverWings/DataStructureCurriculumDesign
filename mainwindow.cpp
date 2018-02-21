#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_chooseStudentButton_clicked()
{
    /*
    QString strFile = QFileDialog::getOpenFileName(this,QStringLiteral("选择Excel文件"),"",tr("Exel file(*.xls *.xlsx)"));
    if (strFile.isEmpty())
    {
     return;
    }
    QAxObject excel("Excel.Application"); //加载Excel驱动
    excel.setProperty("Visible", false); //不显示Excel界面，如果为true会看到启动的Excel界面
    QAxObject* pWorkBooks = excel.querySubObject("WorkBooks");
    pWorkBooks->dynamicCall("Open (const QString&)", strFile);//打开指定文
    QAxObject* pWorkBook = excel.querySubObject("ActiveWorkBook");
    QAxObject* pWorkSheets = pWorkBook->querySubObject("Sheets");//获取工作表
    int nSheetCount = pWorkSheets->property("Count").toInt();  //获取工作表的数目
 */
    ReadExcel re;
    bool ok=re.openExcel(".\\FileCSV\\student.csv");
    qDebug()<<ok;

    ExcelEngine excel(QObject::tr(".\\FileCSV\\student.csv")); //创建
    excel.Open(); //打开

    /*
    int num = 0;
    for (int i=1; i<=10; i++)
    {
        for (int j=1; j<=10; j++)
        {
            excel.SetCellData(i,j,++num); //修改指定单元数据
        }
    }
    */

    QVariant data = excel.GetCellData(1,1); //访问指定单元格数据
    qDebug()<<data;
    excel.GetCellData(2,2);
    excel.GetCellData(3,3);
    excel.Save(); //保存
    excel.Close();
}


void MainWindow::on_loadStudentButton_clicked()
{

}



