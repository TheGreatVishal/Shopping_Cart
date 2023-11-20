// Shopping Cart Project Version 2.0
// Feature to add items in cart of users
#include <stdio.h>
#include <stdlib.h>

struct items
{
    int id;
    int quantity;
    int amount;
    struct items *next;
};

struct users
{
    int id;
    char *name;
    int bill;
    struct items *cart;
    struct users *next;
};

struct products
{
    int id;
    char *P_name;
    int price;
    struct products *next;
};

typedef struct users user;
typedef struct products product;
typedef struct items item;

user *add_user(user *head, int id, char *name, int bill)
{
    user *temp = (user *)malloc(sizeof(user));
    user *ptr = head;

    temp->id = id;
    temp->name = name;
    temp->cart = NULL;
    temp->bill = bill;
    temp->next = NULL;

    if (head == NULL)
    {
        head = temp;
    }
    else
    {
        while (1)
        {
            if (ptr->next == NULL)
            {
                ptr->next = temp;
                break;
            }
            ptr = ptr->next;
        }
    }
    return head;
}

void display_user(user *head, int k)
{
    user *ptr = head;
    if (k == 0)
        printf("\nList of Users :\n");
    else
        printf("User Status :\n");
    while (ptr != NULL)
    {
        printf("User ID : %d | User Name : %s | User Bill : Rs %d\n", ptr->id, ptr->name, ptr->bill);
        ptr = ptr->next;
    }
}

product *add_Product(product *head, int id, char *name, int price)
{
    product *temp = (product *)malloc(sizeof(product));
    product *ptr = head;
    temp->id = id;
    temp->P_name = name;
    temp->price = price;
    temp->next = NULL;
    if (head == NULL)
        head = temp;
    else
    {
        while (1)
        {
            if (ptr->next == NULL)
                break;
            ptr = ptr->next;
        }
        ptr->next = temp;
    }
    return head;
}

void display_product(product *head)
{
    product *ptr = head;
    printf("List of Products :\n");
    while (ptr != NULL)
    {
        printf("Product ID : %d | Product Name : %s | Price : Rs %d\n", ptr->id, ptr->P_name, ptr->price);
        ptr = ptr->next;
    }
}

item *add_item(item *head, int id, int quantity, int amount)
{
    item *temp = (item *)malloc(sizeof(item));
    item *ptr = head;
    temp->id = id;
    temp->quantity = quantity;
    temp->amount = amount;
    temp->next = NULL;
    if (head == NULL)
        head = temp;
    else
    {
        while (1)
        {
            if (ptr->next == NULL)
                break;
            ptr = ptr->next;
        }
        ptr->next = temp;
    }
    return head;
}

void display_item(item *head)
{
    item *ptr = head;
    printf("Items added to cart :\n");
    while (ptr != NULL)
    {
        printf("Product ID : %d | Quantity : %d | Amount : Rs %d\n", ptr->id, ptr->quantity, ptr->amount);
        ptr = ptr->next;
    }
}

item *fetch_cart(user *head, int userId)
{
    user *ptr = head;
    while (1)
    {
        if (ptr->id == userId)
        {
            return ptr->cart;
        }
        ptr = ptr->next;
    }
}

int fetchPrice(product *head, int product_id)
{
    product *ptr = head;
    while (1)
    {
        if (ptr->id == product_id)
        {
            int x = ptr->price;
            return x;
        }
        ptr = ptr->next;
    }
}

user *fetching_current_user(user *head, int userId)
{
    user *ptr = head;

    while (1)
    {
        if (ptr->id == userId)
            return ptr;
        ptr = ptr->next;
    }
}

int update_bill(user *head, int userId, int product_bill)
{
    user *ptr = head;
    while (1)
    {
        if (ptr->id == userId)
        {
            ptr->bill += product_bill;
            int x = ptr->bill;
            return x;
        }
        ptr = ptr->next;
    }
}

void dotted_lines()
{
    for (int i = 1; i <= 68; i++)
    {
        printf("-");
    }
    printf("\n");
}

void main()
{
    user *user = NULL;
    product *product = NULL;
    item *item = NULL;
    int userId, productId, quantity, total_bill = 0;
    int *t_bill;
    t_bill = &total_bill;
    char wish;

    // Adding users (Hardcore)
    user = add_user(user, 1, "Vishal", 0);
    user = add_user(user, 2, "Amogh", 0);
    user = add_user(user, 3, "Mohit", 0);
    user = add_user(user, 4, "Random", 0);
    user = add_user(user, 5, "Jeetu", 0);

    // Adding Products (Hardcore)
    product = add_Product(product, 1, "LCD", 40000);
    product = add_Product(product, 2, "Air Conditioner", 60000);
    product = add_Product(product, 3, "Laptop", 90000);
    product = add_Product(product, 4, "Washing Machine", 25000);
    product = add_Product(product, 5, "Refrigerator", 60000);
    product = add_Product(product, 6, "Pizza", 60);

label:
    dotted_lines();
    display_user(user, 0);

    printf("\nPlease Enter User ID : ");
    scanf("%d", &userId);
    item = fetch_cart(user, userId);
    // Adding Products to cart process
    while (1)
    {
        dotted_lines();
        display_product(product);
        printf("\nPlease enter the Product ID to add to cart : ");
        scanf("%d", &productId);
        printf("Please enter the Quantity of Product ID %d : ", productId);
        scanf("%d", &quantity);
        printf("Item Successfully added to cart!");

        // fetching price of particular Product ID
        int rs = fetchPrice(product, productId);
        int product_bill = rs * quantity;

        // Updating the bill of user
        total_bill = update_bill(user, userId, product_bill);

        item = add_item(item, productId, quantity, product_bill);

        // Asking if they want to purchase more
        printf("\nDo you want to add more items (y/n) : ");
        scanf(" %c", &wish);
        if (wish == 'y')
            continue;
        else
        {
            // to send item into current user's cart
            fetching_current_user(user, userId)->cart = item;
            break;
        }
    }
    dotted_lines();
    display_item(item);
    printf("\n");
    display_user(user, 1);
    printf("\nTotal bill generated for current User ID  -> %d is : Rs %d\n", userId, total_bill);
    char wish2;
    dotted_lines();
    printf("\nNext User (y/n): ");
    scanf(" %c", &wish2);
    if (wish2 == 'n')
        goto end;
    goto label;

    dotted_lines();
end:
    printf("Thank You for Shoping!\n");
    dotted_lines();
}