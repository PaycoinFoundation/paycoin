#include "addresstablemodel.h"
#include "guiutil.h"
#include "walletmodel.h"

#include "wallet.h"
#include "base58.h"
#include "scrapesdb.h"

#include <QFont>
#include <QColor>

const QString AddressTableModel::Send = "S";
const QString AddressTableModel::Receive = "R";

extern CScrapesDB* scrapesDB;

struct AddressTableEntry
{
    enum Type {
        Sending,
        Receiving
    };

    Type type;
    QString label;
    QString address;
    QString scrape_address;

    AddressTableEntry() {}
    AddressTableEntry(Type type, const QString &label, const QString &address, const QString &scrape_address):
        type(type), label(label), address(address), scrape_address(scrape_address) {}
    AddressTableEntry(Type type, const QString &label, const QString &address):
        type(type), label(label), address(address) {}
};

// Private implementation
class AddressTablePriv
{
public:
    CWallet *wallet;
    QList<AddressTableEntry> cachedAddressTable;

    AddressTablePriv(CWallet *wallet):
            wallet(wallet) {}

    void refreshAddressTable()
    {
        cachedAddressTable.clear();

        {
            LOCK(wallet->cs_wallet);
            BOOST_FOREACH(const PAIRTYPE(CTxDestination, std::string)& item, wallet->mapAddressBook)
            {
                const CBitcoinAddress& address = item.first;
                const std::string& strName = item.second;
                bool fMine = IsMine(*wallet, address.Get());

                if (fMine) {
                    std::string addr;
                    if (scrapesDB->HasScrapeAddress(address.ToString()))
                        scrapesDB->ReadScrapeAddress(address.ToString(), addr);

                    cachedAddressTable.append(AddressTableEntry(AddressTableEntry::Receiving,
                                       QString::fromStdString(strName),
                                       QString::fromStdString(address.ToString()),
                                       QString::fromStdString(addr)));
                } else {
                    cachedAddressTable.append(AddressTableEntry(AddressTableEntry::Sending,
                                       QString::fromStdString(strName),
                                       QString::fromStdString(address.ToString())));
                }
            }
        }
    }

    int size()
    {
        return cachedAddressTable.size();
    }

    AddressTableEntry *index(int idx)
    {
        if(idx >= 0 && idx < cachedAddressTable.size())
        {
            return &cachedAddressTable[idx];
        }
        else
        {
            return 0;
        }
    }
};

AddressTableModel::AddressTableModel(CWallet *wallet, WalletModel *parent) :
    QAbstractTableModel(parent),walletModel(parent),wallet(wallet),priv(0)
{
    columns << tr("Label") << tr("Address") << tr("Scrape Address");

    priv = new AddressTablePriv(wallet);
    priv->refreshAddressTable();
}

AddressTableModel::~AddressTableModel()
{
    delete priv;
}

int AddressTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return priv->size();
}

int AddressTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return columns.length();
}

QVariant AddressTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    AddressTableEntry *rec = static_cast<AddressTableEntry*>(index.internalPointer());

    if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch(index.column())
        {
        case Label:
            if(rec->label.isEmpty() && role == Qt::DisplayRole)
            {
                return tr("(no label)");
            }
            else
            {
                return rec->label;
            }
        case Address:
            return rec->address;

        case ScrapeAddress:
            // No scrape address for sending tab.
            if (rec->type == AddressTableEntry::Sending)
                break;

            if (rec->scrape_address.isEmpty() && role == Qt::DisplayRole)
            {
                return tr("(no scrape address)");
            }
            else
            {
                return rec->scrape_address;
            }
        }
    }
    else if (role == Qt::FontRole)
    {
        QFont font;
        if(index.column() == Address)
        {
            font = GUIUtil::bitcoinAddressFont();
        }
        return font;
    }
    else if (role == TypeRole)
    {
        switch(rec->type)
        {
        case AddressTableEntry::Sending:
            return Send;
        case AddressTableEntry::Receiving:
            return Receive;
        default: break;
        }
    }
    return QVariant();
}

bool AddressTableModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if(!index.isValid())
        return false;
    AddressTableEntry *rec = static_cast<AddressTableEntry*>(index.internalPointer());

    editStatus = OK;

    if(role == Qt::EditRole)
    {
        switch(index.column())
        {
        case Label:
            wallet->SetAddressBookName(CBitcoinAddress(rec->address.toStdString()).Get(), value.toString().toStdString());
            rec->label = value.toString();
            break;
        case Address:
            // Refuse to set invalid address, set error status and return false
            if(!walletModel->validateAddress(value.toString()))
            {
                editStatus = INVALID_ADDRESS;
                return false;
            }
            // Double-check that we're not overwriting a receiving address
            if(rec->type == AddressTableEntry::Sending)
            {
                {
                    LOCK(wallet->cs_wallet);
                    // Remove old entry
                    wallet->DelAddressBookName(CBitcoinAddress(rec->address.toStdString()).Get());
                    // Add new entry with new address
                    wallet->SetAddressBookName(CBitcoinAddress(value.toString().toStdString()).Get(), rec->label.toStdString());
                }

                rec->address = value.toString();
            }
            break;
        case ScrapeAddress:
            // No scrape address for sending tab.
            if (rec->type == AddressTableEntry::Sending)
                break;

            /* Require authentication when modifying a scrape address on an
             * encrypted wallet. */
            WalletModel::UnlockContext ctx(walletModel->requestUnlock());
            if (!ctx.isValid())
                return false;

            /* If passing an empty string delete the current scrape address
             * if one exists. */
            if (value.toString().toStdString().empty()) {
                if (scrapesDB->HasScrapeAddress(rec->address.toStdString()))
                    if (!scrapesDB->EraseScrapeAddress(rec->address.toStdString()))
                        return false;
            } else {
                // Confirm the scrape address is a valid address before setting it
                if(!walletModel->validateAddress(value.toString())) {
                    editStatus = INVALID_ADDRESS;
                    return false;
                }

                if (!scrapesDB->WriteScrapeAddress(rec->address.toStdString(), value.toString().toStdString()))
                    return false;
            }

            rec->scrape_address = value.toString();
            break;
        }
        emit dataChanged(index, index);

        return true;
    }
    return false;
}

