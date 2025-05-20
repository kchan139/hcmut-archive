USE HospitalManagementSystem;

-- -----------------------------------------------------
-- Stored Procedures
-- -----------------------------------------------------
DELIMITER $$

-- -----------------------------------------------------
-- Patient Record Management
-- -----------------------------------------------------
CREATE PROCEDURE AddPatient (
    IN p_FName VARCHAR(50),
    IN p_LName VARCHAR(50),
    IN p_Gender ENUM('Male', 'Female', 'Other'),
    IN p_ContactInfo VARCHAR(100),
    IN p_Address_Street VARCHAR(100),
    IN p_Address_District VARCHAR(50),
    IN p_Address_City VARCHAR(50),
    IN p_DOB DATE,
    IN p_CurrentMeds TEXT,
    IN p_EmergencyContactPhone VARCHAR(20)
)
BEGIN
    INSERT INTO PATIENT (FName, LName, Gender, ContactInfo, Address_Street, Address_District, Address_City, DOB, CurrentMeds, EmergencyContactPhone)
    VALUES (p_FName, p_LName, p_Gender, p_ContactInfo, p_Address_Street, p_Address_District, p_Address_City, p_DOB, p_CurrentMeds, p_EmergencyContactPhone);
    SELECT LAST_INSERT_ID() AS PatientID;
END$$

CREATE PROCEDURE UpdatePatientDemographics (
    IN p_PatientID INT,
    IN p_FName VARCHAR(50),
    IN p_LName VARCHAR(50),
    IN p_Gender ENUM('Male', 'Female', 'Other'),
    IN p_DOB DATE,
    IN p_Address_Street VARCHAR(100),
    IN p_Address_District VARCHAR(50),
    IN p_Address_City VARCHAR(50)
)
BEGIN
    UPDATE PATIENT
    SET FName = p_FName, LName = p_LName, Gender = p_Gender, DOB = p_DOB,
        Address_Street = p_Address_Street, Address_District = p_Address_District, Address_City = p_Address_City
    WHERE PatientID = p_PatientID;
END$$

CREATE PROCEDURE UpdatePatientContact (
    IN p_PatientID INT,
    IN p_ContactInfo VARCHAR(100),
    IN p_EmergencyContactPhone VARCHAR(20)
)
BEGIN
    UPDATE PATIENT
    SET ContactInfo = p_ContactInfo, EmergencyContactPhone = p_EmergencyContactPhone
    WHERE PatientID = p_PatientID;
END$$

CREATE PROCEDURE UpdatePatientMedications (
    IN p_PatientID INT,
    IN p_CurrentMeds TEXT
)
BEGIN
    UPDATE PATIENT
    SET CurrentMeds = p_CurrentMeds
    WHERE PatientID = p_PatientID;
END$$

CREATE PROCEDURE DeletePatient (
    IN p_PatientID INT
)
BEGIN
    -- Consider implications: related records in ALLERGIES, MEDICAL_HISTORY, INSURANCE, BILLING etc.
    -- For simplicity, this is a basic delete. Add cascading deletes or checks as needed.
    DELETE FROM ALLERGIES WHERE PatientID = p_PatientID;
    DELETE FROM MEDICAL_HISTORY WHERE PatientID = p_PatientID;
    -- Add more deletions from related tables if direct FKs don't cascade or if soft delete is not used.
    DELETE FROM PATIENT WHERE PatientID = p_PatientID;
END$$

-- -----------------------------------------------------
-- Medical History, Allergies, Insurance Management
-- -----------------------------------------------------
CREATE PROCEDURE AddMedicalHistory (
    IN p_PatientID INT,
    IN p_Type VARCHAR(100),
    IN p_Description TEXT,
    IN p_Treatment TEXT,
    IN p_Stage VARCHAR(50)
)
BEGIN
    INSERT INTO MEDICAL_HISTORY (PatientID, Type, Description, Treatment, Stage)
    VALUES (p_PatientID, p_Type, p_Description, p_Treatment, p_Stage);
