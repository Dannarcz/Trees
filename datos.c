#include <stdio.h>
#include <stdlib.h>

/* Estructura del nodo */
struct Node {
    int key;
    struct Node *left;
    struct Node *right;
};

/* Crear un nuevo nodo */
struct Node* create_node(int key) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    if (node == NULL) {
        fprintf(stderr, "Error: memoria insuficiente\n");
        exit(EXIT_FAILURE);
    }
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/* Insertar en el árbol */
struct Node* insert(struct Node* root, int key) {
    if (root == NULL)
        return create_node(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);

    return root;
}

/* Buscar un valor */
struct Node* search(struct Node* root, int key) {
    if (root == NULL) return NULL;
    if (key == root->key) return root;
    if (key < root->key)
        return search(root->left, key);
    else
        return search(root->right, key);
}

/* Recorridos */
void inorder(struct Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

void preorder(struct Node* root) {
    if (root == NULL) return;
    printf("%d ", root->key);
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->key);
}

void inorder_desc(struct Node* root) {
    if (root == NULL) return;
    inorder_desc(root->right);
    printf("%d ", root->key);
    inorder_desc(root->left);
}

/* Liberar memoria */
void free_tree(struct Node* root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

/* MAIN */
int main(void) {
    struct Node* root = NULL;
    int n, valor;

    printf("¿Cuántos valores deseas insertar en el árbol?: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Ingresa el valor #%d: ", i + 1);
        scanf("%d", &valor);
        root = insert(root, valor);
    }

    printf("\nRecorridos del árbol:\n");
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

    // Búsqueda
    int buscar;
    printf("\nIngresa un valor a buscar en el árbol: ");
    scanf("%d", &buscar);
    struct Node* encontrado = search(root, buscar);
    if (encontrado)
        printf("La clave %d SÍ está en el árbol.\n", buscar);
    else
        printf("La clave %d NO está en el árbol.\n", buscar);

    free_tree(root);
    return 0;
}
