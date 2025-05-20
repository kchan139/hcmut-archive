-- Create Database
CREATE DATABASE IF NOT EXISTS HospitalManagementSystem;
USE HospitalManagementSystem;

-- Create Tables

-- PATIENT Table
CREATE TABLE PATIENT (
    PatientID INT AUTO_INCREMENT PRIMARY KEY,
    FName VARCHAR(50) NOT NULL,
    LName VARCHAR(50) NOT NULL,
    Gender ENUM('Male', 'Female', 'Other'),
    ContactInfo VARCHAR(100),
    Address_Street VARCHAR(100),
    Address_District VARCHAR(50),
    Address_City VARCHAR(50),
    DOB DATE,
    CurrentMeds TEXT,
    EmergencyContactPhone VARCHAR(20)
);

-- EMPLOYEE Table (Superclass)
CREATE TABLE EMPLOYEE (
    EmployeeID VARCHAR(20) PRIMARY KEY,
    Name VARCHAR(100) NOT NULL,
    Gender ENUM('Male', 'Female', 'Other'),
    DOB DATE,
    JobType VARCHAR(50),
    Experience INT,
    Salary DECIMAL(10, 2),
    ContactDetails VARCHAR(100),
    StartDate DATE,
    DepartmentID INT,
    FOREIGN KEY (DepartmentID) REFERENCES DEPARTMENT(DepartmentID)
);

-- DEPARTMENT Table
CREATE TABLE DEPARTMENT (
    DepartmentID INT AUTO_INCREMENT PRIMARY KEY,
    DepartmentName VARCHAR(100) NOT NULL UNIQUE,
    Location VARCHAR(100),
    FOREIGN KEY (ManagerID) REFERENCES EMPLOYEE(EmployeeID)
);

-- DOCTOR Table (Subclass)
CREATE TABLE DOCTOR (
    EmployeeID VARCHAR(20) PRIMARY KEY,
    Specialty VARCHAR(100),
    Certificate VARCHAR(255),
    FOREIGN KEY (EmployeeID) REFERENCES EMPLOYEE(EmployeeID)
);

-- NURSE Table (Subclass)
CREATE TABLE NURSE (
    EmployeeID VARCHAR(20) PRIMARY KEY,
    Specialty VARCHAR(100),
    FOREIGN KEY (EmployeeID) REFERENCES EMPLOYEE(EmployeeID)
);

-- TECHNICIAN Table (Subclass)
CREATE TABLE TECHNICIAN (
    EmployeeID VARCHAR(20) PRIMARY KEY,
    Specialty VARCHAR(100),
    FOREIGN KEY (EmployeeID) REFERENCES EMPLOYEE(EmployeeID)
);

-- OTHER_STAFF Table (Subclass)
CREATE TABLE OTHER_STAFF (
    EmployeeID VARCHAR(20) PRIMARY KEY,
    JobType VARCHAR(50), -- More specific job title
    FOREIGN KEY (EmployeeID) REFERENCES EMPLOYEE(EmployeeID)
);

-- ROOM Table
CREATE TABLE ROOM (
    RoomID INT AUTO_INCREMENT PRIMARY KEY,
    Type VARCHAR(50),
    Name VARCHAR(50),
    Status ENUM('Available', 'Occupied', 'Maintenance'),
    FOREIGN KEY (DepartmentID) REFERENCES DEPARTMENT(DepartmentID)
);

-- EQUIPMENT Table
CREATE TABLE EQUIPMENT (
    EquipmentID INT AUTO_INCREMENT PRIMARY KEY,
    Name VARCHAR(100) NOT NULL,
    Type VARCHAR(50), -- Medical, Diagnostic, Surgery, etc.
    Status ENUM('Available', 'In Use', 'Maintenance', 'Decommissioned')
);

-- SURGERY Table
CREATE TABLE SURGERY (
    SurgeryID INT AUTO_INCREMENT PRIMARY KEY,
    Type VARCHAR(100),
    Date DATETIME,
    Outcome VARCHAR(100),
    Complications TEXT
);

-- DIAGNOSTIC_TEST Table
CREATE TABLE DIAGNOSTIC_TEST (
    TestID INT AUTO_INCREMENT PRIMARY KEY,
    Name VARCHAR(100) NOT NULL,
    Description TEXT,
    Date DATETIME, -- Changed to DATETIME
    Results TEXT
);

-- INSURANCE Table
CREATE TABLE INSURANCE (
    InsuranceID INT AUTO_INCREMENT PRIMARY KEY,
    PolicyNumber VARCHAR(50) NOT NULL UNIQUE,
    Priority INT DEFAULT 1,
    Provider VARCHAR(100),
    Status ENUM('Active', 'Pending', 'Expired', 'Cancelled'),
    CoveragePercentage DECIMAL(5, 2), -- e.g., 80.00 for 80%
    CoverageLimit DECIMAL(12, 2),
    PatientID INT,
    FOREIGN KEY (PatientID) REFERENCES PATIENT(PatientID)
);

-- BILLING Table
CREATE TABLE BILLING (
    BillingID INT AUTO_INCREMENT PRIMARY KEY,
    DateIssued DATE,
    InitialAmount DECIMAL(12, 2),
    CoverAmount DECIMAL(12, 2),
    FinalAmount DECIMAL(12, 2),
    DueDate DATE,
    Status ENUM('Pending', 'Paid', 'Partially Paid', 'Overdue', 'Cancelled'),
    PatientID INT,
    FOREIGN KEY (PatientID) REFERENCES PATIENT(PatientID)
);

