#include "string.h"

typedef struct string string;
typedef struct error error;
typedef struct ok ok;
typedef struct option option;

option construct_empty(string* s) {
	s->s = NULL;
	s->memory_size = 0;
	s->last_char = 0;
	return option_ok();
}

option construct_from_n(string* s, uint64_t n) {
	construct_empty(s);
	s->s = (char*)malloc(sizeof(char) * n);
	if (s->s) {
		s->memory_size = n;
		s->last_char = 0;
		for (uint64_t i = 0; i < n; ++i)
			s->s[i] = ' ';
		return option_ok();
	}
	return option_error(REFUZE_MEMORY_ALLOCATION);
}

option construct_from_s(string* s, string s_) {
	option r_;
	construct_empty(s);
	r_ = construct_from_n(s, s_.memory_size); check(r_);
	r_ = copy_string(s, s_); check(r_);
	return option_ok();
}

option construct_from_char_pointer(string* s, const char* p) {
	option r_;
	if (p == NULL)
		return option_error(NULL_POINTER_ACCES);
	construct_from_n(s, 1);
	uint64_t i = 0;
	while (p[i] != '\0') {
		add_char(s, p[i]);
		++i;
	}
	return option_error(REFUZE_MEMORY_ALLOCATION);
}

option destruct(string* s) {
	if (s->s) {
		free(s->s);
		s->last_char = 0;
		s->memory_size = 0;
		return option_ok();
	}
	return option_error(DEALLOCATE_NULL_POINTER);
}


 option annul(string* s) {
	s->s = NULL;
	s->last_char = 0;
	s->memory_size = 0;
	return option_ok();
}

option appropriate_memory(string* s, string* s_) {
	option r_;
	destruct(s);
	s->s = s_->s;
	s->memory_size = s_->memory_size;
	s->last_char = s_->last_char;
	annul(s_);
	return option_ok();
}

option copy_string(string* s, string s_) {
	if (s->s && s_.s) {
		uint64_t min_size = min(s->last_char, s_.last_char);
		uint64_t i = 0;
		while (i <= min_size) {
			s->s[i] = s_.s[i];
			++i;
		}
		while (i <= s->last_char) {
			s->s[i] = ' ';
			++i;
		}
		return option_ok();
	}
	return option_error(NULL_POINTER_ACCES);
}

option appropriate_string(string* s, string* s_) {
	option r_;
	r_ = construct_from_s(s, *s_); check(r_);
	r_ = copy_string(s, *s_); check(r_);
	return option_ok();
}


option add_memory(string* s, uint64_t n) {
	option r_;
	string s_;
	r_ = construct_from_n(&s_, s->memory_size * n); check(r_);
	r_ = copy_string(&s_, *s); check(r_);
	r_ = appropriate_memory(s, &s_); check(r_);
	return option_ok();
}

option add_char(string* s, char c) {
	if (s->s) {
		if (s->last_char < s->memory_size) {
			s->s[s->last_char] = c;
			s->last_char++;
		}
		else {
			option r_ = add_memory(s, 2); check(r_);
			s->s[s->last_char] = c;
			s->last_char++;
		}
		return option_ok();
	}
	return option_error(NULL_POINTER_ACCES);
}


option read(string* s) {
	option r_;
	char c;
	while (c = getchar() != EOF) {
		r_ = add_char(s, c); check(r_);
	}
	return option_ok();
}

option print(string s) {
	for (uint64_t i = 0; i <= s.last_char; ++i) {
		printf("%s", s.s[i]);
	}
}

option at(string* s, uint64_t i) {
	if (i < s->memory_size)
		return get_option(RES_OK, &s->s[i], NO_ERROR);
	return option_error(OCCUPIED_MEMORY_ACCES);
}