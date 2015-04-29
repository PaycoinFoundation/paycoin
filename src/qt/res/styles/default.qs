* {
    font-family: "Gotham Pro";
    font-size: 12pt;
}

.BitcoinGUI {
    background-color: #333333;
}


QDialog, #SendCoinsEntry, #scrollAreaWidgetContents, #messagesWidget {
    background-color: white;
}

QPushButton {
    border-style: solid;
    border-width: 1px;
    height: 32px;
    padding-left: 10px;
    padding-right: 10px;
    outline: none;
    qproperty-flat: true
}

QPushButton {
    background-color: white;
    border-style: solid;
    border-color: #e9e9e9;
}

#addButton, #newAddressButton {
    background-color: #74c696;
    color: white;
}

#sendButton {
    background-color: #a6dde4;
    color: white;
}

BitcoinAmountField {
    color: black;
    background-color: #a6dde4;
}

#pageFrame {
    background-color: white;
}

#frameTop {
    background-color: white;
    qproperty-minimumSize: 100px;
}


#listTransactions {
    background-color: transparent;
    color: black;
}
#listTransactions::item {
    background-color: white;
    border: 4px solid #112766;
}

QTableView, QTreeView, QListView, QTextEdit {
    background-color: white;
    alternate-background-color: #dfdbdb;
    color: black;
}

QToolBar:vertical QToolButton:on, QMenuBar::item:selected, QMenu::item:selected {
    background-color: #f5932e;
    border-style: solid;
}


QLineEdit, QDoubleSpinBox, QAbstractSpinBox, QPlainTextEdit, QValueComboBox, QComboBox, QListWidget, QTableView:item {
    background-color: #f7f7f7;
    color: #c7c7c7;
    border-style: solid;
    border: 1px solid #e9e9e9;
}

QLineEdit, QDoubleSpinBox, QAbstractSpinBox, QPlainTextEdit, QValueComboBox, QComboBox, QListWidget {
    padding-left: 4px;
    padding-right: 4px;
    height: 30px;
}

#payAmount QValueComboBox {
    background-color: #a6dde4;
    padding-left: 32px;
    padding-right: 32px;
    height: 30px;
    border-color: white;
    color: white;
}

QComboBox QAbstractItemView
{
    background-color: #636363;
    color: white;
}

QTabWidget::pane {
    border: 1px solid #636363;
}

QTabBar::tab {
    padding: 4px;
}

QTabBar::tab:top {
    border-bottom: none;
}

QTabBar::tab:top:last:!selected {
    border-right: 1px solid black;
}

QTabBar::tab:top:selected {
    border-top: 1px solid #636363;
    border-right: 1px solid #636363;
    border-left: 1px solid #636363;
    border-bottom: 1px solid #323232;
}

QTabBar::tab:top:!selected {
    border-top: 1px solid black;
    border-left: 1px solid black;
    margin-top: 4px;
}


QToolButton {
    qproperty-autoRaise: true;
}

QToolBar {
    margin: 0px;
    padding: 0px;
    border-top: 0px;
    border-bottom: 0px;
}

QToolBar:vertical{
    margin: 0px;
    padding-left: 0px;
    border-style: none;
}

QToolBar:vertical QToolButton {
    margin: 0px;
    padding-left: 30px;
    color: white;
    width: 216px;
    border-style: none;
}

QToolBar:vertical QToolButton:hover:!on, QTabBar:tab:hover, QPushButton:hover, #buttonOK:hover, #buttonCancel:hover {
    background-color: #323332;
    color: white;
    border-style: none;
}

QToolBar:vertical QToolButton:focus:!on{
    color: white;
    background-color: #323332;
    border-style: none;
}

#frameTransactions, #labelWallet1, #labelWallet2 {
    background-color: #e6e6e6;
}

#labelBalance, #labelStake, #labelUnconfirmed, #labelNumTransactions {
    background-color: #f5932e;
    color: white;
    qproperty-alignment: AlignCenter;
    min-height: 50px;
    border-bottom: 1px solid #f5a34f;
    padding-left: 10px;
    padding-right: 10px;
}

#menuFrame {
    background-color: #a6dde4;
    qproperty-minimumSize: 250px 100px;
}

#menuFrame QToolButton:focus:!on {
    border-style: none;
}

#menuFrame QToolButton:on {
    border-style: none;
    background-color: white;
}

#menuFrame QToolButton:on {
    background-color: #323332;
    min-height: 200px;
}

#statusPanel {
    background-color: #e6e6e6;
}

SendCoinsEntry, SendCoinsDialog #scrollArea {
    border-style: none;
}


QHeaderView:section {
    background: white;
    color: black;
    border-style: solid;
    border: 1px solid #e9e9e9;
    height: 50px;
}

QTableView::item {
    border: 1px solid #e9e9e9;
}

AddressBookPage, #tableView {
    border-style: none;
}

#viewTransaction, #viewMinting{
    border-style: none;
}

QHeaderView::down-arrow {
    image: url(:/icons/arrow-down);
}

QHeaderView::up-arrow {
    image: url(:/icons/arrow-up);
}
