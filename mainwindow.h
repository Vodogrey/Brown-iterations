#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QLabel>
#include <QTableWidget>
#include <QVector>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QStringList>

#include "calculation.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    void GUI();
    void Buttons();
    void setNames();

signals:
    void setMatrix(QVector<QVector<int> >);

public slots:
    void buttonClicked();
    void setRows();
    void setCol();

private:
    QWidget *m_widget;
    QGridLayout *m_layout;
    QLineEdit *m_strategy_a;
    QLineEdit *m_strategy_b;
    QPushButton *m_pb_ok;

    QTableWidget *m_table_strategy;

    calculation *m_calc;

};

#endif // MAINWINDOW_H