END$$

CREATE PROCEDURE UpdateMedicalHistory (
    IN p_PatientID INT,
    IN p_Type VARCHAR(100),
    IN p_Description TEXT,
    IN p_Treatment TEXT,
    IN p_Stage VARCHAR(50)
)
BEGIN
    UPDATE MEDICAL_HISTORY
    SET Description = p_Description, Treatment = p_Treatment, Stage = p_Stage
    WHERE PatientID = p_PatientID AND Type = p_Type;
END$$

CREATE PROCEDURE AddAllergy (
    IN p_PatientID INT,
    IN p_Allergy VARCHAR(100)
)
BEGIN
    INSERT INTO ALLERGIES (PatientID, Allergy)
    VALUES (p_PatientID, p_Allergy);
END$$

CREATE PROCEDURE DeleteAllergy (
    IN p_PatientID INT,
    IN p_Allergy VARCHAR(100)
)
BEGIN
    DELETE FROM ALLERGIES WHERE PatientID = p_PatientID AND Allergy = p_Allergy;
END$$

CREATE PROCEDURE AddInsurance (
    IN p_PatientID INT,
    IN p_PolicyNumber VARCHAR(50),
    IN p_Priority INT,
    IN p_Provider VARCHAR(100),
    IN p_Status ENUM('Active', 'Pending', 'Expired', 'Cancelled'),
    IN p_CoveragePercentage DECIMAL(5, 2),
    IN p_CoverageLimit DECIMAL(12, 2)
)
BEGIN
    INSERT INTO INSURANCE (PatientID, PolicyNumber, Priority, Provider, Status, CoveragePercentage, CoverageLimit)
    VALUES (p_PatientID, p_PolicyNumber, p_Priority, p_Provider, p_Status, p_CoveragePercentage, p_CoverageLimit);
    SELECT LAST_INSERT_ID() AS InsuranceID;
END$$

CREATE PROCEDURE UpdateInsurance (
    IN p_InsuranceID INT,
    IN p_PolicyNumber VARCHAR(50),
    IN p_Priority INT,
    IN p_Provider VARCHAR(100),
    IN p_Status ENUM('Active', 'Pending', 'Expired', 'Cancelled'),
    IN p_CoveragePercentage DECIMAL(5, 2),
    IN p_CoverageLimit DECIMAL(12, 2)
)
BEGIN
    UPDATE INSURANCE
    SET PolicyNumber = p_PolicyNumber, Priority = p_Priority, Provider = p_Provider, Status = p_Status,
        CoveragePercentage = p_CoveragePercentage, CoverageLimit = p_CoverageLimit
    WHERE InsuranceID = p_InsuranceID;
END$$

CREATE PROCEDURE DeleteInsurance (
    IN p_InsuranceID INT
)
BEGIN
    DELETE FROM COVER WHERE InsuranceID = p_InsuranceID; -- Remove links to bills first
    DELETE FROM INSURANCE WHERE InsuranceID = p_InsuranceID;
END$$

-- -----------------------------------------------------
-- Admin: Staff Management (Doctor, Nurse, Technician)
-- -----------------------------------------------------
CREATE PROCEDURE AddEmployeeBase (
    IN p_EmployeeID VARCHAR(20),
    IN p_Name VARCHAR(100),
    IN p_Gender ENUM('Male', 'Female', 'Other'),
    IN p_DOB DATE,
    IN p_JobType VARCHAR(50),
    IN p_Experience INT,
    IN p_Salary DECIMAL(10, 2),
    IN p_ContactDetails VARCHAR(100),
    IN p_StartDate DATE,
    IN p_DepartmentID INT
)
BEGIN
    INSERT INTO EMPLOYEE (EmployeeID, Name, Gender, DOB, JobType, Experience, Salary, ContactDetails, StartDate, DepartmentID)
    VALUES (p_EmployeeID, p_Name, p_Gender, p_DOB, p_JobType, p_Experience, p_Salary, p_ContactDetails, p_StartDate, p_DepartmentID);
