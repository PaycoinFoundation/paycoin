/********************************************************************************
** Form generated from reading UI file 'multisigdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MULTISIGDIALOG_H
#define UI_MULTISIGDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MultisigDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tabCreateAddress;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *pubkeyEntries;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_14;
    QPushButton *addPubKeyButton;
    QPushButton *clearButton;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_2;
    QLabel *requiredSignaturesLabel;
    QLineEdit *requiredSignatures;
    QLabel *maxSignaturesLabel;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *createAddressButton;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayoutMultisigAddress;
    QLabel *multisigAddressLabel;
    QLineEdit *multisigAddress;
    QPushButton *copyMultisigAddressButton;
    QHBoxLayout *horizontalLayout_3;
    QLabel *redeemScriptLabel;
    QLineEdit *redeemScript;
    QPushButton *copyRedeemScriptButton;
    QHBoxLayout *horizontalLayout_15;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *saveRedeemScriptButton;
    QPushButton *saveMultisigAddressButton;
    QWidget *tabSpendFunds;
    QVBoxLayout *verticalLayout_13;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *inputsBox;
    QVBoxLayout *verticalLayout_6;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *inputs;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_9;
    QLabel *inputsAmountLabel;
    QLabel *inputsAmount;
    QLabel *label;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *addInputButton;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *outputsBox;
    QVBoxLayout *verticalLayout_7;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_3;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *outputs;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_10;
    QLabel *outputsAmountLabel;
    QLabel *outputsAmount;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_16;
    QSpacerItem *horizontalSpacer_12;
    QLabel *feeLabel;
    QLabel *fee;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *addOutputButton;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *createTransactionButton;
    QSpacerItem *horizontalSpacer_5;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_10;
    QLineEdit *transaction;
    QPushButton *copyTransactionButton;
    QPushButton *pasteTransactionButton;
    QHBoxLayout *horizontalLayout_11;
    QPushButton *signTransactionButton;
    QSpacerItem *horizontalSpacer_6;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_13;
    QLineEdit *signedTransaction;
    QPushButton *copySignedTransactionButton;
    QHBoxLayout *horizontalLayout_12;
    QLabel *statusLabel;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *sendTransactionButton;

    void setupUi(QDialog *MultisigDialog)
    {
        if (MultisigDialog->objectName().isEmpty())
            MultisigDialog->setObjectName(QString::fromUtf8("MultisigDialog"));
        MultisigDialog->resize(1327, 595);
        verticalLayout_2 = new QVBoxLayout(MultisigDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tabWidget = new QTabWidget(MultisigDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabCreateAddress = new QWidget();
        tabCreateAddress->setObjectName(QString::fromUtf8("tabCreateAddress"));
        verticalLayout = new QVBoxLayout(tabCreateAddress);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(tabCreateAddress);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1283, 310));
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        pubkeyEntries = new QVBoxLayout();
        pubkeyEntries->setObjectName(QString::fromUtf8("pubkeyEntries"));

        verticalLayout_3->addLayout(pubkeyEntries);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        addPubKeyButton = new QPushButton(tabCreateAddress);
        addPubKeyButton->setObjectName(QString::fromUtf8("addPubKeyButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/add"), QSize(), QIcon::Normal, QIcon::Off);
        addPubKeyButton->setIcon(icon);

        horizontalLayout_14->addWidget(addPubKeyButton);

        clearButton = new QPushButton(tabCreateAddress);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(clearButton->sizePolicy().hasHeightForWidth());
        clearButton->setSizePolicy(sizePolicy);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/remove"), QSize(), QIcon::Normal, QIcon::Off);
        clearButton->setIcon(icon1);
        clearButton->setAutoRepeatDelay(300);

        horizontalLayout_14->addWidget(clearButton);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_8);


        verticalLayout->addLayout(horizontalLayout_14);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        requiredSignaturesLabel = new QLabel(tabCreateAddress);
        requiredSignaturesLabel->setObjectName(QString::fromUtf8("requiredSignaturesLabel"));

        horizontalLayout_2->addWidget(requiredSignaturesLabel);

        requiredSignatures = new QLineEdit(tabCreateAddress);
        requiredSignatures->setObjectName(QString::fromUtf8("requiredSignatures"));
        sizePolicy.setHeightForWidth(requiredSignatures->sizePolicy().hasHeightForWidth());
        requiredSignatures->setSizePolicy(sizePolicy);
        requiredSignatures->setMinimumSize(QSize(127, 0));
        requiredSignatures->setMaxLength(2);
        requiredSignatures->setFrame(true);
        requiredSignatures->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(requiredSignatures);

        maxSignaturesLabel = new QLabel(tabCreateAddress);
        maxSignaturesLabel->setObjectName(QString::fromUtf8("maxSignaturesLabel"));

        horizontalLayout_2->addWidget(maxSignaturesLabel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        createAddressButton = new QPushButton(tabCreateAddress);
        createAddressButton->setObjectName(QString::fromUtf8("createAddressButton"));

        horizontalLayout->addWidget(createAddressButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayoutMultisigAddress = new QHBoxLayout();
        horizontalLayoutMultisigAddress->setObjectName(QString::fromUtf8("horizontalLayoutMultisigAddress"));
        multisigAddressLabel = new QLabel(tabCreateAddress);
        multisigAddressLabel->setObjectName(QString::fromUtf8("multisigAddressLabel"));

        horizontalLayoutMultisigAddress->addWidget(multisigAddressLabel);

        multisigAddress = new QLineEdit(tabCreateAddress);
        multisigAddress->setObjectName(QString::fromUtf8("multisigAddress"));
        multisigAddress->setReadOnly(true);

        horizontalLayoutMultisigAddress->addWidget(multisigAddress);

        copyMultisigAddressButton = new QPushButton(tabCreateAddress);
        copyMultisigAddressButton->setObjectName(QString::fromUtf8("copyMultisigAddressButton"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/editcopy"), QSize(), QIcon::Normal, QIcon::Off);
        copyMultisigAddressButton->setIcon(icon2);
        copyMultisigAddressButton->setAutoDefault(false);

        horizontalLayoutMultisigAddress->addWidget(copyMultisigAddressButton);


        verticalLayout->addLayout(horizontalLayoutMultisigAddress);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        redeemScriptLabel = new QLabel(tabCreateAddress);
        redeemScriptLabel->setObjectName(QString::fromUtf8("redeemScriptLabel"));

        horizontalLayout_3->addWidget(redeemScriptLabel);

        redeemScript = new QLineEdit(tabCreateAddress);
        redeemScript->setObjectName(QString::fromUtf8("redeemScript"));
        redeemScript->setReadOnly(true);

        horizontalLayout_3->addWidget(redeemScript);

        copyRedeemScriptButton = new QPushButton(tabCreateAddress);
        copyRedeemScriptButton->setObjectName(QString::fromUtf8("copyRedeemScriptButton"));
        copyRedeemScriptButton->setIcon(icon2);
        copyRedeemScriptButton->setAutoDefault(false);

        horizontalLayout_3->addWidget(copyRedeemScriptButton);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_11);

        saveRedeemScriptButton = new QPushButton(tabCreateAddress);
        saveRedeemScriptButton->setObjectName(QString::fromUtf8("saveRedeemScriptButton"));

        horizontalLayout_15->addWidget(saveRedeemScriptButton);

        saveMultisigAddressButton = new QPushButton(tabCreateAddress);
        saveMultisigAddressButton->setObjectName(QString::fromUtf8("saveMultisigAddressButton"));

        horizontalLayout_15->addWidget(saveMultisigAddressButton);


        verticalLayout->addLayout(horizontalLayout_15);

        tabWidget->addTab(tabCreateAddress, QString());
        tabSpendFunds = new QWidget();
        tabSpendFunds->setObjectName(QString::fromUtf8("tabSpendFunds"));
        verticalLayout_13 = new QVBoxLayout(tabSpendFunds);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        inputsBox = new QGroupBox(tabSpendFunds);
        inputsBox->setObjectName(QString::fromUtf8("inputsBox"));
        verticalLayout_6 = new QVBoxLayout(inputsBox);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        scrollArea_2 = new QScrollArea(inputsBox);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setMinimumSize(QSize(0, 0));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 613, 221));
        verticalLayout_4 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        inputs = new QVBoxLayout();
        inputs->setObjectName(QString::fromUtf8("inputs"));

        verticalLayout_4->addLayout(inputs);

        verticalSpacer_2 = new QSpacerItem(20, 42, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_6->addWidget(scrollArea_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_9);

        inputsAmountLabel = new QLabel(inputsBox);
        inputsAmountLabel->setObjectName(QString::fromUtf8("inputsAmountLabel"));

        horizontalLayout_6->addWidget(inputsAmountLabel);

        inputsAmount = new QLabel(inputsBox);
        inputsAmount->setObjectName(QString::fromUtf8("inputsAmount"));
        inputsAmount->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        horizontalLayout_6->addWidget(inputsAmount);

        label = new QLabel(inputsBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_6->addWidget(label);


        verticalLayout_6->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        addInputButton = new QPushButton(inputsBox);
        addInputButton->setObjectName(QString::fromUtf8("addInputButton"));
        addInputButton->setIcon(icon);

        horizontalLayout_5->addWidget(addInputButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);


        verticalLayout_6->addLayout(horizontalLayout_5);


        horizontalLayout_4->addWidget(inputsBox);

        outputsBox = new QGroupBox(tabSpendFunds);
        outputsBox->setObjectName(QString::fromUtf8("outputsBox"));
        verticalLayout_7 = new QVBoxLayout(outputsBox);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        scrollArea_3 = new QScrollArea(outputsBox);
        scrollArea_3->setObjectName(QString::fromUtf8("scrollArea_3"));
        scrollArea_3->setMinimumSize(QSize(0, 0));
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 612, 193));
        verticalLayout_5 = new QVBoxLayout(scrollAreaWidgetContents_3);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        outputs = new QVBoxLayout();
        outputs->setObjectName(QString::fromUtf8("outputs"));

        verticalLayout_5->addLayout(outputs);

        verticalSpacer_3 = new QSpacerItem(20, 42, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_3);

        scrollArea_3->setWidget(scrollAreaWidgetContents_3);

        verticalLayout_7->addWidget(scrollArea_3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_10);

        outputsAmountLabel = new QLabel(outputsBox);
        outputsAmountLabel->setObjectName(QString::fromUtf8("outputsAmountLabel"));

        horizontalLayout_7->addWidget(outputsAmountLabel);

        outputsAmount = new QLabel(outputsBox);
        outputsAmount->setObjectName(QString::fromUtf8("outputsAmount"));
        outputsAmount->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        horizontalLayout_7->addWidget(outputsAmount);

        label_2 = new QLabel(outputsBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_7->addWidget(label_2);


        verticalLayout_7->addLayout(horizontalLayout_7);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_12);

        feeLabel = new QLabel(outputsBox);
        feeLabel->setObjectName(QString::fromUtf8("feeLabel"));

        horizontalLayout_16->addWidget(feeLabel);

        fee = new QLabel(outputsBox);
        fee->setObjectName(QString::fromUtf8("fee"));

        horizontalLayout_16->addWidget(fee);

        label_3 = new QLabel(outputsBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_16->addWidget(label_3);


        verticalLayout_7->addLayout(horizontalLayout_16);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        addOutputButton = new QPushButton(outputsBox);
        addOutputButton->setObjectName(QString::fromUtf8("addOutputButton"));
        addOutputButton->setIcon(icon);

        horizontalLayout_8->addWidget(addOutputButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_4);


        verticalLayout_7->addLayout(horizontalLayout_8);


        horizontalLayout_4->addWidget(outputsBox);


        verticalLayout_8->addLayout(horizontalLayout_4);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        createTransactionButton = new QPushButton(tabSpendFunds);
        createTransactionButton->setObjectName(QString::fromUtf8("createTransactionButton"));

        horizontalLayout_9->addWidget(createTransactionButton);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_5);


        verticalLayout_8->addLayout(horizontalLayout_9);


        verticalLayout_13->addLayout(verticalLayout_8);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        transaction = new QLineEdit(tabSpendFunds);
        transaction->setObjectName(QString::fromUtf8("transaction"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(transaction->sizePolicy().hasHeightForWidth());
        transaction->setSizePolicy(sizePolicy1);

        horizontalLayout_10->addWidget(transaction);

        copyTransactionButton = new QPushButton(tabSpendFunds);
        copyTransactionButton->setObjectName(QString::fromUtf8("copyTransactionButton"));
        copyTransactionButton->setIcon(icon2);
        copyTransactionButton->setAutoDefault(false);

        horizontalLayout_10->addWidget(copyTransactionButton);

        pasteTransactionButton = new QPushButton(tabSpendFunds);
        pasteTransactionButton->setObjectName(QString::fromUtf8("pasteTransactionButton"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/editpaste"), QSize(), QIcon::Normal, QIcon::Off);
        pasteTransactionButton->setIcon(icon3);
        pasteTransactionButton->setAutoDefault(false);

        horizontalLayout_10->addWidget(pasteTransactionButton);


        verticalLayout_10->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        signTransactionButton = new QPushButton(tabSpendFunds);
        signTransactionButton->setObjectName(QString::fromUtf8("signTransactionButton"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/edit"), QSize(), QIcon::Normal, QIcon::Off);
        signTransactionButton->setIcon(icon4);

        horizontalLayout_11->addWidget(signTransactionButton);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_6);


        verticalLayout_10->addLayout(horizontalLayout_11);


        verticalLayout_13->addLayout(verticalLayout_10);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        signedTransaction = new QLineEdit(tabSpendFunds);
        signedTransaction->setObjectName(QString::fromUtf8("signedTransaction"));
        sizePolicy1.setHeightForWidth(signedTransaction->sizePolicy().hasHeightForWidth());
        signedTransaction->setSizePolicy(sizePolicy1);
        signedTransaction->setReadOnly(true);

        horizontalLayout_13->addWidget(signedTransaction);

        copySignedTransactionButton = new QPushButton(tabSpendFunds);
        copySignedTransactionButton->setObjectName(QString::fromUtf8("copySignedTransactionButton"));
        copySignedTransactionButton->setIcon(icon2);
        copySignedTransactionButton->setAutoDefault(false);

        horizontalLayout_13->addWidget(copySignedTransactionButton);


        verticalLayout_12->addLayout(horizontalLayout_13);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        statusLabel = new QLabel(tabSpendFunds);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));

        horizontalLayout_12->addWidget(statusLabel);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_7);

        sendTransactionButton = new QPushButton(tabSpendFunds);
        sendTransactionButton->setObjectName(QString::fromUtf8("sendTransactionButton"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/send"), QSize(), QIcon::Normal, QIcon::Off);
        sendTransactionButton->setIcon(icon5);

        horizontalLayout_12->addWidget(sendTransactionButton);


        verticalLayout_12->addLayout(horizontalLayout_12);


        verticalLayout_13->addLayout(verticalLayout_12);

        tabWidget->addTab(tabSpendFunds, QString());

        verticalLayout_2->addWidget(tabWidget);


        retranslateUi(MultisigDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MultisigDialog);
    } // setupUi

    void retranslateUi(QDialog *MultisigDialog)
    {
        MultisigDialog->setWindowTitle(QApplication::translate("MultisigDialog", "Multisig", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        addPubKeyButton->setToolTip(QApplication::translate("MultisigDialog", "Add a member to the signing pool", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        addPubKeyButton->setText(QApplication::translate("MultisigDialog", "&Add public key...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        clearButton->setToolTip(QApplication::translate("MultisigDialog", "Remove all public key fields", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        clearButton->setText(QApplication::translate("MultisigDialog", "Clear all", 0, QApplication::UnicodeUTF8));
        requiredSignaturesLabel->setText(QApplication::translate("MultisigDialog", "Required signatures:", 0, QApplication::UnicodeUTF8));
        requiredSignatures->setText(QString());
        requiredSignatures->setPlaceholderText(QApplication::translate("MultisigDialog", "Enter a number", 0, QApplication::UnicodeUTF8));
        maxSignaturesLabel->setText(QApplication::translate("MultisigDialog", "/ 1", 0, QApplication::UnicodeUTF8));
        createAddressButton->setText(QApplication::translate("MultisigDialog", "Create multisig address", 0, QApplication::UnicodeUTF8));
        multisigAddressLabel->setText(QApplication::translate("MultisigDialog", "Multisig address:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        copyMultisigAddressButton->setToolTip(QApplication::translate("MultisigDialog", "Copy the multisig address to the system clipboard", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        copyMultisigAddressButton->setText(QString());
        redeemScriptLabel->setText(QApplication::translate("MultisigDialog", "Redeem script:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        copyRedeemScriptButton->setToolTip(QApplication::translate("MultisigDialog", "Copy the redeem script to the system clipboard", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        copyRedeemScriptButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        saveRedeemScriptButton->setToolTip(QApplication::translate("MultisigDialog", "The redeem script will be required to spend the funds sent to the multisig address", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        saveRedeemScriptButton->setText(QApplication::translate("MultisigDialog", "Save redeem script", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        saveMultisigAddressButton->setToolTip(QApplication::translate("MultisigDialog", "Add the multisig address to your personal addresses", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        saveMultisigAddressButton->setText(QApplication::translate("MultisigDialog", "Add address to wallet", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabCreateAddress), QApplication::translate("MultisigDialog", "&Create Address", 0, QApplication::UnicodeUTF8));
        inputsBox->setTitle(QApplication::translate("MultisigDialog", "Inputs", 0, QApplication::UnicodeUTF8));
        inputsAmountLabel->setText(QApplication::translate("MultisigDialog", "Inputs amount:", 0, QApplication::UnicodeUTF8));
        inputsAmount->setText(QApplication::translate("MultisigDialog", "123.456", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MultisigDialog", "PPC", 0, QApplication::UnicodeUTF8));
        addInputButton->setText(QApplication::translate("MultisigDialog", "Add input...", 0, QApplication::UnicodeUTF8));
        outputsBox->setTitle(QApplication::translate("MultisigDialog", "Outputs", 0, QApplication::UnicodeUTF8));
        outputsAmountLabel->setText(QApplication::translate("MultisigDialog", "Outputs amount:", 0, QApplication::UnicodeUTF8));
        outputsAmount->setText(QApplication::translate("MultisigDialog", "123.456", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MultisigDialog", "PPC", 0, QApplication::UnicodeUTF8));
        feeLabel->setText(QApplication::translate("MultisigDialog", "Fee:", 0, QApplication::UnicodeUTF8));
        fee->setText(QApplication::translate("MultisigDialog", "123.456", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MultisigDialog", "PPC", 0, QApplication::UnicodeUTF8));
        addOutputButton->setText(QApplication::translate("MultisigDialog", "Add output...", 0, QApplication::UnicodeUTF8));
        createTransactionButton->setText(QApplication::translate("MultisigDialog", "Create transaction", 0, QApplication::UnicodeUTF8));
        transaction->setPlaceholderText(QApplication::translate("MultisigDialog", "Enter a raw transaction or create a new one", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        copyTransactionButton->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        copyTransactionButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        pasteTransactionButton->setToolTip(QApplication::translate("MultisigDialog", "Paste address from clipboard", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pasteTransactionButton->setText(QString());
        pasteTransactionButton->setShortcut(QApplication::translate("MultisigDialog", "Alt+P", 0, QApplication::UnicodeUTF8));
        signTransactionButton->setText(QApplication::translate("MultisigDialog", "Sign transaction", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        copySignedTransactionButton->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        copySignedTransactionButton->setText(QString());
        statusLabel->setText(QString());
        sendTransactionButton->setText(QApplication::translate("MultisigDialog", "Send transaction", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabSpendFunds), QApplication::translate("MultisigDialog", "&Spend Funds", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MultisigDialog: public Ui_MultisigDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MULTISIGDIALOG_H
