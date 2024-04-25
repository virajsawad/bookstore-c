#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Book structure
typedef struct {
    int id;
    char title[100];
    char author[50];
    int quantity;
    float price;
    float totalPrice;  // Total price for the book
} Book;

// Function prototypes
void displayMenu();
void addBook(Book *inventory, int *count);
void viewBooks(Book *inventory, int count);//(
void updateBook(Book *inventory, int count);
void deleteBook(Book *inventory, int *count);
void findBookByID(Book *inventory, int count);
void findBookByName(Book *inventory, int count);
void listBooksByAuthor(Book *inventory, int count);
void placeOrder(Book *inventory, int count);
void generateBill(Book book, int quantity);
void saveInventory(Book *inventory, int count);
void loadInventory(Book *inventory, int *count);

int main() {
    Book inventory[100];
    int count = 0;

    loadInventory(inventory, &count);

    while (1) {
        displayMenu();
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook(inventory, &count);// (&inventory[0]), 
                saveInventory(inventory, count);
                break;
            case 2:
                viewBooks(inventory, count);
                break;
            case 3:
                updateBook(inventory, count);
                saveInventory(inventory, count);
                break;
            case 4:
                deleteBook(inventory, &count);
                saveInventory(inventory, count);
                break;
            case 5:
                findBookByID(inventory, count);
                break;
            case 6:
                findBookByName(inventory, count);
                break;
            case 7:
                listBooksByAuthor(inventory, count);
                break;
            case 8:
                placeOrder(inventory, count);
                saveInventory(inventory, count);
                break;
            case 9:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

void displayMenu() {
    printf("\n");
    printf("*******************************************\n");
    printf("*       Bookstore Management System       *\n");
    printf("*******************************************\n");
    printf("1. Add a book\n");
    printf("2. View books\n");
    printf("3. Update a book\n");
    printf("4. Delete a book\n");
    printf("5. Find book by ID\n");
    printf("6. Find book by name\n");
    printf("7. List books by author\n");
    printf("8. Place an order\n");
    printf("9. Exit\n");
    printf("Enter your choice: ");
}

void addBook(Book *inventory, int *count) {
    Book book;

    printf("Enter book ID: ");
    scanf("%d", &book.id);
    printf("Enter book title: ");
    scanf("%s", book.title);
    printf("Enter book author: ");
    scanf("%s", book.author);
    printf("Enter book quantity: ");
    scanf("%d", &book.quantity);
    printf("Enter book price: ");
    scanf("%f", &book.price);

    book.totalPrice = book.price * book.quantity;

    inventory[*count] = book;
    (*count)++;

    printf("Book added successfully.\n");
}

void viewBooks(Book *inventory, int count) {
    printf("\nBooks in Inventory:\n");
    printf("ID\tTitle\t\tAuthor\t\tQuantity\tPrice\tTotal Price\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%s\t\t%s\t\t%d\t\t%.2f\t%.2f\n", inventory[i].id, inventory[i].title, inventory[i].author, inventory[i].quantity, inventory[i].price, inventory[i].totalPrice);
    }
}

void updateBook(Book *inventory, int count) {
    int id, found = 0;

    printf("Enter book ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (inventory[i].id == id) {
            printf("Enter new title: ");
            scanf("%s", inventory[i].title);
            printf("Enter new author: ");
            scanf("%s", inventory[i].author);
            printf("Enter new quantity: ");
            scanf("%d", &inventory[i].quantity);
            printf("Enter new price: ");
            scanf("%f", &inventory[i].price);

            inventory[i].totalPrice = inventory[i].price * inventory[i].quantity;
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book not found!\n");
    } else {
        printf("Book updated successfully.\n");
    }
}

void deleteBook(Book *inventory, int *count) {
    int id, found = 0;

    printf("Enter book ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < *count; i++) {
        if (inventory[i].id == id) {
            for (int j = i; j < *count - 1; j++) {
                inventory[j] = inventory[j + 1];
            }
            (*count)--;
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book not found!\n");
    } else {
        printf("Book deleted successfully.\n");
    }
}

void findBookByID(Book *inventory, int count) {
    int id, found = 0;

    printf("Enter book ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (inventory[i].id == id) {
            printf("\nBook found:\n");
            printf("ID\tTitle\t\tAuthor\t\tQuantity\tPrice\tTotal Price\n");
            printf("%d\t%s\t\t%s\t\t%d\t\t%.2f\t%.2f\n", inventory[i].id, inventory[i].title, inventory[i].author, inventory[i].quantity, inventory[i].price, inventory[i].totalPrice);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book not found!\n");
    }
}

void findBookByName(Book *inventory, int count) {
    char name[100];
    int found = 0;

    printf("Enter book name to search: ");
    scanf("%s", name);

    printf("\nBooks found by name '%s':\n", name);
    printf("ID\tTitle\t\tAuthor\t\tQuantity\tPrice\tTotal Price\n");
    for (int i = 0; i < count; i++) {
        if (strstr(inventory[i].title, name))//if founf return true else false
		 {
            printf("%d\t%s\t\t%s\t\t%d\t\t%.2f\t%.2f\n", inventory[i].id, inventory[i].title, inventory[i].author, inventory[i].quantity, inventory[i].price, inventory[i].totalPrice);
            found = 1;
        }
    }

    if (!found) {
        printf("No books found with name '%s'.\n", name);
    }
}

void listBooksByAuthor(Book *inventory, int count) {
    char author[50];
    int found = 0;

    printf("Enter author name to list books: ");
    scanf("%s", author);

    printf("\nBooks by author '%s':\n", author);
    printf("ID\tTitle\t\tAuthor\t\tQuantity\tPrice\tTotal Price\n");
    for (int i = 0; i < count; i++) {
        if (strstr(inventory[i].author, author)) {
            printf("%d\t%s\t\t%s\t\t%d\t\t%.2f\t%.2f\n", inventory[i].id, inventory[i].title, inventory[i].author, inventory[i].quantity, inventory[i].price, inventory[i].totalPrice);
            found = 1;
        }
    }

    if (!found) {
        printf("No books found by author '%s'.\n", author);
    }
}

void placeOrder(Book *inventory, int count) {
    int id, quantity, found = 0;

    printf("Enter book ID to order: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (inventory[i].id == id) {
            printf("Enter quantity: ");
            scanf("%d", &quantity);

            if (quantity > inventory[i].quantity) {
                printf("Not enough stock available.\n");
                return;
            }

            float totalCost = inventory[i].price * quantity;
            generateBill(inventory[i], quantity);
            inventory[i].quantity -= quantity;
            inventory[i].totalPrice -= totalCost;
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book not found!\n");
    }
}

void generateBill(Book book, int quantity) {
    printf("\n");
    printf("*******************************************\n");
    printf("*               BOOK BILL                  *\n");
    printf("*******************************************\n");
    printf("Book Title: %s\n", book.title);
    printf("Author: %s\n", book.author);
    printf("Quantity: %d\n", quantity);
    printf("Price per book: %.2f\n", book.price);
    printf("Total Cost: %.2f\n", book.price * quantity);
    printf("*******************************************\n");
    printf("Thank you for visiting us!\n");
    printf("*******************************************\n");
}

void saveInventory(Book *inventory, int count) {
    FILE *file = fopen("franz.txt", "w");

    if (file == NULL) {
        printf("Error saving inventory!\n");
        return;
    }

    fprintf(file, "ID\t\tTitle\t\tAuthor\t\tQuantity\t\tPrice\t\tTotal Price\n");

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d\t\t%s\t\t%s\t\t%d\t\t\t%.2f\t\t%.2f\n", inventory[i].id, inventory[i].title, inventory[i].author, inventory[i].quantity, inventory[i].price, inventory[i].totalPrice);
    }

    fclose(file);

    printf("Inventory saved successfully.\n");
}

void loadInventory(Book *inventory, int *count) {
    FILE *file = fopen("franz.txt", "r");

    if (file == NULL) {
        printf("No existing inventory found.\n");
        return;
    }

    fscanf(file, "%*[^\n]\n");  

    while (fscanf(file, "%d\t%s\t%s\t%d\t%f\t%f\n", &inventory[*count].id, inventory[*count].title, inventory[*count].author, &inventory[*count].quantity, &inventory[*count].price, &inventory[*count].totalPrice) != EOF) {
        (*count)++;
    }

    fclose(file);

    printf("Inventory loaded successfully.\n");
}

