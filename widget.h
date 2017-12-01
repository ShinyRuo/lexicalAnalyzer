#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStringList>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    bool JudgeKeywords(QString cha);
    bool JudgeNumber(QString cha);
    bool JudgeIdentifier(QString cha);
    bool JudgeSeparators(QString cha);
    bool JudgeOperator(QString cha);
    bool characters(QChar c);
    bool spaces(QChar c);
    bool numbers(QChar c);
    void printState(QString str);
    void getwords(QString str);
private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    QString separators;
    QString coperator;
    QStringList wordString;
    int state,row,sum;
};

#endif // WIDGET_H
