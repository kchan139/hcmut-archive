# Data Storage Approach for HCMUT Smart Printing Service

The data storage approach for the HCMUT Smart Printing Service will utilize **MySQL** as the database management system, designed to efficiently manage a variety of data types, including user profiles, document uploads, print logs, printer configurations, and transaction records. The key components of this approach are as follows:

## Database Structure
- The relational **MySQL database** is used to store structured data, such as user information, printer details, and transaction records. Tables are designed with relationships to optimize data retrieval and maintain data integrity.
- **Indexing** is applied to frequently queried fields, such as user IDs and printer IDs, to ensure quick access to frequently requested data, like individual user print logs or printer statuses.

## Document Storage
- **Blob Storage** (Binary Large Object) or a dedicated document storage service is used to securely store uploaded documents. This storage solution allows for handling various file formats and sizes while ensuring quick access for the printing process.
- Documents are stored with a **unique identifier** linking them to the corresponding user and print job in the MySQL database, allowing for efficient cross-referencing between document storage and user data.

## Data Security and Privacy
- All sensitive data, including user details and transaction records, is **encrypted** both at rest and in transit to ensure data confidentiality and integrity.
- **Role-based access control** is implemented to restrict access to specific data types. For example:
  - Only authorized Student Printing Service Officers (SPSOs) can view all print logs.
  - Students can access only their own logs.

## Data Archiving and Retention
- **Automated data archiving** for historical print logs and transaction records is implemented to maintain system performance. Archived data can be retrieved for reporting and auditing purposes but is stored separately from active data.
- A **data retention policy** is enforced, automatically deleting data that exceeds the retention period unless flagged for long-term storage, helping optimize storage usage while adhering to data privacy requirements.

This data storage approach with MySQL ensures that the system is scalable, secure, and efficient, capable of handling high data volumes and providing quick, reliable access to information within the HCMUT Smart Printing Service.

---

## Entity-Relationship Diagram (ERD)
The **Entity-Relationship Diagram (ERD)** for the Student Printing Service system is designed to manage and track various aspects of the printing process, including:
- Student print jobs
- Transactions
- Printer management
- Document handling

![Data Storage Approach](Data_Storage_Approach.png)
