// ------------------------------------------------------------------------------
// Student 1: Mazharul Maaz (300128179)
// Student 2: Austin Fan (300018056)
// -----------------------------------------------------------------------------

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <iomanip>

#include "Bank.h"

using namespace std;

double DepositAccount::rate = 6.50;
double totalAccounts = 0.0;
int ctr = 0;
//******************************************************************
// Basic functions of the BankAccount class
//******************************************************************
inline BankAccount::BankAccount()
{
    accountId = type = updateDate = 0;
    clientName = new char[1];
    balance = 0.0;
}

inline BankAccount::BankAccount(long id, int newType,
    char* name, long newDate, double newBalance) :
    accountId(id), type(newType),
    updateDate(newDate), balance(newBalance)
{
    clientName = new char[strlen(name) + 1];
    strcpy_s(clientName, strlen(name) + 1, name);
}

inline BankAccount::~BankAccount()
{
    if (clientName)
    {
        delete[] clientName;
    }
}

inline void BankAccount::setAccountId(long account)
{
    accountId = account;
}

inline void BankAccount::setType(int newType)
{
    type = newType;
}

inline void BankAccount::setClientName(char* name)
{
    if (clientName)
    {
        delete[] clientName;
    }
    clientName = new char[strlen(name) + 1];
    strcpy_s(clientName, strlen(name) + 1, name);
}

inline void BankAccount::setUpdateDate(long newDate)
{
    updateDate = newDate;
}

inline void BankAccount::setBalance(double newBalance)
{
    balance = newBalance;
}

void BankAccount::print()
{
    cout.setf(ios::fixed);
    cout.precision(2);
    cout << accountId << "\t\t\t" << type << "\t" << updateDate << "\t\t" << balance;
}

//******************************************************************
// Basic functions of the DepositAccount class
//******************************************************************
inline DepositAccount::DepositAccount(long id, int newType, char* name,
    long newDate, double balanceArg, int nbyear) :
    BankAccount(id, newType, name,
        newDate, balanceArg), nbyears(nbyear)
{}

inline void DepositAccount::setNbYears(int nbyear)
{
    nbyears = nbyear;
}

void DepositAccount::print()
{
    Bonus();
    BankAccount::print();
    cout.setf(ios::fixed);
    cout.precision(2);
    cout << "\t" << nbyears << "\t\t" << rate << endl;
}

//******************************************************************
// Functions of the class DepositAccount. It allows to calculate
// the annual bonus on deposit accounts.
// Inputs: Nothing
// Outputs: Nothing
//******************************************************************
void DepositAccount::Bonus()
{
    setBalance(getBalance() + (getBalance() * getRate() * (getNbYears()) / 36000.00));
}



//******************************************************************
// Basic functions of the LoanAccount class
//******************************************************************
inline LoanAccount::LoanAccount(long id, int newType, char* name,
    long newDate, double newBalance, int nbyear,
    double newRate) : BankAccount(id, newType,
        name, newDate, newBalance), nbyears(nbyear), rate(newRate)
{ }

inline void LoanAccount::setNbYears(int nbyear)
{
    nbyears = nbyear;
}

inline void LoanAccount::setRate(double newRate)
{
    rate = newRate;
}

void LoanAccount::print()
{
    BankAccount::print();
    cout.setf(ios::fixed);
    cout.precision(2);
    cout << "\t" << nbyears << "\t\t" << rate << endl;
}

//******************************************************************
// Basic functions of the Transaction class
//******************************************************************
inline Transaction::Transaction(long idTr, int typeTr, long dateTr,
    int codeTr = 01, double amountTr) :
    accountId(idTr), type(typeTr),
    date(dateTr), code(codeTr),
    amount(amountTr)
{ }

inline void Transaction::setAccountId(long compteTr)
{
    accountId = compteTr;
}

inline void Transaction::setType(int typeTr)
{
    type = typeTr;
}

inline void Transaction::setDate(long dateTr)
{
    date = dateTr;
}