END$$

CREATE PROCEDURE UpdateEmployeeBase (
    IN p_EmployeeID VARCHAR(20),
    IN p_Name VARCHAR(100),
    IN p_Gender ENUM('Male', 'Female', 'Other'),
    IN p_DOB DATE,
    IN p_Experience INT,
    IN p_Salary DECIMAL(10, 2),
    IN p_ContactDetails VARCHAR(100),
    IN p_StartDate DATE,
    IN p_DepartmentID INT
)
BEGIN
    UPDATE EMPLOYEE
    SET Name = p_Name, Gender = p_Gender, DOB = p_DOB, Experience = p_Experience, Salary = p_Salary,
        ContactDetails = p_ContactDetails, StartDate = p_StartDate, DepartmentID = p_DepartmentID
    WHERE EmployeeID = p_EmployeeID;
END$$

CREATE PROCEDURE AddDoctor (
    IN p_EmployeeID VARCHAR(20), IN p_Name VARCHAR(100), IN p_Gender ENUM('Male', 'Female', 'Other'), IN p_DOB DATE,
    IN p_Experience INT, IN p_Salary DECIMAL(10, 2), IN p_ContactDetails VARCHAR(100), IN p_StartDate DATE, IN p_DepartmentID INT,
    IN p_Specialty VARCHAR(100), IN p_Certificate VARCHAR(255)
)
BEGIN
    CALL AddEmployeeBase(p_EmployeeID, p_Name, p_Gender, p_DOB, 'Doctor', p_Experience, p_Salary, p_ContactDetails, p_StartDate, p_DepartmentID);
    INSERT INTO DOCTOR (EmployeeID, Specialty, Certificate) VALUES (p_EmployeeID, p_Specialty, p_Certificate);
END$$

CREATE PROCEDURE UpdateDoctor (
    IN p_EmployeeID VARCHAR(20), IN p_Name VARCHAR(100), IN p_Gender ENUM('Male', 'Female', 'Other'), IN p_DOB DATE,
    IN p_Experience INT, IN p_Salary DECIMAL(10, 2), IN p_ContactDetails VARCHAR(100), IN p_StartDate DATE, IN p_DepartmentID INT,
    IN p_Specialty VARCHAR(100), IN p_Certificate VARCHAR(255)
)
BEGIN
    CALL UpdateEmployeeBase(p_EmployeeID, p_Name, p_Gender, p_DOB, p_Experience, p_Salary, p_ContactDetails, p_StartDate, p_DepartmentID);
    UPDATE DOCTOR SET Specialty = p_Specialty, Certificate = p_Certificate WHERE EmployeeID = p_EmployeeID;
END$$

CREATE PROCEDURE DeleteDoctor (IN p_EmployeeID VARCHAR(20))
BEGIN
    DELETE FROM ASSIGN_DOC WHERE DoctorID = p_EmployeeID;
    DELETE FROM PERFORM_SURGERY WHERE DoctorID = p_EmployeeID;
    DELETE FROM DOCTOR WHERE EmployeeID = p_EmployeeID;
    DELETE FROM EMPLOYEE WHERE EmployeeID = p_EmployeeID;
END$$

CREATE PROCEDURE AddNurse (
    IN p_EmployeeID VARCHAR(20), IN p_Name VARCHAR(100), IN p_Gender ENUM('Male', 'Female', 'Other'), IN p_DOB DATE,
    IN p_Experience INT, IN p_Salary DECIMAL(10, 2), IN p_ContactDetails VARCHAR(100), IN p_StartDate DATE, IN p_DepartmentID INT,
    IN p_Specialty VARCHAR(100)
)
BEGIN
    CALL AddEmployeeBase(p_EmployeeID, p_Name, p_Gender, p_DOB, 'Nurse', p_Experience, p_Salary, p_ContactDetails, p_StartDate, p_DepartmentID);
    INSERT INTO NURSE (EmployeeID, Specialty) VALUES (p_EmployeeID, p_Specialty);
