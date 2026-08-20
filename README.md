# AED Simulator

A simulation of an Automated External Defibrillator, written in C++ with Qt.
Group project for COMP 3004 (Object-Oriented Software Engineering) at Carleton
University, Fall 2023.

The simulator covers the device workflow: power-on self test, electrode
placement, ECG rhythm display, shock delivery, CPR prompting, and battery drain
across uses. Prompts are shown on the LCD screen and played as audio.

Demo video made by myself: https://www.youtube.com/watch?v=-ysMmeA1TFk

## Building

Requires Qt 5 and a C++ compiler.

```
cd QTcode/AED
qmake AED.pro
make
./AED
```

Or open `QTcode/AED/AED.pro` in Qt Creator and build from there.

## Repository layout

```
QTcode/AED/               Qt source and image assets
Sequence Diagrams/        One diagram per use case, with an explanation file
UML.pdf                   Class diagram
aed_state.pdf             Device state diagram
Use Cases.pdf             Use case descriptions
Use Case Diagram.pdf      Use case diagram
Traceability_Matrix.pdf   Use cases mapped to implementation
```

## Team

Team 61: Alexander Lako, Warren Currie, Taj Randhawa, Jayden Gaind, Calvin Sorochan.

What each team member did:

Calvin Sorochan
- State Diagram
- Code Skeleton

Alexander Lako
- Created UI interface
- Created basic battery functionality
- Contributed to adjusting code logic

Warren Currie
- ECG implementation
- AED implementation framework
- UML Diagram
- Traceability Matrix

Taj Randhawa
- LCDScreen implementation
- All visual and audio prompts
- CPR, Patient, Shocks, LED, electrode, self-test widgets and functionality
- Sequence Diagrams

Jayden Gaind
- Created the Use Cases
- Created the Use Case Diagram
- Contributed to the Traceability Matrix

Original repository: https://github.com/AlexanderLako/3004GroupProject
