/********************************************************************************
** Form generated from reading UI file 'aboutdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTDIALOG_H
#define UI_ABOUTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AboutDialog
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_3;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *versionLabel;
    QSpacerItem *horizontalSpacer;
    QLabel *label_4;
    QLabel *label_paycoin_copyright;
    QLabel *label_2;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AboutDialog)
    {
        if (AboutDialog->objectName().isEmpty())
            AboutDialog->setObjectName(QString::fromUtf8("AboutDialog"));
        AboutDialog->resize(544, 488);
        horizontalLayout_2 = new QHBoxLayout(AboutDialog);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(9, 0, -1, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        label_3 = new QLabel(AboutDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/icons/res/icons/horizontal_trans-no-shadow.png")));
        label_3->setAlignment(Qt::AlignCenter);
        label_3->setIndent(0);

        verticalLayout_2->addWidget(label_3);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(AboutDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        horizontalLayout->addWidget(label);

        versionLabel = new QLabel(AboutDialog);
        versionLabel->setObjectName(QString::fromUtf8("versionLabel"));
        versionLabel->setText(QString::fromUtf8("v0.1.0"));
        versionLabel->setTextFormat(Qt::RichText);
        versionLabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        horizontalLayout->addWidget(versionLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout);

        label_4 = new QLabel(AboutDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_2->addWidget(label_4);

        label_paycoin_copyright = new QLabel(AboutDialog);
        label_paycoin_copyright->setObjectName(QString::fromUtf8("label_paycoin_copyright"));
        label_paycoin_copyright->setWordWrap(true);
        label_paycoin_copyright->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        verticalLayout_2->addWidget(label_paycoin_copyright);

        label_2 = new QLabel(AboutDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setWordWrap(true);
        label_2->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        verticalLayout_2->addWidget(label_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(AboutDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        horizontalLayout_2->addLayout(verticalLayout_2);


        retranslateUi(AboutDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AboutDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AboutDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AboutDialog);
    } // setupUi

    void retranslateUi(QDialog *AboutDialog)
    {
        AboutDialog->setWindowTitle(QApplication::translate("AboutDialog", "About Paycoin", 0, QApplication::UnicodeUTF8));
        label_3->setText(QString());
        label->setText(QApplication::translate("AboutDialog", "<html><head/><body><p><span style=\" font-weight:600;\">Paycoin</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("AboutDialog", "Copyright \302\251 2014 Paycoin Developers", 0, QApplication::UnicodeUTF8));
        label_paycoin_copyright->setText(QApplication::translate("AboutDialog", "Copyright \302\251 2011-2014 Paycoin Developers", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("AboutDialog", "Copyright \302\251 2009-2014 Bitcoin Developers\n"
"\n"
"This is experimental software.\n"
"\n"
"Distributed under the MIT/X11 software license, see the accompanying file license.txt or http://www.opensource.org/licenses/mit-license.php.\n"
"\n"
"This product includes software developed by the OpenSSL Project for use in the OpenSSL Toolkit (http://www.openssl.org/) and cryptographic software written by Eric Young (eay@cryptsoft.com) and UPnP software written by Thomas Bernard.", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AboutDialog: public Ui_AboutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTDIALOG_H
