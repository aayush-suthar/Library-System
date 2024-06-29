#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<exception>
#include <random>
#include <ctime>
using namespace std;
random_device rd;
mt19937 gen(std::time(nullptr));
uniform_int_distribution<int> dist(10000, 99999);




//############################################################ BOOK CLASS #######################################################



class Book{
string name;
string author;
string isbn;
string publish_year;
int edition;
int copies;
string book_id;
static int book_count;

public:

    void Add_Book();
    void Show_Book();
    void File_Book_Write(int x , int cop);

};
int Book::book_count = 0;


//############################################################ USER CLASS #######################################################


class User{
string name;
string password;
string phone;
string user_id;
public:

    User(){};

    User(string user_id , string name , string password , string phone){
        this->user_id = user_id;
        this->name = name;
        this->password = password;
        this->phone = phone;
    }

    bool Add_User();
    void File_User_Write();
    void User_Main_Menu();
    void Show_User();
    void My_Books();
    void Issue_Book();
    void Deposit_Book();

};


//############################################################ LOAN CLASS #######################################################


class Loan{
string loan_id;
string book_id;
string user_id;
int copies;
string issue_date;
int due;

public:

    Loan(){};

    Loan(string loan_id , string book_id , string user_id , int copies , string issue_date){
        this->loan_id = loan_id;
        this->book_id = book_id;
        this->user_id = user_id;
        this->copies = copies;
        this->issue_date = issue_date;
    }
};

User U;
Book B;
Loan L;










//############################################################ GENERAL FUNCTIONS #######################################################


//############################################################ CLEAR A FILE #######################################################
void ClearFile(const string& filename) {
    ofstream fout(filename, ios::out | ios::trunc);
    if (!fout) {
        throw "File Not opened During Clearing";
    }
    fout.close();
}

//############################################################ CHANGE COPIES #######################################################

void Change_Copies(string id , int num , string user){
    ifstream fin;
    ofstream fout;
    fin.open("Books.txt");
    fout.open("temp.txt" ,ios::out | ios::app);

    if(!fin){
        throw "\n\n\nFile Not opened During Changing Copies\n";
    }
    string line;
    while(getline(fin,line)){
        istringstream iss(line);
        string temp_id , temp_name , temp_auth , temp_year , temp_isbn;
        int temp_cop , temp_edi;
        if(iss >> temp_id >> temp_name >> temp_auth >> temp_edi >> temp_year >> temp_cop >> temp_isbn){
            if(temp_id == id){
                    if(fout.is_open()){
                fout<<temp_id<<"\t\t"<<temp_name<<"\t\t"<<temp_auth<<"\t\t"<<temp_edi<<"\t\t"<<temp_year<<"\t\t"<<temp_cop + num<<"\t\t"<<temp_isbn<<"\n";
                    }
            }else{
                if(fout.is_open()){
                fout<<temp_id<<"\t\t"<<temp_name<<"\t\t"<<temp_auth<<"\t\t"<<temp_edi<<"\t\t"<<temp_year<<"\t\t"<<temp_cop<<"\t\t"<<temp_isbn<<"\n";
                }
            }
        }

    }
    fin.close();
    fout.close();
    try{
    ClearFile("Books.txt");
    }catch(const char* e){throw e;}
    fin.close();
    fout.close();

    fin.open("temp.txt");
    fout.open("Books.txt" ,ios::out | ios::app);
    while(getline(fin,line)){
        istringstream iss(line);
        string temp_id , temp_name , temp_auth , temp_year , temp_isbn;
        int temp_cop , temp_edi;
        if(iss >> temp_id >> temp_name >> temp_auth >> temp_edi >> temp_year >> temp_cop >> temp_isbn){
                    if(fout.is_open()){
                fout<<temp_id<<"\t\t"<<temp_name<<"\t\t"<<temp_auth<<"\t\t"<<temp_edi<<"\t\t"<<temp_year<<"\t\t"<<temp_cop<<"\t\t"<<temp_isbn<<"\n";
                    }
        }

    }
        try{
        ClearFile("temp.txt");
        }catch(const char* e){throw e;}
        fin.close();
        fout.close();

        if(num < 0){
            return;
        }

    fin.open("Loans.txt");
    fout.open("temp.txt" ,ios::out | ios::app);

    if(!fin){
        throw "\n\n\nFile Not opened During Changing Copies\n";
    }
    while(getline(fin,line)){
            if(line.size()==0){continue;}
        istringstream iss(line);
        string temp_id , temp_book_id , temp_user_id;int temp_cop;string s;
        if(iss >> temp_id >> temp_book_id >> temp_user_id >> temp_cop >> s){
            if(temp_book_id == id && user == temp_user_id){
                    if(fout.is_open() && temp_cop >= num){
                fout<<temp_id<<"\t\t"<<temp_book_id<<"\t\t"<<temp_user_id<<"\t\t"<<temp_cop - num<<"\t\t"<<s<<"\n";
                    }
            }else{
                if(fout.is_open()){
                fout<<temp_id<<"\t\t"<<temp_book_id<<"\t\t"<<temp_user_id<<"\t\t"<<temp_cop<<"\t\t"<<s<<"\n";
                }
            }
        }
    }
    fin.close();
    fout.close();
    try{
    ClearFile("Loans.txt");
    }catch(const char* e){throw e;}
    fin.close();

    fout.close();

    fin.open("temp.txt");
    fout.open("Loans.txt" ,ios::out | ios::app);
    while(getline(fin,line)){
        istringstream iss(line);
        string temp_id , temp_book_id , temp_user_id;int temp_cop;
        if(iss >> temp_id >> temp_book_id >> temp_user_id >> temp_cop){
                    if(fout.is_open()){
                fout<<temp_id<<"\t\t"<<temp_book_id<<"\t\t"<<temp_user_id<<"\t\t"<<temp_cop<<"\n";
                    }
        }

    }   try{
        ClearFile("temp.txt");
    }catch(const char* e){throw e;}
        fin.close();
        fout.close();

    cout<<"Enter Any Key";string x;cin>>x;
}


