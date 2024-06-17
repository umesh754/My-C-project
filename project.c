#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#define DATA_DIRECTORY "D:\\project+\\"
#define USERS_FILE DATA_DIRECTORY "users.dat"

struct User {
    char username[50];
    char password[50];
};

char current_username[50];
char current_password[50];

void load_user(const char *username);
int login();
void signup();
void logout();
void new_file();
void display_files();
void delete_file();
void change_password();
void delete_account();
void menu();
void clear_screen();
void show_loading_screen();
void reset_login_attempts();

int main() {
    int login_attempts = 0;
    while (1) {
        int choice;
        clear_screen();
        printf("====================================\n");
        printf("            LOGIN PAGE              \n");
        printf("====================================\n");
        printf("1. Login\n");
        printf("2. Signup\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                while (!login()) {
                    login_attempts++;
                    if (login_attempts >= 3) {
                        printf("Maximum login attempts reached. Resetting...\n");
                        reset_login_attempts();
                    }
                }
                menu();
                break;
            case 2:
                signup();
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
                Sleep(1000);
        }
    }

    return 0;
}

void load_user(const char *username) {
    FILE *file = fopen(USERS_FILE, "rb");
    if (file == NULL) {
        printf("Error opening users file!\n");
        exit(1);
    }

    struct User user;
    while (fread(&user, sizeof(struct User), 1, file)) {
        if (strcmp(user.username, username) == 0) {
            strcpy(current_username, user.username);
            strcpy(current_password, user.password);
            break;
        }
    }

    fclose(file);
}

int login() {
    char username[50];
    char password[50];
    int i = 0;

    clear_screen();
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");

    while (1) {
        char ch = _getch();
        if (ch == 13) {
            password[i] = '\0';
            break;
        } else if (ch == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            password[i++] = ch;
            printf("*");
        }
    }

    printf("\n");
    show_loading_screen();

    load_user(username);
    if (strcmp(username, current_username) == 0 && strcmp(password, current_password) == 0) {
        printf("Login successful!\n");
        Sleep(1000);
        clear_screen();
        return 1;
    } else {
        printf("Login failed! Try again.\n");
        Sleep(1000);
        clear_screen();
        return 0;
    }
}

void signup() {
    struct User new_user;
    FILE *file;

    clear_screen();
    printf("====================================\n");
    printf("              SIGNUP                \n");
    printf("====================================\n");
    printf("Enter a new username: ");
    scanf("%s", new_user.username);

    printf("Enter a new password: ");
    int i = 0;
    while (1) {
        char ch = _getch();
        if (ch == 13) {
            new_user.password[i] = '\0';
            break;
        } else if (ch == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            new_user.password[i++] = ch;
            printf("*");
        }
    }

    file = fopen(USERS_FILE, "ab");
    if (file == NULL) {
        printf("Error opening users file!\n");
        exit(1);
    }

    fwrite(&new_user, sizeof(struct User), 1, file);
    fclose(file);

    printf("\nSignup successful! Please login with your new credentials.\n");
    Sleep(2000);
    clear_screen();
}

void logout() {
    clear_screen();
    printf("Logging out...\n");
    Sleep(1000);
    main();
}

void new_file() {
    char name[50], age[10], address[100], contact_number[15], salary[20];
    char file_path[200];
    FILE *file;

    clear_screen();
    printf("====================================\n");
    printf("          CREATE NEW FILE           \n");
    printf("====================================\n");
    printf("Enter your name: ");
    scanf("%s", name);
    printf("Enter your age: ");
    scanf("%s", age);
    printf("Enter your address: ");
    scanf("%s", address);
    printf("Enter your contact number: ");
    scanf("%s", contact_number);
    printf("Enter your salary: ");
    scanf("%s", salary);

    snprintf(file_path, sizeof(file_path), "%s%s.txt", DATA_DIRECTORY, name);
    file = fopen(file_path, "w");

    if (file == NULL) {
        printf("Error creating file!\n");
        return;
    }

    fprintf(file, "Name: %s\nAge: %s\nAddress: %s\nContact Number: %s\nSalary: %s",
            name, age, address, contact_number, salary);

    fclose(file);
    printf("File '%s' created successfully.\n", file_path);
    Sleep(2000);
    clear_screen();
}

void display_files() {
    char file_path[200];
    char file_name[100];
    char buffer[255];
    FILE *file;

    clear_screen();
    printf("====================================\n");
    printf("           DISPLAY FILE             \n");
    printf("====================================\n");
    printf("Enter the name of the file to display (without extension): ");
    scanf("%s", file_name);

    snprintf(file_path, sizeof(file_path), "%s%s.txt", DATA_DIRECTORY, file_name);
    file = fopen(file_path, "r");

    if (file == NULL) {
        printf("File not found!\n");
        return;
    }

    printf("=== %s ===\n", file_name);
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    printf("=====================\n");

    fclose(file);
    Sleep(3000);
    clear_screen();
}

