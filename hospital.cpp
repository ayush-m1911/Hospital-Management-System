#include <iostream>
#include <string>
#include<fstream>
using namespace std;

class Person {
protected:
    int id;
    string name;
    string phone;

public:
    Person(int p_id, string p_name, string p_phone) {
        id = p_id;
        name = p_name;
        phone = p_phone;
    }

    void showPersonDetails() {
        cout << "ID: " << id << ", Name: " << name << ", Contact: " << phone << endl;
    }
};

#include <iostream>
using namespace std;

typedef struct month
{
    int month;
    int year;
}Month;

typedef struct expdate
{
    int date;
    Month m;
}Exp;

typedef struct quant
{
    int amount;
    double price;
    Exp ddate;
}Quant;

typedef struct attendance
{
    Month m;
    int attain[31];
    Att *down;
}Att;

typedef struct time
{
    int hour;
    int min;
}Time;

typedef struct schedule
{
    int date;
    Month m;
    Time t;
}Sch;

typedef struct amt
{
    Month m;
    double amt;
    Amt *next,*prev;
}Amt;

Amt *head=NULL;

void show_amt_bankbal()
{
    if (head==NULL)
    {
        cout << "The history as well as current balence is 0";
    }
    else
    {
        Amt *temp = head;
        while (temp->next!=NULL)
        {
            temp=temp->next;
        }
        cout << "Month :" << temp->m.month << "\t" << "Year :" << temp->m.year << endl;
        cout << "Amount :" << temp->amt << endl;
    }   
}

void show_history_bankbal()
{
    if (head==NULL)
    {
        cout << "The history as well as current balence is 0";
    }
    else
    {
        Amt *temp = head;
        cout << "The bank account history is :\n";
        while (temp!=NULL)
        {
            cout << "Month :" << temp->m.month << "\t" << "Year :" << temp->m.year << endl;
            cout << "Amount :" << temp->amt << endl << endl;
            temp=temp->next;
        }
    }    
}

static int flag=2005;
class staff
{
private:
    int staff_ID;
    double salary;
    Att *attendance;
    Sch schedule;
public:
    staff();
    ~staff();
    void salary_assign(Amt **head);
};

staff::staff()
{
    cout << "Enter the salary of this guy :\t";
    cin >> salary;
    staff_ID=flag;
    flag++;
}

staff::~staff()
{
}

void staff::salary_assign(Amt **head)
{
    int days=0;
    Att *temp=attendance;
    for (int i = 0; i < attendance->m.month; i++)
    {
        temp=temp->down;
    }
    for (int i = 0; i < 31; i++)
    {
        if (temp->attain[i]==1)
        {
            days++;
        }
    }
    (head)->amt-=days(int)(salary/30);
}

class inventory
{
private:
    Quant A;
public:
    inventory();
    ~inventory();
    void refill(Amt **head);
};

inventory::inventory()
{
    A.amount=70;
    cout << "Enter the price of this Inventory item :\t";
    cin >> A.price;
}

void inventory::refill(Amt **head)
{
    if (A.amount<70)
    {
        (head)->amt-=(70-A.amount)(A.price);
        A.amount=70;
    }
}

class Doctor : public Person {
protected:
    string specialization;

public:
    Doctor(int doc_id, string doc_name, string doc_phone, string spec)
        : Person(doc_id, doc_name, doc_phone) {
        specialization = spec;
    }

    void showDoctorDetails() {
        showPersonDetails();
        cout << "Specialization: " << specialization << endl;
    }
};

class Patient : public Person {
protected:
    string illness;

public:
    Patient(int pat_id, string pat_name, string pat_phone, string disease)
        : Person(pat_id, pat_name, pat_phone) {
        illness = disease;
    }

    void showPatientDetails() {
        showPersonDetails();
        cout << "Illness: " << illness << endl;
    }
};

class Billing : public Doctor, public Patient {
private:
    double totalAmount;
    string paymentStatus;

public:
    Billing(int doc_id, string doc_name, string doc_phone, string spec, 
            int pat_id, string pat_name, string pat_phone, string disease, 
            double amount, string status)
        : Doctor(doc_id, doc_name, doc_phone, spec), 
          Patient(pat_id, pat_name, pat_phone, disease) {
        totalAmount = amount;
        paymentStatus = status;
    }

    void showBillingDetails() {
        cout << "Billing Info:" << endl;
        cout << "Doctor ID: " << Doctor::id << ", Patient ID: " << Patient::id << endl;
        cout << "Amount: $" << totalAmount << ", Payment Status: " << paymentStatus << endl;
    }

    void updateAmount(double newAmount) {
        totalAmount = newAmount;
    }

    void updatePaymentStatus(string newStatus) {
        paymentStatus = newStatus;
    }
};

int main() {
    Doctor doc(101, "Dr. Smith", "1234567890", "Cardiology");
    Patient pat(201, "John Doe", "0987654321", "Heart Disease");
    Billing bill(101, "Dr. Smith", "1234567890", "Cardiology", 
                 201, "John Doe", "0987654321", "Heart Disease", 
                 1500.00, "Unpaid");

    cout << "Doctor Details:" << endl;
    doc.showDoctorDetails();
    cout << endl;

    cout << "Patient Details:" << endl;
    pat.showPatientDetails();
    cout << endl;

    cout << "Billing Details:" << endl;
    bill.showBillingDetails();
    cout << endl;

    bill.updateAmount(2000.00);
    bill.updatePaymentStatus("Paid");

    cout << "Updated Billing Details:" << endl;
    bill.showBillingDetails();

    return 0;
}