//############################################################ GET ISSUED COLPIES #######################################################

int Get_Issued_Copies(string isbn , string id)
{
    ifstream fin;

    fin.open("Books.txt");

    if(!fin){
        throw "\n\n\nFile Not opened During Getting Issued Copies\n";
    }
    string line;
    while(getline(fin,line)){
        istringstream iss(line);
        string temp_id , temp_name , temp_auth , temp_year , temp_isbn;
        int temp_cop , temp_edi;
        if(iss >> temp_id >> temp_name >> temp_auth >> temp_edi >> temp_year >> temp_cop >> temp_isbn){

            if(temp_id == id && temp_isbn == isbn){
                return temp_cop;
            }
        }
    }
return 0;
}

//############################################################ WRITE USER IN FILE #######################################################

void User::File_User_Write(){

    ofstream fout;

    fout.open("Users.txt" , ios::out |ios::app);

    if(!fout){
        throw "\n\n\nFile Not opened During Writing User\n";
    }
    if(fout.is_open()){
        fout<<user_id<<"\t\t"<<name<<"\t\t"<<password<<"\t\t"<<phone<<"\n";
    }
    fout.close();
    return;
}

//############################################################ WRITE BOOK IN FILE #######################################################

void Book::File_Book_Write(int type , int copies)
{
if(type == 0){
    ofstream fout;
    fout.open("Books.txt" , ios::out |ios::app);
    if(!fout){
        throw "\n\n\nFile Not opened During Writing Books\n";
    }
    if(fout.is_open()){
        fout<<book_id<<"\t\t"<<name<<"\t\t"<<author<<"\t\t"<<edition<<"\t\t"<<publish_year<<"\t\t"<<copies<<"\t\t"<<isbn<<"\n";
    }
    fout.close();
    return;
}else{
    ifstream fin;
    ofstream fout;
    fin.open("Books.txt");
    fout.open("temp.txt", ios::out | ios::app);

    if(!fin){
        throw "\n\n\nFile Not opened During Writing Books\n";
    }

    string line;
    while(getline(fin,line)){
        istringstream iss(line);
        string temp_id , temp_name , temp_auth , temp_year , temp_isbn;
        int temp_cop , temp_edi;
        if(iss >> temp_id >> temp_name >> temp_auth >> temp_edi >> temp_year >> temp_cop >> temp_isbn){
            if(temp_isbn == isbn){
                    if(fout.is_open()){
                fout<<temp_id<<"\t\t"<<temp_name<<"\t\t"<<temp_auth<<"\t\t"<<temp_edi<<"\t\t"<<temp_year<<"\t\t"<<temp_cop + copies<<"\t\t"<<temp_isbn<<"\n";
                    }

                    }else{
                    if(fout.is_open()){
                fout<<temp_id<<"\t\t"<<temp_name<<"\t\t"<<temp_auth<<"\t\t"<<temp_edi<<"\t\t"<<temp_year<<"\t\t"<<temp_cop<<"\t\t"<<temp_isbn<<"\n";
                    }
            }

        }
    }
    try{
    ClearFile("Books.txt");
    }catch(const char* e){throw e;}
    fin.close();
    fout.close();

    fin.open("temp.txt");
    fout.open("Books.txt" ,ios::out | ios::app);
    while(getline(fin,line)){
        istringstream iss(line);
        string temp_id , temp_name , temp_auth , temp_year , temp_isbn;
        int temp_cop , temp_edi;
        if(iss >> temp_id >> temp_name >> temp_auth >> temp_edi >> temp_year >> temp_cop >> temp_isbn){
                    if(fout.is_open()){
                fout<<temp_id<<"\t\t"<<temp_name<<"\t\t"<<temp_auth<<"\t\t"<<temp_edi<<"\t\t"<<temp_year<<"\t\t"<<temp_cop<<"\t\t"<<temp_isbn<<"\n";
                    }
        }

    }
        try{
        ClearFile("temp.txt");
        }catch(const char* e){throw e;}
    cout<<"Enter Any Key";string x;cin>>x;
    return;

}
}

//############################################################ CHECK USER EXISTENCE #######################################################

bool Check_User_Existence(string name , string password){
    ifstream fin;

    fin.open("Users.txt");

    if(!fin){
        throw "\n\n\nFile Not opened During Checking User\n";
    }
    string line;

    while(getline(fin,line)){
            if(line.size() == 0){continue;}
        istringstream iss(line);
        string temp_id , temp_name , temp_pass , temp_phone;
        if(iss >> temp_id >> temp_name >> temp_pass >> temp_phone){
            if(temp_name == name && temp_pass == password){
                return 1;
            }
        }else{
            return 0;
        }
     }
    fin.close();
    return 0;
}

//############################################################ GET USER INFORMATION #######################################################

