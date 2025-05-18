This class diagram illustrates two main actions students can perform:

- Print a Document:

A student submits a print job through the printDocument() function. The PrintingService processes the request, manages the printer, and applies configuration changes made by the student (e.g., paper size, number of copies). After confirming the print request, a log is generated containing details like the student ID, page usage, printer start time, and end time.

- View Printing Logs:

A student can view their printing history using the viewLog() function. The PrintingService retrieves logs associated with the student's ID. The SPSO and University Administrator can view logs for all students, while individual students only have access to their own logs.


![Authenticate via HCMUT SSO - Activity Diagram](Student_Smart_Printing_Module.md.png)
