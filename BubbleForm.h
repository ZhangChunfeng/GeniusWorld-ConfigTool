#ifndef BUBBLEFORM_H
#define BUBBLEFORM_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>

namespace Ui {
class BubbleForm;
}

class BubbleForm : public QWidget
{
    Q_OBJECT

public:
    explicit BubbleForm(QWidget *parent = 0);
    ~BubbleForm();

    /*****s设置气泡文本内容***********/
    void setText(const QString& text);
    /*****s获取气泡文本内容***********/
    QString getText();
    /*****设置气泡显隐***************/
    void setShown(bool iVisible);
     /*****设置气泡位置***************/
    void setPosition(const QPoint& pos);

private:
    void paintEvent(QPaintEvent*);

private slots:
    void on_pushButton_clicked();

private:
    Ui::BubbleForm *ui;
    QString                 bubbleContent;
};

#endif // BUBBLEFORM_H
