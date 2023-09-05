#include <stdio.h>
#include <string.h>

// Định nghĩa cấu trúc dữ liệu liên hệ
struct Contact {
    char name[100];
    char phone[15];
    char address[100];
};

// Hàm để thêm liên hệ mới vào tập tin
void add_contact(FILE *file) {
    struct Contact contact;

    printf("Enter name: ");
    scanf("%s", contact.name);
    printf("Enter phone number: ");
    scanf("%s", contact.phone);
    printf("Enter address: ");
    scanf("%s", contact.address);

    // Ghi thông tin liên hệ vào tập tin
    fprintf(file, "%s,%s,%s\n", contact.name, contact.phone, contact.address);

    printf("Contact added successfully!\n");
}

// Hàm để hiển thị danh sách liên hệ từ tập tin
void display_contacts(FILE *file) {
    struct Contact contact;

    printf("Contact List:\n");

    // Đọc và hiển thị thông tin liên hệ từ tập tin
    while (fscanf(file, "%[^,],%[^,],%[^\n]\n", contact.name, contact.phone, contact.address) != EOF) {
        printf("Name: %s\nPhone: %s\nAddress: %s\n\n", contact.name, contact.phone, contact.address);
    }
}

// Hàm để tìm kiếm thông tin liên hệ dựa trên tên
void search_contact(FILE *file, const char *search_name) {
    struct Contact contact;
    int found = 0;

    // Đọc và tìm kiếm thông tin liên hệ từ tập tin
    while (fscanf(file, "%[^,],%[^,],%[^\n]\n", contact.name, contact.phone, contact.address) != EOF) {
        if (strcmp(contact.name, search_name) == 0) {
            printf("Contact found:\nName: %s\nPhone: %s\nAddress: %s\n", contact.name, contact.phone, contact.address);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Contact not found!\n");
    }
}

int main() {
    FILE *file;
    char file_name[] = "contacts.txt";
    int choice;
    char search_name[100];

    // Mở tập tin danh bạ
    file = fopen(file_name, "a+");

    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    printf("Welcome to the Contact Manager!\n");

    while (1) {
        printf("1. Add a new contact\n");
        printf("2. Display all contacts\n");
        printf("3. Search for a contact\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_contact(file);
                break;
            case 2:
                rewind(file); // Đặt con trỏ tập tin ở đầu
                display_contacts(file);
                break;
            case 3:
                printf("Enter name to search for: ");
                scanf("%s", search_name);
                rewind(file); // Đặt con trỏ tập tin ở đầu
                search_contact(file, search_name);
                break;
            case 4:
                fclose(file); // Đóng tập tin trước khi thoát
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

