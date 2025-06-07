#include "MAI.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <cmath>

MAI::MAI(QObject *parent) : QObject(parent) {}

void MAI::setCriteria(const QVector<QString>& criteria) {
    m_criteria = criteria;
    m_criteriaWeights.resize(criteria.size());
    m_criteriaMatrix.resize(criteria.size(), QVector<double>(criteria.size(), 1.0));
}

void MAI::setAlternatives(const QVector<QString>& alternatives) {
    m_alternatives  = alternatives;
    m_alternativeMatrices.resize(m_criteria.size());
    for (auto& matrix : m_alternativeMatrices) {
        matrix.resize(alternatives.size(), QVector<double>(alternatives.size(), 1.0));
    }
}

void MAI::setCriteriaPairwiseComparison(int row, int col, double value) {
    if (row >= 0 && row < m_criteriaMatrix.size() && col >= 0 && col < m_criteriaMatrix.size()) {
        m_criteriaMatrix[row][col] = value;
        m_criteriaMatrix[col][row] = 1.0 / value;
    }
}

void MAI::setAlternativePairwiseComparison(int criterionIndex, int row, int col, double value) {
    if (criterionIndex >= 0 && criterionIndex < m_alternativeMatrices.size() &&
        row >= 0 && row < m_alternativeMatrices[criterionIndex].size() &&
        col >= 0 && col < m_alternativeMatrices[criterionIndex].size()) {
        m_alternativeMatrices[criterionIndex][row][col] = value;
        m_alternativeMatrices[criterionIndex][col][row] = 1.0 / value;
    }
}

bool MAI::calculateWeights() {
    if (!calculateMatrixWeights(m_criteriaMatrix, m_criteriaWeights)) {
        return false;
    }

    m_alternativeWeights.resize(m_alternativeMatrices.size());
    for (int i = 0; i < m_alternativeMatrices.size(); ++i) {
        m_alternativeWeights[i].resize(m_alternatives .size());
        if (!calculateMatrixWeights(m_alternativeMatrices[i], m_alternativeWeights[i])) {
            return false;
        }
    }

    calculateFinalScores();
    return true;
}

QVector<double> MAI::getCriteriaWeights() const {
    return m_criteriaWeights;
}

QVector<QVector<double>> MAI::getAlternativeWeights() const {
    return m_alternativeWeights;
}

QVector<double> MAI::getFinalScores() const {
    return m_finalScores;
}

bool MAI::saveToJson(const QString& filename) {
    QJsonObject root;

    QJsonArray criteriaArray;
    for (const auto& criterion : m_criteria) {
        criteriaArray.append(criterion);
    }
    root["criteria"] = criteriaArray;

    QJsonArray criteriaMatrixArray;
    for (const auto& row : m_criteriaMatrix) {
        QJsonArray rowArray;
        for (double val : row) {
            rowArray.append(val);
        }
        criteriaMatrixArray.append(rowArray);
    }
    root["criteria_matrix"] = criteriaMatrixArray;

    QJsonArray alternativesArray;
    for (const auto& alternative : m_alternatives ) {
        alternativesArray.append(alternative);
    }
    root["alternatives"] = alternativesArray;

    QJsonArray alternativeMatricesArray;
    for (const auto& matrix : m_alternativeMatrices) {
        QJsonArray matrixArray;
        for (const auto& row : matrix) {
            QJsonArray rowArray;
            for (double val : row) {
                rowArray.append(val);
            }
            matrixArray.append(rowArray);
        }
        alternativeMatricesArray.append(matrixArray);
    }
    root["alternative_matrices"] = alternativeMatricesArray;

    QJsonDocument doc(root);
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }
    file.write(doc.toJson());
    file.close();
    return true;
}

bool MAI::loadFromJson(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull()) {
        return false;
    }

    QJsonObject root = doc.object();

    QJsonArray criteriaArray = root["criteria"].toArray();
    m_criteria.clear();
    for (const auto& item : criteriaArray) {
        m_criteria.append(item.toString());
    }

    QJsonArray criteriaMatrixArray = root["criteria_matrix"].toArray();
    m_criteriaMatrix.clear();
    for (const auto& rowItem : criteriaMatrixArray) {
        QJsonArray rowArray = rowItem.toArray();
        QVector<double> row;
        for (const auto& valItem : rowArray) {
            row.append(valItem.toDouble());
        }
        m_criteriaMatrix.append(row);
    }

    QJsonArray alternativesArray = root["alternatives"].toArray();
    m_alternatives .clear();
    for (const auto& item : alternativesArray) {
        m_alternatives .append(item.toString());
    }

    QJsonArray alternativeMatricesArray = root["alternative_matrices"].toArray();
    m_alternativeMatrices.clear();
    for (const auto& matrixItem : alternativeMatricesArray) {
        QJsonArray matrixArray = matrixItem.toArray();
        QVector<QVector<double>> matrix;
        for (const auto& rowItem : matrixArray) {
            QJsonArray rowArray = rowItem.toArray();
            QVector<double> row;
            for (const auto& valItem : rowArray) {
                row.append(valItem.toDouble());
            }
            matrix.append(row);
        }
        m_alternativeMatrices.append(matrix);
    }

    return calculateWeights();
}

bool MAI::calculateMatrixWeights(const QVector<QVector<double>>& matrix, QVector<double>& weights) {
    if (matrix.isEmpty()) return false;

    int size = matrix.size();
    weights.resize(size);

    QVector<double> geometricMeans(size, 1.0);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            geometricMeans[i] *= matrix[i][j];
        }
        geometricMeans[i] = std::pow(geometricMeans[i], 1.0 / size);
    }

    double sum = 0.0;
    for (double mean : geometricMeans) {
        sum += mean;
    }

    if (sum == 0.0) return false;

    for (int i = 0; i < size; ++i) {
        weights[i] = geometricMeans[i] / sum;
    }

    return true;
}

void MAI::calculateFinalScores() {
    m_finalScores.resize(m_alternatives .size(), 0.0);

    for (int alt = 0; alt < m_alternatives .size(); ++alt) {
        for (int crit = 0; crit < m_criteria.size(); ++crit) {
            m_finalScores[alt] += m_criteriaWeights[crit] * m_alternativeWeights[crit][alt];
        }
    }
}