inline void Transaction::setCode(int codeTr)
{
    code = codeTr;
}

inline void Transaction::setAmount(double amountTr)
{
    amount = amountTr;
}




//****************************************************************************
// Purpose: Sort a list of bank accounts in ascending order of ids and types.
//
// WARNING: This sort leaves the last account (of id 0) of the list which has 
// its position to assure the tests of end of list later !!!
//
// Inputs: listAccount(BankAccount *), a list of bank accounts.
// Outputs: listAccount(BankAccount *), sorted list of bank accounts.
//****************************************************************************
void swap(BankAccount **xp, BankAccount **yp)
{
    BankAccount* temp = *xp;
    *xp = *yp;
    *yp = temp;
}
BankAccount** sortAccounts(BankAccount** list)
{


    // sorting by account id
    
    for (int i = 0; i < ctr; i++){
        // Last i elements are already in place
        for (int j = 0; j < ctr-i-1; j++){   //6
        
            if (list[j]->getAccountId() > list[j+1]->getAccountId()){
                swap(&list[j], &list[j+1]);
            }
        }
    }


    //sorting by account type
    int attributes = 7;
    for (int i = 0; i < attributes; i++){
        // Last i elements are already in place
        for (int j = 0; j < attributes-i-1; j++){
            if (list[j]->getAccountId() == list[j+1]->getAccountId()){
                if (list[j]->getType() > list[j+1]->getType()){
                    swap(&list[j], &list[j+1]);

                }
            }
        }
    }

    // seeing if sort worked
    /*
    cout<<"testing sort"<<endl;
    for (int i = 0; i < 6; i++){
        std::cout << list[i]->getAccountId() <<  "      ";
        std::cout << list[i]->getClientName() <<  "      ";
        std::cout << list[i]->getBalance() <<  "      ";
        std::cout << list[i]->getType() <<  "      ";
        std::cout << list[i]->isLoanAccount() <<  "      ";
        std::cout << list[i]->isDepositAccount() <<  "      ";
        std::cout << list[i]->getNbYears() <<  std::endl;
    }
    */

    return list;

}

//******************************************************************
// Purpose: This function reads the file 'clients.txt' and builds 
// an array containing the different bank accounts of customers.
//
// Inputs: Nothing
// Output: listAccount(type: BankAccount *), the list of bank 
//         accounts read from the file 'clients.txt'.
//******************************************************************
BankAccount** readAccounts()
{
    ifstream inputFile("clients.txt");	// Opening the input file
    if (!inputFile)            		// If the file is not found...
    {
        cout << "File not found !!!" << endl;
        exit(0);
    }

    BankAccount** listAccounts = new BankAccount * [K_SizeMax];
    if (!listAccounts) {
        cout << "Full memory. !!!" << endl;
        return listAccounts;
    }

    BankAccount** pAccount = listAccounts;

    long accountRead, dateRead;
    int TypeRead, nbyearRead, counter = 0;
    double balanceRead, RateRead;
    char nameRead[60];

    inputFile >> accountRead >> TypeRead >> dateRead >> balanceRead >> nbyearRead >> RateRead;
    inputFile.getline(nameRead, 60);

    while (inputFile && (counter < K_SizeMax - 1)) {
        // YOU HAVE TO DO SOMETHING FROM HERE !!!

        if (TypeRead == 1 || TypeRead == 2){
            *pAccount = new BankAccount(accountRead, TypeRead, nameRead, dateRead, balanceRead);
        }
        if (TypeRead == 3){
            balanceRead = balanceRead + (balanceRead * 6.50 * (nbyearRead) / 36000.00);
            *pAccount = new DepositAccount(accountRead, TypeRead, nameRead, dateRead, balanceRead, nbyearRead);
        }
        if (TypeRead == 4){
            balanceRead = balanceRead + (balanceRead * RateRead * (nbyearRead) / 36000.00);
            *pAccount = new LoanAccount(accountRead, TypeRead, nameRead, dateRead, balanceRead, nbyearRead, RateRead);
        }
        // UNTIL THIS POINT.

        inputFile >> accountRead >> TypeRead >> dateRead >> balanceRead >> nbyearRead >> RateRead;
        inputFile.getline(nameRead, 60);
        pAccount++;
        counter++;
        ctr++;
    }
    *pAccount = new BankAccount();
    return listAccounts;
}