vector<string> Get_User_Info(string name , string password){
    vector<string> data;
    ifstream fin;

    fin.open("Users.txt");

    if(!fin){
        throw "\n\n\nFile Not opened Getting User Info\n";
    }

    string line;

    while(getline(fin,line)){
            if(line.size() == 0){continue;}
        istringstream iss(line);
        string temp_id , temp_name , temp_pass , temp_phone;
        if(iss >> temp_id >> temp_name >> temp_pass >> temp_phone){
            if(temp_name == name && temp_pass == password){
                data = {temp_id , temp_name , temp_pass , temp_phone};
                return data;
            }
        }else{
            return data;
        }
     }
    fin.close();
    return data;
}

//############################################################ CHECK BOOK EXISTENCE #######################################################

bool check_Book_Existence(string id)
{
    fstream fin;

    fin.open("Books.txt");

    if(!fin){
        throw "\n\n\nFile Not opened During Checking Books\n";
    }
    string line;

    if(getline(fin,line)&& line.size() == 0){}

    while(getline(fin,line)){
        istringstream iss(line);
        string temp_id , temp_;
        if(iss >> temp_id){
            if(temp_id == id){
                return 1;
            }
        }else{
            return 0;
        }
     }
    fin.close();
    return 0;

}














//############################################################ ADMINISTRATION FUNCTIONS #######################################################


//############################################################ DISPLAY ALL ISSUED BOOK/LOANS #######################################################


void Display_All_Loan()
{
    system("cls");
    ifstream fin;
    cout<<"Enter 0 to return \n";int x;

    if(x == 0){
        return;
    }

    fin.open("Loans.txt");

    if(!fin){
        throw "\n\n\nFile Not opened During Displaying Loans\n";
    }
    string line;
    while(getline(fin,line)){
        istringstream iss(line);
        string temp_id , temp_book_name , temp_user_name; int copies;
        if(iss >> temp_id >> temp_book_name >> temp_user_name>> copies){
            cout<<"\t\t\t\t\t\tLOAN ID    : "<<temp_id<<endl;
            cout<<"\t\t\t\t\t\tBOOK ID    : "<<temp_book_name<<endl;
            cout<<"\t\t\t\t\t\tUSER ID    : "<<temp_user_name<<endl;
            cout<<"\t\t\t\t\t\tCOPIES     : "<<copies<<"\n\n";
        }

    }
    fin.close();
    cin>>x;
return;
}

//############################################################ MODIFY BOOK #######################################################

void Modify_Book(){
    system("cls");
    string id;
        cout<<"Enter -1 to return\n";
    cout<<"\t\t\t\t\t\tEnter Book ID   : \n";cin>>id;
    if(id == "-1"){return;}

    ifstream fin;
    ofstream fout;
    fin.open("Books.txt");
    fout.open("temp.txt", ios::out | ios::app);

    if(!fin || !fout){
        throw "\n\n\nFile Not opened During Modifying Books\n";
    }

    string line;
    while(getline(fin,line)){
        istringstream iss(line);
        string temp_id , temp_name , temp_auth , temp_year , temp_isbn;
        int temp_cop , temp_edi;
        if(iss >> temp_id >> temp_name >> temp_auth >> temp_edi >> temp_year >> temp_cop >> temp_isbn){
            if(temp_id == id){
                        string name , author , isbn , publish_year;
                        int edition , cop;
                        cout<<"\t\t\t\t\t\tEnter Book Name    : ";cin>>name;
                        cout<<"\t\t\t\t\t\tEnter Author Name  : ";cin>>author;
                        cout<<"\t\t\t\t\t\tISBN Code          : ";cin>>isbn;
                        cout<<"\t\t\t\t\t\tPublish Year       : ";cin>>publish_year;
                        cout<<"\t\t\t\t\t\tEdition(number)    : ";cin>>edition;
                        cout<<"\t\t\t\t\t\tcopies             : ";cin>>cop;
                    if(fout.is_open()){
                fout<<temp_id<<"\t\t"<<name<<"\t\t"<<author<<"\t\t"<<edition<<"\t\t"<<publish_year<<"\t\t"<<cop<<"\t\t"<<isbn<<"\n";
                    }
                    }else{
                    if(fout.is_open()){
                fout<<temp_id<<"\t\t"<<temp_name<<"\t\t"<<temp_auth<<"\t\t"<<temp_edi<<"\t\t"<<temp_year<<"\t\t"<<temp_cop<<"\t\t"<<temp_isbn<<"\n";
                    }
            }

        }
    }
    try{
    ClearFile("Books.txt");
    }catch(const char* e){throw e;}
    fin.close();
    fout.close();

    fin.open("temp.txt");
    fout.open("Books.txt" ,ios::out | ios::app);
    while(getline(fin,line)){
        istringstream iss(line);
        string temp_id , temp_name , temp_auth , temp_year , temp_isbn;
        int temp_cop , temp_edi;
        if(iss >> temp_id >> temp_name >> temp_auth >> temp_edi >> temp_year >> temp_cop >> temp_isbn){
                    if(fout.is_open()){
                fout<<temp_id<<"\t\t"<<temp_name<<"\t\t"<<temp_auth<<"\t\t"<<temp_edi<<"\t\t"<<temp_year<<"\t\t"<<temp_cop<<"\t\t"<<temp_isbn<<"\n";
                    }
        }

    }
        try{
        ClearFile("temp.txt");
        }catch(const char* e){throw e;}
    cout<<"Enter Any Key";string x;cin>>x;
    return;
    }

//############################################################ DELETE BOOK #######################################################

