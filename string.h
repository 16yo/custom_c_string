#ifndef STRING_H

#define STRING_H

#include <inttypes.h>
#include <stdio.h>
#include "option.h"

// Структура Строка
struct string {
	char* s;
	uint64_t memory_size;
	uint64_t last_char;
};

typedef struct string string;

// Процедура конструирования строки из n символов
option construct_from_n(string* s, uint64_t n);

// Процедура конструирования строки из другой строки
option construct_from_s(string* s, string s_);

// Процедура конструирования строки из массива символов
option construct_from_char_pointer(string* s, const char* p);

// Процедура деструктирования строки
option destruct(string* s);

// Аннулировать строку 
option annul(string* s);

// Процедура присвоения памяти
option appropriate_memory(string* s, string* s_);

// Процедура присвоения строки
option appropriate_string(string* s, string* s_);

// Процедура копирования строки (без учёта памяти)

// Пример: <'abc'; '1234'> -> <'123'; '1234'>
// Пример: <'abcd'; '123'> -> <'123 '; '123'>
option copy_string(string* s, string s_);

// Процедура добавления памяти в строку
option add_memory(string* s, uint64_t n);

// Добавить символ
option add_char(string* s, char c);

// Считать строку
option read(string* s);

// Вывести строку
option print(string s);

// Получить i-тый символ строки
option at(string* s, uint64_t i);

// Макросы
#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

#endif