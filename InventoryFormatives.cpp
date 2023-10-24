#include <iostream>
#include <vector>
#include <string>

class Item {
public:
    Item(const std::string& name) : name(name) {}
    virtual void use() const = 0;
    virtual std::string getDescription() const = 0;

    const std::string& getName() const {
        return name;
    }

protected:
    std::string name;
};

class HealthPotion : public Item {
public:
    HealthPotion(const std::string& name) : Item(name) {}

    void use() const override {
        std::cout << "Vous avez gagné +15 en heal en utilisant la potion de soins." << std::endl;
    }

    std::string getDescription() const override {
        return "Potion de Soins: " + name;
    }
};

class StrengthPotion : public Item {
public:
    StrengthPotion(const std::string& name) : Item(name) {}

    void use() const override {
        std::cout << "Vous avez gagné +150000 en force en utilisant la potion de force." << std::endl;
    }

    std::string getDescription() const override {
        return "Potion de Force: " + name;
    }
};

class Weapon : public Item {
public:
    Weapon(const std::string& name) : Item(name) {}

    void use() const override {
        if (name == "Arc") {
            std::cout << "L'arc fait 'phew' quand il est utilisé." << std::endl;
        }
        else if (name == "Épée") {
            std::cout << "L'épée fait 'swoosh' quand elle est utilisée." << std::endl;
        }
    }

    std::string getDescription() const override {
        return "Arme: " + name;
    }
};

class Map : public Item {
public:
    Map(const std::string& name) : Item(name) {}

    void use() const override {
        std::cout << "La carte dit : 'Vous êtes ici' quand elle est utilisée." << std::endl;
    }

    std::string getDescription() const override {
        return "Carte: " + name;
    }
};

class Inventory {
public:
    void addItem(Item* item) {
        items.push_back(item);
    }

    void listItems() const {
        for (size_t i = 0; i < items.size(); ++i) {
            std::cout << i + 1 << ". " << items[i]->getDescription() << std::endl;
        }
    }

    void useItem(int index) {
        if (index >= 0 && index < items.size()) {
            items[index]->use();
        }
        else {
            std::cout << "Index d'objet invalide." << std::endl;
        }
    }

private:
    std::vector<Item*> items;
};

int main() {
    Inventory inventory;
    int choice;

    do {
        std::cout << "1. Ajouter un objet à l'inventaire" << std::endl;
        std::cout << "2. Ouvrir et afficher l'inventaire" << std::endl;
        std::cout << "3. Utiliser un objet de l'inventaire" << std::endl;
        std::cout << "4. Quitter" << std::endl;
        std::cout << "Faites votre choix : ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::cout << "Choisissez le type d'objet à ajouter : " << std::endl;
            std::cout << "1. Potion de Soins" << std::endl;
            std::cout << "2. Potion de Force" << std::endl;
            std::cout << "3. Arc" << std::endl;
            std::cout << "4. Épée" << std::endl;
            std::cout << "5. Carte" << std::endl;
            int itemType;
            std::cin >> itemType;

            std::string itemName;
            std::cout << "Nom de l'objet : ";
            std::cin >> itemName;

            Item* item = nullptr;
            switch (itemType) {
            case 1:
                item = new HealthPotion(itemName);
                break;
            case 2:
                item = new StrengthPotion(itemName);
                break;
            case 3:
                item = new Weapon("Arc");
                break;
            case 4:
                item = new Weapon("Épée");
                break;
            case 5:
                item = new Map(itemName);
                break;
            default:
                std::cout << "Type d'objet invalide." << std::endl;
            }

            if (item != nullptr) {
                inventory.addItem(item);
                std::cout << "Objet ajouté à l'inventaire." << std::endl;
            }

            break;
        }
        case 2:
            inventory.listItems();
            break;
        case 3:
            int index;
            std::cout << "Indice de l'objet à utiliser : ";
            std::cin >> index;
            inventory.useItem(index - 1);
            break;
        case 4:
            std::cout << "Au revoir !" << std::endl;
            break;
        default:
            std::cout << "Choix invalide." << std::endl;
            return 404;
        }
    } while (choice != 4);

    return 0;
}

