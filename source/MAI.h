#ifndef MAI_H
#define MAI_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QJsonObject>

class  MAI: public QObject
{
    Q_OBJECT

public:
    explicit MAI(QObject *parent = nullptr);

    // Установка критериев и альтернатив
    void setCriteria(const QVector<QString>& criteria);
    void setAlternatives(const QVector<QString>& alternatives);

    // Установка парных сравнений
    void setCriteriaPairwiseComparison(int row, int col, double value);
    void setAlternativePairwiseComparison(int criterionIndex, int row, int col, double value);

    // Расчет весов
    bool calculateWeights();

    // Получение результатов
    QVector<double> getCriteriaWeights() const;
    QVector<QVector<double>> getAlternativeWeights() const;
    QVector<double> getFinalScores() const;

    // Работа с JSON
    bool saveToJson(const QString& filename);
    bool loadFromJson(const QString& filename);

private:
    // Вспомогательные методы
    bool calculateMatrixWeights(const QVector<QVector<double>>& matrix, QVector<double>& weights);
    void calculateFinalScores();

    // Данные
    QVector<QString> m_criteria;
    QVector<QString> m_alternatives ;
    QVector<QVector<double>> m_criteriaMatrix;
    QVector<QVector<QVector<double>>> m_alternativeMatrices;

    // Результаты
    QVector<double> m_criteriaWeights;
    QVector<QVector<double>> m_alternativeWeights;
    QVector<double> m_finalScores;
};

#endif // MAI_H

