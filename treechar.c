#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;                // Valor almacenado en el nodo (usamos int, pero guarda el código ASCII)
    struct Node *left;      // Puntero al hijo izquierdo
    struct Node *right;     // Puntero al hijo derecho
};

// Crear un nuevo nodo con una clave dada
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

/* Insertar una clave en el BST */
struct Node* insert(struct Node* root, int key) {
    if (root == NULL) {
        return create_node(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else {
        root->right = insert(root->right, key);
    }

    return root;
}

/* Buscar una clave en el BST */
struct Node* search(struct Node* root, int key) {
    if (root == NULL) return NULL;
    if (key == root->key) return root;
    if (key < root->key) return search(root->left, key);
    return search(root->right, key);
}

/* Recorridos del árbol */
void inorder(struct Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%c ", root->key);   // Mostrar como carácter
    inorder(root->right);
}

void preorder(struct Node* root) {
    if (root == NULL) return;
    printf("%c ", root->key);
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%c ", root->key);
}

/* Liberar memoria */
void free_tree(struct Node* root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

void inorder_desc(struct Node* root) {
    if (root == NULL) return;
    inorder_desc(root->right);   // primero los mayores
    printf("%d ", root->key);    // luego la raíz
    inorder_desc(root->left);    // finalmente los menores
}


/* Función main */
int main(void) {
    struct Node* root = NULL;

    // Insertar letras A–I (entre comillas simples)
    int keys[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
    size_t n = sizeof(keys) / sizeof(keys[0]);

    for (size_t i = 0; i < n; ++i) {
        root = insert(root, keys[i]);
    }

    // Mostrar recorridos
    printf("Inorder (orden ascendente): ");
    inorder(root);
    printf("\n");

    printf("Preorder: ");
    preorder(root);
    printf("\n");

    printf("Postorder: ");
    postorder(root);
    printf("\n");

    printf("Inorder (orden descendente): ");
    inorder_desc(root);
    printf("\n");


    // Buscar letras
    int to_find1 = 'F';
    int to_find2 = 'Z';

    struct Node* found1 = search(root, to_find1);
    if (found1 != NULL) {
        printf("Clave %c encontrada en el árbol.\n", to_find1);
    } else {
        printf("Clave %c NO encontrada en el árbol.\n", to_find1);
    }

    struct Node* found2 = search(root, to_find2);
    if (found2 != NULL) {
        printf("Clave %c encontrada en el árbol.\n", to_find2);
    } else {
        printf("Clave %c NO encontrada en el árbol.\n", to_find2);
    }

    // Liberar memoria
    free_tree(root);
    root = NULL;

    return 0;
}