QVariant AddressTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal)
    {
        if(role == Qt::DisplayRole)
        {
            return columns[section];
        }
    }
    return QVariant();
}

Qt::ItemFlags AddressTableModel::flags(const QModelIndex & index) const
{
    if(!index.isValid())
        return 0;
    AddressTableEntry *rec = static_cast<AddressTableEntry*>(index.internalPointer());

    Qt::ItemFlags retval = Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    // Can edit address and label for sending addresses,
    // label and scrapeaddress for receiving addresses.
    if(rec->type == AddressTableEntry::Sending ||
      (rec->type == AddressTableEntry::Receiving && index.column()==Label) ||
      (rec->type == AddressTableEntry::Receiving && index.column()==ScrapeAddress))
    {
        retval |= Qt::ItemIsEditable;
    }
    return retval;
}

QModelIndex AddressTableModel::index(int row, int column, const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    AddressTableEntry *data = priv->index(row);
    if(data)
    {
        return createIndex(row, column, priv->index(row));
    }
    else
    {
        return QModelIndex();
    }
}

void AddressTableModel::update()
{
    // Update address book model from Bitcoin core
    beginResetModel();
    priv->refreshAddressTable();
    endResetModel();
}

QString AddressTableModel::addRow(const QString &type, const QString &label, const QString &address)
{
    std::string strLabel = label.toStdString();
    std::string strAddress = address.toStdString();

    editStatus = OK;

    if(type == Send)
    {
        if(!walletModel->validateAddress(address))
        {
            editStatus = INVALID_ADDRESS;
            return QString();
        }
        // Check for duplicate addresses
        {
            LOCK(wallet->cs_wallet);
            if(wallet->mapAddressBook.count(CBitcoinAddress(strAddress).Get()))
            {
                editStatus = DUPLICATE_ADDRESS;
                return QString();
            }
        }
    }
    else if(type == Receive)
    {
        // Generate a new address to associate with given label
        WalletModel::UnlockContext ctx(walletModel->requestUnlock());
        if(!ctx.isValid())
        {
            // Unlock wallet failed or was cancelled
            editStatus = WALLET_UNLOCK_FAILURE;
            return QString();
        }
        CPubKey newKey;
        if(!wallet->GetKeyFromPool(newKey, true))
        {
            editStatus = KEY_GENERATION_FAILURE;
            return QString();
        }
        strAddress = CBitcoinAddress(newKey.GetID()).ToString();
    }
    else
    {
        return QString();
    }
    // Add entry
    {
        LOCK(wallet->cs_wallet);
        wallet->SetAddressBookName(CBitcoinAddress(strAddress).Get(), strLabel);
    }
    return QString::fromStdString(strAddress);
}

bool AddressTableModel::removeRows(int row, int count, const QModelIndex & parent)
{
    Q_UNUSED(parent);
    AddressTableEntry *rec = priv->index(row);
    if(count != 1 || !rec || rec->type == AddressTableEntry::Receiving)
    {
        // Can only remove one row at a time, and cannot remove rows not in model.
        // Also refuse to remove receiving addresses.
        return false;
    }
    {
        LOCK(wallet->cs_wallet);
        wallet->DelAddressBookName(CBitcoinAddress(rec->address.toStdString()).Get());
    }
    return true;
}

/* Look up label for address in address book, if not found return empty string.
 */
QString AddressTableModel::labelForAddress(const QString &address) const
{
    {
        LOCK(wallet->cs_wallet);
        CBitcoinAddress address_parsed(address.toStdString());
        std::map<CTxDestination, std::string>::iterator mi = wallet->mapAddressBook.find(address_parsed.Get());
        if (mi != wallet->mapAddressBook.end())
        {
            return QString::fromStdString(mi->second);
        }
    }
    return QString();
}

int AddressTableModel::lookupAddress(const QString &address) const
{
    QModelIndexList lst = match(index(0, Address, QModelIndex()),
                                Qt::EditRole, address, 1, Qt::MatchExactly);
    if(lst.isEmpty())
    {
        return -1;
    }
    else
    {
        return lst.at(0).row();
    }
}
