// Copyright (c) 2012 The Bitcoin developers
// Copyright (c) 2012-2015 The Peercoin developers
// Copyright (c) 2014-2015 The Paycoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef BITCOIN_VERSION_H
#define BITCOIN_VERSION_H

#include <string>

//
// client versioning
//

// These need to be macro's, as version.cpp's voodoo requires it

// paycoin version - intended for display purpose only
#define PEERUNITY_VERSION_MAJOR       0
#define PEERUNITY_VERSION_MINOR       3
#define PEERUNITY_VERSION_REVISION    1
#define PEERUNITY_VERSION_BUILD       0

static const int PEERUNITY_VERSION =
                           1000000 * PEERUNITY_VERSION_MAJOR
                         +   10000 * PEERUNITY_VERSION_MINOR
                         +     100 * PEERUNITY_VERSION_REVISION
                         +       1 * PEERUNITY_VERSION_BUILD;

// paycoin version - reference for code tracking
#define PPCOIN_VERSION_MAJOR       0
#define PPCOIN_VERSION_MINOR       4
#define PPCOIN_VERSION_REVISION    0
#define PPCOIN_VERSION_BUILD       0

static const int PPCOIN_VERSION =
                           1000000 * PPCOIN_VERSION_MAJOR
                         +   10000 * PPCOIN_VERSION_MINOR
                         +     100 * PPCOIN_VERSION_REVISION
                         +       1 * PPCOIN_VERSION_BUILD;

// bitcoin version - reference for code tracking
#define BITCOIN_VERSION_MAJOR       0
#define BITCOIN_VERSION_MINOR       6
#define BITCOIN_VERSION_REVISION    3
#define BITCOIN_VERSION_BUILD       0

static const int BITCOIN_VERSION =
                           1000000 * BITCOIN_VERSION_MAJOR
                         +   10000 * BITCOIN_VERSION_MINOR
                         +     100 * BITCOIN_VERSION_REVISION
                         +       1 * BITCOIN_VERSION_BUILD;

static const int CLIENT_VERSION = BITCOIN_VERSION;

extern const std::string CLIENT_NAME;
extern const std::string CLIENT_BUILD;
extern const std::string CLIENT_DATE;


//
// network protocol versioning
//

static const int PROTOCOL_VERSION = 70004;

/* As of Paycoin protocol 70002 the MIN_PROTO_VERSION is initialized
 * and determined in init to allow for a pseudo dynamic change of minimum
 * protocol. This is also updated at runtime: net.cpp/ThreadSocketHandler2
 * Old nodes are dropped upon minimum protocol change instead of simply
 * being denied on reconnect. */
extern int MIN_PROTO_VERSION;

// nTime field added to CAddress, starting with this version;
// if possible, avoid requesting addresses nodes older than this
static const int CADDR_TIME_VERSION = 31402;

// only request blocks from nodes outside this range of versions
static const int NOBLKS_VERSION_START = 32000;
static const int NOBLKS_VERSION_END = 32400;

// BIP 0031, pong message, is enabled for all versions AFTER this one
static const int BIP0031_VERSION = 60000;

#endif
