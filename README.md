# Vaccination Slot & Appointment Scheduler

A console app in C++ for managing vaccination appointments. You can register patients, create slots, book and cancel appointments, and keep track of whether someone has had their first and second dose.

## What it does

- Register a patient (each one gets a unique ID)
- Add a vaccination slot with centre name, vaccine name, date, time, capacity and the recommended gap between doses
- Show only the slots that still have seats left
- Book an appointment for a registered patient
- Block the same patient from booking the same slot twice, and block a slot from going over capacity
- Cancel an appointment, which frees the seat again
- View all patients, all appointments, or the appointments of one patient
- Record Dose 1 and Dose 2
- For Dose 2, check that the vaccine is the same as Dose 1 and that enough days have passed
- Show each patient's status as `No Dose`, `1 Dose` or `2 Doses`
- Reject bad number input so `cin` doesn't get stuck

## Classes

| Class | What it does |
|---|---|
| `Patient` | Patient details and dose info |
| `VaccinationSlot` | Slot details, capacity, seats booked, dose gap |
| `Appointment` | One appointment, and whether it is booked or cancelled |
| `VaccinationScheduler` | Holds the vectors and runs all the menu options |

## What you need

- A compiler that supports C++17
- A terminal or command prompt

No external libraries, just the standard library.

Check [PROJECT_REQUIREMENTS.md](PROJECT_REQUIREMENTS.md) for the full requirements and scope.

## How to run

Windows (g++ / MinGW):

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic vaccination_scheduler.cpp -o vaccination_scheduler.exe
.\vaccination_scheduler.exe
```

Linux / macOS:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic vaccination_scheduler.cpp -o vaccination_scheduler
./vaccination_scheduler
```

## Menu

1. Register Patient
2. Add Vaccination Slot
3. View Available Slots
4. Book Appointment
5. Cancel Appointment
6. View Registered Patients
7. View All Appointments
8. View Patient Appointments
9. Record Dose 1
10. Record Dose 2
0. Exit

## How to record doses

1. Register the patient.
2. Add a slot for the vaccine and enter the recommended gap in days.
3. Record Dose 1: enter the patient ID, the slot ID (this is how the program knows which vaccine), and the date.
4. Record Dose 2: pick a slot with the same vaccine and enter the date.
5. The program compares the two dates and only accepts Dose 2 if the gap is long enough.

Dates are typed in as `DD-MM-YYYY`. The program doesn't read the system date, so the slot date and time are also typed in by hand.

## Input checking

All number inputs go through one shared function. It rejects text, decimals, and anything with extra characters after the number. If the input is wrong, you go back to the menu (or the current step) and the input stream is cleared, so it doesn't break.

Dose dates are also checked to be real calendar dates before the gap is calculated.

## Limitations

- Everything is stored in vectors, so all data is lost when you close the program
- No file handling and no database
- It's a console app made for a college project demo
- It isn't connected to any real vaccination system and doesn't check medical guidelines. The dose gap is whatever the user enters, so use a proper source for it
- Not included: waiting list, certificates, centre-wise reports, and separate roles for citizens and centre admins

## Files

- `vaccination_scheduler.cpp`: the source code
- `README.md`: this file
- `PROJECT_REQUIREMENTS.md`: requirements and scope
