#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <exception>

std::string ft_down(const std::string& input) 
{
    std::string tmp;
	
	tmp = input;
    for (char& c : tmp) 
        if (c >= 'A' && c <= 'Z')
            c += 0x20;
    return tmp;
}
class Contact 
{
public:
    std::string name;
    std::string phone_number;
    std::string nickname;
    bool bookmarked;

    Contact(std::string name, std::string phone_number, std::string nickname) 
        : name(name), phone_number(phone_number), nickname(nickname), bookmarked(false) {}

    void display() const {
        std::cout << "Name: " << name << ", Phone Number: " << phone_number 
                  << ", Nickname: " << nickname << ", Bookmarked: " << (bookmarked ? "Yes" : "No") << std::endl;
    }
};

class Phonebook 
{
private:
    std::vector<Contact> contacts;

public:
    void add_contact(const std::string& name, const std::string& phone_number, const std::string& nickname) 
	{
        for (const auto& contact : contacts) {
            if (contact.phone_number == phone_number) 
			{
                std::cout << "Error: Phone number already exists." << std::endl;
                return;
            }
        }
        contacts.emplace_back(name, phone_number, nickname);
        std::cout << "Contact added successfully." << std::endl;
    }

    void search_contacts() 
	{
		size_t i;
		size_t index;
		int j;
		std::string tmp;

        if (contacts.empty()) 
		{
            std::cout << "No contacts found." << std::endl;
            return;
        }

        for (i = 0; i < contacts.size(); ++i)
            std::cout << i << ": " << contacts[i].name << std::endl;

        std::cout << "Enter the index of the contact to view details: ";

        std::cin >> tmp;
        /*
		for (j=0; j <= tmp.length(); j++)
			if ((tmp[j] >= '1') && (tmp[j] <= '9'))
			{}
			else
			{
				std::cout << "Enter the index right " << std::endl;
				return;
			}
            */
           try {index = stoi(tmp);}
            catch()
                {
                    std::cerr << "error: "  << '\n';
                }
		        
        if (index < contacts.size()) 
		{
            contacts[index].display();
            std::cout << "Do you want to bookmark this contact? (yes/no): ";
            std::string bookmark;
            std::cin >> bookmark;
			bookmark = ft_down(bookmark);
            if ((bookmark == "yes") || (bookmark == "y")) 
			{
                contacts[index].bookmarked = true;
                std::cout << "Contact bookmarked." << std::endl;
            }
        } else 
            std::cout << "Invalid index." << std::endl;
    }

    void remove_contact() 
	{
        std::cout << "Remove by index or phone number? (index/phone): ";
        std::string method;
        std::cin >> method;
		size_t index;

		method = ft_down(method);

        if (method == "index") 
		{
            std::cout << "Enter the index of the contact to remove: ";
            std::cin >> index;
            if (index < contacts.size()) 
			{
                contacts.erase(contacts.begin() + index);
                std::cout << "Contact removed successfully." << std::endl;
            } else
                std::cout << "Invalid index." << std::endl;
        } 
		else if (method == "phone") 
		{
            std::cout << "Enter the phone number of the contact to remove: ";
            std::string phone_number;
            std::cin >> phone_number;
            auto it = std::remove_if(contacts.begin(), contacts.end(), [&](const Contact& contact) 
			{
                return contact.phone_number == phone_number;
            });
            if (it != contacts.end()) {
                contacts.erase(it, contacts.end());
                std::cout << "Contact removed successfully." << std::endl;
            } else {
                std::cout << "No contact found with the provided phone number." << std::endl;
            }
        } else
            std::cout << "Invalid method." << std::endl;
    }

    void list_bookmarked_contacts() const {
        bool found = false;
        for (const auto& contact : contacts) {
            if (contact.bookmarked) {
                contact.display();
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

	phonebook.add_contact("name1", "1111", "n1");
	phonebook.add_contact("name2", "2222", "n2");
	phonebook.add_contact("name3", "3333", "n3");

    while (true) 
	{
         
        std::cout << "Enter command (ADD, SEARCH, REMOVE, BOOKMARK, EXIT): ";
    
        std::cin >> command;
		command = ft_down(command);


        if (command == "add") 
		{
            std::string name, phone_number, nickname;
            std::cout << "Enter name: ";
            std::cin.ignore(); // ignore newline character left in the input buffer
            std::getline(std::cin, name);
            std::cout << "Enter phone number: ";
            std::getline(std::cin, phone_number);
            std::cout << "Enter nickname: ";
            std::getline(std::cin, nickname);
            phonebook.add_contact(name, phone_number, nickname);
        } 
		else if (command == "search") 
		{
            phonebook.search_contacts();
        } 
		else if (command == "remove") 
		{
            phonebook.remove_contact();
        } 
		else if (command == "bookmark") 
		{
            phonebook.list_bookmarked_contacts();
        } 
		else if (command == "exit") 
		{
            return(0);
        } 
		else 
		{
            std::cout << "Invalid command." << std::endl;
        }
    }

    return 0;
}
