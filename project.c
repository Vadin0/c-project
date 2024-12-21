#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_BORROWED 100

typedef struct {
    int id;
    char title[100];
    char author[100];
    int isBorrowed; 
} Book;

typedef struct {
    int studentId;
    int bookId;
} BorrowedBook;

Book library[MAX_BOOKS];
BorrowedBook borrowedBooks[MAX_BORROWED];
int bookCount = 0;
int borrowedCount = 0;

void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Library is full. Cannot add more books.\n");
        return;
    }
    Book newBook;
    printf("Enter Book ID: ");
    scanf("%d", &newBook.id);
    printf("Enter Book Title: ");
    scanf(" %[^\n]%*c", newBook.title); 
    printf("Enter Book Author: ");
    scanf(" %[^\n]%*c", newBook.author);
    newBook.isBorrowed = 0; 
    library[bookCount++] = newBook;
    printf("Book Added Successfully.\n");
}

void borrowBook() {
    int studentId, bookId;
    printf("Enter Student ID: ");
    scanf("%d", &studentId);
    printf("Enter Book ID: ");
    scanf("%d", &bookId);

    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == bookId && library[i].isBorrowed == 0) {
            library[i].isBorrowed = 1; // mark as borrowed
            borrowedBooks[borrowedCount++] = (BorrowedBook){studentId, bookId};
            printf("Book Borrowed Successfully by Student %d.\n", studentId);
            return;
        }
    }
    printf("Book is not available for borrowing.\n");
}

void returnBook() {
    int studentId, bookId, daysLate;
    printf("Enter Student ID: ");
    scanf("%d", &studentId);
    printf("Enter Book ID: ");
    scanf("%d", &bookId);
    printf("Enter Number of Days Late: ");
    scanf("%d", &daysLate);

    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == bookId && library[i].isBorrowed) {
            library[i].isBorrowed = 0; 

            int fine = daysLate > 0 ? daysLate * 10 : 0;
            if (fine > 0) {
                printf("Fine of Rs. %d Applied.\n", fine);
            }

            
            for (int j = 0; j < borrowedCount; j++) {
                if (borrowedBooks[j].studentId == studentId && borrowedBooks[j].bookId == bookId) {
                    borrowedBooks[j] = borrowedBooks[--borrowedCount]; 
                    break;
                }
            }

            printf("Book Returned Successfully.\n");
            return;
        }
    }
    printf("Book was not borrowed or does not exist.\n");
}

void generateReports() {
    printf("List of All Available Books:\n");
    for (int i = 0; i < bookCount; i++) {
        if (!library[i].isBorrowed) {
            printf("ID: %d, Title: \"%s\", Author: %s\n", library[i].id, library[i].title, library[i].author);
        }
    }

    printf("\nList of Borrowed Books:\n");
    for (int i = 0; i < borrowedCount; i++) {
        for (int j = 0; j < bookCount; j++) {
            if (borrowedBooks[i].bookId == library[j].id) {
                printf("Student ID: %d, Book Title: \"%s\"\n", borrowedBooks[i].studentId, library[j].title);
                break;
            }
        }
    }
}

int main() {
    int choice;
    do {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. Borrow Book\n");
        printf("3. Return Book\n");
        printf("4. Generate Reports\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                borrowBook();
                break;
            case 3:
                returnBook();
                break;
            case 4:
                generateReports();
                break;
            case 5:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

}
