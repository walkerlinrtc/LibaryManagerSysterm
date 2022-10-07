#include "comboboxdelegate.h"

ComboboxDelegate::ComboboxDelegate(int column, QList<QString> valueList, QObject* parent) {
    Q_UNUSED(parent);

    currentColumn = column;
    comboboxValue = valueList;
}

QWidget* ComboboxDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const {
    if (index.isValid() && index.column() == currentColumn) {
        QComboBox* editor = new QComboBox(parent);
        editor->setStyleSheet("QComboBox {"
                              "border: 1px solid gray;"     /* 边框 */
                              "border-radius: 5px;"         /* 圆角 */
                              "padding: 1px 18px 1px 3px;"  /* 字体填衬 */
                              "font: normal normal 15px 华文楷体;"
                              "background-color: rgb(255, 255, 255);""}");
        editor->installEventFilter(const_cast<ComboboxDelegate*>(this));
        return editor;
    }
    else {
        return QItemDelegate::createEditor(parent, option, index);
    }
}

void ComboboxDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const {
    if (index.isValid() && index.column() == currentColumn) {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox* combox = static_cast<QComboBox*>(editor);
        for (int i = 0; i < comboboxValue.size(); i++) {
            combox->addItem(comboboxValue[i]);
        }
        combox->setCurrentText(value);
    }
    else {
        QItemDelegate::setEditorData(editor, index);
    }
}

void ComboboxDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const {
    if (index.isValid() && index.column() == currentColumn) {
        QComboBox* combox = static_cast<QComboBox*>(editor);
        model->setData(index, combox->currentText());
    }
    else {
        QItemDelegate::setModelData(editor, model, index);
    }
}

void ComboboxDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const {
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
