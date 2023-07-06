#include <iostream>
#include <conio.h>
#include <iomanip> //input-output manipulator
#include <stdlib.h>
#include <cstring>
#include <stdio.h>
#include <fstream>
using namespace std;
#include <windows.h>  

// Function is used to set the cursor position at the specified coordinates
void gotoxy(int x, int y){
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

// Book Class
class book{
    char bookName[50]; // Book Name
    char authorName[20]; // Author Name
    char bookNo[6];    // Book No.
public:

    void createBook(){
        cout << "\n... NEW BOOK ENTRY ...\n";
        cout << "\nENTER BOOK NO: ";
        cin >> bookNo;
        cout << "\nENTER BOOK NAME: ";
        gets(bookName);
        gets(bookName); // enables enter with space
        cout << "\nENTER AUTHOR NAME: ";
        gets(authorName);
        cout << "\n\n\nBook Created......👌👌👌";
    }

    void showBook(){
        cout << "\nBook Number: " << bookNo;
        cout << "\nBook Name: ";
        puts(bookName);
        cout << "\nBook Author Name: ";
        puts(authorName);
    }

    void modifyBook(){
        cout << "\nBook Number: " << bookNo;
        cout << "\nEnter Modified Book Name :";
        gets(bookName);
        cout << "\nEnter Modified Author's Name :";
        gets(authorName);
    }

    char *retBookNo(){ // string return
        return bookNo;
    }

    void report(){
        cout << bookNo << setw(30) << bookName << setw(30) << authorName << endl;
    }
}; // class ends here

class student{
    char admissionNo[6]; // Admission No.
    char studentName[20]; // Student Name
    char studentBookNo[6]; // Student Book No
    int token;     // Total book of student
public:

    void createStudent(){
        system("cls");
        cout << "\nNEW STUDENT ENTRY...\n";
        cout << "\nEnter The Admission No: ";
        cin>>admissionNo;
        cout << "Enter The Student Name ";
        gets(studentName);
        gets(studentName);
        token = 0;
        studentBookNo[0] = '\0';
        cout << "\n\nStudent Record Created...";
    }

    void showStudent(){
        cout << "\nAdmission Number : " << admissionNo;
        cout << "\nStudent Name : ";
        puts(studentName);
        cout << "\nNo of Book Issued : " << token;
        if (token == 1){
            cout << "\nBook Number " << studentBookNo;
        }
    }

    void modifyStudent(){
        cout << "\nAdmission No. " << admissionNo;
        cout << "\nModify Student Name : ";
        gets(studentName);
    }

    char *retAdmNo(){
        return admissionNo;
    }

    char *retStuBookNo(){
        return studentBookNo;
    }

    int retToken(){
        return token;
    }

    void addToken(){
        token = 1;
    }

    void resetToken(){
        token = 0;
    }

    void getStuBookNo(char t[]){
        strcpy(studentBookNo, t);
    }

    void report(){
        cout << "\t" << admissionNo << setw(20) << studentName << setw(10) << token << endl;
    }
}; // class ends here

fstream fp, fp1; // object
book bk;         // book class object
student st;      // student class object

void writeBook(){
    char ch;
    fp.open("book.txt", ios::out | ios::app); // write and append data
    do{
        system("cls");
        bk.createBook();
        fp.write((char *)&bk, sizeof(book)); // size of class
        cout << "\n\nDo you want to add more record...(y/n?) ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void writeStudent(){
    char ch;
    fp.open("student.txt", ios::out | ios::app); // write and append data
    do{
        system("cls");
        st.createStudent();
        fp.write((char *)&st, sizeof(student)); // size of class
        cout << "\n\nDo you want to add more record...(y/n?) ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void displaySpecificBook(char n[]){
    cout << "\nBOOK DETAILS\n";
    int flag = 0;                 // book not found
    fp.open("book.txt", ios::in); // read data
    while (fp.read((char *)&bk, sizeof(book))){
        if (strcmpi(bk.retBookNo(), n) == 0){ // not case sensitive
            bk.showBook();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0){ // book not found
        cout << "\n\nBook does not exist";
    }
    getch();
}

void displaySpecificStudent(char n[]){
    cout << "\nSTUDENT DETAILS\n";
    int flag = 0;                    // student not found
    fp.open("student.txt", ios::in); // read data
    while (fp.read((char *)&st, sizeof(student))){
        if (strcmpi(st.retAdmNo(), n) == 0){ // not case sensitive
            st.showStudent();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0){ // student not found
        cout << "\n\nStudent does not exist";
    }
    getch();
}

void modifyBook(){
    char n[6];
    int found = 0; // seach book of given data
    system("cls");
    cout << "\n\nMODIFY BOOK RECORD...";
    cout << "\n\nEnter the book no. ";
    cin >> n;
    fp.open("book.txt", ios::in | ios::out);
    while (fp.read((char *)&bk, sizeof(book)) && found == 0){
        if (strcmpi(bk.retBookNo(), n) == 0){
            bk.showBook();
            cout << "\nEnter the new details book";
            bk.modifyBook();
            int pos = (int)(-1 * sizeof(bk));
            fp.seekp(pos, ios::cur); // back from current position
            fp.write((char *)&bk, sizeof(book));
            cout << "\n\nRecord Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0){
        cout << "\n\nRecord Not Found";
    }
    getch(); // press key to get out
}
void modifyStudent(){
    char n[6];
    int found = 0; // seach book of given data
    system("cls");
    cout << "\n\nMODIFY STUDENT RECORD...";
    cout << "\n\nEnter the Admission no. ";
    cin >> n;
    fp.open("student.txt", ios::in | ios::out);
    while (fp.read((char *)&st, sizeof(student)) && found == 0){
        if (strcmpi(st.retAdmNo(), n) == 0){
            st.showStudent();
            cout << "\nEnter the new details of student";
            st.modifyStudent();
            int pos = (int)(-1 * sizeof(st));
            fp.seekp(pos, ios::cur); // back from current position
            fp.write((char *)&st, sizeof(student));
            cout << "\n\nRecord Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0){
        cout << "\n\nRecord Not Found";
    }
    getch(); // press key to get out
}

void deleteStudent(){
    char n[6];
    int flag = 0;
    system("cls");
    cout << "\n\n\n\tDELETE STUDENT...";
    cout << "\n\nEnter the Admission no> : ";
    cin >> n;
    fp.open("student.txt", ios::in | ios::out);
    fstream fp2;
    fp2.open("temp.txt", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char *)&st, sizeof(student))){
        if (strcmpi(st.retAdmNo(), n) != 0)
            fp2.write((char *)&st, sizeof(student));
        else
            flag = 1; // student found
    }
    fp2.close();
    fp.close();
    remove("student.txt");
    rename("temp.txt", "student.txt"); // data after deletion moved to temp
    if (flag == 1)
        cout << "\n\n\tRecord Deleted..";
    else
        cout << "\n\nRecord not Found";
    getch();
}

void deleteBook(){
    char n[6]; // book no.
    int flag = 0;
    system("cls");
    cout << "\n\n\n\tDELETE BOOK...";
    cout << "\n\nEnter the Book no> : ";
    cin >> n;
    fp.open("book.txt", ios::in | ios::out);
    fstream fp2;                    // New onject
    fp2.open("Temp.txt", ios::out); // temp having data else than that to be deleted
    fp.seekg(0, ios::beg);
    while (fp.read((char *)&bk, sizeof(book))){
        if (strcmpi(bk.retBookNo(), n) != 0)
            fp2.write((char *)&st, sizeof(book));
        else
            flag = 1; // student found
    }
    fp2.close();
    fp.close();
    remove("book.txt");
    rename("Temp.txt", "book.txt"); // data after deletion moved to temp
    if (flag == 1)
        cout << "\n\n\tRecord Deleted... ";
    else
        cout << "\n\nRecord not Found";
    getch();
}

void displayAllStudents(){
    system("cls");
    fp.open("student.txt", ios::in); // read mode
    if (!fp){
        cout << "File Could Not Be Open";
        getch();
        return; // press any key and return
    }
    cout << "\n\n\t\tStudent List\n\n";
    cout << "==================================================================\n";
    cout << "\tAdmission No." << setw(10) << "Name" << setw(20) << "Book Issued\n";
    cout << "==================================================================\n";
    while (fp.read((char *)&st, sizeof(student))){
        st.report();
    }
    fp.close();
    getch();
}

void displayAllBooks(){
    system("cls");
    fp.open("book.txt", ios::in); // read mode
    if (!fp){
        cout << "File Could Not Be Open";
        getch();
        return; // press any key and return
    }
    cout << "\n\n\t\tBook List\n\n";
    cout << "==================================================================\n";
    cout << "\tBook No." << setw(20) << "Book Name" << setw(25) << "Book Author\n";
    cout << "==================================================================\n";
    while (fp.read((char *)&bk, sizeof(book))){
        bk.report();
    }
    fp.close();
    getch();
}

void bookIssue(){
    char sn[6], bn[6];
    int found = 0, flag = 0;
    system("cls");
    cout << "\n\nBOOK ISSUE...";
    cout << "\n\n\tEnter Admission no.";
    cin >> sn;
    fp.open("student.txt", ios::in | ios::out);
    fp1.open("book.txt", ios::in | ios::out);
    while (fp.read((char *)&st, sizeof(student)) && found == 0){
        if (strcmpi(st.retAdmNo(), sn) == 0){ // compare admsn no.
            found = 1;
            if (st.retToken() == 0){ // if book not issued
                cout << "\n\n\tEnter The Book No.";
                cin >> bn;
                while (fp1.read((char *)&bk, sizeof(book)) && flag == 0){
                    if (strcmpi(bk.retBookNo(), bn) == 0){ // compare book no.
                        flag = 1;
                        st.addToken();
                        st.getStuBookNo(bk.retBookNo()); // pass book no.
                        int pos = (int)(-1 * sizeof(st));
                        fp.seekg(pos, ios::cur);
                        fp.write((char *)&st, sizeof(student));
                        cout << "\n\n\tBook Issued Successfully\n\n Please Note The Book Issue Date On Backside Of Your Book And Return Book Within 15 Days, Otherwise Fine Of 15 Rs Per Day";
                    }
                }
                if (flag == 0){
                    cout << "Book No. Does Not Exists";
                }
            }
            else{
                cout << "You Have Not Returned The Last Book";
            }
        }
    }
    if (found == 0){
        cout << "Student Record Not Exists...";
    }
    getch();
    fp.close();
    fp1.close();
}

void bookDeposit(){
    char sn[6], bn[6];
    int found = 0, flag = 0, day, fine;
    system("cls");
    cout << "\n\nBOOK DEPOSIT...";
    cout << "\n\n\tEnter Admission no. Of Student";
    cin >> sn;
    fp.open("student.txt", ios::in | ios::out);
    fp1.open("book.txt", ios::in | ios::out);
    while (fp.read((char *)&st, sizeof(student)) && found == 0){
        if (strcmpi(st.retAdmNo(), sn) == 0){ // compare admsn no.
            found = 1;
            if (st.retToken() == 1){ // if book issued
                while (fp1.read((char *)&bk, sizeof(book)) && flag == 0){
                    if (strcmpi(bk.retBookNo(), st.retStuBookNo()) == 0){
                        flag = 1;
                        bk.showBook();
                        cout << "\n\n Book Deposited In No. Of Days";
                        cin >> day;
                        if (day > 15){
                            fine = (day - 15) * 1;
                            cout << "\n\n Fine = " << fine;
                        }
                        st.resetToken();
                        int pos = (int)(-1 * sizeof(st));
                        fp.seekg(pos, ios::cur);
                        fp.write((char *)&st, sizeof(student));
                        cout << "\n\n\tBook Deposited Successfully";
                    }
                }
                if (flag == 0){
                    cout << "Book No. Does Not Exists";
                }
            }
            else{
                cout << "No Book Issued";
            }
        }
    }
    if (found == 0){
        cout << "Student Record Not Exists...";
    }
    getch();
    fp.close();
    fp1.close();
}

void start(){
    // system("cls");
    gotoxy(35, 11);
    cout << "WELCOME TO LIBRARY";
    gotoxy(35, 14);
    cout << " MANAGEMENT";
    gotoxy(35, 17);
    cout << " SYSTEM";
    cout << " \n  by: Amit";
    getch();
}

void adminMenu(){
    system("cls");
    string s;
    getline(cin,s);

    int ch2;
    cout << "\n\n\n\tADMINISTRATOR MENU";
    cout << "\n\n\n\t1.CREATE STUDENT RECORD";
    cout << "\n\t2.DISPLAY ALL STUDENT RECORD";
    cout << "\n\t3.DISPLAY SPECIFIC STUDENT RECORD";
    cout << "\n\t4.MODIFY STUDENT RECORD";
    cout << "\n\t5.DELETE STUDENT RECORD";
    cout << "\n\t6.CREATE BOOK";
    cout << "\n\t7.CREATE ALL BOOKS";
    cout << "\n\t8.DISPLAY SPECIFIC BOOK";
    cout << "\n\t9.MODIFY BOOK RECORD";
    cout << "\n\t10.DELETE BOOK RECORD";
    cout << "\n\t11.BACK TO MAIN MENU";
    cout << "\n\n\n\tPLEASE ENTER YOUR CHOICE(1-11)";
    cin >> ch2;
    switch (ch2){
    case 1:
        writeStudent();
        break;
    case 2:
        displayAllStudents();
        break;
    case 3:
        char num[6];
        system("cls");
        cout << "\n\n\t Please enter admission no.";
        cin >> num;
        displaySpecificStudent(num);
        break;
    case 4:
        modifyStudent();
        break;
    case 5:
        deleteStudent();
        break;
    case 6:
        writeBook();
        break;
    case 7:
        displayAllBooks();
        break;
    case 8:{
        char num[6];
        system("cls");
        cout << "\n\n\tPlease enter book no: ";
        cin >> num;
        displaySpecificBook(num);
        break;
    }
    case 9:
        modifyBook();
        break;
    case 10:
        deleteBook();
        break;
    case 11:
        return;
    default:
        cout << "Invalid choice";
    }
    adminMenu();
}
signed main(){
    char ch;
    system("cls");
    system("Color E2"); //CLI color changer
    start();
    do{
        system("cls");
        cout << "\n\n\n\t MAIN MENU";
        cout << "\n\n\t1 BOOK ISSUE";
        cout << "\n\n\t2 BOOK DEPOSIT";
        cout << "\n\n\t3 ADMINISTRATOR MENU";
        cout << "\n\n\t4 EXIT";
        cout << "\n\n\t PLEASE SELECT YOUR OPTION(1-4): ";
        ch = getche();
        switch (ch){
        case '1':
            bookIssue();
            break;
        case '2':
            bookDeposit();
            break;
        case '3':
            adminMenu();
            break;
        case '4':
            exit(0);
            break;
        default:
            cout << "INVALID CHOICE";
        }
    } while (ch != 4);
    return 0;
}