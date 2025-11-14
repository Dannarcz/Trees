#include <stdio.h>
#include <stdlib.h>

/* Estructura del nodo */
struct Node {
    int key;
    struct Node *left;
    struct Node *right;
};

struct Node* create_node(int key) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    if (!node) {
        fprintf(stderr, "Error: memoria insuficiente\n");
        exit(EXIT_FAILURE);
    }
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct Node* insert(struct Node* root, int key) {
    if (root == NULL)
        return create_node(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);

    return root;
}

struct Node* search(struct Node* root, int key) {
    if (root == NULL)
        return NULL;

    if (key == root->key)
        return root;

    if (key < root->key)
        return search(root->left, key);

    return search(root->right, key);
}

/* Recorridos del árbol */
void inorder(struct Node* root) {
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

void inorder_desc(struct Node* root) {
    if (!root) return;
    inorder_desc(root->right);
    printf("%d ", root->key);
    inorder_desc(root->left);
}

void preorder(struct Node* root) {
    if (!root) return;
    printf("%d ", root->key);
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->key);
}

void free_tree(struct Node* root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

/* Programa principal */
int main(void) {
    struct Node* root = NULL;
    char buffer[100];

    printf("Ingrese números para construir el árbol (escriba 'fin' para terminar):\n");

    while (1) {
        printf("Número: ");

        if (!fgets(buffer, sizeof(buffer), stdin))
            break;

        int value;
        if (sscanf(buffer, "%d", &value) == 1) {
            root = insert(root, value);
        } else {
            printf("Entrada no numérica detectada. Termina la inserción.\n");
            break;
        }
    }

    printf("\n--- Resultados ---\n");
    printf("Inorder (ascendente): ");
    inorder(root);
    printf("\n");

    printf("Inorder (descendente): ");
    inorder_desc(root);
    printf("\n");

    printf("Preorder: ");
    preorder(root);
    printf("\n");

    printf("Postorder: ");
    postorder(root);
    printf("\n");

    free_tree(root);
    return 0;
}