void Delete_Book(){
    system("cls");
    string id;
        cout<<"Enter -1 to return\n";
    cout<<"\t\t\t\t\t\tEnter Book ID   : \n";cin>>id;
    if(id == "-1"){return;}
    ifstream fin;
    ofstream fout;
    fin.open("Books.txt");
    fout.open("temp.txt", ios::out | ios::app);

    if(!fin){
        throw "\n\n\nFile Not opened During Deleting Books\n";
    }
    string line;
    while(getline(fin,line)){
        istringstream iss(line);
        string temp_id , temp_name , temp_auth , temp_year , temp_isbn;
        int temp_cop , temp_edi;
        if(iss >> temp_id >> temp_name >> temp_auth >> temp_edi >> temp_year >> temp_cop >> temp_isbn){
            if(temp_id == id){
            }else{
                    if(fout.is_open()){
                fout<<temp_id<<"\t\t"<<temp_name<<"\t\t"<<temp_auth<<"\t\t"<<temp_edi<<"\t\t"<<temp_year<<"\t\t"<<temp_cop<<"\t\t"<<temp_isbn<<"\n";
                    }
            }
        }
    }
    try{
    ClearFile("Books.txt");
    }catch(const char* e){throw e;}
    fin.close();
    fout.close();

    fin.open("temp.txt");
    fout.open("Books.txt" ,ios::out | ios::app);
    while(getline(fin,line)){
        istringstream iss(line);
        string temp_id , temp_name , temp_auth , temp_year , temp_isbn;
        int temp_cop , temp_edi;
        if(iss >> temp_id >> temp_name >> temp_auth >> temp_edi >> temp_year >> temp_cop >> temp_isbn){
                    if(fout.is_open()){
                fout<<temp_id<<"\t\t"<<temp_name<<"\t\t"<<temp_auth<<"\t\t"<<temp_edi<<"\t\t"<<temp_year<<"\t\t"<<temp_cop<<"\t\t"<<temp_isbn<<"\n";
                    }
        }

    }
        try{
        ClearFile("temp.txt");
        }catch(const char* e){throw e;}
    cout<<"Enter Any Key";string x;cin>>x;
    return;
}

//############################################################ ADD BOOK #######################################################

void Book::Add_Book()
{
    system("cls");
        cout<<"Enter -1 to return in any below field\n";
    string name , author , isbn , publish_year;
    int edition , copies;

    cout<<"\t\t\t\t\t\tEnter Book Name    : ";cin>>name;
    if(name == "-1"){return;}
    cout<<"\t\t\t\t\t\tEnter Author Name  : ";cin>>author;
    if(author == "-1"){return;}
    cout<<"\t\t\t\t\t\tISBN Code          : ";cin>>isbn;
    if(isbn == "-1"){return;}
    cout<<"\t\t\t\t\t\tPublish Year       : ";cin>>publish_year;
    if(publish_year == "-1"){return;}
    cout<<"\t\t\t\t\t\tEdition(number)    : ";cin>>edition;
    if(edition == -1){return;}
    cout<<"\t\t\t\t\t\tcopies             : ";cin>>copies;
    if(copies == -1){return;}
    string id = "B" + to_string( dist(gen) );
    this->book_id = id;
    this->name = name;
    this->author = author;
    this->isbn = isbn;
    this->publish_year = publish_year;
    this->edition = edition;
    this->copies = copies;

    try{
    if((check_Book_Existence(id))){
        File_Book_Write(1 , copies);
    }else{
        File_Book_Write(0 , copies);
    }
    }catch(const char* e){throw e;}

}

//############################################################ SHOW A BOOK #######################################################

void Book::Show_Book(){
system("cls");
cout<<"\t\t\t\t\t\tID                   : "<<book_id<<"\n";
cout<<"\t\t\t\t\t\tNAME                 : "<<name<<"\n";
cout<<"\t\t\t\t\t\tAUTHOR               : "<<author<<"\n";
cout<<"\t\t\t\t\t\tEDITION              : "<<edition<<"\n";
cout<<"\t\t\t\t\t\tPUBLISH YEAR         : "<<publish_year<<"\n";
cout<<"\t\t\t\t\t\tCOPIES AVAILABLE     : "<<copies<<"\n";
cout<<"\t\t\t\t\t\tISBN                 : "<<isbn<<"\n";
cout<<"\t\t\t\t\t\tEnter 0 to return ";
int x;cin>>x;
if(x == 0){
    return;
}else{
    Show_Book();
}
}

//############################################################ MODIFY USER #######################################################

void Modify_User(){

    system("cls");
    string id;
        cout<<"Enter -1 to return in any below field\n";
    cout<<"\t\t\t\t\t\tEnter User ID      : ";cin>>id;
    if(id == "-1"){return;}
    cout<<"\t\t\t\t\t\tEnter New Name     : ";string name;cin>>name;
    if(name == "-1"){return;}
    cout<<"\t\t\t\t\t\tEnter New Password : ";string pass;cin>>pass;
    if(pass == "-1"){return;}
    cout<<"\t\t\t\t\t\tEnter New Phone    : +91 ";string phone;cin>>phone;cout<<endl;
    if(phone == "-1"){return;}
    ifstream fin;
    ofstream fout;

    fin.open("Users.txt");
    fout.open("temp.txt", ios::out | ios::app);



    if(!fin){
        throw "\n\n\nFile Not opened During Modifying Users\n";
    }

    string line;
    while(getline(fin,line)){
        istringstream iss(line);
        string temp_id , temp_name , temp_pass , temp_phone;
        if(iss >> temp_id >> temp_name >> temp_pass >> temp_phone){
            if(temp_id == id){
                fout<<temp_id<<"\t\t"<<name<<"\t\t"<<pass<<"\t\t"<<phone<<"\n";
            }else{
            fout<<temp_id<<"\t\t"<<temp_name<<"\t\t"<<temp_pass<<"\t\t"<<temp_phone<<"\n";
            }
        }
    }
    ClearFile("Users.txt");
    fin.close();
    fout.close();

    fin.open("temp.txt");
    fout.open("Users.txt" ,ios::out | ios::app);
    while(getline(fin,line)){
        istringstream iss(line);
        string temp_id , temp_name , temp_pass , temp_phone;
        if(iss >> temp_id >> temp_name >> temp_pass >> temp_phone){
            fout<<temp_id<<"\t\t"<<temp_name<<"\t\t"<<temp_pass<<"\t\t"<<temp_phone<<"\n";
        }

    }
        ClearFile("temp.txt");
    cout<<"Update Done Successfully Enter Any Key";string x;cin>>x;
    return;

}

