#pragma once

#include "central_widget.h"
#include "int_validator_delegate.h"

#include "recognition/perceptron.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    QVBoxLayout* createInputArea();
    QFormLayout* createLearningSettingsArea();
    QTextEdit* createLearningResultTextEdit();
    QVBoxLayout* createClassificationArea();
    void setClassificationAreaEnabled(bool value);
    void clearClassificationArea();
    
    CentralWidget* centralWidget_;

    QVBoxLayout* inputArea_;
    QFormLayout* learningSettingsArea_;
    QSpinBox* classesNumSpinBox_;
    QSpinBox* learningVectorsNumSpinBox_;
    QSpinBox* vectorsDimensionSpinBox_;
    QPushButton* learningButton_;
    const int learningSettingSpinBoxMaxWidth = 180;
    const int learningSettingSpinBoxMinWidth = 90;

    QTextEdit* learningResultTextEdit_;

    QVBoxLayout* classificationArea_;
    QLabel* classificationLabel_;
    IntValidatorDelegate* intValidator_;
    QTableWidget* vectorInputWidget_;
    QPushButton* classificationButton_;
    QTextEdit* classificationResultTextEdit_;

    std::unique_ptr<Perceptron> perceptron_;
    std::vector<std::vector<Vector>> learningDataSet_;

    size_t classCount_;
    size_t learningVectorsCount_;
    size_t vectorsDimension_;
    size_t maxRandomVectors_;

private slots:
    void handleVectorsSizeChange(int i);
    void learningButtonClicked();
    void classificationButtonClicked();

private:
    [[nodiscard]] bool generateDataSet();
    void printLearningResult();
    void printLearningDataSet();
    void printSumFunctions();
    void printSumFunctionValues(const Vector& vector);

    Vector getInputVector() const;
    int qTableWidgetItemToInt(const QTableWidgetItem* item) const;
};
