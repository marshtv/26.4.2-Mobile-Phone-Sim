#include <iostream>
#include <string>
#include <sstream>
#include <vector>

class PhoneNumber {
	private:
		char country_char = '+';
		unsigned int country_num = 7;
		unsigned int mob_ID[3] = {0};
		unsigned int reg_num[3] = {0};
		unsigned int first_pair[2] = {0};
		unsigned int second_pair[2] = {0};
	public:
		void initPhoneNum(std::string in_str) {
			for (int i = 0; i < in_str.length(); i++) {
				if (in_str[i] < 3) {
					mob_ID[i] = (int)in_str[i] + 48;
				}
				if (in_str[i] > 2 && in_str[i] < 6) {
					reg_num[i - 3] = (int)in_str[i] + 48;
				}
				if (in_str[i] > 5 && in_str[i] < 8) {
					first_pair[i - 6] = (int)in_str[i] + 48;
				}
				if (in_str[i] > 7 && in_str[i] < 10) {
					first_pair[i - 8] = (int)in_str[i] + 48;
				}
			}
		}

		void showFullNum() {
			for (int i = 0; i < 12; i++) {
				if (i == 0)
					std::cout << country_char;
				if (i == 1)
					std::cout << country_num;
				if (i == 2)
					std::cout << "(" << mob_ID[0];
				if (i == 3)
					std::cout << mob_ID[1];
				if (i == 4)
					std::cout << mob_ID[2] << ")";
				if (i > 4 && i < 8)
					std::cout << reg_num[i - 5];
				if (i == 8)
					std::cout << "-" << first_pair[0];
				if (i == 9)
					std::cout << first_pair[1];
				if (i == 10)
					std::cout << "-" << second_pair[0];
				if (i == 11)
					std::cout << second_pair[1];
			}
		}
};

class Contact {
	private:
		std::string firstName;
		std::string lastName;
		PhoneNumber* phoneNumber = new PhoneNumber;
	public:
		void initContact(std::string& firstName_str, std::string& lastName_str, std::string& phoneNum_str) {
			firstName.resize(firstName_str.size());
			firstName = firstName_str;
			lastName.resize(lastName_str.size());
			lastName = lastName_str;
			phoneNumber->initPhoneNum(phoneNum_str);
		}
};

class MobilePhone {
	private:
		std::vector<Contact*> contactBook;
	public:
		void addContact() {
			std::cout << "Input first name:";
			std::string firstName_str;
			std::cin >> firstName_str;

			std::cout << "Input last name:";
			std::string lastName_str;
			std::cin >> lastName_str;

			std::cout << "Input 10 digits of current phone number:";
			std::string phoneNum_str;
			std::cin >> phoneNum_str;
			while (phoneNum_str.length() < 10 || phoneNum_str.length() > 10) {
				std::cout << "Incorrect quantity of digits (you need 10). Try again." << std::endl;
				std::cout << "Input 10 digits of current phone number:";
				phoneNum_str.resize(10);
				std::cin >> phoneNum_str;
			}
			Contact* contact = new Contact;
			contact->initContact(firstName_str, lastName_str, phoneNum_str);
			contactBook.push_back(contact);
			delete contact;
			contact = nullptr;
		}
};

int main() {

	return 0;
}
