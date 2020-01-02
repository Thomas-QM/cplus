/* This file was automatically generated.  Do not edit! */
#undef INTERFACE
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "math.h"
#include "string.h"
typedef enum {
	t_name, t_non_bind,
	t_add, t_sub,
	t_ellipsis, t_comma,
	t_in, t_for,
	t_eq, t_lparen, t_rparen,
	t_str, t_num,
	t_sync, t_eof
} token_type;
typedef struct {
	char* start;
	char* end;
} span;
typedef struct {
	char* qualifier;
	char* x;
} name;
typedef struct {
	enum {
		num_decimal,
		num_integer,
	} ty;

	union {
		uint64_t uint;
		int64_t integer;
		long double decimal;
	};
} num;
typedef struct {
	token_type tt;
	span s;

	union {
		name* name;
		char* str;
		num* num;
	} val;
} token;

void token_free(token* t);

typedef struct {
	unsigned long size;

	unsigned long length;
	char* data;
} vector;
typedef struct {
	vector* vec;

	unsigned long i;
	char rev;
	void* x;
} vector_iterator;

int vector_next(vector_iterator* iter);

vector_iterator vector_iterate(vector* vec);

typedef struct {
	unsigned long key_size;
	unsigned long size;

	/// hash and compare
	uint64_t (* hash)(void*);

	/// compare(&left, &right)
	int (* compare)(void*, void*);

	unsigned long length;
	unsigned long num_buckets;
	char* buckets;
}map;
typedef struct {
	map ids;
}module;
typedef struct {
	char* file;
	span s;
	unsigned long len;

	vector tokens;

	module global;

	/// tells whether to continue into codegen
	char errored;
}frontend;
void frontend_free(frontend *fe);
#define CONTROL_BYTES 16
typedef struct {
	uint8_t control_bytes[CONTROL_BYTES];
}bucket;
typedef struct {
	map* map;

	char c;
	unsigned long bucket;

	void* key;
	void* x;
	char current_c;
	bucket* bucket_ref;
} map_iterator;

int map_next(map_iterator* iterator);

map_iterator map_iterate(map* map);

void module_free(module* b);

typedef struct id id;
typedef struct value value;
typedef struct expr expr;

int cost(expr* exp);

typedef struct {
	frontend* fe;
	module* mod;

	map scope;
	//vector of copied substitutes for lazy evaluation
	vector sub;
} evaluator;

int condition(evaluator* ev, expr* exp1, expr* exp2);

typedef struct {
	vector condition; //vec of sub_conds
	vector val; //expression for every substitute indexes
} substitution;

int bind(expr* from, expr* to, substitution* sub);

int binary(expr* exp);

struct expr {
	span s;
	int cost; //memoized cost

	enum {
		exp_bind, exp_num,
		exp_add, exp_invert, exp_mul, exp_div, exp_pow, //1-2 args
		//a conditional is a for expressed without the base, def is a for if i=1
				exp_cond, exp_def, exp_for, exp_call //2-3 args
	} kind;

	union {
		num* by;
		unsigned long bind;
		struct expr* inner;

		struct {
			struct expr* base; //if zero
			struct expr* step;

			char named;
			unsigned long x;
			struct expr* i;
		} _for;

		struct {
			struct expr* left;
			struct expr* right;
		} binary;

		struct {
			struct value* to;
			substitution sub;
		} call;
	};
};
struct value {
	vector substitutes;
	map substitute_idx;

	struct expr* val;
};
struct id {
	span s;
	char* name;
	value val;
	span substitutes;
	unsigned precedence;
};

void id_free(id* xid);

void expr_free(expr* exp);

void map_free(map* map);

void vector_free(vector* vec);

void value_free(value* val);

frontend make_frontend();

void map_configure_string_key(map* map, unsigned long size);

map map_new();

void module_init(module* b);

int read_file(frontend* fe, char* filename);

int is_name(token* x);

void print_num(num* n);

void* heapcpy(size_t size, const void* val);

void note(const span* s, const char* x);

void warn(const span* s, const char* x);

int throw(const span* s, const char* x);

void* vector_get(vector* vec, unsigned long i);

void* vector_pushcpy(vector* vec, void* x);

vector vector_new(unsigned long size);

#if _WIN32
void set_col(FILE *f,char color);
#endif
#if !(_WIN32)

void set_col(FILE* f, char color);

#endif

void msg(frontend* fe,
				 const span* s,
				 char color1,
				 char color2,
				 const char* template_empty,
				 const char* template,
				 const char* msg);

void* heap(size_t size);

char* spanstr(span* s);

unsigned long span_len(span* s);

int span_eq(span s, char* x);

int compare_name(name* x1, name* x2);

uint64_t hash_string(char** x);

uint64_t hash_name(name* x);

extern const span SPAN_NULL;
extern frontend* FRONTEND;