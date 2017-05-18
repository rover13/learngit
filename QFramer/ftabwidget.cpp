/****************************************************************************
**
** Copyright (C) 2014 dragondjf
**
** QFramer is a frame based on Qt5.3, you will be more efficient with it. 
** As an Qter, Qt give us a nice coding experience. With user interactive experience(UE) 
** become more and more important in modern software, deveployers should consider business and UE.
** So, QFramer is born. QFramer's goal is to be a mature solution 
** which you only need to be focus on your business but UE for all Qters.
**
** Version	: 0.2.5.0
** Author	: dragondjf
** Website	: https://github.com/dragondjf
** Project	: https://github.com/dragondjf/QCFramer
** Blog		: http://my.oschina.net/dragondjf/home/?ft=atme
** Wiki		: https://github.com/dragondjf/QCFramer/wiki
** Lincence: LGPL V2
** QQ: 465398889
** Email: dragondjf@gmail.com, ding465398889@163.com, 465398889@qq.com
** 
****************************************************************************/

#include "ftabwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QBoxLayout>
#include <QStackedLayout>
FTabWidget::FTabWidget(QWidget *parent) :
    QWidget(parent)
{
    initUI();
    initConnect();
}

void FTabWidget::initUI()
{
    tabTile = new QWidget;
    tabTile->setObjectName(QString("FTabTile"));

    stackLayout = new QStackedLayout;
   // tabLayout = new QVBoxLayout;
	tabLayout = new QHBoxLayout;
    tabLayout->addStretch();
    tabLayout->setContentsMargins(0, 0, 0, 0);
    tabLayout->setSpacing(0);
    tabTile->setLayout(tabLayout);
	
	QVBoxLayout* tabStateLyout = new QVBoxLayout;
	tabStateLyout->addWidget(tabTile,1);
	tabStateLyout->addLayout(stackLayout,20);
	tabStateLyout->setSpacing(0);
	tabStateLyout->setContentsMargins(0, 0, 0, 0);
	
	tabVlayout = new QVBoxLayout;
	tabVlayout->setSpacing(0);
	tabVlayout->setContentsMargins(0, 0, 0, 0);

	QHBoxLayout* tablayTest = new QHBoxLayout;
	tablayTest->addLayout(tabVlayout, 1);
	tablayTest->addLayout(tabStateLyout, 15);
	tablayTest->setSpacing(0);
	tablayTest->setContentsMargins(0, 0, 0, 0);

    /*mainLayout = new QHBoxLayout;*/
	mainLayout = new QVBoxLayout;
    //mainLayout->addWidget(tabTile);
    //mainLayout->addLayout(stackLayout);
	mainLayout->addLayout(tablayTest);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
	//mainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(mainLayout);
}

void FTabWidget::initConnect()
{


}

void FTabWidget::addWidget(const QString &tile, const QString &objectName, QWidget *widget)
{
    Q_UNUSED(objectName)
    buttonTitles  << tile;
    FCheckabelButton* button = new FCheckabelButton(tile);
    buttons.append(button);
//    button->setObjectName(objectName);
    button->setFixedSize(100, 30);
    tabLayout->insertWidget(tabLayout->count() - 1, button, 0, Qt::AlignCenter);
    connect(button, SIGNAL(clicked()), this, SLOT(setButtonChecked()));
//    widget->setObjectName(objectName);
    stackLayout->addWidget(widget);
}

QList<FCheckabelButton*> FTabWidget::getButtons()
{
    return buttons;
}

void FTabWidget::setButtonChecked()
{
    for (int i = 0; i < buttons.size(); ++i) {
        if (buttons.at(i) == sender())
        {
            buttons.at(i)->setChecked(true);
            stackLayout->setCurrentIndex(i);
            emit indexChanged(i);
        }
        else{
            buttons.at(i)->setChecked(false);
        }
    }
}

void FTabWidget::addDockWidget(QWidget *widget)
{
	tabVlayout->addWidget(widget);
}
