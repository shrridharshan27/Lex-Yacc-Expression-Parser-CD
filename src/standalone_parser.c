/**
 * ============================================================================
 * Standalone Expression Parser & Parse Tree Generator in Pure C
 * Does not require external flex/bison installed.
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    char val[64];
    struct Node *left;
    struct Node *right;
} Node;

Node *new_node(const char *val, Node *l, Node *r) {
    Node *n = (Node *)malloc(sizeof(Node));
    strncpy(n->val, val, sizeof(n->val) - 1);
    n->val[sizeof(n->val) - 1] = '\0';
    n->left = l;
    n->right = r;
    return n;
}

const char *src;
int pos = 0;

void skip_ws(void) {
    while (src[pos] && isspace((unsigned char)src[pos])) pos++;
}

Node *parse_expr(void);

Node *parse_factor(void) {
    skip_ws();
    if (src[pos] == '(') {
        pos++;
        Node *n = parse_expr();
        skip_ws();
        if (src[pos] == ')') pos++;
        else printf("Error: Expected ')'\n");
        return n;
    }
    if (isalpha((unsigned char)src[pos]) || src[pos] == '_') {
        char buf[64]; int b = 0;
        while (isalnum((unsigned char)src[pos]) || src[pos] == '_') {
            buf[b++] = src[pos++];
        }
        buf[b] = '\0';
        return new_node(buf, NULL, NULL);
    }
    if (isdigit((unsigned char)src[pos])) {
        char buf[64]; int b = 0;
        while (isdigit((unsigned char)src[pos])) {
            buf[b++] = src[pos++];
        }
        buf[b] = '\0';
        return new_node(buf, NULL, NULL);
    }
    return NULL;
}

Node *parse_term(void) {
    Node *left = parse_factor();
    while (1) {
        skip_ws();
        if (src[pos] == '*' || src[pos] == '/') {
            char op[2] = {src[pos++], '\0'};
            Node *right = parse_factor();
            left = new_node(op, left, right);
        } else {
            break;
        }
    }
    return left;
}

Node *parse_expr(void) {
    Node *left = parse_term();
    while (1) {
        skip_ws();
        if (src[pos] == '+' || src[pos] == '-') {
            char op[2] = {src[pos++], '\0'};
            Node *right = parse_term();
            left = new_node(op, left, right);
        } else {
            break;
        }
    }
    return left;
}

void print_tree(Node *root, int depth) {
    if (!root) return;
    print_tree(root->right, depth + 1);
    for (int i = 0; i < depth; i++) printf("     ");
    printf("[%s]\n", root->val);
    print_tree(root->left, depth + 1);
}

void print_traversal(Node *root) {
    if (!root) return;
    printf("(");
    print_traversal(root->left);
    printf(" %s ", root->val);
    print_traversal(root->right);
    printf(")");
}

int main(void) {
    const char *test_expressions[] = {
        "a + b * (c - d)",
        "x = 10 * 5 + 3",
        "(p + q) * (r - s) / 2"
    };

    printf("============================================================\n");
    printf("  EXPERIMENT 3: EXPRESSION PARSER & PARSE TREE CONVERTER    \n");
    printf("============================================================\n\n");

    for (int i = 0; i < 3; i++) {
        src = test_expressions[i];
        pos = 0;
        printf("Test Case %d: Input = \"%s\"\n", i + 1, src);
        
        // check assignment
        char id_buf[64];
        skip_ws();
        int saved = pos;
        if (isalpha(src[pos])) {
            int b = 0;
            while (isalnum(src[pos])) id_buf[b++] = src[pos++];
            id_buf[b] = '\0';
            skip_ws();
            if (src[pos] == '=') {
                pos++;
                Node *rhs = parse_expr();
                Node *root = new_node("=", new_node(id_buf, NULL, NULL), rhs);
                printf("Status: Valid Assignment Statement!\n");
                printf("Hierarchical Parse Tree:\n");
                print_tree(root, 0);
                printf("\n------------------------------------------------------------\n");
                continue;
            }
        }
        pos = saved;
        Node *root = parse_expr();
        if (root) {
            printf("Status: Valid Arithmetic Expression!\n");
            printf("Hierarchical Parse Tree:\n");
            print_tree(root, 0);
        } else {
            printf("Status: Syntax Error!\n");
        }
        printf("\n------------------------------------------------------------\n");
    }
    return 0;
}
