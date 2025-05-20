from django.contrib import admin
from .models import *

# Register your models here.
# ==================== Inline Admin Classes ====================
class AllergyInline(admin.TabularInline):
    model = Allergy
    extra = 1

class MedicalHistoryInline(admin.TabularInline):
    model = MedicalHistory
    extra = 1

class DoctorInline(admin.StackedInline):
    model = Doctor
    extra = 0
    max_num = 1

class NurseInline(admin.StackedInline):
    model = Nurse
    extra = 0
    max_num = 1

class TechnicianInline(admin.StackedInline):
    model = Technician
    extra = 0
    max_num = 1

class SurgeryAssignmentInline(admin.TabularInline):
    model = SurgeryAssignment
    extra = 1

class TestAssignmentInline(admin.TabularInline):
    model = TestAssignment
    extra = 1

class BedInline(admin.TabularInline):
    model = Bed
    extra = 2

# ==================== Main Admin Classes ====================
@admin.register(Patient)
class PatientAdmin(admin.ModelAdmin):
    list_display = ('patient_id', 'full_name', 'gender', 'date_of_birth')
    search_fields = ('first_name', 'last_name', 'patient_id')
    inlines = [AllergyInline, MedicalHistoryInline]
    
    def full_name(self, obj):
        return f"{obj.first_name} {obj.last_name}"
    full_name.short_description = 'Full Name'

@admin.register(Employee)
class EmployeeAdmin(admin.ModelAdmin):
    list_display = ('employee_id', 'name', 'job_type', 'department', 'start_date')
    list_filter = ('job_type', 'department')
    search_fields = ('name', 'employee_id')
    inlines = [DoctorInline, NurseInline, TechnicianInline]

@admin.register(Department)
class DepartmentAdmin(admin.ModelAdmin):
    list_display = ('department_id', 'name', 'location', 'manager')
    search_fields = ('name', 'location')

@admin.register(Room)
class RoomAdmin(admin.ModelAdmin):
    list_display = ('room_number', 'department', 'room_type', 'status')
    list_filter = ('department', 'room_type')
    inlines = [BedInline]

@admin.register(Equipment)
class EquipmentAdmin(admin.ModelAdmin):
    list_display = ('equipment_id', 'name', 'type', 'status', 'technician')
    list_filter = ('type', 'status')
    raw_id_fields = ('technician',)

@admin.register(Surgery)
class SurgeryAdmin(admin.ModelAdmin):
    list_display = ('surgery_id', 'type', 'date', 'outcome')
    list_filter = ('outcome', 'date')
    inlines = [SurgeryAssignmentInline]

@admin.register(DiagnosticTest)
class DiagnosticTestAdmin(admin.ModelAdmin):
    list_display = ('test_id', 'test_name', 'date', 'results_summary')
    search_fields = ('test_name',)
    inlines = [TestAssignmentInline]
    
    def results_summary(self, obj):
        return f"{obj.results[:50]}..." if obj.results else ""
    results_summary.short_description = 'Results'

@admin.register(Insurance)
class InsuranceAdmin(admin.ModelAdmin):
    list_display = ('insurance_id', 'provider', 'status', 'patient')
    list_filter = ('status', 'provider')
    raw_id_fields = ('patient',)

@admin.register(Billing)
class BillingAdmin(admin.ModelAdmin):
    list_display = ('billing_id', 'patient', 'final_amount', 'status', 'due_date')
    list_filter = ('status', 'due_date')
    raw_id_fields = ('patient',)

@admin.register(Payment)
class PaymentAdmin(admin.ModelAdmin):
    list_display = ('payment_id', 'billing', 'amount_paid', 'payment_date')
    list_filter = ('payment_date', 'method')

# ==================== Junction Tables ====================
@admin.register(InsuranceBilling)
class InsuranceBillingAdmin(admin.ModelAdmin):
    list_display = ('insurance', 'billing')
    raw_id_fields = ('insurance', 'billing')

# ==================== Weak Entities ====================
@admin.register(MedicalHistory)
class MedicalHistoryAdmin(admin.ModelAdmin):
    list_display = ('patient', 'type', 'stage')
    raw_id_fields = ('patient',)

@admin.register(Allergy)
class AllergyAdmin(admin.ModelAdmin):
    list_display = ('patient', 'allergy')
    raw_id_fields = ('patient',)