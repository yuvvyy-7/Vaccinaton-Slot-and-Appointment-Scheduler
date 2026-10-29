#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

class Patient {
private:
    int patientId;
    string name;
    int age;
    string phone;

public:
    Patient(int id, string name, int age, string phone)
        : patientId(id), name(name), age(age), phone(phone) {}

    int getId() const {
        return patientId;
    }

    string getName() const {
        return name;
    }

    void display() const {
        cout << left
             << setw(10) << patientId
             << setw(20) << name
             << setw(10) << age
             << setw(15) << phone << '\n';
    }
};

class VaccinationSlot {
private:
    int slotId;
    string centerName;
    string vaccineName;
    string date;
    string time;
    int capacity;
    int booked;

public:
    VaccinationSlot(
        int id,
        string center,
        string vaccine,
        string date,
        string time,
        int capacity
    )
        : slotId(id),
          centerName(center),
          vaccineName(vaccine),
          date(date),
          time(time),
          capacity(capacity),
          booked(0) {}

    int getId() const {
        return slotId;
    }

    int getAvailableSeats() const {
        return capacity - booked;
    }

    bool bookSlot() {
        if (booked >= capacity) {
            return false;
        }

        booked++;
        return true;
    }

    void cancelBooking() {
        if (booked > 0) {
            booked--;
        }
    }

    void display() const {
        cout << left
             << setw(8) << slotId
             << setw(20) << centerName
             << setw(15) << vaccineName
             << setw(15) << date
             << setw(10) << time
             << setw(10) << capacity
             << setw(10) << booked
             << setw(10) << getAvailableSeats()
             << '\n';
    }
};

class Appointment {
private:
    int appointmentId;
    int patientId;
    int slotId;
    string status;

public:
    Appointment(int id, int patient, int slot)
        : appointmentId(id),
          patientId(patient),
          slotId(slot),
          status("Booked") {}

    int getAppointmentId() const {
        return appointmentId;
    }

    int getPatientId() const {
        return patientId;
    }

    int getSlotId() const {
        return slotId;
    }

    string getStatus() const {
        return status;
    }

    void cancel() {
        status = "Cancelled";
    }

    void display() const {
        cout << left
             << setw(15) << appointmentId
             << setw(12) << patientId
             << setw(10) << slotId
             << setw(15) << status
             << '\n';
    }
};

class VaccinationScheduler {
private:
    vector<Patient> patients;
    vector<VaccinationSlot> slots;
    vector<Appointment> appointments;

    int nextPatientId = 1001;
    int nextSlotId = 1;
    int nextAppointmentId = 5001;

    Patient* findPatient(int patientId) {
        for (auto& patient : patients) {
            if (patient.getId() == patientId) {
                return &patient;
            }
        }

        return nullptr;
    }

    VaccinationSlot* findSlot(int slotId) {
        for (auto& slot : slots) {
            if (slot.getId() == slotId) {
                return &slot;
            }
        }

        return nullptr;
    }

    Appointment* findAppointment(int appointmentId) {
        for (auto& appointment : appointments) {
            if (appointment.getAppointmentId() == appointmentId) {
                return &appointment;
            }
        }

        return nullptr;
    }

public:
    void registerPatient() {
        string name;
        string phone;
        int age;

        cout << "\nEnter patient name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter age: ";
        cin >> age;

        cout << "Enter phone number: ";
        cin >> phone;

        patients.emplace_back(
            nextPatientId,
            name,
            age,
            phone
        );

        cout << "\nPatient registered successfully.\n";
        cout << "Patient ID: " << nextPatientId << '\n';

        nextPatientId++;
    }

    void addSlot() {
        string centerName;
        string vaccineName;
        string date;
        string time;
        int capacity;

        cout << "\nEnter vaccination center: ";
        cin.ignore();
        getline(cin, centerName);

        cout << "Enter vaccine name: ";
        getline(cin, vaccineName);

        cout << "Enter date (DD-MM-YYYY): ";
        cin >> date;

        cout << "Enter time: ";
        cin >> time;

        cout << "Enter slot capacity: ";
        cin >> capacity;

        slots.emplace_back(
            nextSlotId,
            centerName,
            vaccineName,
            date,
            time,
            capacity
        );

        cout << "\nSlot added successfully.\n";
        cout << "Slot ID: " << nextSlotId << '\n';

        nextSlotId++;
    }

    void displaySlots() const {
        if (slots.empty()) {
            cout << "\nNo vaccination slots available.\n";
            return;
        }

        cout << "\nAvailable Vaccination Slots\n\n";

        cout << left
             << setw(8) << "ID"
             << setw(20) << "Center"
             << setw(15) << "Vaccine"
             << setw(15) << "Date"
             << setw(10) << "Time"
             << setw(10) << "Capacity"
             << setw(10) << "Booked"
             << setw(10) << "Available"
             << '\n';

        cout << string(98, '-') << '\n';

        for (const auto& slot : slots) {
            if (slot.getAvailableSeats() > 0) {
                slot.display();
            }
        }
    }

