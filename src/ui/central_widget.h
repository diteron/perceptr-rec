#pragma once

class CentralWidget : public QWidget {
public:
    CentralWidget(QWidget* parent = nullptr);
    ~CentralWidget();

    void addLayout(QLayout* layout, int stretch);
    //void addLayout(QLayout* layout, int row, int column, int rowSpan, int columnSpan,
    //               Qt::Alignment alignment = Qt::Alignment());
    void addWidget(QWidget* widget, int stretch, Qt::Alignment alignment = Qt::Alignment());
    //void addWidget(QWidget* widget, int fromRow, int fromColumn, int rowSpan, int columnSpan,
    //               Qt::Alignment alignment = Qt::Alignment());
    //void addItem(QLayoutItem* item, int row, int column, int rowSpan = 1, int columnSpan = 1,
    //             Qt::Alignment alignment = Qt::Alignment());


private:
    QHBoxLayout* layout_ = nullptr;
};

