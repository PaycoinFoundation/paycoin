// Copyright (c) 2015 The Paycoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef PRIMEKEYS_H
#define PRIMEKEYS_H

#include <string>
#include <vector>

void getPrimePubKeyList(unsigned char, std::vector<std::string>&, int&);
void initPrimePubKeyLists();
void initPrimeP2PubKeyLists();

#endif // PRIMEKEYS_H
