#include <iostream>
#include <string>
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
		void initPhoneNum(std::string& in_str) {
			for (int i = 0; i < in_str.size(); i++) {
				if (i < 3)
					mob_ID[i] = (int)in_str[i] - 48;
				if (i > 2 && i < 6)
					reg_num[i - 3] = (int)in_str[i] - 48;
				if (i > 5 && i < 8)
					first_pair[i - 6] = (int)in_str[i] - 48;
				if (i > 7)
					second_pair[i - 8] = (int)in_str[i] - 48;
			}
		}

		bool comparePhoneNumbers(std::string& compareNum_str) {
			for (int i = 0; i < 12; i++) {
				if (compareNum_str[0] != country_char || (int)compareNum_str[1] - 48 != country_num)
					return false;
				else if (i > 1 && i < 5) {
					if (((int) compareNum_str[i] - 48) != mob_ID[i - 2])
						return false;
				} else if (i > 4 && i < 8) {
					if (((int) compareNum_str[i] - 48) != reg_num[i - 5])
						return false;
				} else if (i > 7 && i < 10) {
					if (((int) compareNum_str[i] - 48) != first_pair[i - 8])
						return false;
				} else if (i > 9) {
					if (((int) compareNum_str[i] - 48) != second_pair[i - 10])
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
		PhoneNumber* phoneNumber;
	public:
		void initContact(std::string& firstName_str, std::string& lastName_str, std::string phoneNum_str) {
			firstName.resize(firstName_str.size());
			firstName = firstName_str;
			lastName.resize(lastName_str.size());
			lastName = lastName_str;
			phoneNumber = new PhoneNumber;
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
			std::cout << "Input first name and last name:";
			std::string firstName_str, lastName_str;
			std::cin >> firstName_str >> lastName_str;

			std::cout << "Input last 10 digits of phone number:";
			std::string phoneNum_str;
			std::cin >> phoneNum_str;
			while (phoneNum_str.size() < 10 || phoneNum_str.size() > 10) {
				std::cout << "Incorrect quantity of digits (you need last 10). Try again." << std::endl;
				std::cout << "Input 10 digits of current phone number:";
				phoneNum_str.resize(10);
				std::cin >> phoneNum_str;
			}
			auto* contact = new Contact;
			contact->initContact(firstName_str, lastName_str, phoneNum_str);
			contactBook.push_back(contact);
		}

		void showContactsList() {
			if (!contactBook.empty()) {
				for (int i = 0; i < contactBook.size(); i++) {
					std::cout << i << ") ";
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
				}
			}
			return nullptr;
		}

		PhoneNumber* getPhoneByNumStr(std::string& phone_str) {
			for (int i = 0; i < contactBook.size(); i++) {
				if (contactBook[i]->getPhoneNumber()->comparePhoneNumbers(phone_str))
					return contactBook[i]->getPhoneNumber();
			}
			return nullptr;
		}

		PhoneNumber* getPhoneBySelectMethod() {
			std::cout << "Select search method (1 - by Name, 2 - by phone number):";
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
				return getPhoneByName(f_name, l_name);
			} else {
				std::cout << "Input Phone Number (with country code +7):";
				std::string phone_str;
				std::cin >> phone_str;
				return getPhoneByNumStr(phone_str);
			}
		}

		void call() {
			auto* phoneNumCall = new PhoneNumber;
			phoneNumCall = getPhoneBySelectMethod();
			std::cout << "-----------------------------" << std::endl;
			if (phoneNumCall != nullptr) {
				std::cout << "CALL ";
				phoneNumCall->showFullNum();
				std::cout << std::endl;
			} else
				std::cout << "No phone number exist with tis name :(" << std::endl;
		}

		void sms() {
			auto* phoneNumSms = new PhoneNumber;
			phoneNumSms = getPhoneBySelectMethod();
			std::cout << "-----------------------------" << std::endl;
			if (phoneNumSms != nullptr) {
				phoneNumSms->showFullNum();
				std::cout << std::endl;
				std::cout << "Message:" << std::endl;
				std::string sms_str;
				std::getline(std::cin >> std::ws, sms_str);
				std::cout << "Sent" << std::endl;
			} else
				std::cout << "No phone number exist with tis name :(" << std::endl;
		}
};

std::string checkCommandAddEnd() {
	std::cout << "Input command:";
	std::string in_comm_str;
	std::cin >> in_comm_str;
	while (in_comm_str != "add" && in_comm_str != "end") {
		std::cout << "ERROR input. Try again." << std::endl;
		std::cout << "Input command:";
		std::cin >> in_comm_str;
	}
	return in_comm_str;
}

std::string checkCommandCallSmsExit() {
	std::cout << "Input command:";
	std::string in_comm_str;
	std::cin >> in_comm_str;
	while (in_comm_str != "call" && in_comm_str != "sms" && in_comm_str != "exit") {
		std::cout << "ERROR input. Try again." << std::endl;
		std::cout << "Input command:";
		std::cin >> in_comm_str;
	}
	return in_comm_str;
}

int main() {
	auto* mobilePhone = new MobilePhone;
	std::cout << "--------------------------------------" << std::endl;
	std::cout << "Welcome to mobile phone!" << std::endl;
	std::cout << "--------------------------------------" << std::endl;
	std::cout << "Lets add a contacts to Contact's Book!" << std::endl;
	std::cout << "You have 2 commands:" << std::endl;
	std::cout << '"' << "add" << '"' << " - for add contact," << std::endl;
	std::cout << '"' << "end" << '"' << " - for end adding contacts." << std::endl;
	std::cout << "--------------------------------------" << std::endl;
	std::string command = checkCommandAddEnd();
	while (command != "end") {
		std::cout << "--------------------------------------" << std::endl;
		mobilePhone->addContact();

		std::cout << "--------------------------------------" << std::endl;
		command = checkCommandAddEnd();
	}
	std::cout << "----------------------" << std::endl;
	std::cout << "Contact Book List:" << std::endl;
	std::cout << "--------------------------------------" << std::endl;

	mobilePhone->showContactsList();

	std::cout << "--------------------------------------" << std::endl;
	std::cout << "You have 3 commands:" << std::endl;
	std::cout << '"' << "call" << '"' << " - for call by phone," << std::endl;
	std::cout << '"' << "sms" << '"' << " - for send sms message," << std::endl;
	std::cout << '"' << "exit" << '"' << " - for exit program." << std::endl;
	std::cout << "-----------------------------" << std::endl;
	command = checkCommandCallSmsExit();
	while (command != "exit") {
		std::cout << "-----------------------------" << std::endl;
		if (command == "call")
			mobilePhone->call();
		if (command == "sms")
			mobilePhone->sms();
		std::cout << "-----------------------------" << std::endl;
		command = checkCommandCallSmsExit();
	}

	std::cout << "-----------------------------" << std::endl;
	std::cout << "Good by!!!" << std::endl;

	delete mobilePhone;
	mobilePhone = nullptr;

	return 0;
}
