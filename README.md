# AED Simulator

A simulation of an Automated External Defibrillator, written in C++ with Qt.
Group project for COMP 3004 (Object-Oriented Software Engineering) at Carleton
University, Fall 2023.

The simulator takes the device through a full use: power on and self test, pad
type, electrode placement, ECG analysis, shock delivery and CPR coaching, with
the battery draining as it goes. The prompts run on the LCD screen, from "CHECK
RESPOSIVENESS." and "ATTACH DEFIB PADS TO PATIENT'S BARE CHEST." through "SHOCK
ADVISED." and a three second countdown to "START CPR." and "PUSH HARDER."

Five rhythms can be set from the panel: healthy, ventricular fibrillation,
ventricular tachycardia, asystole and PEA. Only vFib and vTach are shockable,
and the rest get "NO SHOCK ADVISED." The ECG trace is drawn with QCustomPlot.

Demo video: https://www.youtube.com/watch?v=-ysMmeA1TFk

## My contribution

Team of five. Mine:

- LCDScreen, and all the visual and audio prompts
- The CPR, patient, shock, LED, electrode and self test widgets, and the
  functionality behind them
- The sequence diagrams in `Sequence Diagrams/`, one per use case

The full team breakdown is at the bottom.

## Building

```
cd QTcode/AED
qmake AED.pro
make
./AED
```

Or open `QTcode/AED/AED.pro` in Qt Creator.

## Repository layout

```
QTcode/AED/               Qt sources and images: aed, battery, ecg, lcdscreen,
                          mainwindow, and a bundled copy of QCustomPlot
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