-- PAYMENT Table
CREATE TABLE PAYMENT (
    PaymentID INT AUTO_INCREMENT PRIMARY KEY,
    Date DATETIME,
    Method ENUM('Cash', 'Credit Card', 'Insurance', 'Bank Transfer'),
    AmountPaid DECIMAL(12, 2),
    PaymentReceiptNumber VARCHAR(50) UNIQUE,
    Notes TEXT,
    BillingID INT,
    FOREIGN KEY (BillingID) REFERENCES BILLING(BillingID)
);

-- ALLERGIES Table (Weak Entity)
CREATE TABLE ALLERGIES (
    PatientID INT,
    Allergy VARCHAR(100), -- Partial Key
    PRIMARY KEY (PatientID, Allergy), -- Composite PK
    FOREIGN KEY (PatientID) REFERENCES PATIENT(PatientID)
);

-- MEDICAL_HISTORY Table (Weak Entity)
CREATE TABLE MEDICAL_HISTORY (
    PatientID INT,
    Type VARCHAR(100), -- Partial Key
    Description TEXT,
    Treatment TEXT,
    Stage VARCHAR(50),
    PRIMARY KEY (PatientID, Type),
    FOREIGN KEY (PatientID) REFERENCES PATIENT(PatientID)
);

-- BED Table (Weak Entity)
CREATE TABLE BED (
    RoomID INT,
    BedNumber VARCHAR(10), -- Partial Key (e.g., 'A', 'B', '101')
    PRIMARY KEY (RoomID, BedNumber), -- Composite PK
    FOREIGN KEY (RoomID) REFERENCES ROOM(RoomID)
);

-- COVER Table (Intermediate for Insurance-Billing M:N)
CREATE TABLE COVER (
    BillingID INT,
    InsuranceID INT,
    PRIMARY KEY (BillingID, InsuranceID), -- Composite PK
    FOREIGN KEY (BillingID) REFERENCES BILLING(BillingID),
    FOREIGN KEY (InsuranceID) REFERENCES INSURANCE(InsuranceID)
);

-- ASSIGN_DOC Table (Intermediate for Doctor-Patient M:N)
CREATE TABLE ASSIGN_DOC (
    DoctorID VARCHAR(20),
    PatientID INT,
    PRIMARY KEY (DoctorID, PatientID), -- Composite PK
    FOREIGN KEY (DoctorID) REFERENCES DOCTOR(EmployeeID),
    FOREIGN KEY (PatientID) REFERENCES PATIENT(PatientID)
);

-- ASSIGN_NURSE Table (Intermediate for Nurse-Patient M:N)
CREATE TABLE ASSIGN_NURSE (
    NurseID VARCHAR(20),
    PatientID INT,
    PRIMARY KEY (NurseID, PatientID), -- Composite PK
    FOREIGN KEY (NurseID) REFERENCES NURSE(EmployeeID),
    FOREIGN KEY (PatientID) REFERENCES PATIENT(PatientID)
);

-- MAINTAINS Table (Intermediate for Technician-Equipment M:N with attributes)
CREATE TABLE MAINTAINS (
    TechID VARCHAR(20),
    EquipmentID INT,
    MaintenanceType VARCHAR(100),
    MaintenanceDate DATE,
    PRIMARY KEY (TechID, EquipmentID, MaintenanceDate), -- Composite PK including date to allow multiple maintenances
    FOREIGN KEY (TechID) REFERENCES TECHNICIAN(EmployeeID),
    FOREIGN KEY (EquipmentID) REFERENCES EQUIPMENT(EquipmentID)
);

-- PERFORM_SURGERY Table (Intermediate for Surgery-Doctor-Patient Ternary)
CREATE TABLE PERFORM_SURGERY (
    SurgeryID INT,
    DoctorID VARCHAR(20),
    PatientID INT,
    PRIMARY KEY (SurgeryID, DoctorID), -- Composite PK
    FOREIGN KEY (SurgeryID) REFERENCES SURGERY(SurgeryID),
    FOREIGN KEY (DoctorID) REFERENCES DOCTOR(EmployeeID),
    FOREIGN KEY (PatientID) REFERENCES PATIENT(PatientID)
);

-- USE_IN_SURGERY Table (Intermediate for Surgery-Equipment M:N)
CREATE TABLE USE_IN_SURGERY (
    SurgeryID INT,
    EquipID INT,
    PRIMARY KEY (SurgeryID, EquipID), -- Composite PK
    FOREIGN KEY (SurgeryID) REFERENCES SURGERY(SurgeryID),
    FOREIGN KEY (EquipID) REFERENCES EQUIPMENT(EquipmentID)
);

-- PERFORM_TEST Table (Intermediate for Test-Nurse-Patient Ternary)
CREATE TABLE PERFORM_TEST (
    TestID INT,
    NurseID VARCHAR(20),
    PatientID INT,
    PRIMARY KEY (TestID, NurseID), -- Composite PK
    FOREIGN KEY (TestID) REFERENCES DIAGNOSTIC_TEST(TestID),
    FOREIGN KEY (NurseID) REFERENCES NURSE(EmployeeID),
    FOREIGN KEY (PatientID) REFERENCES PATIENT(PatientID)
);

-- USE_IN_TEST Table (Intermediate for Test-Equipment M:N)
CREATE TABLE USE_IN_TEST (
    TestID INT,
    EquipID INT,
    PRIMARY KEY (TestID, EquipID), -- Composite PK
    FOREIGN KEY (TestID) REFERENCES DIAGNOSTIC_TEST(TestID),
    FOREIGN KEY (EquipID) REFERENCES EQUIPMENT(EquipmentID)
);