    void bookAppointment() {
        int patientId;
        int slotId;

        cout << "\nEnter patient ID: ";
        cin >> patientId;

        Patient* patient = findPatient(patientId);

        if (patient == nullptr) {
            cout << "Patient not found.\n";
            return;
        }

        cout << "Enter slot ID: ";
        cin >> slotId;

        VaccinationSlot* slot = findSlot(slotId);

        if (slot == nullptr) {
            cout << "Slot not found.\n";
            return;
        }

        if (slot->getAvailableSeats() <= 0) {
            cout << "Sorry, this slot is fully booked.\n";
            return;
        }

        for (const auto& appointment : appointments) {
            if (appointment.getPatientId() == patientId &&
                appointment.getSlotId() == slotId &&
                appointment.getStatus() == "Booked") {

                cout << "Patient already has an appointment for this slot.\n";
                return;
            }
        }

        slot->bookSlot();

        appointments.emplace_back(
            nextAppointmentId,
            patientId,
            slotId
        );

        cout << "\nAppointment booked successfully.\n";
        cout << "Appointment ID: " << nextAppointmentId << '\n';

        nextAppointmentId++;
    }

    void cancelAppointment() {
        int appointmentId;

        cout << "\nEnter appointment ID: ";
        cin >> appointmentId;

        Appointment* appointment = findAppointment(appointmentId);

        if (appointment == nullptr) {
            cout << "Appointment not found.\n";
            return;
        }

        if (appointment->getStatus() == "Cancelled") {
            cout << "Appointment is already cancelled.\n";
            return;
        }

        VaccinationSlot* slot = findSlot(
            appointment->getSlotId()
        );

        if (slot != nullptr) {
            slot->cancelBooking();
        }

        appointment->cancel();

        cout << "Appointment cancelled successfully.\n";
    }

    void displayPatients() const {
        if (patients.empty()) {
            cout << "\nNo patients registered.\n";
            return;
        }

        cout << "\nRegistered Patients\n\n";

        cout << left
             << setw(10) << "ID"
             << setw(20) << "Name"
             << setw(10) << "Age"
             << setw(15) << "Phone"
             << '\n';

        cout << string(55, '-') << '\n';

        for (const auto& patient : patients) {
            patient.display();
        }
    }

    void displayAppointments() const {
        if (appointments.empty()) {
            cout << "\nNo appointments found.\n";
            return;
        }

        cout << "\nAppointments\n\n";

        cout << left
             << setw(15) << "Appointment ID"
             << setw(12) << "Patient ID"
             << setw(10) << "Slot ID"
             << setw(15) << "Status"
             << '\n';

        cout << string(52, '-') << '\n';

        for (const auto& appointment : appointments) {
            appointment.display();
        }
    }

    void displayPatientAppointments() {
        int patientId;

        cout << "\nEnter patient ID: ";
        cin >> patientId;

        Patient* patient = findPatient(patientId);

        if (patient == nullptr) {
            cout << "Patient not found.\n";
            return;
        }

        bool found = false;

        cout << "\nAppointments for Patient ID "
             << patientId << "\n\n";

        for (const auto& appointment : appointments) {
            if (appointment.getPatientId() == patientId) {
                appointment.display();
                found = true;
            }
        }

        if (!found) {
            cout << "No appointments found for this patient.\n";
        }
    }

    void run() {
        int choice;

        do {
            cout << "\n========================================\n";
            cout << "   VACCINATION SLOT & APPOINTMENT\n";
            cout << "            SCHEDULER\n";
            cout << "========================================\n";

            cout << "1. Register Patient\n";
            cout << "2. Add Vaccination Slot\n";
            cout << "3. View Available Slots\n";
            cout << "4. Book Appointment\n";
            cout << "5. Cancel Appointment\n";
            cout << "6. View Registered Patients\n";
            cout << "7. View All Appointments\n";
            cout << "8. View Patient Appointments\n";
            cout << "0. Exit\n";

            cout << "\nEnter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    registerPatient();
                    break;

                case 2:
                    addSlot();
                    break;

                case 3:
                    displaySlots();
                    break;

                case 4:
                    bookAppointment();
                    break;

                case 5:
                    cancelAppointment();
                    break;

                case 6:
                    displayPatients();
                    break;

                case 7:
                    displayAppointments();
                    break;

                case 8:
                    displayPatientAppointments();
                    break;

                case 0:
                    cout << "\nThank you for using the scheduler.\n";
                    break;

                default:
                    cout << "\nInvalid choice. Please try again.\n";
            }

        } while (choice != 0);
    }
};

int main() {
    VaccinationScheduler scheduler;
    scheduler.run();

    return 0;
}