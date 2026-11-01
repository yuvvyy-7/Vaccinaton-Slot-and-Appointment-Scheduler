#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>
using namespace std;

// Converts DD-MM-YYYY into a day count for checking the dose gap.
int dateToDays(const string& date) {
    tm enteredDate = {};
    istringstream input(date);
    input >> get_time(&enteredDate, "%d-%m-%Y");

    if (input.fail()) return -1;

    int day = enteredDate.tm_mday;
    int month = enteredDate.tm_mon;
    int year = enteredDate.tm_year;

    enteredDate.tm_hour = 12;
    time_t timestamp = mktime(&enteredDate);
    if (timestamp == -1) return -1;

    tm* checkedDate = localtime(&timestamp);
    if (checkedDate == nullptr || checkedDate->tm_mday != day ||
        checkedDate->tm_mon != month || checkedDate->tm_year != year) {
        return -1;
    }

    return static_cast<int>(timestamp / 86400);
}

class Patient {
private:
    int id;
    string name;
    int age;
    string phone;
    bool dose1Taken;
    bool dose2Taken;
    string vaccineName;
    string dose1Date;
    int recommendedGap;

public:
    Patient(int id, string name, int age, string phone)
        : id(id), name(name), age(age), phone(phone),
          dose1Taken(false), dose2Taken(false), recommendedGap(0) {}

    int getId() const {
        return id;
    }

    bool hasDose1() const {
        return dose1Taken;
    }

    bool hasDose2() const {
        return dose2Taken;
    }

    string getVaccineName() const {
        return vaccineName;
    }

    string getDose1Date() const {
        return dose1Date;
    }

    int getRecommendedGap() const {
        return recommendedGap;
    }

    void recordDose1(string vaccine, string date, int gap) {
        dose1Taken = true;
        vaccineName = vaccine;
        dose1Date = date;
        recommendedGap = gap;
    }

    void recordDose2() {
        dose2Taken = true;
    }

    void display() const {
        cout << endl;
        string doseStatus = dose2Taken ? "2 Doses" :
                            dose1Taken ? "1 Dose" : "No Dose";

        cout << left << setw(10) << id << setw(20) << name
             << setw(10) << age << setw(15) << phone
             << doseStatus << '\n';
    }
};

class VaccinationSlot {
private:
    int id;
    string center;
    string vaccine;
    string date;
    string time;
    int capacity;
    int booked;
    int recommendedGap;

public:
    VaccinationSlot(int id, string center, string vaccine,
                    string date, string time, int capacity, int gap)
        : id(id), center(center), vaccine(vaccine), date(date), time(time),
          capacity(capacity), booked(0), recommendedGap(gap) {}

    int getId() const {
        return id;
    }

    string getVaccine() const {
        return vaccine;
    }

    int getRecommendedGap() const {
        return recommendedGap;
    }

    int getAvailable() const {
        return capacity - booked;
    }

    bool book() {
        if (booked >= capacity) return false;
        booked++;
        return true;
    }

    void releaseSeat() {
        if (booked > 0) booked--;
    }

    void display() const {
        cout << endl;
        cout << left << setw(8) << id << setw(18) << center
             << setw(15) << vaccine << setw(15) << date
             << setw(10) << time << setw(10) << capacity
             << setw(10) << booked << setw(10) << getAvailable()
             << recommendedGap << " days\n";
    }
};

class Appointment {
private:
    int id;
    int patientId;
    int slotId;
    bool booked;

public:
    Appointment(int id, int patientId, int slotId)
        : id(id), patientId(patientId), slotId(slotId), booked(true) {}

    int getId() const {
        return id;
    }

    int getPatientId() const {
        return patientId;
    }

    int getSlotId() const {
        return slotId;
    }

    bool isBooked() const {
        return booked;
    }

    void cancel() {
        booked = false;
    }

