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

		bool comparePhoneNumbers(std::string cmprNum_str) {
			for (int i = 0; i < 12; i++) {
				if (cmprNum_str[0] != country_char)
					return false;
				if (((int)cmprNum_str[1] + 48) != country_num)
					return false;
				if (i > 1 && i < 5) {
					if (((int) cmprNum_str[i] + 48) != mob_ID[i - 2])
						return false;
				}
				if (i > 4 && i < 8) {
					if (((int) cmprNum_str[i] + 48) != reg_num[i - 5])
						return false;
				}
				if (i > 7 && i < 10) {
					if (((int) cmprNum_str[i] + 48) != first_pair[i - 8])
						return false;
				}
				if (i > 9 && i < 12) {
					if (((int) cmprNum_str[i] + 48) != first_pair[i - 10])
						return false;
				}
			}
			return true;
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

		void showContact() {
			std::cout << firstName << " " << lastName << ": ";
			phoneNumber->showFullNum();
			std::cout << std::endl;
		}

		std::string getFirstName() {
			return firstName;
		}

		std::string getLastName() {
			return lastName;
		}

		PhoneNumber* getPhoneNumber() {
			return phoneNumber;
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

		void showContactsList() {
			if (!contactBook.empty()) {
				for (int i = 0; i < contactBook.size(); i++) {
					contactBook[i]->showContact();
				}
			} else
				std::cout << "No contacts exist :(" << std::endl;
		}

		PhoneNumber* getPhoneByName(std::string& firstName, std::string& lastName) {
			for (int i = 0; i < contactBook.size(); i++) {
				if (contactBook[i]->getFirstName() == firstName &&
					contactBook[i]->getLastName() == lastName) {
					return contactBook[i]->getPhoneNumber();
				} else
					return nullptr;
			}
		}

		PhoneNumber* getPhoneByNumStr(std::string& phone_str) {
			int count = 0;
			for (int i = 0; i < contactBook.size(); i++) {
				if (contactBook[i]->getPhoneNumber()->comparePhoneNumbers(phone_str))
					return contactBook[i]->getPhoneNumber();
				else
					return nullptr;
			}
		}

		void makeCall() {
			std::cout << "Select Call method (1 - by Name, 2 - by phone number):";
			int select;
			std::cin >> select;
			while (select < 1 || select > 2) {
				std::cout << "ERROR input (1 or 2). Try again:";
				std::cin >> select;
			}
			if (select == 1) {
				std::cout << "Input First Name and Last Name:";
				std::string f_name, l_name;
				std::cin >> f_name >> l_name;
				if (getPhoneByName(f_name, l_name) != nullptr) {
					std::cout << "CALL ";
					getPhoneByName(f_name, l_name)->showFullNum();
				} else
					std::cout << "No phone number exist with tis name :(" << std::endl;
			} else {
				std::cout << "Input Phone Number (with country code +7):";
				std::string phone_str;
				std::cin >> phone_str;
				if (getPhoneByNumStr(phone_str) != nullptr) {
					std::cout << "CALL ";
					getPhoneByNumStr(phone_str)->showFullNum();
				} else
					std::cout << "No this phone number exist :(" << std::endl;
			}
		}

	void sendSMS() {
		std::cout << "Select SMS method (1 - by Name, 2 - by phone number):";
		int select;
		std::cin >> select;
		while (select < 1 || select > 2) {
			std::cout << "ERROR input (1 or 2). Try again:";
			std::cin >> select;
		}
		if (select == 1) {
			std::cout << "Input First Name and Last Name:";
			std::string f_name, l_name;
			std::cin >> f_name >> l_name;
			if (getPhoneByName(f_name, l_name) != nullptr) {
				std::cout << "CALL ";
				getPhoneByName(f_name, l_name)->showFullNum();
			} else
				std::cout << "No phone number exist with tis name :(" << std::endl;
		} else {
			std::cout << "Input Phone Number (with country code +7):";
			std::string phone_str;
			std::cin >> phone_str;
			if (getPhoneByNumStr(phone_str) != nullptr) {
				std::cout << "CALL ";
				getPhoneByNumStr(phone_str)->showFullNum();
			} else
				std::cout << "No this phone number exist :(" << std::endl;
		}
	}
};

int main() {

	return 0;
}