//*****************************************************************************************
// Purpose: This function validates whether the transaction code 
//          corresponds to the correct account:
//              - 01 ==> account (01: Check, 02: Savings, 03: Deposit and 04: Loan)
//              - 02 ==> account (01: Check, 02: Savings)
//              - 03 ==> account (01: Check).
//
// Inputs: trans (Type: Transaction) an instance of the Transaction class.
// Outputs: true (Type bool) if the transaction matches one of the accounts listed above.
// false (Type bool) otherwise.
//*****************************************************************************************
Bool BankAccount::validateTransaction(const Transaction trans) const
{
    if (((trans.getCode() == 02) && (isDepositAccount() || isLoanAccount())) ||
        ((trans.getCode() == 03) && (isDepositAccount() || isLoanAccount() || isSavingsAccount())))
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }

}





//******************************************************************************
// Purpose: This function is used to execute the transaction already performed 
// (update the balance of an account).
//
// Inputs: trans (Transaction Type), instance of Transaction class
// Outputs: Nothing
//*******************************************************************************
void BankAccount::executeTransaction(const Transaction trans)
{
    if (validateTransaction(trans))
    {
        if (trans.getCode() == 01)    // Deposit
        {
            setBalance(getBalance() + trans.getAmount());
        }
        else
        {
            if (trans.getCode() == 02)    // Withdrawal
            {
                if (getBalance() >= trans.getAmount())
                {
                    setBalance(getBalance() - (trans.getAmount() + 0.50));
                }
                else { cout << " insufficient balance!! " << endl; }
            }
            else 			// Check
            {
                if (getBalance() >= trans.getAmount())
                {
                    setBalance(getBalance() - trans.getAmount());
                }
                else { cout << " insufficient balance!! " << endl; }
            }
        }

    }

}

//***********************************************************************
// Purpose: This function is used to execute a read transaction
// (updating the balance of the loan account).
//
// Inputs: trans (Transaction Type), instance of the Transaction class
// Outputs: Nothing
//***********************************************************************
void LoanAccount::executeTransaction(const Transaction trans)
{
    if (validateTransaction(trans))
    {
        if (trans.getCode() == 01)    // Deposit
        {
            setBalance(getBalance() - trans.getAmount());

        }
    }
}





//*************************************************************************
// Purpose: This function allows to read the file 'transact.txt' 
//          and to update the accounts concerned by the transactions read.
//
// Inputs: listAccount (type BankAccount *), the list of bank accounts.
// Output: Nothing.
//*************************************************************************
void updateAccounts(BankAccount** listAccounts) {
    ifstream inputFile("transact.txt");	// Opening the input file
    if (!inputFile)            		// If the file is not found...
    {
        std::cout << "File not found !!!" << endl;
        exit(0);
    }

    Transaction** listTransactions = new Transaction * [K_SizeMax];
    if (!listTransactions) {
        std::cout << "Full memory. !!!" << endl;
        return;
    }

    Transaction** pTransactions = listTransactions;

    long accountRead, dateRead, codeRead;
    int typeRead, counter = 0;
    double amountRead;

    inputFile >> accountRead >> typeRead >> dateRead >> codeRead >> amountRead;

    while (inputFile && (counter < K_SizeMax - 1)) {

        *pTransactions = new Transaction(accountRead, typeRead, dateRead, codeRead, amountRead);

        inputFile >> accountRead >> typeRead >> dateRead >> codeRead >> amountRead;
        pTransactions++;
        counter++;
    }
    *pTransactions = new Transaction();

    for (int i = 0; i < counter; i++) {
        for (int j = 0; j < ctr; j++) {
            if ((listTransactions[i]->getType() == listAccounts[j]->getType()) && (listTransactions[i]->getNumAccount() == listAccounts[j]->getAccountId())) {
                if (listAccounts[j]->validateTransaction(*listTransactions[i])) {
                    if (listTransactions[i]->getType() == 4) {
                        dynamic_cast<LoanAccount*>(listAccounts[j])->executeTransaction(*listTransactions[i]);
                    }
                    else {
                        listAccounts[j]->executeTransaction(*listTransactions[i]);
                    }
                }
                break;
            }
        }
    }
    for (int j = 0; j < ctr; j++) {
        if (listAccounts[j]->getType() == 3) {
            double temp = listAccounts[j]->getBalance() + (listAccounts[j]->getBalance() * listAccounts[j]->getRate() * listAccounts[j]->getNbYears() / 36000.00);
            listAccounts[j]->setBalance(temp);
        }
    }
}

