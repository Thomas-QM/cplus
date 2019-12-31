/* This file was automatically generated.  Do not edit! */
#undef INTERFACE
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "math.h"
#include "string.h"
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
num* num_new(num x);
typedef struct expr expr;
typedef struct {
  char* start;
  char* end;
} span;
int cost(expr* e);
typedef struct {
  unsigned long size;

  unsigned long length;
  char* data;
} vector;
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
} map;
typedef struct {
  map ids;
} module;
typedef struct {
  char* file;
  span s;
  unsigned long len;

  vector tokens;

  module global;

  /// tells whether to continue into codegen
  char errored;
} frontend;
typedef struct {
  frontend* fe;
  module* mod;

  map scope;
  substitution* sub;
} evaluator;
int condition(evaluator* ev, expr* from, expr* to);
typedef struct {
  vector condition; //condition of substitution
  vector val; //expression for every substitute indexes
} substitution;
typedef struct exp_idx exp_idx;
typedef enum {
  move_left, move_right,
  move_for_i, move_for_base,
  move_call_i
} move_kind;
struct exp_idx {
  struct exp_idx* from;
  move_kind kind;
  unsigned long i; //index of substitute
};
int bind(expr* from, expr* to, substitution* sub, exp_idx* cursor);
typedef struct value value;
struct value {
  vector substitutes;
  map substitute_idx;

  struct expr* val;
};
struct expr {
  span s;

  struct expr* first;

  int cost; //memoized cost

  enum {
	exp_add, exp_invert, exp_mul, exp_div, exp_pow, //1-2 args
	//a conditional is a for expressed without the base, def is a for if i=1
		exp_cond, exp_def, exp_for, exp_call //2-3 args
  } kind;

  union {
	struct {
	  enum {
		exp_bind, exp_num, exp_inner
	  } ty;
	  union {
		num* by;
		unsigned long bind;
		struct expr* inner;
	  } val;
	};

	struct {
	  struct expr* base; //if zero

	  char named;
	  unsigned long x;
	  struct expr* i;
	} _for;

	struct {
	  struct value* to;
	  substitution sub;
	} call;
  };
};
void set_num(expr* e, num n);
num num_invert(num n);
num num_add(num num1, num num2);
num num_pow(num num1, num num2);
num num_div(num num1, num num2);
num num_mul(num num1, num num2);
int num_eq(num num1, num num2);
extern num ONE;
extern num ZERO;
void commute(num* num1, num* num2);
void convert_dec(num* n);
