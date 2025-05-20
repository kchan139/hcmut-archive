from django.db import models


# Create your models here.
class Patient(models.Model):
    GENDER_CHOICES = [("M", "Male"), ("F", "Female"), ("O", "Other")]
    patient_id = models.AutoField(primary_key=True)
    first_name = models.CharField(max_length=100)
    last_name = models.CharField(max_length=100)
    gender = models.CharField(max_length=1, choices=GENDER_CHOICES)
    contact_info = models.CharField(max_length=100)
    home_address = models.TextField()
    date_of_birth = models.DateField()
    current_medications = models.TextField(blank=True)
    emergency_contact = models.CharField(max_length=100)


class Department(models.Model):
    department_id = models.AutoField(primary_key=True)
    name = models.CharField(max_length=100)
    location = models.CharField(max_length=200)
    manager = models.OneToOneField(
        "Employee", on_delete=models.PROTECT, related_name="managed_department"
    )


class Employee(models.Model):
    JOB_TYPE_CHOICES = [
        ("doctor", "Doctor"),
        ("nurse", "Nurse"),
        ("technician", "Technician"),
        ("other", "Other"),
    ]
    employee_id = models.CharField(primary_key=True, max_length=10)
    name = models.CharField(max_length=100)
    gender = models.CharField(max_length=1, choices=Patient.GENDER_CHOICES)
    date_of_birth = models.DateField()
    job_type = models.CharField(max_length=20, choices=JOB_TYPE_CHOICES)
    experience = models.PositiveIntegerField()
    salary = models.DecimalField(max_digits=10, decimal_places=2)
    contact_details = models.TextField()
    start_date = models.DateField()
    department = models.ForeignKey(
        Department, on_delete=models.SET_NULL, null=True, blank=True
    )


class Doctor(models.Model):
    employee = models.OneToOneField(
        Employee, on_delete=models.CASCADE, primary_key=True
    )
    specialty = models.CharField(max_length=100)
    certificate = models.TextField()


class Nurse(models.Model):
    employee = models.OneToOneField(
        Employee, on_delete=models.CASCADE, primary_key=True
    )
    specialty = models.CharField(max_length=100)


class Technician(models.Model):
    employee = models.OneToOneField(
        Employee, on_delete=models.CASCADE, primary_key=True
    )
    specialty = models.CharField(max_length=100)
    responsibility = models.TextField()


class Room(models.Model):
    room_number = models.AutoField(primary_key=True)
    department = models.ForeignKey(Department, on_delete=models.CASCADE)
    room_type = models.CharField(max_length=100)
    room_name = models.CharField(max_length=100)
    status = models.CharField(max_length=50)


class Equipment(models.Model):
    equipment_id = models.AutoField(primary_key=True)
    name = models.CharField(max_length=100)
    type = models.CharField(max_length=100)
    status = models.CharField(max_length=50)
    technician = models.ForeignKey(
        Employee, on_delete=models.SET_NULL, null=True, blank=True
    )


class Surgery(models.Model):
    surgery_id = models.AutoField(primary_key=True)
    type = models.CharField(max_length=200)
    date = models.DateField()
    outcome = models.CharField(max_length=100)
    complications = models.TextField(blank=True)


class SurgeryAssignment(models.Model):
    surgery = models.ForeignKey(Surgery, on_delete=models.CASCADE)
    doctor = models.ForeignKey(Employee, on_delete=models.CASCADE)
    patient = models.ForeignKey(Patient, on_delete=models.CASCADE)


class DiagnosticTest(models.Model):
    test_id = models.AutoField(primary_key=True)
    test_name = models.CharField(max_length=200)
    description = models.TextField()
    date = models.DateField()
    results = models.TextField()


class TestAssignment(models.Model):
    test = models.ForeignKey(DiagnosticTest, on_delete=models.CASCADE)
    nurse = models.ForeignKey(Employee, on_delete=models.CASCADE)
    patient = models.ForeignKey(Patient, on_delete=models.CASCADE)


class Insurance(models.Model):
    insurance_id = models.AutoField(primary_key=True)
    policy_number = models.CharField(max_length=100)
    priority = models.PositiveIntegerField()
    provider = models.CharField(max_length=200)
    status = models.CharField(max_length=50)
    coverage_percentage = models.DecimalField(max_digits=5, decimal_places=2)
    coverage_limit = models.DecimalField(max_digits=10, decimal_places=2)
    patient = models.ForeignKey(Patient, on_delete=models.CASCADE)


class Billing(models.Model):
    billing_id = models.AutoField(primary_key=True)
    date_issued = models.DateField()
    initial_amount = models.DecimalField(max_digits=10, decimal_places=2)
    cover_amount = models.DecimalField(max_digits=10, decimal_places=2)
    final_amount = models.DecimalField(max_digits=10, decimal_places=2)
    due_date = models.DateField()
    status = models.CharField(max_length=50)
    patient = models.ForeignKey(Patient, on_delete=models.CASCADE)


class InsuranceBilling(models.Model):
    insurance = models.ForeignKey(Insurance, on_delete=models.CASCADE)
    billing = models.ForeignKey(Billing, on_delete=models.CASCADE)


class Payment(models.Model):
    payment_id = models.AutoField(primary_key=True)
    payment_date = models.DateField()
    method = models.CharField(max_length=50)
    amount_paid = models.DecimalField(max_digits=10, decimal_places=2)
    receipt_number = models.CharField(max_length=100)
    notes = models.TextField(blank=True)
    billing = models.ForeignKey(Billing, on_delete=models.CASCADE)


class Allergy(models.Model):
    patient = models.ForeignKey(Patient, on_delete=models.CASCADE)
    allergy = models.CharField(max_length=200)

    class Meta:
        unique_together = ("patient", "allergy")


class MedicalHistory(models.Model):
    patient = models.ForeignKey(Patient, on_delete=models.CASCADE)
    type = models.CharField(max_length=200)
    description = models.TextField()
    treatment = models.TextField()
    stage = models.CharField(max_length=100)

    class Meta:
        unique_together = ("patient", "type")


class Bed(models.Model):
    room = models.ForeignKey(Room, on_delete=models.CASCADE)
    bed_number = models.CharField(max_length=10)
    status = models.CharField(max_length=50)

    class Meta:
        unique_together = ("room", "bed_number")
