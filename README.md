# Hotel Management System

This project is a simple C-based Hotel Management System designed to manage room reservations, customer billing, and food orders for a small hotel. The system uses linked lists to maintain the records of rooms, customers, and the food menu. The primary functionalities include:

- **Room Reservation**: Allocate available rooms to customers based on their preference (AC or Non-AC).
- **Customer Management**: Add and remove customer details, track billing, and display customer information.
- **Food Ordering**: Customers can order food items from a predefined menu, and the cost is added to their total bill.
- **Billing System**: Calculate and display the final bill during customer checkout.

## Features
- Interactive command-line interface for hotel staff.
- Separate handling of AC and Non-AC rooms.
- Unique IDs for each room and menu item to simplify selection.
- Dynamically allocated memory for managing customer, room, and food information.

## How to Run
Compile the program using GCC or any C compiler:
```sh
gcc hotel_management.c -o hotel_management
```
Run the executable:
```sh
./hotel_management
```

## Technologies Used
- **C Programming Language**: The entire system is implemented using C, with an emphasis on pointer manipulation and dynamic memory allocation.
- **Data Structures**: Linked lists are used to manage different entities (rooms, customers, and menu items).

## Future Improvements
- Add file handling to save data between runs.
- Implement more detailed error handling.
- Add more menu items and room types.
