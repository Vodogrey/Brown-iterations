#include "calculation.h"

#define EPS 0.1
#define STARTSTRATEGY 0

calculation::calculation()
{

}

calculation::~calculation()
{

}

//матрица будет такого вида:
//
// тактика1 || строка по А(но подписана В?) || тактика2 || строка то В(но написана А) || Vmin || Vmax || Vstar
//
// как это работает
//
// тактика А выбирается по максивальному элементу в строке
// тактика В выбирается из минимального в этой строке и берется столбец
//
//
//
//


void calculation::Brown()
{
    int iteration = 1;
    double vStar;

    int stratA;
    int stratB;

    getStart();
    QVector<double> vec;
    do {
        game_matrix.resize(game_matrix.size()+1);
        game_matrix[iteration].resize(pay_matrix.size() + pay_matrix[0].size() + 5); // чтобы по столбцам попасть;
// поиск стратегии А
        vec.clear();
        for(int i = 1; i < pay_matrix.size()+1; i++) {
            vec.append(game_matrix[iteration-1][i]); // брать из игвовой матрицы
        }

        stratA = findStratA(vec);
//
//вывод стратегии А
        game_matrix[iteration][0] = stratA;
//вывод суммы за ход 1 игрока
        for(int i = 0; i < pay_matrix.size(); i++) {
            if(iteration >= 1) {
                game_matrix[iteration][i+1] = game_matrix[iteration - 1][i+1] + pay_matrix[stratA][i];
            }
            else {
                game_matrix[iteration][i+1] = game_matrix[iteration][i+1] + pay_matrix[stratA][i];
            }
        }

// поиск стратегии В
        vec.clear();
        for(int i = pay_matrix.size() + 2; i < pay_matrix.size() + 2 + pay_matrix[0].size(); i++) { // проверить тут
            vec.append(game_matrix[iteration-1][i]);
        }
        stratB = findStratB(vec);
// нашел

//вывод стратегии В
        game_matrix[iteration][pay_matrix.size() + 1] = stratB;
//вывод суммы за ход 2 игрока
        for(int i = 0; i < pay_matrix.size(); i++) {
                game_matrix[iteration][i+pay_matrix.size() + 2] = game_matrix[iteration - 1][i+pay_matrix.size() + 2]
                        + pay_matrix[i][stratB];
        }

// тут надо мин макс стар
        int min = findMin(vec);
        int max = findMax(vec);

        game_matrix[iteration][pay_matrix.size() + pay_matrix[0].size() + 2] = min;
        game_matrix[iteration][pay_matrix.size() + pay_matrix[0].size() + 3] = max;
        game_matrix[iteration][pay_matrix.size() + pay_matrix[0].size() + 4] = (max+min)/2;

        vStar = game_matrix[iteration][pay_matrix.size() + pay_matrix[0].size() + 4] -
                game_matrix[iteration - 1][pay_matrix.size() + pay_matrix[0].size() + 4];
///     /////
        iteration++;
    } while (vStar > EPS);
}

void calculation::setPayMatrix(QVector<QVector<int> > matrix)
{
    pay_matrix = matrix;
    qDebug() << pay_matrix.size() << pay_matrix[0].size();
    Brown();
}

double calculation::findStratA(QVector<double> vec)
{
    double max = 0;
    int pos = 0;
    for(int i = 0; i < vec.size(); i++) {
        if(vec.at(i) >= max) {
            max = vec.at(i);
            pos = i;
        }
    }
    return pos;
}

double calculation::findStratB(QVector<double> vec)
{
    double min = 99999999;
    int pos = 0;
    for(int i = 0; i < vec.size(); i++) {
        if(vec.at(i) <= min) {
            min = vec.at(i);
            pos = i;
        }
    }
    return pos;
}

double calculation::findMax(QVector<double> vec)
{
    double max = 0;
    for(int i = 0; i < vec.size(); i++) {
        if(vec.at(i) >= max) {
            max = vec.at(i);
        }
    }
    return max;
}
double calculation::findMin(QVector<double> vec)
{
    double min = 999999999;
    for(int i = 0; i < vec.size(); i++) {
        if(vec.at(i) <= min) {
            min = vec.at(i);
        }
    }
    return min;
}


void calculation::getStart()
{
    game_matrix.resize(game_matrix.size()+1);
    game_matrix[0].resize(pay_matrix.size() + pay_matrix[0].size() + 5); // чтобы по столбцам попасть;
    for(int i = 0; i < pay_matrix.size(); i++)
        game_matrix[0][0] = STARTSTRATEGY,
        game_matrix[0][i+1] = pay_matrix[STARTSTRATEGY][i];
// сделали для стратегии А, а надо еще для стратегии В
    QVector<double> vec;
    int stratB;
    vec.clear();
    for(int i = 0; i < pay_matrix[0].size(); i++) {
        vec.append(pay_matrix[i][STARTSTRATEGY]);
    }
    stratB = findStratB(vec);

    for(int i = 0; i < pay_matrix[0].size(); i++)
        game_matrix[0][pay_matrix.size() + 1] = stratB, // попадаем в столбец стратегии В
        game_matrix[0][i+pay_matrix.size() + 2] = pay_matrix[i][stratB];

// готово
}
