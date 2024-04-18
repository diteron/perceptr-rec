#pragma once



class IntValidatorDelegate :  public QItemDelegate {
public:
    IntValidatorDelegate(QWidget* parent = nullptr);
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                          const QModelIndex& index) const;
};

