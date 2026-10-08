%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void);
void yyerror(const char *s);

/* Parse tree node structure */
typedef struct Node {
    char val[64];
    struct Node *left;
    struct Node *right;
} Node;

Node *create_node(const char *val, Node *left, Node *right) {
    Node *n = (Node *)malloc(sizeof(Node));
    strncpy(n->val, val, sizeof(n->val) - 1);
    n->val[sizeof(n->val) - 1] = '\0';
    n->left = left;
    n->right = right;
    return n;
}

void print_tree_hierarchical(Node *root, int depth) {
    if (!root) return;
    print_tree_hierarchical(root->right, depth + 1);
    for (int i = 0; i < depth; i++) printf("    ");
    printf("[%s]\n", root->val);
    print_tree_hierarchical(root->left, depth + 1);
}

Node *tree_root = NULL;
%}

%union {
    char *str;
    struct Node *node;
}

%token <str> ID NUM
%token ASSIGN SEMI PLUS MINUS MUL DIV LPAREN RPAREN

%type <node> statement expr

%left PLUS MINUS
%left MUL DIV

%%
statement : ID ASSIGN expr SEMI {
            $$ = create_node("=", create_node($1, NULL, NULL), $3);
            tree_root = $$;
            printf("\n>>> Valid Assignment Statement! <<<\n");
          }
          | expr SEMI {
            tree_root = $1;
            printf("\n>>> Valid Arithmetic Expression! <<<\n");
          }
          ;

expr : expr PLUS expr   { $$ = create_node("+", $1, $3); }
     | expr MINUS expr  { $$ = create_node("-", $1, $3); }
     | expr MUL expr    { $$ = create_node("*", $1, $3); }
     | expr DIV expr    { $$ = create_node("/", $1, $3); }
     | LPAREN expr RPAREN { $$ = $2; }
     | ID               { $$ = create_node($1, NULL, NULL); }
     | NUM              { $$ = create_node($1, NULL, NULL); }
     ;
%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error: %s\n", s);
}

int main(void) {
    printf("Enter expression or assignment (e.g. total = a + b * (c - d); ):\n");
    if (yyparse() == 0 && tree_root) {
        printf("\nConstructed Parse Tree (Hierarchical 90-deg view):\n");
        printf("---------------------------------------------------\n");
        print_tree_hierarchical(tree_root, 0);
        printf("---------------------------------------------------\n");
    }
    return 0;
}
