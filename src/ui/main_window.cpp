#include "pch.h"
#include "main_window.h"

#include "recognition/vector_dataset_generator.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    centralWidget_(nullptr),
    inputArea_(nullptr),
    learningSettingsArea_(nullptr),
    classesNumSpinBox_(nullptr),
    learningVectorsNumSpinBox_(nullptr),
    vectorsDimensionSpinBox_(nullptr),
    learningButton_(nullptr),
    learningResultTextEdit_(nullptr),
    classificationArea_(nullptr),
    classificationLabel_(nullptr),
    intValidator_(nullptr),
    vectorInputWidget_(nullptr),
    classificationButton_(nullptr),
    classificationResultTextEdit_(nullptr),
    perceptron_(nullptr),
    learningDataSet_(),
    classCount_(0),
    learningVectorsCount_(0),
    vectorsDimension_(0),
    maxRandomVectors_(0)
{
    centralWidget_ = new CentralWidget(this);
    setCentralWidget(centralWidget_);

    inputArea_ = createInputArea();
    learningResultTextEdit_ = createLearningResultTextEdit();
    centralWidget_->addLayout(inputArea_, 2);
    centralWidget_->addWidget(learningResultTextEdit_, 6);
}

MainWindow::~MainWindow()
{}

QVBoxLayout* MainWindow::createInputArea()
{
    auto* inputArea = new QVBoxLayout(centralWidget_);
    learningSettingsArea_ = createLearningSettingsArea();
    classificationArea_ = createClassificationArea();
    inputArea->addLayout(learningSettingsArea_);
    inputArea->addLayout(classificationArea_);
    inputArea->addStretch();

    return inputArea;
}

QFormLayout* MainWindow::createLearningSettingsArea()
{
    auto* learningSettingsArea = new QFormLayout(centralWidget_);

    classesNumSpinBox_ = new QSpinBox(centralWidget_);
    classesNumSpinBox_->setMinimum(2);
    learningVectorsNumSpinBox_ = new QSpinBox(centralWidget_);
    learningVectorsNumSpinBox_->setMinimum(1);
    vectorsDimensionSpinBox_ = new QSpinBox(centralWidget_);
    vectorsDimensionSpinBox_->setMinimum(1);
    connect(vectorsDimensionSpinBox_, &QSpinBox::valueChanged, this, &MainWindow::handleVectorsSizeChange);
    learningButton_ = new QPushButton("Learning", centralWidget_);
    connect(learningButton_, &QPushButton::clicked, this, &MainWindow::learningButtonClicked);

    learningSettingsArea->setHorizontalSpacing(20);
    learningSettingsArea->addRow("Number of classes:", classesNumSpinBox_);
    learningSettingsArea->addRow("Number of learning vectors for each class:", learningVectorsNumSpinBox_);
    learningSettingsArea->addRow("Dimension of vectors:", vectorsDimensionSpinBox_);
    learningSettingsArea->addRow(nullptr, learningButton_);

    return learningSettingsArea;
}

QTextEdit* MainWindow::createLearningResultTextEdit()
{
    auto* textEdit = new QTextEdit(centralWidget_);
    textEdit->setReadOnly(true);
    textEdit->setMinimumWidth(300);
    textEdit->setMinimumHeight(400);
    textEdit->setFont(QFont("Consolas"));

    return textEdit;
}

QVBoxLayout* MainWindow::createClassificationArea()
{
    auto* classificationArea = new QVBoxLayout(centralWidget_);

    classificationLabel_ = new QLabel("Enter vector for classification:", centralWidget_);
    vectorInputWidget_ = new QTableWidget(1, vectorsDimensionSpinBox_->value(), centralWidget_);
    vectorInputWidget_->setMaximumHeight(70);
    vectorInputWidget_->horizontalHeader()->setDefaultSectionSize(30);
    vectorInputWidget_->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    intValidator_ = new IntValidatorDelegate(vectorInputWidget_);
    vectorInputWidget_->setItemDelegate(intValidator_);

    classificationButton_ = new QPushButton("Classification", this);
    classificationButton_->setMinimumWidth(100);
    classificationButton_->setMaximumWidth(130);
    connect(classificationButton_, &QPushButton::clicked, this, &MainWindow::classificationButtonClicked);

    classificationResultTextEdit_ = new QTextEdit(centralWidget_);
    classificationResultTextEdit_->setReadOnly(true);
    classificationResultTextEdit_->setMinimumHeight(200);
    classificationResultTextEdit_->setFont(QFont("Consolas"));
    classificationResultTextEdit_->setEnabled(false);

    classificationArea->addWidget(classificationLabel_);
    classificationArea->addWidget(vectorInputWidget_);
    classificationArea->addWidget(classificationButton_, 0, Qt::AlignCenter);
    classificationArea->addWidget(classificationResultTextEdit_);

    setClassificationAreaEnabled(false);

    return classificationArea;
}

