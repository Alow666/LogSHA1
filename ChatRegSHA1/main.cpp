#include <iostream>

#include "Chat.h"



int main() {
	Chat test;
	char log1[10] = "login";
	char log2[10] = "login1";
	char log3[10] = "login2";
	char log4[10] = "login3";
	char log5[10] = "login4";

	char log[10] = "login";


	char pas1[10] = "123123";
	char pas2[10] = "1231232";
	char pas3[10] = "1231233";
	char pas4[10] = "1231234";
	char pas5[10] = "1231235";

	char pas[10] = "12312";
	
	
	test.reg(log1, pas1, 10);
	test.reg(log2, pas2, 10);
	test.reg(log3, pas3, 10);
	test.reg(log4, pas4, 10);
	test.reg(log5, pas5, 10);

	std::cout<< test.login(log1, pas1, 10) <<std::endl;
	std::cout<< test.login(log2, pas2, 10) <<std::endl;
	std::cout<< test.login(log3, pas3, 10) <<std::endl;
	std::cout<< test.login(log4, pas4, 10) <<std::endl;
	std::cout<< test.login(log5, pas5, 10) <<std::endl;
	
	std::cout << '\n';

	std::cout<< test.login(log, pas5, 10) <<std::endl;
	std::cout << '\n';
	std::cout<< test.login(log5, pas4, 10) <<std::endl;
	


	
	return 0;
}