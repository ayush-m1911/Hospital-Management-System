#include <iostream>
#include <string>
#include<fstream>
#include<vector>
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

// Appointment class
class Appointment {
public:
    string appointmentID;
    int doctorID;
    int patientID;
    string date;

    // Constructor to initialize appointment details and generate appointment ID
    Appointment(const Doctor& doctor, const Patient& patient, const string& appointmentDate)
        : doctorID(doctor.getId()), patientID(patient.getId()), date(appointmentDate) {
        appointmentID = generateAppointmentID(); // Generate the appointment ID
    }

    // Method to generate the appointment ID using string concatenation
    string generateAppointmentID() const {
        return to_string(doctorID).insert(0, 4 - to_string(doctorID).length(), '0') + // Pad doctor ID with zeros
               to_string(patientID).insert(0, 5 - to_string(patientID).length(), '0') + // Pad patient ID with zeros
               date; // Using DDMM format without year
    }
    string toString() const {
        return "AppID: " + appointmentID + " DocID: " + to_string(doctorID) + " PatID: " + to_string(patientID) + " Date: " + date;
    }
    // Static function to extract doctor ID from appointment ID
     static Appointment fromString(const string& data) {
        size_t pos = 0, prev_pos = 0;
        vector<string> tokens;

        while ((pos = data.find(',', prev_pos)) != string::npos) {
            tokens.push_back(data.substr(prev_pos, pos - prev_pos));
            prev_pos = pos + 1;
        }
        tokens.push_back(data.substr(prev_pos));

        return Appointment(Doctor(stoi(tokens[1]), "", "", ""), 
                           Patient(stoi(tokens[2]), "", "", ""), tokens[3]);
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