//############################################################ DELETE USER #######################################################

void Delete_User(){
    system("cls");
    string id;
    cout<<"Enter -1 to return\n";
    cout<<"\t\t\t\t\t\tEnter User ID : ";cin>>id;
    if(id == "-1"){return;}
    ifstream fin;
    ofstream fout;

    fin.open("Users.txt");
    fout.open("temp.txt", ios::out | ios::app);


    if(!fin){
        throw "\n\n\nFile Not opened During Deleting Users\n";
    }


    string line;
    while(getline(fin,line)){
        istringstream iss(line);
        string temp_id , temp_name , temp_pass , temp_phone;
        if(iss >> temp_id >> temp_name >> temp_pass >> temp_phone){
            if(temp_id == id){
                continue;
            }
            if(fout.is_open()){
            fout<<temp_id<<"\t\t"<<temp_name<<"\t\t"<<temp_pass<<"\t\t"<<temp_phone<<"\n";
            }
        }
    }
    ClearFile("Users.txt");
    fin.close();
    fout.close();

    fin.open("temp.txt");
    fout.open("Users.txt" ,ios::out | ios::app);
    while(getline(fin,line)){
        istringstream iss(line);
        string temp_id , temp_name , temp_pass , temp_phone;
        if(iss >> temp_id >> temp_name >> temp_pass >> temp_phone){
            if(fout.is_open()){
                fout<<temp_id<<"\t\t"<<temp_name<<"\t\t"<<temp_pass<<"\t\t"<<temp_phone<<"\n";
            }
        }

    }
    ClearFile("temp.txt");
    cout<<"Done Successfully Enter Any Key";string x;cin>>x;
    return;
}

//############################################################ ADD USER #######################################################

bool User::Add_User()
{
    string res;
    system("cls");
    cout<<"Enter -1 to return in any below field\n";
    string name,password,email;
    string phone;

    cout<<"\t\t\t\t\t\tEnter UserName : ";cin>>name;
    if(name == "-1"){
        return 0;
    }
    cout<<"\t\t\t\t\t\tEnter password : ";cin>>password;
    if(password == "-1"){
        return 0;
    }
    cout<<"\t\t\t\t\t\tPhone : +91 ";cin>>phone;
    if(phone == "-1"){
        return 0;
    }
    if(phone.size() != 10){cout<<"\n\n\nInValid Phone Number , \n";return 0;};
    for(int i = 0 ; i < phone.size() ; i++){
        if(!isdigit(phone[i])){
            cout<<"\n\n\nInValid Phone Number\n";
            return 0;
        }
    }


    try{
    if(Check_User_Existence(name , password)){
        cout<<"\n\n\nAccount Already Created - Enter Any key : ";cin>>res;
        return 0;
    }
    }catch(const char *e){
        throw e;
        return 0;
    }
    string id = "A" + to_string( dist(gen) );

    this->user_id = id;
    this->name = name;
    this->password = password;
    this->phone = phone;

    try{
        File_User_Write();
    }catch(const char* e){
        throw e;
    }

return 1;
}

//############################################################ SEARCH USER #######################################################

void Search_User(){
    system("cls");
    string id;
    cout<<"\t\t\t\t\t\tEnter User ID : ";cin>>id;
    ifstream fin;

    fin.open("Users.txt");

    if(!fin){
        throw "\n\n\nFile Not opened During Searching Users\n";
    }
    string line;
    while(getline(fin,line)){
        istringstream iss(line);
        string temp_id , temp_name , temp_pass , temp_phone;
        if(iss >> temp_id >> temp_name >> temp_pass >> temp_phone){
            if(temp_id == id){
            cout<<"\t\t\t\t\t\tID       : "<<temp_id<<endl;
            cout<<"\t\t\t\t\t\tNAME     : "<<temp_name<<endl;
            cout<<"\t\t\t\t\t\tPASSWORD : "<<temp_pass<<endl;
            cout<<"\t\t\t\t\t\tPHONE    : "<<temp_phone<<"\n\n";
            fin.close();
            cout<<"Enter 0 to return \n";int x;cin>>x;
            if(x == 0){return;}
            }
        }

    }

    cout<<"User NOT FOUND\n";
    return;
}

//############################################################ DISPLAY ALL USER #######################################################