void MainWindow::setClassificationAreaEnabled(bool value)
{
    vectorInputWidget_->setEnabled(value);
    classificationButton_->setEnabled(value);
    classificationResultTextEdit_->setEnabled(value);
}

void MainWindow::clearClassificationArea()
{
    vectorInputWidget_->clear();
    classificationResultTextEdit_->clear();
}

void MainWindow::handleVectorsSizeChange(int i)
{
    vectorInputWidget_->setColumnCount(i);
}

void MainWindow::learningButtonClicked()
{
    classCount_ = classesNumSpinBox_->value();
    learningVectorsCount_ = learningVectorsNumSpinBox_->value();
    vectorsDimension_ = vectorsDimensionSpinBox_->value();
    if (!generateDataSet()) {
        return;
    }

    perceptron_ = std::make_unique<Perceptron>(classCount_, vectorsDimension_, 10'000);
    perceptron_->learning(learningDataSet_);
    if (!perceptron_->isLearningConverged()) {
        QApplication::beep();
        QMessageBox::warning(nullptr, QApplication::applicationName(),
                             "Learning algorithm has not converged, might be some errors in classification!");
    }

    printLearningResult();
    setClassificationAreaEnabled(true);
}

void MainWindow::classificationButtonClicked()
{
    Vector inputVector = getInputVector();
    if (inputVector.getDimension() != vectorsDimension_ + 1) {
        QApplication::beep();
        QMessageBox::warning(nullptr, QApplication::applicationName(),
                             "Incorrect vector dimension!");
        return;
    }

    int vectorClass = perceptron_->getVectorClass(inputVector);
    classificationResultTextEdit_->clear();
    classificationResultTextEdit_->append("The vector belongs to Class " + QString::number(vectorClass + 1));
    printSumFunctionValues(inputVector);
}

bool MainWindow::generateDataSet()
{
    VectorDataSetGenerator dataSetGenerator(-10, 10);
    learningDataSet_ = dataSetGenerator.generateDataSet(classCount_, learningVectorsCount_, vectorsDimension_);

    if (learningDataSet_.empty()) {
        QApplication::beep();
        QMessageBox::warning(nullptr, QApplication::applicationName(),
                             "Cannot generate random data set\nReduce the number of classes or the number of vectors in them.");
        clearClassificationArea();
        setClassificationAreaEnabled(false);
        return false;
    }

    return true;
}

void MainWindow::printLearningResult()
{
    learningResultTextEdit_->clear();
    printLearningDataSet();
    printSumFunctions();
}

void MainWindow::printLearningDataSet()
{
    for (size_t classIdx = 0; classIdx < learningDataSet_.size(); ++classIdx) {
        learningResultTextEdit_->append("Class #" + QString::number(classIdx + 1) + ":");
        for (size_t vectorIdx = 0; vectorIdx < learningDataSet_[classIdx].size(); ++vectorIdx) {
            QString vectorStr(learningDataSet_[classIdx][vectorIdx].toString().c_str());
            learningResultTextEdit_->append(vectorStr + ";");
        }
        learningResultTextEdit_->append("");
    }
}

void MainWindow::printSumFunctions()
{
    const std::vector<SumFunction>& sumFunctions = perceptron_->getSumFunctions();

    learningResultTextEdit_->append("Sum functions:");
    for (size_t i = 0; i < sumFunctions.size(); ++i) {
        QString functionStr(sumFunctions[i].toString(i + 1).c_str());
        learningResultTextEdit_->append(functionStr + ";");
    }
}

void MainWindow::printSumFunctionValues(const Vector& vector)
{
    const std::vector<SumFunction>& sumFunctions = perceptron_->getSumFunctions();

    for (size_t i = 0; i < sumFunctions.size(); ++i) {
        int vectorValue = sumFunctions[i].getVectorValue(vector);
        QString functionStr("d(" + QString::number(i + 1) + ") = ");
        classificationResultTextEdit_->append(functionStr + QString::number(vectorValue) + ";");
    }
}

Vector MainWindow::getInputVector() const
{
    int vectorsDimension = vectorsDimensionSpinBox_->value();
    Vector inputVector(vectorsDimensionSpinBox_->value() + 1);
    for (int i = 0; i < vectorsDimension; ++i) {
        int cellValue = qTableWidgetItemToInt(vectorInputWidget_->item(0, i));
        inputVector.setElement(i, cellValue);
    }
    inputVector.setElement(vectorsDimension, 1);

    return inputVector;
}

int MainWindow::qTableWidgetItemToInt(const QTableWidgetItem* item) const
{
    return item != nullptr ? item->text().toInt() : 0;
}
