#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>

std::string ft_down(const std::string& input) {
    std::string tmp = input;
    for (char& c : tmp) {
        if (c >= 'A' && c <= 'Z') {
            c += 0x20;
        }
    }
    return tmp;
}

class Contact {
public:
    std::string name;
    std::string phone_number;
    std::string nickname;
    bool bookmarked;
    size_t index;

    Contact(const std::string& name, const std::string& phone_number, const std::string& nickname, size_t idx)
        : name(name), phone_number(phone_number), nickname(nickname), bookmarked(false), index(idx) {}

    void display() const {
        std::cout << "Index: " << index << ", Name: " << name << ", Phone Number: " << phone_number
                  << ", Nickname: " << nickname << ", Bookmarked: " << (bookmarked ? "Yes" : "No") << std::endl;
    }
};

class Phonebook {
private:
    std::vector<std::unique_ptr<Contact>> contacts;

    void update_indices() {
        for (size_t i = 0; i < contacts.size(); ++i) {
            contacts[i]->index = i + 1;
        }
    }

public:
    void add_contact(const std::string& name, const std::string& phone_number, const std::string& nickname) {
        size_t idx = contacts.size() + 1;
        contacts.emplace_back(std::make_unique<Contact>(name, phone_number, nickname, idx));
        std::cout << "Contact added successfully with index " << idx << std::endl;
    }

    void search_contacts() {
        if (contacts.empty()) {
            std::cout << "No contacts found." << std::endl;
            return;
        }

        for (const auto& contact : contacts) {
            contact->display();
        }

        std::cout << "Enter the index of the contact to view details: ";
        std::string input;
        std::cin >> input;
		if ((input[0] > 126) || (input[0] < 0x20))
            {
                std::cout << "fatal invalid command" << std::endl;
                return;
            }
        try {
            size_t idx = std::stoi(input);
            if (idx > 0 && idx <= contacts.size()) {
                Contact& selected_contact = *contacts[idx - 1];
                selected_contact.display();
                std::cout << "Do you want to bookmark this contact? (yes/no): ";
                std::string bookmark;
                std::cin >> bookmark;
                bookmark = ft_down(bookmark);
                if (bookmark == "yes" || bookmark == "y") {
                    selected_contact.bookmarked = true;
                    std::cout << "Contact bookmarked." << std::endl;
                }
            } else {
                std::cout << "Invalid index." << std::endl;
            }
        } catch (const std::invalid_argument&) {
            std::cout << "Invalid input. Please enter a valid index." << std::endl;
        } catch (const std::out_of_range&) {
            std::cout << "Index out of range. Please enter a valid index." << std::endl;
        }
    }

    void remove_contact() {
        std::cout << "Remove by index or phone number? (index/phone): ";
        std::string method;
        std::cin >> method;
		if ((method[0] > 126) || (method[0] < 0x20))
            {
                std::cout << "fatal invalid command" << std::endl;
                return;
            }
        method = ft_down(method);

        if (method == "index") {
            std::cout << "Enter the index of the contact to remove: ";
            std::string input;
            std::cin >> input;
            try {
                size_t idx = std::stoi(input);
                if (idx > 0 && idx <= contacts.size()) {
                    contacts.erase(contacts.begin() + (idx - 1));
                    update_indices();
                    std::cout << "Contact removed successfully." << std::endl;
                } else {
                    std::cout << "Invalid index." << std::endl;
                }
            } catch (const std::invalid_argument&) {
                std::cout << "Invalid input. Please enter a valid index." << std::endl;
            } catch (const std::out_of_range&) {
                std::cout << "Index out of range. Please enter a valid index." << std::endl;
            }
        } else if (method == "phone") {
            std::cout << "Enter the phone number of the contact to remove: ";
            std::string phone_number;
            std::cin >> phone_number;
			if ((phone_number[0] > 126) || (phone_number[0] < 0x20))
            {
                std::cout << "fatal invalid command" << std::endl;
                return;
            }

            auto it = std::find_if(contacts.begin(), contacts.end(),
                                   [&](const std::unique_ptr<Contact>& contact) {
                                       return contact->phone_number == phone_number;
                                   });

            if (it != contacts.end()) {
                contacts.erase(it);
                update_indices();
                std::cout << "Contact removed successfully." << std::endl;
            } else {
                std::cout << "No contact found with the provided phone number." << std::endl;
            }
        } else {
            std::cout << "Invalid method." << std::endl;
        }
    }

    void list_bookmarked_contacts() const {
        bool found = false;
        for (const auto& contact : contacts) {
            if (contact->bookmarked) {
                contact->display();
                found = true;
            }
        }
        if (!found) {
            std::cout << "No bookmarked contacts found." << std::endl;
        }
    }
};

int main() {
    Phonebook phonebook;
    std::string command;

	phonebook.add_contact("name1", "1111", "1");
	phonebook.add_contact("name2", "2222", "2");
	phonebook.add_contact("name3", "3333", "3");
	phonebook.add_contact("name4", "4444", "4");
	phonebook.add_contact("", "5555", "");

    while (true) {
        std::cout << "Enter command (add, search, remove, bookmark, exit): ";
        std::cin >> command;
		if ((command[0] > 126) || (command[0] < 0x20))
            {
                std::cout << "fatal invalid command" << std::endl;
                return (0);
            }
        command = ft_down(command);

        if (command == "add") {
            std::string name, phone_number, nickname;
            std::cout << "Enter name: ";
            std::cin.ignore(); // ignore newline character left in the input buffer
            std::getline(std::cin, name);
            std::cout << "Enter phone number: ";
            std::getline(std::cin, phone_number);
            std::cout << "Enter nickname: ";
            std::getline(std::cin, nickname);
            phonebook.add_contact(name, phone_number, nickname);
        } else if (command == "search") {
            phonebook.search_contacts();
			command = "";
        } else if (command == "remove") {
            phonebook.remove_contact();
			command = "";
        } else if (command == "bookmark") {
            phonebook.list_bookmarked_contacts();
			command = "";
        } else if (command == "exit") {
            break;
        } else {
            std::cout << '\n' << "Invalid command." << std::endl;
			
			if ((command[0] > 126) || (command[0] < 0x20))
			{
					std::cout << "fatal invalid command" << std::endl;
			 		return (0);
			}
			else 
				command = "";
        }
    }

    return 0;
}
