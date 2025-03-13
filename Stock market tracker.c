#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOL_LENGTH 10

// Structure for StockNode
typedef struct StockNode {
    char stock_symbol[MAX_SYMBOL_LENGTH];
    float stock_price;
    struct StockNode *left;
    struct StockNode *right;
} StockNode;

// Structure for StockMarketTree
typedef struct StockMarketTree {
    StockNode *root;
} StockMarketTree;

// Function to create a new stock node
StockNode* create_stock_node(const char *stock_symbol, float stock_price) {
    StockNode *new_node = (StockNode*)malloc(sizeof(StockNode));
    strncpy(new_node->stock_symbol, stock_symbol, MAX_SYMBOL_LENGTH);
    new_node->stock_price = stock_price;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Function to initialize the stock market tree
void init_stock_market_tree(StockMarketTree *tree) {
    tree->root = NULL;
}

// Function to insert a stock into the tree
StockNode* insert_stock(StockNode *node, const char *stock_symbol, float stock_price) {
    if (node == NULL) {
        return create_stock_node(stock_symbol, stock_price);
    }

    if (strcmp(stock_symbol, node->stock_symbol) < 0) {
        node->left = insert_stock(node->left, stock_symbol, stock_price);
    } else if (strcmp(stock_symbol, node->stock_symbol) > 0) {
        node->right = insert_stock(node->right, stock_symbol, stock_price);
    } else {
        // Update price if stock already exists
        node->stock_price = stock_price;
    }

    return node;
}

// Function to search for a stock price by its symbol
float search_stock_price(StockNode *node, const char *stock_symbol) {
    if (node == NULL) {
        return -1;  // Stock not found
    }

    if (strcmp(stock_symbol, node->stock_symbol) == 0) {
        return node->stock_price;
    } else if (strcmp(stock_symbol, node->stock_symbol) < 0) {
        return search_stock_price(node->left, stock_symbol);
    } else {
        return search_stock_price(node->right, stock_symbol);
    }
}

// Function to search and return the stock node
StockNode* search_stock_node(StockNode *node, const char *stock_symbol) {
    if (node == NULL) {
        return NULL;
    }

    if (strcmp(stock_symbol, node->stock_symbol) == 0) {
        return node;
    } else if (strcmp(stock_symbol, node->stock_symbol) < 0) {
        return search_stock_node(node->left, stock_symbol);
    } else {
        return search_stock_node(node->right, stock_symbol);
    }
}

// Function to update the stock price
void update_stock_price(StockNode *node, const char *stock_symbol, float new_price) {
    StockNode *stock_node = search_stock_node(node, stock_symbol);
    if (stock_node != NULL) {
        stock_node->stock_price = new_price;
        printf("Price of %s updated to %.2f.\n", stock_symbol, new_price);
    } else {
        printf("Stock symbol not found in the tree.\n");
    }
}

// Function for in-order traversal of the tree to display all stocks
void in_order_traversal(StockNode *node) {
    if (node != NULL) {
        in_order_traversal(node->left);
        printf("%s: %.2f\n", node->stock_symbol, node->stock_price);
        in_order_traversal(node->right);
    }
}

// Function to display menu
void display_menu() {
    printf("\nStock Market Tree Menu:\n");
    printf("1. Insert a stock\n");
    printf("2. Search for a stock\n");
    printf("3. Update the price of a stock\n");
    printf("4. Display all stocks\n");
    printf("5. Exit\n");
}

// Main function
int main() {
    StockMarketTree tree;
    init_stock_market_tree(&tree);

    int choice;
    char stock_symbol[MAX_SYMBOL_LENGTH];
    float stock_price;

    while (1) {
        display_menu();
        printf("Choose an option (1-5): ");
        scanf("%d", &choice);
        getchar();  // To consume the newline character

        switch (choice) {
            case 1:
                // Insert a stock
                printf("Enter stock symbol (e.g., AAPL): ");
                fgets(stock_symbol, MAX_SYMBOL_LENGTH, stdin);
                stock_symbol[strcspn(stock_symbol, "\n")] = 0;  // Remove the newline character

                printf("Enter price for %s: ", stock_symbol);
                scanf("%f", &stock_price);

                tree.root = insert_stock(tree.root, stock_symbol, stock_price);
                printf("Stock %s inserted with price %.2f.\n", stock_symbol, stock_price);
                break;

            case 2:
                // Search for a stock
                printf("Enter stock symbol to search (e.g., AAPL): ");
                fgets(stock_symbol, MAX_SYMBOL_LENGTH, stdin);
                stock_symbol[strcspn(stock_symbol, "\n")] = 0;  // Remove the newline character

                stock_price = search_stock_price(tree.root, stock_symbol);
                if (stock_price != -1) {
                    printf("Price of %s: %.2f\n", stock_symbol, stock_price);
                } else {
                    printf("Stock symbol %s not found.\n", stock_symbol);
                }
                break;

            case 3:
                // Update stock price
                printf("Enter stock symbol to update price (e.g., AAPL): ");
                fgets(stock_symbol, MAX_SYMBOL_LENGTH, stdin);
                stock_symbol[strcspn(stock_symbol, "\n")] = 0;  // Remove the newline character

                printf("Enter new price for %s: ", stock_symbol);
                scanf("%f", &stock_price);

                update_stock_price(tree.root, stock_symbol, stock_price);
                break;

            case 4:
                // Display all stocks
                printf("\nAll stocks:\n");
                in_order_traversal(tree.root);
                break;

            case 5:
                printf("Exiting the program.\n");
                exit(0);

            default:
                printf("Invalid choice, please select a number between 1 and 5.\n");
        }
    }

    return 0;
}
