/*who_knows_*/

#include <bits/stdc++.h>
using namespace std;

const int N = 1e6;
const long long k = 132974;
long long ac_cnt = 0;

class accounts{
    string name;
    long long ac_no;
    double balance;
    long long passHash;

public:
    void reg();
    void deposit();
    void withdraw();
    void setName(string s){
        name = s;
    }
    void setID(long long n){
        ac_no = n;
    }
    void setPass(long long pass){
        passHash = pass;
    }
    void setBal(double d){
        balance = d;
    }
    long long getPass(){
        return passHash;
    }
    string getName(){
        return name;
    }
    long long getBal(){
        return balance;
    }
    long long getID(){
        return ac_no;
    }
};

accounts database[N];

long long hashGen(string s){
    long long prime = 7;
    const int mod = 1e9 + 7;
    long long hash = 0;
    for (int i = 0; i < s.size();++i){
        hash += ((s[i] * prime) % mod);
        prime = ((prime * prime) % mod);
    }
    return hash;
}

void accounts :: reg(){
    cout << "Enter Full name:" << endl;
    fflush(stdin);
    getline(cin, name);
    cout << "Choose a password:" << endl;
    fflush(stdin);
    string password;
    getline(cin, password);
    passHash = hashGen(password);
    balance = 0;
    while(balance==0){
        cout << "Enter initial deposit:" << endl;
        deposit();
    }
    ac_no = k + ac_cnt;
    cout << "Your account no is: " << ac_no << endl;
    cout << "Use this account no to login!\n" << endl;
    ac_cnt++;
}

void accounts :: deposit(){
    double dep;
    cin >> dep;
    if(dep<=0){
        cout << "Operation failed!\nInvalid deposit amount!" << endl;
        return;
    }
    balance += dep;
    cout << "Operation Successfull!" << endl;
    cout << "Current balance is: " << balance << endl;
}

void accounts :: withdraw(){
    double wd;
    cin >> wd;
    if(balance<wd){
        cout << "Not enough balance!\n" << endl;
        return;
    }
    else if(wd<0){
        cout << "Operation failed!\nInvalid withdraw amount" << endl;
        return;
    }
    balance -= wd;
    cout << "Operation Successfull!" << endl;
    cout << "Current balance is: " << balance << endl;
}

void errMessage(){
    cout << "Error\n" << endl;
}

bool identification(long long id,long long pass){
    if(database[id-k].getPass()!=pass){
        cout << "wrong password\n" << endl;
        return false;
    }
    return true;
}

void accMenu(long long id){
    cout << "\nWelcome to ABC Banking," << database[id - k].getName() << "!" << endl;
    cout << "1.Show balance" << endl;
    cout << "2.Deposit" << endl;
    cout << "3.Withdraw" << endl;
    cout << "4.Change Password" << endl;
    cout << "0.Logout" << endl;
    int choice;
    cin >> choice;
    if(choice==1){
        cout << "\nAccount Balance: " << database[id - k].getBal() << endl;
        accMenu(id);
    }
    else if(choice==2){
        cout << "\nEnter deposit amount: " << endl;
        database[id - k].deposit();
        accMenu(id);
    }
    else if(choice==3){
        cout << "\nEnter withdraw amount: " << endl;
        database[id - k].withdraw();
        accMenu(id);
    }
    else if(choice==4){
        string pass;
        long long hash;
        cout << "Enter old password:" << endl;
        fflush(stdin);
        getline(cin, pass);
        hash = hashGen(pass);
        if(identification(id,hash)){
            cout << "Enter new password:" << endl;
            getline(cin, pass);
            hash = hashGen(pass);
            database[id - k].setPass(hash);
            cout << "Password changed successfully!" << endl;
            accMenu(id);
        }
        else
            accMenu(id);
    }
    else if(choice==0){
        return;
    }
    else{
        errMessage();
        accMenu(id);
    }
}

void mainMenu(){
    cout << "Welcome to ABC Banking" << endl;
    cout << "1.Register" << endl;
    cout << "2.Sign in" << endl;
    cout << "0.Exit" << endl;
    int choice;
    cin >> choice;
    if(choice==1){
        accounts newAccount;
        newAccount.reg();
        long long id = newAccount.getID();
        database[id - k] = newAccount;
        mainMenu();
    }
    else if(choice==2){
        string pass;
        long long id;
        cout << "Enter Account No:" << endl;
        cin >> id;
        if(id-k<0 || id-k>ac_cnt-1){
            cout << "No account found for this ID" << endl;
            mainMenu();
        }
        else{
            cout << "Enter password:" << endl;
            fflush(stdin);
            getline(cin, pass);
            if(identification(id,hashGen(pass))){
                accMenu(id);
        }
        mainMenu();
        }
    }
    else if(choice==0){
        return;
    }
    else{
        errMessage();
        mainMenu();
    }
}

void importData(){
    ifstream file;
    file.open("database.txt");
    if(file.is_open()){
        file >> ac_cnt;
        for (int i = 0; i < ac_cnt;++i){
            string name;
            long long ac_no;
            double balance;
            long long password;
            file.ignore();
            getline(file, name);
            file >> ac_no;
            file >> password;
            file >> balance;
            database[i].setName(name);
            database[i].setID(ac_no);
            database[i].setPass(password);
            database[i].setBal(balance);
        }
    }
    file.close();
}
void exportData(){
    ofstream file;
    file.open("database.txt", ios::trunc);
    file << ac_cnt << endl;
    for (int i = 0; i < ac_cnt;++i){
        string name = database[i].getName();
        long long id = database[i].getID();
        double balance = database[i].getBal();
        long long password = database[i].getPass();
        file << name << endl
             << id << endl
             << password << endl
             << balance << endl;
    }
    file.close();
}

int main(){

    importData();
    mainMenu();
    exportData();

    return 0;
}
