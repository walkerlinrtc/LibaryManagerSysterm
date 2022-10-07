#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QItemDelegate>   //代理，为模型中的数据项提供显示和编辑功能
#include <QComboBox>        //下拉框

class ComboboxDelegate : public QItemDelegate {
    Q_OBJECT
private:
    QList<QString> comboboxValue;
    int currentColumn;

public:
    ComboboxDelegate(int column, QList<QString> valueList, QObject* parent = nullptr);

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;
    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};

#endif // COMBOBOXDELEGATE_H
