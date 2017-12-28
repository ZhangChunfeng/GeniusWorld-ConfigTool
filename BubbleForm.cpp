#include "BubbleForm.h"
#include "ui_BubbleForm.h"

BubbleForm::BubbleForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BubbleForm)
{
    ui->setupUi(this);
    this->setWindowOpacity(1);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAutoFillBackground(true);
}

BubbleForm::~BubbleForm()
{
    delete ui;
}

/*
 * Function      :setText
 * Description:设置气泡文本内容
 * Parameters  :text-设置的文本内容
 * Return          :
 */
void BubbleForm::setText(const QString &text)
{
    bubbleContent = text;
    this->ui->textLabel->setText(bubbleContent);
}

/*
 * Function      :getText
 * Description:获取气泡文本内容
 * Parameters  :
 * Return          :气泡文本内容
 */
QString BubbleForm::getText()
{
    return bubbleContent;
}

/*
 * Function      :setShown
 * Description:设置气泡显隐
 * Parameters  :iVisible：true-显示，false-隐藏
 * Return          :
 */
void BubbleForm::setShown(bool iVisible)
{
    if(iVisible) {
        this->show();
    } else {
        this->hide();
    }
}

/*
 * Function      :setPosition
 * Description:设置气泡位置
 * Parameters  :pos-要设置的气泡位置
 * Return          :
 */
void BubbleForm::setPosition(const QPoint &pos)
{
    QRect rect = this->geometry();
    rect.moveBottomLeft(QPoint(pos.x(), pos.y() + 90));
    this->setGeometry(rect);
}

void BubbleForm::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.save();
    QPixmap bkgrdPix(":/res/resources/bubble1.png");
    painter.drawPixmap(this->rect(), bkgrdPix);
    painter.restore();
}

void BubbleForm::on_pushButton_clicked()
{
    this->close();
}