void delete_file() {
    char file_name[100];
    char file_path[200];

    clear_screen();
    printf("====================================\n");
    printf("           DELETE FILE              \n");
    printf("====================================\n");
    printf("Enter the name of the file to delete (without extension): ");
    scanf("%s", file_name);

    snprintf(file_path, sizeof(file_path), "%s%s.txt", DATA_DIRECTORY, file_name);

    if (remove(file_path) == 0) {
        printf("File '%s' deleted successfully.\n", file_path);
    } else {
        printf("File not found!\n");
    }

    Sleep(2000);
    clear_screen();
}

void change_password() {
    char username[50];
    char old_password[50];
    char new_password[50];
    int i = 0;

    clear_screen();
    printf("====================================\n");
    printf("          CHANGE PASSWORD           \n");
    printf("====================================\n");
    printf("Enter your current username: ");
    scanf("%s", username);
    printf("Enter your current password: ");

    while (1) {
        char ch = _getch();
        if (ch == 13) {
            old_password[i] = '\0';
            break;
        } else if (ch == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            old_password[i++] = ch;
            printf("*");
        }
    }

    printf("\n");

    load_user(username);
    if (strcmp(username, current_username) == 0 && strcmp(old_password, current_password) == 0) {
        printf("Enter new password: ");
        i = 0;
        while (1) {
            char ch = _getch();
            if (ch == 13) {
                new_password[i] = '\0';
                break;
            } else if (ch == 8) {
                if (i > 0) {
                    i--;
                    printf("\b \b");
                }
            } else {
                new_password[i++] = ch;
                printf("*");
            }
        }

        strcpy(current_password, new_password);

        FILE *file = fopen(USERS_FILE, "rb+");
        if (file == NULL) {
            printf("Error opening users file!\n");
            exit(1);
        }

        struct User user;
        while (fread(&user, sizeof(struct User), 1, file)) {
            if (strcmp(user.username, current_username) == 0) {
                fseek(file, -sizeof(struct User), SEEK_CUR);
                strcpy(user.password, new_password);
                fwrite(&user, sizeof(struct User), 1, file);
                break;
            }
        }

        fclose(file);

        printf("\nPassword changed successfully!\n");
    } else {
        printf("\nInvalid username or password!\n");
    }

    Sleep(2000);
    clear_screen();
}

void delete_account() {
    char username[50];
    char password[50];
    int i = 0;

    clear_screen();
    printf("====================================\n");
    printf("           DELETE ACCOUNT           \n");
    printf("====================================\n");
    printf("Enter your current username: ");
    scanf("%s", username);
    printf("Enter your current password: ");

    while (1) {
        char ch = _getch();
        if (ch == 13) {
            password[i] = '\0';
            break;
        } else if (ch == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            password[i++] = ch;
            printf("*");
        }
    }

    printf("\n");

    load_user(username);
    if (strcmp(username, current_username) == 0 && strcmp(password, current_password) == 0) {
        FILE *file = fopen(USERS_FILE, "rb+");
        FILE *temp = fopen(DATA_DIRECTORY "temp.dat", "wb");
        if (file == NULL || temp == NULL) {
            printf("Error opening users file!\n");
            exit(1);
        }

        struct User user;
        while (fread(&user, sizeof(struct User), 1, file)) {
            if (strcmp(user.username, username) != 0) {
                fwrite(&user, sizeof(struct User), 1, temp);
            }
        }

        fclose(file);
        fclose(temp);

        remove(USERS_FILE);
        rename(DATA_DIRECTORY "temp.dat", USERS_FILE);

        printf("\nAccount deleted successfully!\n");
        Sleep(2000);
        clear_screen();
        main();  // Go back to the login/signup screen
    } else {
        printf("\nInvalid username or password!\n");
        Sleep(2000);
        clear_screen();
    }
}

void menu() {
    int choice;

    while (1) {
        clear_screen();
        printf("====================================\n");
        printf("               MENU                 \n");
        printf("====================================\n");
        printf("1. New File\n");
        printf("2. Display Files\n");
        printf("3. Delete File\n");
        printf("4. Change Password\n");
        printf("5. Delete Account\n");
        printf("6. Logout\n");
        printf("7. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                new_file();
                break;
            case 2:
                display_files();
                break;
            case 3:
                delete_file();
                break;
            case 4:
                change_password();
                break;
            case 5:
                delete_account();
                break;
            case 6:
                logout();
                break;
            case 7:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
                Sleep(1000);
        }
    }
}

void clear_screen() {
    system("cls");
}

void show_loading_screen() {
    printf("Validating...");
    fflush(stdout);
    Sleep(2000);
    printf("\n");
}

void reset_login_attempts() {
    clear_screen();
}
