#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Date {
  int day, month, year;
};

struct Student {
  char registration[10];
  char name[40];
  struct Date birthday;
  float grade;
  struct Student* next;
};
 
struct Node {
  struct Student student;
  struct Node* next;
};

struct Date parseDate(char str_date[11]) {
  struct Date date;
  int day, month, year;

  sscanf(str_date, "%d/%d/%d", &day, &month, &year);

  date.day = day;
  date.month = month;
  date.year = year;

  return date;
}

char *stringifyDate(struct Date date) {
  static char date_str[11];

  sprintf(date_str, "%d/%d/%d", date.day, date.month, date.year);

  return date_str;
}

struct Student newStudent(
  char *registration,
  char *name,
  char *input_date,
  float grade
) {
  struct Student student;

  strcpy(student.registration, registration);
  strcpy(student.name, name);
  student.birthday = parseDate(input_date);
  student.grade = grade;
  
  return student;
}

void insert(struct Node** head_ref) {
  char registration[10], name[40], birthday[11];
  float grade;
  struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
  struct Node *last = *head_ref;

  scanf("%s", registration);
  scanf("%s", name);
  scanf("%s", birthday);
  scanf("%f", &grade);

  struct Student student = newStudent(
    registration,
    name,
    birthday,
    grade
  );

  new_node->student = student;
  new_node->next = NULL;

  if (*head_ref == NULL) {
    *head_ref = new_node;
    return;
  } 
    
  while (last->next != NULL) {
    last = last->next;
  }

  last->next = new_node;
}

void delete(struct Node** head_ref) {
  char registration[10];
  struct Node *tmp = *head_ref, *prev;

  scanf("%s", registration);

  if (tmp == NULL) {
    printf("Lista Vazia!\n");
    return;
  }

  if (tmp != NULL && strcmp(tmp->student.registration, registration) == 0) {
    *head_ref = tmp->next;
    free(tmp);
    return;
  }

  while (tmp != NULL && strcmp(tmp->student.registration, registration) != 0) {
    prev = tmp;
    tmp = tmp->next;
  }

  if (tmp == NULL) return;

  prev->next = tmp->next;

  free(tmp);
}

void length(struct Node* head) {
  int listLength = 0;
  struct Node* current = head;

  while (current != NULL) {
    listLength++;
    current = current->next;
  }

  printf("%d\n", listLength);
}
 
void list(struct Node* head) {
  if (head == NULL) {
    printf("Lista Vazia!\n");
    return;
  }
  
  while (head != NULL) {
    printf("%s, ", head->student.registration);
    printf("%s, ", head->student.name);
    printf("%s, ", stringifyDate(head->student.birthday));
    printf("%.2f\n", head->student.grade);
    head = head->next;
  }
}

void reverseList(struct Node* head) {
  if (head == NULL) return;

  reverseList(head->next);
  printf("%s, ", head->student.registration);
  printf("%s, ", head->student.name);
  printf("%s, ", stringifyDate(head->student.birthday));
  printf("%.2f\n", head->student.grade);
}

void freeMemory(struct Node* head) {
  struct Node *tmp;

  while (head != NULL) {
    tmp = head;
    head = head->next;
    free(tmp);
    printf("-");
  }

  printf("\n");
}

void menu(struct Node* head) {
  int opt;

  scanf("%d", &opt);

  if (opt < 0 || opt > 5) {
    return menu(head);
  }

  if (opt == 1) {
    insert(&head);
    return menu(head);
  } else if (opt == 2) {
    delete(&head);
    return menu(head);
  } else if (opt == 3) {
    list(head);
    return menu(head);
  } else if (opt == 4) {
    if (head == NULL) {
      printf("Lista Vazia!\n");
      return menu(head);
    }
    reverseList(head);
    return menu(head);
  } else if (opt == 5) {
    length(head);
    return menu(head);
  }

  freeMemory(head);
}
 
int main() {
  struct Node* head = NULL;

  menu(head);

  return 0;
}
