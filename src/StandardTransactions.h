////////////////////////////////////////////////////////////////////////////////
//
// StandardTransactions.h
//
// Copyright (c) 2011-2012 Eric Lombrozo
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef STANDARD_TRANSACTIONS_H__
#define STANDARD_TRANSACTIONS_H__

#include "CoinNodeData.h"
#include "Base58Check.h"

using namespace Coin;

class StandardTxOut : public TxOut
{
public:
    StandardTxOut() { }

    void payToAddress(const std::string& address, uint64_t value);
    void payToScriptHash(const std::string& scriptHash, uint64_t value);
};

void StandardTxOut::payToAddress(const std::string& address, uint64_t value)
{
    uchar_vector pubKeyHash;
    uint version;
    if (!fromBase58Check(address, pubKeyHash, version))
        throw std::runtime_error("Invalid address checksum.");
    this->scriptPubKey = uchar_vector("76a914") + pubKeyHash + uchar_vector("88ac");
    this->value = value;
}

void StandardTxOut::payToScriptHash(const std::string& address, uint64_t value)
{
    uchar_vector pubKeyHash;
    uint version;
    if (!fromBase58Check(address, pubKeyHash, version))
        throw std::runtime_error("Invalid address checksum.");
    this->scriptPubKey = uchar_vector("a914") + pubKeyHash + uchar_vector("87");
    this->value = value;
}

#endif // STANDARD_TRANSACTIONS_H__
