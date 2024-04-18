#include "pch.h"
#include "int_validator_delegate.h"

IntValidatorDelegate::IntValidatorDelegate(QWidget* parent)
    : QItemDelegate(parent)
{}

QWidget* IntValidatorDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                                            const QModelIndex& index) const
{
    QLineEdit* lineEdit = new QLineEdit(parent);
    QIntValidator* validator = new QIntValidator(lineEdit);
    lineEdit->setValidator(validator);
    return lineEdit;
}