//******************************************************************************
// Purpose: This function displays the list of bank accounts for all customers.
//
// Inputs: listAccount (type: BankAccount *), the list of bank accounts.
// Outputs: Nothing
//******************************************************************************
void displayAccounts(BankAccount** listAccounts)
{
    cout.setf(ios::fixed);
    cout.precision(2);

    cout << endl << endl << endl;

    Bool find[K_SizeMax];
    for (int k = 0; k < K_SizeMax; k++) { find[k] = FALSE; }

    cout << "                       THE REPORT OF THE BANK ACCOUNTS OF CLIENTS" << endl;
    cout << "                       ------------------------------------------" ;


    //sum for total balance of a client accounts
    double sum = 0;

    cout << endl << endl<< "           Client Name: " << listAccounts[0]->getClientName()<<endl<<endl;
    cout << "       Bank Account      Type    Update Date     Balance      Nb.Years    Rate" <<endl;
    cout << "       ------------      ----    -----------     -------      --------    ---- ";

    //ctr is equal to the number of accounts
    for (int i = 0; i < ctr; i++){
        
        if (i>0 && listAccounts[i]->getAccountId() != listAccounts[i-1]->getAccountId()){
            cout << endl << endl<< "           Client Name: " << listAccounts[i]->getClientName()<<endl<<endl;
            cout << "       Bank Account      Type    Update Date     Balance      Nb.Years    Rate" <<endl;
            cout << "       ------------      ----    -----------     -------      --------    ---- ";
        }
        cout << endl <<"       " << listAccounts[i]->getAccountId();
        cout << "               " << listAccounts[i]->getType();
        cout << "       " << listAccounts[i]->getUpdatedate();
        cout << "        " << listAccounts[i]->getBalance();


        //checking account
        if (listAccounts[i]->getType() == 1){
        }

        //savings account
        if (listAccounts[i]->getType() == 2){
        }

        //term deposit account
        if (listAccounts[i]->getType() == 3){
            cout << "        " << listAccounts[i]->getNbYears();
            cout << "        " << listAccounts[i]->getRate();
        }
        
        //loan account
        if (listAccounts[i]->getType() == 4){
            cout << "        " << listAccounts[i]->getNbYears();
            cout << "        " << listAccounts[i]->getRate();
        }


        sum=listAccounts[i]->getBalance()+sum;
        if (listAccounts[i]->getAccountId() != listAccounts[i+1]->getAccountId()){
            cout << endl << "                                               ----------";
            cout << endl << "                          TOTAL ACCOUNTS: " <<sum;
            sum = 0;
        }
        
    }

}




int main()
{
    BankAccount** list = readAccounts();
    sortAccounts(list);
    displayAccounts(list);
    updateAccounts(list);
    cout << endl << endl;
    cout << "               ************************************************" << endl;
    cout << "               * RE-DISPLAY OF DATA AFTER THE UPDATE *" << endl;
    cout << "               ************************************************" << endl;
    displayAccounts(list);
    cout << endl;

    system("PAUSE");
    return 0;
}