void Display_All_User(){
    system("cls");
    ifstream fin;
    cout<<"Enter 0 to return \n";int x;

    if(x == 0){
        return;
    }

    fin.open("Users.txt");

    if(!fin){
        throw "\n\n\nFile Not opened During Displaying All Users\n";
    }
    string line;
    while(getline(fin,line)){
        istringstream iss(line);
        string temp_id , temp_name , temp_pass , temp_phone;
        if(iss >> temp_id >> temp_name >> temp_pass >> temp_phone){
            cout<<"\t\t\t\t\t\tID       : "<<temp_id<<endl;
            cout<<"\t\t\t\t\t\tNAME     : "<<temp_name<<endl;
            cout<<"\t\t\t\t\t\tPASSWORD : "<<temp_pass<<endl;
            cout<<"\t\t\t\t\t\tPHONE    : "<<temp_phone<<"\n\n";
        }

    }
    fin.close();
    cin>>x;
}









//############################################################ USER FUNCTIONS #######################################################


//############################################################ DISPLAY ALL BOOKS #######################################################

void Display_All_Book()
{
    system("cls");
    ifstream fin;
    cout<<"Enter 0 to return \n";int x;

    if(x == 0){
        return;
    }

    fin.open("Books.txt");

    if(!fin){
        throw "\n\n\nFile Not opened During Displaying All Books\n";
    }
    string line;
    while(getline(fin,line)){
        istringstream iss(line);
        string temp_id , temp_name , temp_auth , temp_year , temp_isbn;
        int temp_cop , temp_edi;
        if(iss >> temp_id >> temp_name >> temp_auth >> temp_edi >> temp_year >> temp_cop >> temp_isbn){
            cout<<"\t\t\t\t\t\tID                   : "<<temp_id<<"\n";
            cout<<"\t\t\t\t\t\tNAME                 : "<<temp_name<<"\n";
            cout<<"\t\t\t\t\t\tAUTHOR               : "<<temp_auth<<"\n";
            cout<<"\t\t\t\t\t\tEDITION              : "<<temp_edi<<"\n";
            cout<<"\t\t\t\t\t\tPUBLISH YEAR         : "<<temp_year<<"\n";
            cout<<"\t\t\t\t\t\tCOPIES AVAILABLE     : "<<temp_cop<<"\n";
            cout<<"\t\t\t\t\t\tISBN                 : "<<temp_isbn<<"\n\n";
        }

    }
    fin.close();
    cin>>x;
}

//############################################################ DEPOSIT BOOKS #######################################################

void User::Deposit_Book()
{
    system("cls");
        cout<<"Enter -1 to return in any below field\n";
    string name , author , isbn;int copies , edition;
    cout<<"\t\t\t\t\t\tNAME      : ";cin>>name;
    if(name == "-1"){return;}
    cout<<"\t\t\t\t\t\tAUTHOR    : ";cin>>author;
    if(author == "-1"){return;}
    cout<<"\t\t\t\t\t\tEDITION   : ";cin>>edition;
    if(edition == -1){return;}
    cout<<"\t\t\t\t\t\tISBN      : ";cin>>isbn;
    if(isbn == "-1"){return;}
    cout<<"\t\t\t\t\t\tCOPIES    : ";cin>>copies;
    if(copies == -1){return;}

    ifstream fin;

    fin.open("Books.txt");

    if(!fin){
        throw "\n\n\nFile Not opened During Depositing Books\n";
    }
    string line;
    while(getline(fin,line)){
            if(line.size() == 0){continue;}
        istringstream iss(line);
        string temp_id , temp_name , temp_auth , temp_year , temp_isbn;
        int temp_cop , temp_edi;
        if(iss >> temp_id >> temp_name >> temp_auth >> temp_edi >> temp_year >> temp_cop >> temp_isbn){

            if(temp_name == name && temp_auth == author && temp_edi == edition && temp_isbn == isbn){

                 int issued_copies = Get_Issued_Copies(temp_isbn , temp_id);
                 string res;

                if(copies > issued_copies){
                    cout<<"ONLY "<<issued_copies<<" COPIES ARE BORROWED : Enter Any Key To Return : ";cin>>res;
                    return;
                }else{
                    Change_Copies(temp_id , copies , this->user_id);
                    cout<<"DEPOSIT SUCCESSFULLY : Enter Any Key To Return : ";cin>>res;
                    return;
                }
            }
        }
    }
}


//############################################################ ISSUE BOOKS #######################################################

void User::Issue_Book()
{
    system("cls");
    cout<<"Enter -1 to return in any below field\n";
    string name , author , isbn;int copies , edition;
    cout<<"\t\t\t\t\t\tNAME      : ";cin>>name;
    if(name == "-1"){return;}
    cout<<"\t\t\t\t\t\tAUTHOR    : ";cin>>author;
    if(author == "-1"){return;}
    cout<<"\t\t\t\t\t\tEDITION   : ";cin>>edition;
    if(edition == -1){return;}
    cout<<"\t\t\t\t\t\tISBN      : ";cin>>isbn;
    if(isbn == "-1"){return;}
    cout<<"\t\t\t\t\t\tCOPIES    : ";cin>>copies;
    if(copies == -1){return;}
    ifstream fin;

    fin.open("Books.txt");

    if(!fin){
        throw "\n\n\nFile Not opened During Issuing Books\n";
    }
    string line;
    while(getline(fin,line)){
            if(line.size() == 0){continue;}
        istringstream iss(line);
        string temp_id , temp_name , temp_auth , temp_year , temp_isbn;
        int temp_cop , temp_edi;
        if(iss >> temp_id >> temp_name >> temp_auth >> temp_edi >> temp_year >> temp_cop >> temp_isbn){

            if(temp_name == name && temp_auth == author && temp_edi == edition && temp_isbn == isbn){

                if(copies > temp_cop){
                    cout<<"ONLY "<<temp_cop<<" COPIES ARE AVAILABLE\n";
                    return;
                }else{
                    time_t tt; struct tm* ti; time(&tt);ti = localtime(&tt);
                    Change_Copies(temp_id , -1*copies , this->user_id);
                        string id = "L" + to_string( dist(gen) );
                        Loan L(id , temp_id , this->user_id , copies , asctime(ti));
                        ofstream fout;
                        fout.open("Loans.txt",ios::app);
                            if(!fout){
                                throw "\n\n\nFile Not opened During Displaying Books\n";
                            }
                            if(fout.is_open()){
                                fout<<id<<"\t\t"<<temp_id<<"\t\t"<<this->user_id<<"\t\t"<<copies<<"\t\t"<<asctime(ti);
                            }
                        fout.close();
                    cout<<"ISSUED SUCCESSFULLY\n";
                    return;
                }

            }
        }


    }

}

