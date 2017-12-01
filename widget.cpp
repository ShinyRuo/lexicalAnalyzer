#include "widget.h"
#include "ui_widget.h"
#include <QTextStream>
#include <QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    //C语言关键字
    wordString<<"short"<< "int"<< "long"<<"float"<< "double"<<"char"
            <<"struct"<<"union"<<"enum"<<"typedef"<<"const"<<"unsigned"<<"signed"<<"extern"
            <<"static"<<"void"<<"if"<<"else"<<"switch"<<"case"<<"for"<<"do"<<"while"<<
            "goto"<<"continue"<<"break"<<"default"<<"sizeof"<< "return"<<"true"<<"false";

    separators=" ,;(){}\'\":#";

    coperator="+-*/%=><!";
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::JudgeKeywords(QString cha)
{
    foreach (QString str, wordString) {
        if(str == cha){
            state = 1;
            return true;
        }
    }
    return false;
}

bool Widget::JudgeNumber(QString cha)
{
    int i;
    for(i=0;i<cha.size();++i)
        if(!numbers(cha[i])) return false;
    state =3;
    return true;
}
bool Widget::JudgeIdentifier(QString cha)
{
    int i;
    if(cha[0] == '$'||cha[0] == '_'||characters(cha[0]))
    {
        for(i=0;i<cha.size();++i)
        {
            if(spaces(cha[i])==1) return false;
        }
        state=2;
        return true;
    }
    return false;
}

bool Widget::JudgeSeparators(QString cha)
{
    for(int i=0 ; i<separators.size();++i)
    {
        if(cha[0] == separators[i])
        {
            return true;
        }
    }
    return false;
}

bool Widget::JudgeOperator(QString cha)
{
    for(int i=0 ; i<coperator.size();++i)
    {
        if(cha[0] == coperator[i])
        {
            return true;
        }
    }
    return false;
}

bool Widget::characters(QChar c)
{
    if ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A'))
    {
        return true;
    }
    return false;
}

bool Widget::spaces(QChar c)
{
    if ((c > 'z' || (c < 'a' && c > 'Z') || (c < 'A' && c > '9') || (c < '0')) && c != '_' && c != '$')
    {
        return true;
    }
    return false;
}

bool Widget::numbers(QChar c)
{
    if (c <= '9' && c >= '0')
    {
        return true;
    }
    return false;
}


void Widget::printState(QString str)
{
    QString s="("+QString::number(state,10)+",\""+str+"\")\n";
    ui->resultText->append(s);
}

void Widget::getwords(QString str)
{
    QString s="";
    QChar ch;
    int p=0;
    while(p<str.size())
    {
    ch=str[p++];
    while(ch==' ')
    {
       ch=str[p];
       p++;
    }
    if(characters(ch))
    {
        while(characters(ch)||numbers(ch))
        {
            s+=ch;
            ch=str[p++];
        }
        p--;
        if(JudgeKeywords(s))
        {
            printState(s);
            s="";
        }
        else if(JudgeIdentifier(s))
        {
            printState(s);
            s="";
        }
    }
    else if(numbers(ch))
    {
        while(numbers(ch))
        {
            s+=ch;
            ch=str[p++];
        }
        p--;
        if(JudgeNumber(s))
        {
            printState(s);
            s="";
        }
        s="";
    }
    else {
        s+=ch;
        if(JudgeOperator(s))
        {
            state=4;
            printState(s);
            s="";
        }
        if(JudgeSeparators(s))
        {
            state=5;
            printState(s);
            s="";
        }
    }
    }
}


void Widget::on_pushButton_clicked()
{
    QString textInput = ui->lexText->toPlainText();
    QString s;
    QTextStream ts(&textInput);
    while(!ts.atEnd())
    {
        s=ts.readLine();
        getwords(s);
    }
    //qDebug()<<separators[0]<<separators[1]<<separators[2]<<separators[3];
}
