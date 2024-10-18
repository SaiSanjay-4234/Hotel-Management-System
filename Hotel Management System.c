#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct food{
    int id;
    char item[20];
    int price;
    struct food *next;
};
struct food *menu = NULL;

struct room{
    int id;
    int room_no, price, vacant, AC;
    struct room *next;
};
struct room *room_list = NULL;

struct customer_details {
    int room_no, bill;
    char name[20], phone_no[30];
    struct customer_details *next;
};
struct customer_details *customer_list = NULL;

void create_food_menu(){
    struct food *temp = (struct food *)malloc(sizeof(struct food));
    temp->id = 1;
    strcpy(temp->item, "paneer-pizza");
    temp->price = 100;
    temp->next = NULL;
    menu = temp;

    struct food *temp1 = (struct food *)malloc(sizeof(struct food));
    temp1->id = 2;
    strcpy(temp1->item, "babycorn-pizza");
    temp1->price = 120;
    temp->next = temp1;
    temp1->next = NULL;
}

void Display_customer_details() {
    struct customer_details *customer = customer_list;
    if (customer_list == NULL) {
        printf("NO CUSTOMERS\n");
        return;
    }
    while (customer != NULL) {
        printf("Room: %d\nName: %s\nPhone No: %s\nBill: %d\n\n", customer->room_no, customer->name, customer->phone_no, customer->bill);
        customer = customer->next;
    }
}

void create_room_list() {
    int i;
    for (i = 1; i <= 20; i++) {
        struct room *temp = (struct room *)malloc(sizeof(struct room));
        temp->id = i;
        temp->room_no = i;
        temp->vacant = 1;
        temp->next = NULL;
        if (i <= 10) {
            temp->AC = 1;
            temp->price = 1000;
        } else {
            temp->AC = 0;
            temp->price = 500;
        }
        if (room_list == NULL) {
            room_list = temp;
        } else {
            struct room *cur = room_list;
            while (cur->next != NULL) {
                cur = cur->next;
            }
            cur->next = temp;
        }
    }
}

void add_customer() {
    char name[20], phone_no[30];
    int AC;
    printf("Enter Name: ");
    scanf("%19s", name);
    printf("Enter Phone Number: ");
    scanf("%29s", phone_no);
    printf("Enter 1 for AC or 2 for NONAC:");
    int req;
    scanf("%d", &req);
    struct room *tem = room_list;
    while (tem != NULL) {
        if (req == 1 && tem->vacant == 1 && tem->AC == 1) {
            AC = 1;
            tem->vacant = 0;
            break;
        }
        if (req == 2 && tem->vacant == 1 && tem->AC == 0) {
            AC = 0;
            tem->vacant = 0;
            break;
        }
        tem = tem->next;
    }
    if (tem != NULL) {
        struct customer_details *temp_customer = (struct customer_details *)malloc(sizeof(struct customer_details));
        strcpy(temp_customer->name, name);
        strcpy(temp_customer->phone_no, phone_no);
        temp_customer->next = NULL;
        temp_customer->room_no = tem->room_no;
        printf("Alloted Room: %d\n", tem->room_no);
        temp_customer->bill = tem->price;
        temp_customer->next = customer_list;
        customer_list = temp_customer;
    } else {
        printf("No rooms available for the requested type\n");
    }
}

void Remove_customer() {
    int room, flag = 0;
    printf("Room number of the person who is vacating: ");
    scanf("%d", &room);
    if (customer_list != NULL) {
        struct customer_details *vacate_customer = customer_list;
        if (vacate_customer->room_no == room) {
            customer_list = customer_list->next;
            flag = 1;
            printf("Total bill = %d\n", vacate_customer->bill);
            free(vacate_customer);
        } else {
            while (vacate_customer->next != NULL) {
                if (vacate_customer->next->room_no == room) {
                    struct customer_details *tmp = vacate_customer->next;
                    vacate_customer->next = vacate_customer->next->next;
                    printf("Total bill = %d\n", tmp->bill);
                    free(tmp);
                    flag = 1;
                    break;
                }
                vacate_customer = vacate_customer->next;
            }
        }
        if (flag) {
            struct room *vacate_room = room_list;
            while (vacate_room != NULL) {
                if (vacate_room->room_no == room) {
                    vacate_room->vacant = 1;
                    break;
                }
                vacate_room = vacate_room->next;
            }
        } else {
            printf("No customer found with that room number\n");
        }
    } else {
        printf("ALL ROOMS ARE VACATED\n");
    }
}

void Receive_food_order() {
    char dish[20];
    int room, price;
    struct food *Dish = menu;
    printf("FOOD MENU\n\n");
    while (Dish != NULL) {
        printf("ID: %d, %s   %d\n", Dish->id, Dish->item, Dish->price);
        Dish = Dish->next;
    }
    printf("Enter Dish ID: ");
    int dish_id;
    scanf("%d", &dish_id);
    printf("Room: ");
    scanf("%d", &room);

    Dish = menu; // Reset Dish pointer to start of menu
    while (Dish != NULL) {
        if (Dish->id == dish_id) {
            price = Dish->price;
            struct customer_details *order_customer = customer_list;
            while (order_customer != NULL) {
                if (order_customer->room_no == room) {
                    order_customer->bill += price;
                    printf("Order added. Current bill: %d\n", order_customer->bill);
                    return;
                }
                order_customer = order_customer->next;
            }
            printf("No customer found with that room number\n");
            return;
        }
        Dish = Dish->next;
    }
    printf("No such Dish\n");
}

int main() {
    int choice;
    create_room_list();
    create_food_menu();
    printf("\t\t WELCOME TO HOTEL MANAGEMENT\n\n\t\tBELOW ARE THE AVAILABLE CHOICES\n");

    while (1) {
        printf("Enter the details\n1. Add Customer\n2. Remove Customer\n3. Display Customer Details\n4. Receive Food Order\n5. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: add_customer();
                    break;
            case 2: Remove_customer();
                    break;
            case 3: Display_customer_details();
                    break;
            case 4: Receive_food_order();
                    break;
            case 5: exit(0);
            default: printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
