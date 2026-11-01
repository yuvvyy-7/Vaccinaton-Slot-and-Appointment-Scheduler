# Project Requirements

## 1. Project title

**Vaccination Slot & Appointment Scheduler in C++**

## 2. Purpose

The purpose of this project is to create a simple, menu-driven application that manages patient registration, vaccination slot availability, appointment booking and cancellation, and vaccination dose tracking.

## 3. Project scope

The application is a single-user console program. It stores data temporarily in memory using C++ vectors. It supports the first-dose and second-dose tracking workflow, including a check for the recommended gap between doses.

This version intentionally does not include file handling, database storage, a waiting list, automatic waiting-list promotion, vaccination certificate generation, centre-wise reports, or separate citizen and centre-admin login menus.

## 4. Functional requirements

### FR-01: Patient registration

- The system shall allow the user to register a patient.
- The system shall collect the patient's name, age, and phone number.
- The system shall assign a unique patient ID to each registered patient.
- The system shall reject an age that is not greater than zero.

### FR-02: Vaccination slot creation

- The system shall allow the user to create a vaccination slot.
- Each slot shall contain a unique slot ID, centre name, vaccine name, date, time, capacity, and recommended gap between doses in days.
- Capacity and recommended gap must be greater than zero.

### FR-03: View available slots

- The system shall display slots that have at least one available seat.
- The display shall include the slot's centre, vaccine, date, time, capacity, booked count, available count, and recommended dose gap.

### FR-04: Appointment booking

- The system shall allow a registered patient to book an existing slot.
- The system shall reject an unknown patient ID or slot ID.
- The system shall not allow a slot to exceed its capacity.
- The system shall prevent a patient from having the same slot actively booked more than once.
- The system shall generate a unique appointment ID for each successful booking.

### FR-05: Appointment cancellation

- The system shall allow an appointment to be cancelled using its appointment ID.
- The system shall reject an unknown appointment ID and an appointment that is already cancelled.
- Cancelling a booked appointment shall release one seat in the associated slot.

### FR-06: Patient and appointment views

- The system shall display all registered patients and their dose status.
- The system shall display all appointments and their status.
- The system shall display appointments belonging to a selected patient ID.

### FR-07: Dose 1 tracking

- The system shall allow Dose 1 to be recorded for an existing patient who has not already received Dose 1.
- The user shall select an existing slot to identify the vaccine and recommended gap.
- The user shall manually enter the Dose 1 date in `DD-MM-YYYY` format.
- The system shall store the vaccine name, Dose 1 date, and recommended gap in the patient's record.

### FR-08: Dose 2 tracking

- The system shall require Dose 1 to be recorded before Dose 2.
- The system shall not allow Dose 2 to be recorded more than once.
- The user shall select an existing slot for Dose 2.
- The selected slot's vaccine shall match the vaccine recorded for Dose 1.
- The user shall manually enter the Dose 2 date in `DD-MM-YYYY` format.
- The system shall record Dose 2 only when the elapsed calendar days meet or exceed the recommended gap stored during Dose 1 tracking.

### FR-09: Numeric input validation

- The system shall validate integer inputs such as menu choices, age, capacity, recommended gap, patient ID, slot ID, and appointment ID.
- The system shall reject non-integer input and recover without entering an infinite input-failure loop.

### FR-10: Menu navigation

- The system shall provide a menu for the available operations.
- The system shall continue displaying the menu until the user selects Exit.
- The system shall handle an unsupported menu choice with an error message.

## 5. Non-functional requirements

- **Language:** C++.
- **Language standard:** C++17 or later.
- **Interface:** Text-based console interface.
- **Code organisation:** Use classes and encapsulation to separate patient, slot, appointment, and scheduler responsibilities.
- **Data structures:** Use STL vectors to store patients, slots, and appointments during execution.
- **Dependencies:** C++ standard library only; no third-party packages are required.
- **Usability:** Prompts and menu labels should be understandable to a beginner user.
- **Maintainability:** Keep methods and class responsibilities straightforward so the code can be explained and modified easily.

## 6. Input and data rules

- Patient age must be a positive integer.
- Slot capacity must be a positive integer.
- Recommended gap must be a positive integer representing days.
- Dose dates must be entered in `DD-MM-YYYY` format and must represent valid calendar dates.
- Slot date and time are entered manually by the user.
- The program does not use the computer's current date/time as a live appointment timestamp.

## 7. Expected outputs

- A patient ID after successful registration.
- A slot ID after successful slot creation.
- An appointment ID after successful booking.
- Updated available capacity after booking or cancellation.
- Appointment status (`Booked` or `Cancelled`).
- Patient dose status (`No Dose`, `1 Dose`, or `2 Doses`).
- Confirmation or explanatory messages when dose tracking succeeds or fails validation.

## 8. Acceptance criteria

The project is considered to meet its current scope when:

1. A patient can be registered and displayed.
2. A vaccination slot can be created and displayed.
3. A valid appointment can be booked and the available seat count decreases.
4. A booked appointment can be cancelled and the available seat count increases.
5. Duplicate active bookings for the same patient and slot are rejected.
6. Dose 1 can be recorded once for a registered patient.
7. Dose 2 is rejected if Dose 1 is missing, the vaccine does not match, the dose is already recorded, or the recommended gap has not elapsed.
8. Dose 2 is accepted when the vaccine matches and the entered date meets the recommended gap.
9. Invalid text in integer fields is rejected without causing the menu or input flow to loop indefinitely.

## 9. Known limitations

- Records exist only while the program is running; they are not saved after exit.
- The application is not connected to a government or healthcare system.
- The recommended dose interval is user-entered and is not medically verified by the software.
- The program is an educational demonstration, not a production healthcare or appointment platform.