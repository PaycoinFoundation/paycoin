Test Report: Coin Control
===================================================

This report covers test results of the coin control feature of Paycoin v0.4.0 released [here](http://www.paycointalk.org/index.php?topic=2648.msg23426#msg23426). The tests are done on windows 7 professional 32bit. Paycoin distribution paycoin-rc.zip is downloaded and unzip'ped in D:\bin

## Basic features

The test method used is basically clicking/typing on the GUI of Paycoin running on Paycoin testnet, and comparing the results with those specified in [_Yet another Coin Control Release_ by cozz](https://bitcointalk.org/index.php?topic=144331.0).

There are three addresses with initial balance used in the test, 
* test1  mkLh7wYGYQiKVm8tLwCs9LusKF2y1gffm9  8.01PPC 
* test2  n2LzA1UH46QZPdCGvN2NorPeqg1BbTuw4g  2PPC
* test3  mpRAV4VSsxmKh5nRpDuQPquhdHPKu4xUuS  7PPC

### start paycoin

* Run paycoin with a bat file that has the command
```
D:\bin\paycoin-rc\paycoin-rc-qt -conf=D:\bin\paycoin-rc\paycoin.conf
```
The config file D:\bin\paycoin-rc\paycoin.conf contains
```
datadir=D:\bin\paycoin-rc
testnet=1
server=1
rpcuser=mh
rpcpassword=x
daemon=1
genproclimit=1
daemon=1
```
(Note for future upgrade: with 0.9.1 btc wallet, datadir must be specified in the command line, not in the config file.)

* After paycoin-rc is started, in the debug->Information the "On testnet" box is in checked as expected. 
* peerunit-rc successfully syncs with the testnet. "D:\bin\paycoin-rc\testnet" subdirectory is created with downloaded block chain.

### start coin control

* In settings->options->display check "Display coin control features (expert only!)".
* The following GUI functions are verified (custom change address is tested below)

> _Main_
>   * Settings checkbox "Display coin control features (experts only!)" (default=no)
>
> _Tab Send coins_
>   * Button Inputs
>     * click on this button opens actual coin control dialog. If no Inputs are selected "automatically selected" is shown.
>   * Change Checkbox
>     * checked -> provide custom change address

### _Coin Control Dialog_ 

* Send 1 PPC from test2 to test1 to 1) create change 2) create two outputs in test1.  
  Results: test2 has 0.99PPC left and test1 has 9.01PPC, as shown by coin control window. (A strict verification can be done using a block explorer. txid 94686d535fae9fc015b7e3a270123f437066c60f3c63b658774ffb60e530ee3a )  
  This confirms:

>  * select outputs by checkbox -> only the checked outputs are used when sending a transaction  
>    if none are selected -> coin control inactive (just as normal)

* Send 5 PPC from test1 to test2 using test3 as the custom change address.  
  Results: test1 has 1 PPC test2 has 5.99 PPC test3 has 10 PPC, as expected. The custom change address function is verified. txid eed4baecbcaedcf442647103fc8a18812dce2b4c852ee447b473f157c41cb837


* These are all confirmed:

> 
>  * Shows a list of all unspent outputs with two view modes
>    * tree mode: outputs including change are grouped by wallet address  
>       tree can be opened showing the actual outputs for this wallet address including change  
>       if change, the change bitcoin address is shown in column "address", otherwise the column "address" is empty, because its a direct output of the wallet address having the bitcoin address already shown in the parent node (same with label)
>    * list mode: simple list of all unspent outputs
>  * check/uncheck all by clicking on "(Un)select all"
>  * sort colums
>  * tooltip available in column list mode in column label for the change (shows from which address the change came from)

Note for the last item: the tooltip not only shows in list mode but also in tree mode.