    void display() const {
        cout << endl;
        cout << left << setw(15) << id << setw(12) << patientId
             << setw(10) << slotId << (booked ? "Booked" : "Cancelled") << '\n';
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

    Patient* findPatient(int id) {
        for (auto& patient : patients)
            if (patient.getId() == id) return &patient;
        return nullptr;
    }

    VaccinationSlot* findSlot(int id) {
        for (auto& slot : slots)
            if (slot.getId() == id) return &slot;
        return nullptr;
    }

    Appointment* findAppointment(int id) {
        for (auto& appointment : appointments)
            if (appointment.getId() == id) return &appointment;
        return nullptr;
    }

    void showAppointmentHeader() const {
        cout << endl;
        cout << left << setw(15) << "Appointment ID"
             << setw(12) << "Patient ID" << setw(10) << "Slot ID"
             << "Status\n";
        cout << string(48, '-') << '\n';
    }

public:
    void registerPatient() {
        string name, phone;
        int age;

        cout << "Enter patient name: ";
        cin >> ws;
        getline(cin, name);

        cout << "Enter age: ";
        cin >> age;
        cout << "Enter phone number: ";
        cin >> phone;

        if (age <= 0) {
            cout << endl;
            cout << "\nInvalid age. Registration cancelled.\n";
            return;
        }

        patients.emplace_back(nextPatientId, name, age, phone);
        cout << endl;
        cout << "\nPatient registered. Patient ID: " << nextPatientId++ << '\n';
    }

    void addSlot() {
        string center, vaccine, date, time;
        int capacity, gap;

        cout << "Enter vaccination center: ";
        cin >> ws;
        getline(cin, center);
        cout << "Enter vaccine name: ";
        getline(cin, vaccine);
        cout << "Enter date (DD-MM-YYYY): ";
        cin >> date;
        cout << "Enter time: ";
        cin >> time;
        cout << "Enter slot capacity: ";
        cin >> capacity;
        cout << "Enter recommended gap between doses (days): ";
        cin >> gap;

        if (capacity <= 0 || gap <= 0) {
            cout << endl;
            cout << "\nCapacity and recommended gap must be greater than zero.\n";
            return;
        }

        slots.emplace_back(nextSlotId, center, vaccine, date, time, capacity, gap);
        cout << endl;
        cout << "\nSlot added. Slot ID: " << nextSlotId++ << '\n';
    }

    void displayPatients() const {
        if (patients.empty()) {
            cout << endl;
            cout << "\nNo patients registered.\n";
            return;
        }
        cout << endl;
        cout << left << setw(10) << "Patient ID" << setw(20) << "Name"
             << setw(10) << "Age" << setw(15) << "Phone" << "Dose Status\n";
        cout << string(75, '-') << '\n';

        for (const auto& patient : patients)
            patient.display();
    }

    void displayAvailableSlots() const {
        bool found = false;

        cout << endl;
        cout << left << setw(8) << "Slot ID" << setw(18) << "Center"
             << setw(15) << "Vaccine" << setw(15) << "Date"
             << setw(10) << "Time" << setw(10) << "Capacity"
             << setw(10) << "Booked" << setw(10) << "Available"
             << "Dose Gap\n";
        cout << string(112, '-') << '\n';

        for (const auto& slot : slots) {
            if (slot.getAvailable() > 0) {
                slot.display();
                found = true;
            }
        }

        if (!found) cout << "\nNo available slots.\n";
    }

    void bookAppointment() {
        int patientId, slotId;

        cout << "Enter patient ID: ";
        cin >> patientId;
        if (findPatient(patientId) == nullptr) {
            cout << "Patient not found.\n";
            return;
        }

        cout << "Enter slot ID: ";
        cin >> slotId;
        VaccinationSlot* slot = findSlot(slotId);

        if (slot == nullptr) {
            cout << "\nSlot not found.\n";
            return;
        }

        for (const auto& appointment : appointments) {
            if (appointment.getPatientId() == patientId &&
                appointment.getSlotId() == slotId && appointment.isBooked()) {
                cout << "\nPatient already has this slot booked.\n";
                return;
            }
        }

        if (!slot->book()) {
            cout << "\nThis slot is fully booked.\n";
            return;
        }

        appointments.emplace_back(nextAppointmentId, patientId, slotId);
        cout << "\nAppointment booked. Appointment ID: " << nextAppointmentId++ << '\n';
    }

    void cancelAppointment() {
        int id;
        cout << "Enter appointment ID: ";
        cin >> id;

        Appointment* appointment = findAppointment(id);
        if (appointment == nullptr) {
            cout << "\nAppointment not found.\n";
            return;
        }
        if (!appointment->isBooked()) {
            cout << "\nAppointment is already cancelled.\n";
            return;
        }

        VaccinationSlot* slot = findSlot(appointment->getSlotId());
        if (slot != nullptr) slot->releaseSeat();
        appointment->cancel();

        cout << "\nAppointment cancelled.\n";
    }

    void recordDose1() {
        int patientId, slotId;
        string date;

        cout << "Enter patient ID: ";
        cin >> patientId;
        Patient* patient = findPatient(patientId);
        if (patient == nullptr) {
            cout << "\nPatient not found.\n";
            return;
        }
        if (patient->hasDose1()) {
            cout << "\nDose 1 has already been recorded.\n";
            return;
        }

        cout << "Enter slot ID (to select vaccine): ";
        cin >> slotId;
        VaccinationSlot* slot = findSlot(slotId);
        if (slot == nullptr) {
            cout << "\nSlot not found.\n";
            return;
        }

        cout << "Enter Dose 1 date (DD-MM-YYYY): ";
        cin >> date;
        if (dateToDays(date) == -1) {
            cout << "\nInvalid date format or date.\n";
            return;
        }

        patient->recordDose1(slot->getVaccine(), date, slot->getRecommendedGap());
        cout << "\nDose 1 recorded successfully. Recommended gap: "
             << slot->getRecommendedGap() << " days.\n";
    }

    void recordDose2() {
        int patientId, slotId;
        string date;

        cout << "Enter patient ID: ";
        cin >> patientId;
        Patient* patient = findPatient(patientId);
        if (patient == nullptr) {
            cout << "\nPatient not found.\n";
            return;
        }
        if (!patient->hasDose1()) {
            cout << "\nRecord Dose 1 before Dose 2.\n";
            return;
        }
        if (patient->hasDose2()) {
            cout << "\nDose 2 has already been recorded.\n";
            return;
        }

        cout << "Enter slot ID for Dose 2: ";
        cin >> slotId;
        VaccinationSlot* slot = findSlot(slotId);
        if (slot == nullptr) {
            cout << "\nSlot not found.\n";
            return;
        }
        if (slot->getVaccine() != patient->getVaccineName()) {
            cout << "\nVaccine must match Dose 1.\n";
            return;
        }

        cout << "Enter Dose 2 date (DD-MM-YYYY): ";
        cin >> date;
        int dose1Day = dateToDays(patient->getDose1Date());
        int dose2Day = dateToDays(date);

        if (dose2Day == -1) {
            cout << "\nInvalid date format or date.\n";
            return;
        }
        if (dose2Day - dose1Day < patient->getRecommendedGap()) {
            cout << "\nRecommended gap not completed. Required gap: "
                 << patient->getRecommendedGap() << " days.\n";
            return;
        }

        patient->recordDose2();
        cout << "\nDose 2 recorded successfully. Patient is fully vaccinated.\n";
    }

    void displayAppointments() const {
        if (appointments.empty()) {
            cout << "\nNo appointments found.\n";
            return;
        }

        showAppointmentHeader();
        for (const auto& appointment : appointments)
            appointment.display();
    }

    void displayPatientAppointments() {
        int patientId;
        cout << "Enter patient ID: ";
        cin >> patientId;

        if (findPatient(patientId) == nullptr) {
            cout << "\nPatient not found.\n";
            return;
        }

        bool found = false;
        showAppointmentHeader();
        for (const auto& appointment : appointments) {
            if (appointment.getPatientId() == patientId) {
                appointment.display();
                found = true;
            }
        }
        if (!found) cout << "\nNo appointments for this patient.\n";
    }

    void run() {
        int choice;

        do {
            cout << "\n===== VACCINATION SLOT & APPOINTMENT SCHEDULER =====\n";
            cout << "1. Register Patient\n";
            cout << "2. Add Vaccination Slot\n";
            cout << "3. View Available Slots\n";
            cout << "4. Book Appointment\n";
            cout << "5. Cancel Appointment\n";
            cout << "6. View Registered Patients\n";
            cout << "7. View All Appointments\n";
            cout << "8. View Patient Appointments\n";
            cout << "9. Record Dose 1\n";
            cout << "10. Record Dose 2\n";
            cout << "0. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1: registerPatient(); break;
                case 2: addSlot(); break;
                case 3: displayAvailableSlots(); break;
                case 4: bookAppointment(); break;
                case 5: cancelAppointment(); break;
                case 6: displayPatients(); break;
                case 7: displayAppointments(); break;
                case 8: displayPatientAppointments(); break;
                case 9: recordDose1(); break;
                case 10: recordDose2(); break;
                case 0: cout << "\nThank you for using the scheduler.\n"; break;
                default: cout << "\nInvalid choice. Try again.\n";
            }
        } while (choice != 0);
    }
};

int main() {
    VaccinationScheduler scheduler;
    scheduler.run();
    return 0;
}
