/********************************************************************************
** Form generated from reading UI file 'overviewpage.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OVERVIEWPAGE_H
#define UI_OVERVIEWPAGE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OverviewPage
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QFormLayout *formLayout_2;
    QLabel *label;
    QLabel *labelBalance;
    QLabel *label_2;
    QLabel *labelNumTransactions;
    QLabel *label_3;
    QLabel *labelUnconfirmed;
    QLabel *label_6;
    QLabel *labelStake;
    QLabel *label_5;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QListView *listTransactions;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *OverviewPage)
    {
        if (OverviewPage->objectName().isEmpty())
            OverviewPage->setObjectName(QString::fromUtf8("OverviewPage"));
        OverviewPage->resize(552, 342);
        horizontalLayout = new QHBoxLayout(OverviewPage);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        frame = new QFrame(OverviewPage);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        formLayout_2 = new QFormLayout(frame);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_2->setHorizontalSpacing(12);
        formLayout_2->setVerticalSpacing(12);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label);

        labelBalance = new QLabel(frame);
        labelBalance->setObjectName(QString::fromUtf8("labelBalance"));
        labelBalance->setText(QString::fromUtf8("0 BTC"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, labelBalance);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, label_2);

        labelNumTransactions = new QLabel(frame);
        labelNumTransactions->setObjectName(QString::fromUtf8("labelNumTransactions"));

        formLayout_2->setWidget(5, QFormLayout::FieldRole, labelNumTransactions);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_3);

        labelUnconfirmed = new QLabel(frame);
        labelUnconfirmed->setObjectName(QString::fromUtf8("labelUnconfirmed"));
        labelUnconfirmed->setText(QString::fromUtf8("0 BTC"));

        formLayout_2->setWidget(4, QFormLayout::FieldRole, labelUnconfirmed);

        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_6);

        labelStake = new QLabel(frame);
        labelStake->setObjectName(QString::fromUtf8("labelStake"));
        labelStake->setText(QString::fromUtf8("0 BTC"));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, labelStake);

        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        label_5->setFont(font);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_5);


        verticalLayout_2->addWidget(frame);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        frame_2 = new QFrame(OverviewPage);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_4 = new QLabel(frame_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);

        listTransactions = new QListView(frame_2);
        listTransactions->setObjectName(QString::fromUtf8("listTransactions"));
        listTransactions->setFrameShape(QFrame::NoFrame);
        listTransactions->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listTransactions->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        verticalLayout->addWidget(listTransactions);


        verticalLayout_3->addWidget(frame_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout_3);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);

        retranslateUi(OverviewPage);

        QMetaObject::connectSlotsByName(OverviewPage);
    } // setupUi

    void retranslateUi(QWidget *OverviewPage)
    {
        OverviewPage->setWindowTitle(QApplication::translate("OverviewPage", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("OverviewPage", "Balance:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("OverviewPage", "Number of transactions:", 0, QApplication::UnicodeUTF8));
        labelNumTransactions->setText(QApplication::translate("OverviewPage", "0", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("OverviewPage", "Unconfirmed:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("OverviewPage", "Stake:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("OverviewPage", "Wallet", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("OverviewPage", "<b>Recent transactions</b>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class OverviewPage: public Ui_OverviewPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OVERVIEWPAGE_H
