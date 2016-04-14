#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    GUI();
    Buttons();
}

void MainWindow::GUI()
{
    m_layout = new QGridLayout();
    m_widget = new QWidget();
    m_pb_ok = new QPushButton("OK");

    m_strategy_a = new QLineEdit();
    m_strategy_b = new QLineEdit();

    m_table_strategy = new QTableWidget();


    m_layout->addWidget(m_strategy_a, 0,0,1,2);
    m_layout->addWidget(m_strategy_b, 1,0,1,2);
    m_layout->addWidget(m_pb_ok, 3,1,1,1);
    m_layout->addWidget(m_table_strategy,4,0,2,2);

    m_widget->setLayout(m_layout);

    this->setCentralWidget(m_widget);

    m_calc = new calculation();

}

void MainWindow::Buttons()
{
    connect(m_pb_ok, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(m_strategy_a, SIGNAL(textEdited(QString)), this, SLOT(setRows()));
    connect(m_strategy_b, SIGNAL(textEdited(QString)), this, SLOT(setCol()));
    connect(this, SIGNAL(setMatrix(QVector<QVector<int> >)), m_calc, SLOT(setPayMatrix(QVector<QVector<int> >)));
}


void MainWindow::buttonClicked()
{
    //qDebug() << "click" << m_table_strategy->item(1,1)->text().toInt();
    QVector<QVector<int> > temp;

    temp.resize(m_table_strategy->rowCount());

    for(int i = 0; i < m_table_strategy->rowCount(); i++) {
        temp[i].resize(m_table_strategy->columnCount());
        for(int j = 0; j < m_table_strategy->columnCount(); j++) {
           temp[i][j] = m_table_strategy->item(i,j)->text().toInt();
        }
    }
    emit setMatrix(temp);

}

void MainWindow::setRows()
{
   m_table_strategy->setRowCount(m_strategy_a->text().toInt());

   QStringList VertHeaders;

   for(int i = 0; i < m_table_strategy->rowCount(); i++) {
       VertHeaders << "A" + QString::number(i+1);
   }
   m_table_strategy->setVerticalHeaderLabels(VertHeaders);

}

void MainWindow::setCol()
{
    m_table_strategy->setColumnCount(m_strategy_b->text().toInt());

    QStringList HorisHeaders;


    for(int i = 0; i < m_table_strategy->columnCount(); i++) {
        HorisHeaders << "B" + QString::number(i+1);
    }

    m_table_strategy->setHorizontalHeaderLabels(HorisHeaders);
}
