#include <stdio.h>
#include <string.h>
// تعريف حجم المخزن
#define SIZE 15
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
        printf("[Status] Buffer Full! Cannot insert '%c' (Character Lost)\n", data);
        return;
    }
    
    cb->buffer[cb->tail] = data;
    cb->tail = (cb->tail + 1) % SIZE;
    // التحريك الدائري 
    cb->count++;
}
// دالة القراءة 
char read(struct CircularBuffer *cb) {
    if (isEmpty(cb)) return '\0';
    
    char data = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % SIZE;
    cb->count--;
    return data;
}
// دالة main
int main() {
    struct CircularBuffer cb;
    init(&cb);

    char name[50];
    char added[] = "CE-ESY";
    char finalStr[100];

    printf(">>> enter your name: ");
    scanf("%s", name);

    // دمج النصوص
    strcpy(finalStr, name);
    strcat(finalStr, added);

    printf("\n--- Processing Report ---\n");
    printf("Target String: %s\n", finalStr);
    printf("Buffer Capacity: %d characters\n", SIZE);
    printf("Total Length: %lu\n", (unsigned long)strlen(finalStr));
    // مرحلة الكتابة
    for (int i = 0; i < strlen(finalStr); i++) {
        write(&cb, finalStr[i]);
    }
    // مرحلة القراءة
    while (!isEmpty(&cb)) {
        printf("%c", read(&cb));
    }

    // التحقق النهائي من حالة المخزن
    printf("\n\n... Checking Final Status...\n");
    if (isEmpty(&cb)) {
        printf ( "Success: Buffer is now completely empty.\n");
    }

    return 0;
}