END$$

CREATE PROCEDURE UpdateNurse (
    IN p_EmployeeID VARCHAR(20), IN p_Name VARCHAR(100), IN p_Gender ENUM('Male', 'Female', 'Other'), IN p_DOB DATE,
    IN p_Experience INT, IN p_Salary DECIMAL(10, 2), IN p_ContactDetails VARCHAR(100), IN p_StartDate DATE, IN p_DepartmentID INT,
    IN p_Specialty VARCHAR(100)
)
BEGIN
    CALL UpdateEmployeeBase(p_EmployeeID, p_Name, p_Gender, p_DOB, p_Experience, p_Salary, p_ContactDetails, p_StartDate, p_DepartmentID);
    UPDATE NURSE SET Specialty = p_Specialty WHERE EmployeeID = p_EmployeeID;
END$$

CREATE PROCEDURE DeleteNurse (IN p_EmployeeID VARCHAR(20))
BEGIN
    DELETE FROM ASSIGN_NURSE WHERE NurseID = p_EmployeeID;
    DELETE FROM PERFORM_TEST WHERE NurseID = p_EmployeeID;
    DELETE FROM NURSE WHERE EmployeeID = p_EmployeeID;
    DELETE FROM EMPLOYEE WHERE EmployeeID = p_EmployeeID;
END$$

CREATE PROCEDURE AddTechnician (
    IN p_EmployeeID VARCHAR(20), IN p_Name VARCHAR(100), IN p_Gender ENUM('Male', 'Female', 'Other'), IN p_DOB DATE,
    IN p_Experience INT, IN p_Salary DECIMAL(10, 2), IN p_ContactDetails VARCHAR(100), IN p_StartDate DATE, IN p_DepartmentID INT,
    IN p_Specialty VARCHAR(100)
)
BEGIN
    CALL AddEmployeeBase(p_EmployeeID, p_Name, p_Gender, p_DOB, 'Technician', p_Experience, p_Salary, p_ContactDetails, p_StartDate, p_DepartmentID);
    INSERT INTO TECHNICIAN (EmployeeID, Specialty) VALUES (p_EmployeeID, p_Specialty);
END$$

CREATE PROCEDURE UpdateTechnician (
    IN p_EmployeeID VARCHAR(20), IN p_Name VARCHAR(100), IN p_Gender ENUM('Male', 'Female', 'Other'), IN p_DOB DATE,
    IN p_Experience INT, IN p_Salary DECIMAL(10, 2), IN p_ContactDetails VARCHAR(100), IN p_StartDate DATE, IN p_DepartmentID INT,
    IN p_Specialty VARCHAR(100)
)
BEGIN
    CALL UpdateEmployeeBase(p_EmployeeID, p_Name, p_Gender, p_DOB, p_Experience, p_Salary, p_ContactDetails, p_StartDate, p_DepartmentID);
    UPDATE TECHNICIAN SET Specialty = p_Specialty WHERE EmployeeID = p_EmployeeID;
END$$

CREATE PROCEDURE DeleteTechnician (IN p_EmployeeID VARCHAR(20))
BEGIN
    DELETE FROM MAINTAINS WHERE TechID = p_EmployeeID;
    DELETE FROM TECHNICIAN WHERE EmployeeID = p_EmployeeID;
    DELETE FROM EMPLOYEE WHERE EmployeeID = p_EmployeeID;
END$$

-- -----------------------------------------------------
-- Assign Doctors/Nurses to Patients
-- -----------------------------------------------------
CREATE PROCEDURE AssignDoctorToPatient (IN p_DoctorID VARCHAR(20), IN p_PatientID INT)
BEGIN
    INSERT INTO ASSIGN_DOC (DoctorID, PatientID) VALUES (p_DoctorID, p_PatientID);
END$$

