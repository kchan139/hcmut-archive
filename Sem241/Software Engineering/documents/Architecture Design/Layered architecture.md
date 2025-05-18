# Layered Architecture

The layered architecture pattern, also known as the n-tier architecture pattern, is one of the most commonly used designs. It is the default standard for many Java EE applications, making it highly familiar to architects, designers, and developers alike. This pattern aligns well with the traditional communication flows and organizational structures found in most companies, which makes it a natural fit for business application development.

We choose this pattern because it is widely recognized and relatively straightforward to implement. In the layered architecture pattern, components are arranged into horizontal layers, each dedicated to a specific function within the application. For instance, the presentation layer manages user interface and browser interactions, while the business layer handles the business logic needed to process requests. With the separation of concerns among components, it simplifies the development, testing, and maintenance process. The isolation from the layered architecture also allows us to make changes in one layer without affecting the other layers.

However, this structure also has its disadvantages:
- **Rigid structure**: The strict layer hierarchy can be limiting, especially if the application needs to bypass certain layers for efficiency or services that frequently change dynamically. Since our printing system is a simple system and only focuses on providing printing utility to the students and the university staff, this problem won’t affect us as much as it would for high scalability applications.
- **High overhead**: While it is true some layered architectures can perform well, the pattern does not lend itself to high-performance applications due to inefficiencies of having to go through multiple layers of the architecture to fulfill a business request, especially for simpler requests that do not add value or perform operations at every layer. Because the size and scale of HCMUT_SSPS are not very large, we can accept this disadvantage.

So, even though there are disadvantages to consider, the benefits outweigh the impact caused by the shortcomings.

![Layered Architecture](Layered_architecture.png)

The system is being used by two main types of users: students and the university staff (SPSO, Uni admin). So, the presentation layer respectively has two interfaces: one for the students and one for the staff.

### Student Functionalities
- Log in (authenticated by HCMUT_SSO in the service layer)
- View Printing History (reads data from the database layer)
- Configure printing format of their documents
- Access the buying page for printing (through payment service providers in the service layer)
- Printing itself, which accesses the manage printing service and interacts with the persistence layer for read/write data purposes.

### SPSO/University Admin Functionalities
- Log in
- View students' printing logs
- View annual reports
- System configuration
- Manage printers

Some functions overlap with the students' functionalities. For example:
- **Viewing reports**: Accesses the report generation service and reads corresponding data from the database.
- **Printers management**: Accesses the Manage Printing service, allowing attributes and statuses to be edited via the persistence layer.

### Service Layer Flexibility
The service layer in our diagram is marked as open, meaning requests are allowed to bypass this layer and go directly to the layer below it. This makes sense because some functions, like **View Printing History**, don’t require additional processing from the service layer and benefit from direct access to the persistence layer for faster, simpler data retrieval.
