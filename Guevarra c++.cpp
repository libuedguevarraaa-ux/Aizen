#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib> // rand()
#include <ctime>   // time()
#include <vector>

struct Item
{
    int id;
    std::string name;
    double price;
    int stock;
};

int main()
{
    std::srand(std::time(0)); 

    std::vector<Item> catalog;
    std::vector<int> cart;

    
    catalog.push_back({1, "Burger", 5.99, 10 + std::rand() % 11});
    catalog.push_back({2, "Fries", 2.49, 10 + std::rand() % 11});
    catalog.push_back({3, "Soda", 1.50, 10 + std::rand() % 11});
    catalog.push_back({4, "Pizza", 8.99, 10 + std::rand()% 11});
    catalog.push_back({5, "Ice Scream", .99, 10 + std::rand()% 11});
    catalog.push_back({6, "Fried Chicken", 9.99, 10 + std::rand()% 11});
    cart.resize(catalog.size(), 0);

    int choice = 0;

    while (true)
    {
        // --- Menu ---
        std::cout << "\n=== Ordering Menu ===\n";
        for (size_t i = 0; i < catalog.size(); i++)
        {
            std::cout << catalog[i].id << ". " << catalog[i].name
                      << " - $" << std::fixed << std::setprecision(2)
                      << catalog[i].price;
            if (catalog[i].stock > 0)
                std::cout << " (Stock: " << catalog[i].stock << ")";
            else
                std::cout << " (Out of stock)";
            std::cout << "\n";
        }
        std::cout << catalog.size() + 1 << ". View Cart\n";
        std::cout << catalog.size() + 2 << ". Checkout & Exit\n";
        std::cout << catalog.size() + 3 << ". Add New Item\n";

        std::cout << "\nEnter your choice: ";
        std::cin >> choice;

        // --- View Cart ---
        if (choice == static_cast<int>(catalog.size()) + 1)
        {
            std::cout << "\n--- Your Cart ---\n";
            bool empty = true;
            for (size_t i = 0; i < catalog.size(); i++)
            {
                if (cart[i] > 0)
                {
                    std::cout << catalog[i].name << " x " << cart[i]
                              << " = $" << catalog[i].price * cart[i] << "\n";
                    empty = false;
                }
            }
            if (empty)
                std::cout << "\nCart is empty.\n";
        }
        // --- Checkout ---
        else if (choice == static_cast<int>(catalog.size()) + 2)
        {
            std::cout << "\n=== Checkout ===\n";
            double total = 0;
            for (size_t i = 0; i < catalog.size(); i++)
            {
                if (cart[i] > 0)
                {
                    double subtotal = catalog[i].price * cart[i];
                    std::cout << catalog[i].name << " x " << cart[i]
                              << " = $" << subtotal << "\n";
                    total += subtotal;
                }
            }
            std::cout << "Total: $" << total << "\n";
            std::cout << "Thank you for your order!\n";
            break;
        }
        // --- Add New Item ---
        else if (choice == static_cast<int>(catalog.size()) + 3)
        {
            Item newItem;
            newItem.id = catalog.size() + 1;
            std::cout << "Enter name of new item: ";
            std::cin.ignore();
            std::getline(std::cin, newItem.name);
            std::cout << "Enter price: ";
            std::cin >> newItem.price;
            std::cout << "Enter stock quantity: ";
            std::cin >> newItem.stock;

            catalog.push_back(newItem);
            cart.push_back(0); // add corresponding cart entry
            std::cout << "\nNew item added!\n";
        }
        // --- Item selection ---
        else if (choice >= 1 && choice <= static_cast<int>(catalog.size()))
        {
            size_t idx = choice - 1;

            if (catalog[idx].stock == 0)
            {
                std::cout << "\nSorry, " << catalog[idx].name << " is out of stock.\n";
                continue;
            }

            while (true)
            {
                std::cout << "\nEnter quantity for " << catalog[idx].name
                          << " (max " << catalog[idx].stock << ", 0 to go back): ";
                int qty;
                std::cin >> qty;

                if (qty == 0)
                {
                    std::cout << "\nReturning to menu...\n";
                    break;
                }
                else if (qty > 0 && qty <= catalog[idx].stock)
                {
                    cart[idx] += qty;
                    catalog[idx].stock -= qty;
                    std::cout << "\n"
                              << qty << " x " << catalog[idx].name << " added to cart.\n";
                    break;
                }
                else
                {
                    std::cout << "\nSorry not enough stock.\n";
                }
            }
        }
        // --- Invalid choice ---
        else
        {
            std::cout << "\nInvalid choice. Try again.\n";
        }
    }

    std::cout << "\nPress Enter to exit...";
    std::cin.ignore();
    std::cin.get();
    return 0;
}