* This item is verified except that [coin locking is not supported](https://bitcointalk.org/index.php?topic=276606.msg2958814#msg2958814) as of v0.4.

>  * Context menu  
>    Copy to clipboard (amount,label,address,transaction id,lock,unlock)

* These labels are tested **except that priorities are not verified because I do not know how priority levels for Paycoins and Peershares are defined**. 

>  * Labels at the top  
>    Quantity: number of selected outputs  
>    Amount: sum of selected unspent outputs  
>    Fee:   see "Calculation of fee and transaction size" below  
>    minus fee: simply the amount shown is "Selected" minus the amount shown in "Fee"  
>    Bytes: see "Calculation of fee and transaction size" below  
>    Priority: priority = coinage / transactionsize. coinage = value * confirmations.  miners order transactions by priority when selecting which go into a block  
>    Low Output: "yes" if any recipient receives an amount < 0.01BTC  
>    Change: shows the change you get back

Low Output is yes when the amount is less than 0.01 PPC.

* **Copy amount to clipboard by direct right clicking the _labels_ does not work. However right clicking the _values_ works.**

>  * direct right click the labels for copy amount to clipboard

* The following are verified except that "The amount exceeds your balance" is "Insufficient funds!"

> **Selection**  
> In this version of coin control, all selected outputs are going into the transaction for sure!!
> Of course, if you select more than you actually send, the bitcoin core will send the rest back to you as change, just as normal.  
> And of course, if you select less than you send you will get "The amount exceeds your balance".  
> And as already mentioned, if none are selected, coin control is inactive, this means everything is just the same as without coin control.

> **Fee**  
> If the sum of selected outputs minus the amount you are going to send is smaller than the required fee, you will probably get  
> "The total exceeds your balance when the transaction fee is included"  
> This is because you didnt select enough outputs to pay the fee.  
> You always must select enough outputs, so that those outputs can pay the fee.


* **I do not know how to independently calculate transaction size so transaction size calculation is not tested.**

> **Calculation of fee and transaction size**  
> The fee is calculated according to the fee set in the Settings menu.  
> The calculation assumes 2 outputs in total. One for the destination address and one for the change.  
> The formula is nBytesOutputs + (2 * 34) + 10. nBytesOutputs is the sum of selected outputs, 148 or 180 bytes per output, depending if compressed public key.  
> Due to the inner workings of bitcoin the size per output is actually +/- 1 byte. Meaning the shown calculation is not always 100% correct.  
> If you send exactly "selected minus fee" then you will not have change (1 output only). The transaction will then be 34 bytes smaller as what was calculated before.

* Paycoin has a fixed transaction fee so this part below about free transaction calculation is irrelevant hence not tested. 

> **Free Transactions**  
> In order to be able to send a free transaction, you need to follow the rules:  
>     - transaction size must be < 10000 bytes  
>     - priority must be at least "medium"  
>     - any recipient must receive at least 0.01BTC  
>     - change must be either zero or at least 0.01BTC  
>  If you violate one rule you will see a min-fee and also the labels turn red:  
>  Bytes.Priority,Low Output,Change. Depending which rule you violated.  
>  Those 4 labels also have tool tips explaining this.  
>  Also remember that violating one of the first 2 rules means 0.0005 PER kilobyte min-fee,
>  while violating one of the last 2 means 0.0005 min-fee only.

## Features related to Proof-of-Stake

* Mint some POS coins and test features [added](https://bitcointalk.org/index.php?topic=276948.msg2980120#msg2980120) by YAC for POS output. Pass. 

> graying-out (checkbox can't be ticked) and setting a red background of immature PoS coins in the Coin Control view.

## Summary
The coin control implmented in paycoin-rc passed tests of all main function items [specified by cozz](https://bitcointalk.org/index.php?topic=144331.0). One minor item that did not pass, and two minor untested items, are marked in bold above.

## History
Test reprt for an early build of paycoin_coin-control is [here](http://www.paycointalk.org/index.php?topic=2699.msg23386#msg23386).

mhps
2014-04-29


