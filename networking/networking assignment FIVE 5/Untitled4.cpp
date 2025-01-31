#include <stdio.h>
#include <string.h>

int main() {
    char inputString[] = "<User.Name>John<User.Age>25<User.GPA>3.75<User.IP>192.168.1.1";

    char *namePtr = strstr(inputString, "<User.Name>") + strlen("<User.Name>");
    char *agePtr = strstr(inputString, "<User.Age>") + strlen("<User.Age>");
    char *gpaPtr = strstr(inputString, "<User.GPA>") + strlen("<User.GPA>");
    char *ipPtr = strstr(inputString, "<User.IP>") + strlen("<User.IP>");

    // Extracting name
    char userName[50];
    sscanf(namePtr, "%[^<]", userName);

    // Extracting age
    int age;
    sscanf(agePtr, "%d", &age);

    // Extracting GPA
    float gpa;
    sscanf(gpaPtr, "%f", &gpa);

    // Extracting IP
    char userIP[20];
    sscanf(ipPtr, "%[^<]", userIP);

    printf("Name: %s\n", userName);
    printf("Age: %d\n", age);
    printf("GPA: %.2f\n", gpa);
    printf("IP: %s\n", userIP);

    return 0;
}