CREATE PROCEDURE RemoveDoctorFromPatient (IN p_DoctorID VARCHAR(20), IN p_PatientID INT)
BEGIN
    DELETE FROM ASSIGN_DOC WHERE DoctorID = p_DoctorID AND PatientID = p_PatientID;
END$$

CREATE PROCEDURE AssignNurseToPatient (IN p_NurseID VARCHAR(20), IN p_PatientID INT)
BEGIN
    INSERT INTO ASSIGN_NURSE (NurseID, PatientID) VALUES (p_NurseID, p_PatientID);
END$$

CREATE PROCEDURE RemoveNurseFromPatient (IN p_NurseID VARCHAR(20), IN p_PatientID INT)
BEGIN
    DELETE FROM ASSIGN_NURSE WHERE NurseID = p_NurseID AND PatientID = p_PatientID;
END$$

-- -----------------------------------------------------
-- Billing and Insurance
-- -----------------------------------------------------
CREATE PROCEDURE GenerateBill (
    IN p_PatientID INT,
    IN p_InitialAmount DECIMAL(12, 2),
    IN p_DateIssued DATE,
    IN p_DueDate DATE
)
BEGIN
    INSERT INTO BILLING (PatientID, DateIssued, InitialAmount, CoverAmount, FinalAmount, DueDate, Status)
    VALUES (p_PatientID, p_DateIssued, p_InitialAmount, 0.00, p_InitialAmount, p_DueDate, 'Pending');
    SELECT LAST_INSERT_ID() AS BillingID;
END$$

CREATE PROCEDURE RecalculateBillCoverage (IN p_BillingID INT)
BEGIN
    DECLARE v_InitialAmount DECIMAL(12,2);
    DECLARE v_TotalCover DECIMAL(12,2) DEFAULT 0.00;

    SELECT InitialAmount INTO v_InitialAmount
    FROM BILLING
    WHERE BillingID = p_BillingID;

    SELECT COALESCE(SUM(
                LEAST(
                    (v_InitialAmount * I.CoveragePercentage) / 100.0,
                    I.CoverageLimit
                )
            ), 0.00)
    INTO v_TotalCover
    FROM INSURANCE I
    JOIN COVER C ON I.InsuranceID = C.InsuranceID
    WHERE C.BillingID = p_BillingID AND I.Status = 'Active';

    IF v_TotalCover > v_InitialAmount THEN
        SET v_TotalCover = v_InitialAmount;
    END IF;

    UPDATE BILLING
    SET CoverAmount = v_TotalCover,
        FinalAmount = v_InitialAmount - v_TotalCover
    WHERE BillingID = p_BillingID;
END$$

CREATE PROCEDURE LinkInsuranceToBillAndRecalculate (IN p_BillingID INT, IN p_InsuranceID INT)
BEGIN
    -- Check if patient associated with bill has this insurance
    DECLARE v_PatientID_Bill INT;
    DECLARE v_PatientID_Insurance INT;
    DECLARE v_InsuranceActive BOOLEAN;

    SELECT PatientID INTO v_PatientID_Bill FROM BILLING WHERE BillingID = p_BillingID;
    SELECT PatientID, (Status = 'Active') INTO v_PatientID_Insurance, v_InsuranceActive FROM INSURANCE WHERE InsuranceID = p_InsuranceID;

    IF v_PatientID_Bill IS NOT NULL AND v_PatientID_Insurance IS NOT NULL AND v_PatientID_Bill = v_PatientID_Insurance AND v_InsuranceActive THEN
        INSERT IGNORE INTO COVER (BillingID, InsuranceID) VALUES (p_BillingID, p_InsuranceID);
        CALL RecalculateBillCoverage(p_BillingID);
    ELSE
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Insurance policy cannot be linked or is not active for this patient''s bill.';
    END IF;
END$$