//############################################################ MY BOOKS #######################################################

void User::My_Books()
{
    system("cls");
    ifstream fin;
    ifstream fin_1;
    cout<<"Enter 0 to return \n";int x;

    if(x == 0){
        return;
    }
    fin.open("Loans.txt");
    if(!fin || !fin_1){
        throw "\n\n\nFile Not opened During Displaying ALL_MY_BOOKS\n";
    }
    string line;
    while(getline(fin,line)){
            if(line.size() == 0){continue;}
        istringstream iss(line);
        string temp_id , temp_book_id, temp_user_id; int temp_copies;
        if(iss >> temp_id >> temp_book_id>> temp_user_id>> temp_copies){
                if(this->user_id == temp_user_id){
                    string p;
                        fin_1.open("Books.txt");
                    while(getline(fin_1,p)){
                            if(p.size() == 0){continue;}
                        istringstream s(p);
                            string temp_id , temp_name , temp_auth , temp_year , temp_isbn;
                            int temp_cop , temp_edi;
                            if(s >> temp_id >> temp_name >> temp_auth >> temp_edi >> temp_year >> temp_cop >> temp_isbn){
                                if(temp_book_id == temp_id){
                                cout<<"\t\t\t\t\t\tID                   : "<<temp_id<<"\n";
                                cout<<"\t\t\t\t\t\tNAME                 : "<<temp_name<<"\n";
                                cout<<"\t\t\t\t\t\tAUTHOR               : "<<temp_auth<<"\n";
                                cout<<"\t\t\t\t\t\tEDITION              : "<<temp_edi<<"\n";
                                cout<<"\t\t\t\t\t\tPUBLISH YEAR         : "<<temp_year<<"\n";
                                cout<<"\t\t\t\t\t\tCOPIES AVAILABLE     : "<<temp_copies<<"\n";
                                cout<<"\t\t\t\t\t\tISBN                 : "<<temp_isbn<<"\n\n";
                                }
                            }
                    }
                        fin_1.close();
                }
        }
    }
    fin.close();
    cin>>x;
return;
}

//############################################################ SHOW USER #######################################################

void User::Show_User(){
system("cls");
cout<<"\t\t\t\t\t\tID :       "<<user_id<<endl;
cout<<"\t\t\t\t\t\tNAME :     "<<name<<endl;
cout<<"\t\t\t\t\t\tPASSWORD : "<<password<<endl;
cout<<"\t\t\t\t\t\tContact :  "<<phone<<"\n\n";
cout<<"\t\t\t\t\t\tEnter 0 to return ";
int x;cin>>x;
if(x == 0){
    return;
}else{
    Show_User();
}
}


//############################################################ USER MAIN MENU #######################################################

void User::User_Main_Menu(){
system("cls");
cout<<"\t\t\t\t\t\t"<<name<<" Main Menu\n"<<endl;
cout<<"\t\t\t\t\t\t1. View Profile\n";
cout<<"\t\t\t\t\t\t2. View MyBooks\n";
cout<<"\t\t\t\t\t\t3. Issue Book\n";
cout<<"\t\t\t\t\t\t4. Deposit Book\n";
cout<<"\t\t\t\t\t\t5. Show All Books\n";
cout<<"\t\t\t\t\t\tChoose from [1-6]\n";
cout<<"\t\t\t\t\t\tEnter 0 to return"<<endl;
int opt;
cin>>opt;
string res;

switch(opt){
    case 1:
        Show_User();
        User_Main_Menu();
        break;
    case 2:
        try{
        My_Books();
        }catch(const char* e){cout<<e<<" : Enter Any Key To RETURN :";cin>>res;}
        User_Main_Menu();
        break;
    case 3:
        try{
        Issue_Book();
        }catch(const char* e){cout<<e<<" : Enter Any Key To RETURN :";cin>>res;}
        User_Main_Menu();
        break;
    case 4:
        try{
        Deposit_Book();
        }catch(const char* e){cout<<e<<" : Enter Any Key To RETURN :";cin>>res;}
        User_Main_Menu();
        break;
    case 5:
        try{
        Display_All_Book();
        }catch(const char* e){cout<<e<<" : Enter Any Key To RETURN :";cin>>res;}
        User_Main_Menu();
        break;
    case 0:
        break;
    default:
        User_Main_Menu();

return;
}

}












//############################################################ MAIN MENU FUNCTIONS #######################################################


//############################################################ ADMINISTRATION #######################################################


