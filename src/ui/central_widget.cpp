#include "pch.h"
#include "central_widget.h"

CentralWidget::CentralWidget(QWidget* parent) : QWidget(parent)
{
    layout_ = new QHBoxLayout(this);
    layout_->setContentsMargins(8, 8, 8, 8);
    setLayout(layout_);
}

CentralWidget::~CentralWidget()
{}

void CentralWidget::addLayout(QLayout* layout, int stretch)
{
    layout_->addLayout(layout, stretch);
}

//void CentralWidget::addLayout(QLayout* layout, int row, int column, int rowSpan, int columnSpan,
//                              Qt::Alignment alignment)
//{
//    layout_->addLayout(layout, row, column, rowSpan, columnSpan, alignment);
//}

void CentralWidget::addWidget(QWidget* widget, int stretch, Qt::Alignment alignment)
{
    layout_->addWidget(widget, stretch, alignment);
}

//void CentralWidget::addWidget(QWidget* widget, int fromRow, int fromColumn, int rowSpan, int columnSpan, Qt::Alignment alignment)
//{
//    layout_->addWidget(widget, fromRow, fromColumn, rowSpan, columnSpan, alignment);
//}

//void CentralWidget::addItem(QLayoutItem* item, int row, int column, int rowSpan, int columnSpan, Qt::Alignment alignment)
//{
//    layout_->addItem(item, row, column, rowSpan, columnSpan, alignment);
//}