-- -----------------------------------------------------
-- Diagnostic Tests Management
-- -----------------------------------------------------
CREATE PROCEDURE OrderDiagnosticTest (
    IN p_PatientID INT,
    IN p_NurseID_Performer VARCHAR(20), -- Nurse who will perform/is associated
    IN p_TestName VARCHAR(100),
    IN p_TestDescription TEXT,
    IN p_TestDate DATETIME
)
BEGIN
    DECLARE v_TestID INT;
    INSERT INTO DIAGNOSTIC_TEST (Name, Description, Date, Results)
    VALUES (p_TestName, p_TestDescription, p_TestDate, NULL);
    SET v_TestID = LAST_INSERT_ID();

    IF p_NurseID_Performer IS NOT NULL THEN
        INSERT INTO PERFORM_TEST (TestID, NurseID, PatientID)
        VALUES (v_TestID, p_NurseID_Performer, p_PatientID);
    END IF;
    SELECT v_TestID AS TestID;
END$$

CREATE PROCEDURE RecordTestResults (
    IN p_TestID INT,
    IN p_Results TEXT
)
BEGIN
    UPDATE DIAGNOSTIC_TEST
    SET Results = p_Results
    WHERE TestID = p_TestID;
END$$

CREATE PROCEDURE AssignEquipmentToTest (IN p_TestID INT, IN p_EquipID INT)
BEGIN
    INSERT INTO USE_IN_TEST (TestID, EquipID) VALUES (p_TestID, p_EquipID);
END$$

-- -----------------------------------------------------
-- Surgery Management
-- -----------------------------------------------------
CREATE PROCEDURE ScheduleSurgery (
    IN p_PatientID INT,
    IN p_DoctorID VARCHAR(20),
    IN p_SurgeryType VARCHAR(100),
    IN p_SurgeryDate DATETIME
)
BEGIN
    DECLARE v_SurgeryID INT;
    INSERT INTO SURGERY (Type, Date, Outcome, Complications)
    VALUES (p_SurgeryType, p_SurgeryDate, NULL, NULL);
    SET v_SurgeryID = LAST_INSERT_ID();

    INSERT INTO PERFORM_SURGERY (SurgeryID, DoctorID, PatientID)
    VALUES (v_SurgeryID, p_DoctorID, p_PatientID);
    SELECT v_SurgeryID AS SurgeryID;
END$$

CREATE PROCEDURE UpdateSurgeryOutcome (
    IN p_SurgeryID INT,
    IN p_Outcome VARCHAR(100),
    IN p_Complications TEXT
)
BEGIN
    UPDATE SURGERY
    SET Outcome = p_Outcome, Complications = p_Complications
    WHERE SurgeryID = p_SurgeryID;
END$$

CREATE PROCEDURE AssignEquipmentToSurgery (IN p_SurgeryID INT, IN p_EquipID INT)
BEGIN
    INSERT INTO USE_IN_SURGERY (SurgeryID, EquipID) VALUES (p_SurgeryID, p_EquipID);
END$$

-- -----------------------------------------------------
-- Equipment Maintenance (Technician)
-- -----------------------------------------------------
CREATE PROCEDURE LogEquipmentMaintenance (
    IN p_TechID VARCHAR(20),
    IN p_EquipmentID INT,
    IN p_MaintenanceType VARCHAR(100),
    IN p_MaintenanceDate DATE
)
BEGIN
    INSERT INTO MAINTAINS (TechID, EquipmentID, MaintenanceType, MaintenanceDate)
    VALUES (p_TechID, p_EquipmentID, p_MaintenanceType, p_MaintenanceDate);
    -- Optionally update equipment status here, e.g., to 'Maintenance' or 'Available'
END$$

CREATE PROCEDURE UpdateEquipmentStatus (
    IN p_EquipmentID INT,
    IN p_NewStatus ENUM('Available', 'In Use', 'Maintenance', 'Decommissioned')
)
BEGIN
    UPDATE EQUIPMENT
    SET Status = p_NewStatus
    WHERE EquipmentID = p_EquipmentID;
END$$

DELIMITER ;