void Administration(){
    system("cls");

    string x;

    cout<<"\t########################################  ADMINISTRATION  ########################################\n";
    cout<<"\t\t\t\t\t\t1.  Show All Users\n";
    cout<<"\t\t\t\t\t\t2.  Search User\n";
    cout<<"\t\t\t\t\t\t3.  Add User\n";
    cout<<"\t\t\t\t\t\t4.  Delete User\n";
    cout<<"\t\t\t\t\t\t5.  Modify User\n";
    cout<<"\t\t\t\t\t\t6.  Show All Books\n";
    cout<<"\t\t\t\t\t\t7.  Add Books\n";
    cout<<"\t\t\t\t\t\t8.  Delete Book\n";
    cout<<"\t\t\t\t\t\t9.  Modify Book\n";
    cout<<"\t\t\t\t\t\t10. All Issued Books\n";
    cout<<"\t\t\t\t\t\t0.  Return to Main Menu\n";
    cout<<"\t\t\t\t\t\tEnter Option from [0-10] ";int opt;cin>>opt;
    bool chk;
    string res;
    switch(opt){

        case 1:
            try{
            Display_All_User();
            }catch(const char* e){cout<<e<<" : Enter Any Key To RETURN :";cin>>res;return;}
            Administration();
            break;
        case 2:
            try{
            Search_User();
            }catch(const char* e){cout<<e<<" : Enter Any Key To RETURN :";cin>>res;return;}
            Administration();
            break;
        case 3:try{
            chk = U.Add_User();
            if(chk) {cout<<"Added Successfully\n";} else {cout<<"Error : User Not Added\n";};
            cout<<"Enter 0 to return ";cin>>x;
            }catch(const char* e){cout<<e<<" : Enter Any Key To RETURN :";cin>>res;return;}
            Administration();
            break;
        case 4:
            try{
            Delete_User();
            }catch(const char* e){cout<<e<<" : Enter Any Key To RETURN :";cin>>res;return;}
            Administration();
            break;
        case 5:
            try{
            Modify_User();
            }catch(const char* e){cout<<e<<" : Enter Any Key To RETURN :";cin>>res;return;}
            Administration();
            break;
        case 6:
            try{
            Display_All_Book();
            }catch(const char* e){cout<<e<<" : Enter Any Key To RETURN :";cin>>res;return;}
            Administration();
            break;
        case 7:
            try{
            B.Add_Book();
            }catch(const char* e){cout<<e<<" : Enter Any Key To RETURN :";cin>>res;return;}
            Administration();
            break;
        case 8:
            try{
            Delete_Book();
            }catch(const char* e){cout<<e<<" : Enter Any Key To RETURN :";cin>>res;return;}
            Administration();
            break;
        case 9:
            try{
            Modify_Book();
            }catch(const char* e){cout<<e<<" : Enter Any Key To RETURN :";cin>>res;return;}
            Administration();
            break;
        case 10:
            try{
            Display_All_Loan();
            }catch(const char* e){cout<<e<<" : Enter Any Key To RETURN :";cin>>res;return;}
            Administration();
    }


}

//############################################################ LOGIN #######################################################

void Login(){
    system("cls");
    string name;
    string password;
    cout<<"\t\t\t\t\t\tLogin"<<endl;
    cout<<"\t\t\t\t\t\tEnter your UserName(no space) : ";cin>>name;
    cout<<"\t\t\t\t\t\tEnter your password(no space) : ";cin>>password;


    try{
    if(Check_User_Existence(name , password)){
        vector<string> data = Get_User_Info(name , password);
        for(auto i : data){cout<<i<<" ";}
        User P(data[0] , data[1] , data[2] , data[3]);
        P.User_Main_Menu();
    }else{
            cout<<"\n\nUser Not Found : Enter Any Key : ";string x;cin>>x;
            if(x.size() != 0){
                return;
            }

    }
    return ;
    }catch(const char *e){
        throw e;
    }
return;
}

//############################################################ SIGN-IN #######################################################

void SignIn(){
    string x;
    bool chk = U.Add_User();

    if(chk){
         U.User_Main_Menu();
    }else{
        cout<<"Error in SignIn, Enter Any Key : ";cin>>x;return;
    }
}



//############################################################ MAIN MENU #######################################################

int Main_Menu(){
system("cls");
int exit_code = 0;
int option;
cout<<"\t######################################  LIBRARY MANAGEMENT  ######################################\n"<<endl;
cout<<"\t\t\t\t\t\t 1. User Login "<<endl;
cout<<"\t\t\t\t\t\t 2. User SignIn "<<endl;
cout<<"\t\t\t\t\t\t 3. Administration"<<endl;
cout<<"\t\t\t\t\t\t 4. EXIT"<<endl;
cout<<"\t\t\t\t\t\t Enter option from [1-4]: ";cin>>option;
string key;
string err;
switch(option)
{
    case 1:
        try{
        Login();
        }catch(const char*e){
            cout<<e<<endl;
        }
        break;
    case 2:
        try{
        SignIn();
        }catch(const char* e){
            cout<<e<<endl;
        }
        break;
    case 3:
        system("cls");
        cout<<"Enter key 0 to return\n";
        cout<<"Enter Access Key(Key : AAYUSH) : ";cin>>key;
        if(key == "0"){
            Main_Menu();
        }
        if(key == "AAYUSH"){
        Administration();
        }
        break;
    case 4:
        exit_code = 1;
        break;
    default:
        cout<<"\n\n\nInValid Option\n"<<endl;
        return Main_Menu();

}


return exit_code;
}

int main(){

int exit_code = 0;

while(!exit_code){
exit_code = Main_Menu();
}

cout<<"Thanks"<<endl;



return 0;
}
