#include <stdio.h>
#include <string.h>
// تعريف حجم المخزن
#define SIZE 10 
// المخزن الدائري 
struct CircularBuffer {
    char buffer[SIZE];
    int head;
    int tail;
    int count;
};
// دالة التهيئة
void init(struct CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}
// للتحقق من الامتلاء
int isFull(struct CircularBuffer *cb) {
    return cb->count == SIZE;
}
// للتحقق من الفراغ
int isEmpty(struct CircularBuffer *cb) {
    return cb->count == 0;
}
// دالة الكتابة 
void write(struct CircularBuffer *cb, char data) {
    if (isFull(cb)) {
        printf("\nBuffer Overflow\n");
        return;
    }
    cb->buffer[cb->tail] = data;
    cb->tail = (cb->tail + 1) % SIZE;  //التحريك الدائري
    cb->count++;
}
// دالة القراءة
char read(struct CircularBuffer *cb) {
    if (isEmpty(cb)) {
        printf("\nBuffer Underflow\n");
        return '\0';
    }
    char data = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % SIZE;
    cb->count--;
    return data;
}

int main() {
    struct CircularBuffer cb;
    init(&cb);

    char name[50];
    char added[] = "CE-ESY";

    printf("Enter your name: ");
    scanf("%s", name);

    strcat(name, added);

    for (int i = 0; i < strlen(name); i++) {
        write(&cb, name[i]);
    }

    while (!isEmpty(&cb)) {
        printf("%c", read(&cb));
    }

    return 0;
}

