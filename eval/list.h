typedef struct {
  enum {INT, STR, LST} t;
  union {
    int i;
    char *s;
    struct cell *l;
  } u;
} expr;

typedef struct cell {
  expr data;
  struct cell *next;
} *list;


