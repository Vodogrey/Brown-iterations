#ifndef CALCULATION_H
#define CALCULATION_H

#include <QVector>
#include <QObject>

#include <QDebug>


class calculation : public QObject
{
    Q_OBJECT

public:
    calculation();
    ~calculation();
    void Brown();

public slots:
    void setPayMatrix(QVector<QVector<int> > matrix);

protected:
    double findStratA(QVector<double> vec);
    double findStratB(QVector<double> vec);
    void getStart();

   double findMax(QVector<double> vec);
   double findMin(QVector<double> vec);

private:

    QVector<QVector<int> > pay_matrix;
    QVector<QVector<float> > game_matrix;
};

#endif // CALCULATION_H
