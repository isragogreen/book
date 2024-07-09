#include <iostream>
#include <string>

int	main(int argc, char* argv[])
{
	int	i;
	int	j;
	std::string	arg1;
	std::string tmp;
	std::string arg2;

	if (argc < 3)
	{
		std::cout << "too low  arguments" << std::endl;
		return (1);
	}
	arg2 = argv[2];
	i = 2;
	while (++i < argc)
		arg2 = arg2 + " " + argv[i];
	tmp = arg2;
	
	arg1 = argv[1];
//	arg2 = argv[2];
	if ((arg1 == "down") || (arg1 == "DOWN"))
		{
			i = arg2.size() + 1;
			while ( --i >= 0)
				if ((arg2[i] >= 'A') && (arg2[i] <= 'Z'))
					arg2[i] += 0x20;
		}
	else	if ((arg1 == "up") || (arg1 == "UP"))
				{
					i = arg2.size() + 1;
					while ( --i >= 0)
						if ((arg2[i] >= 'a') && (arg2[i] <= 'z'))
							arg2[i] -= 0x20;	
				} 
			else
				{
					std::cout << "mistake param " << arg1 << std::endl;
					return (2);
				}
	std::cout << "input  is: " << tmp << std::endl;
	std::cout << "you  make: " << argv[1] << std::endl;
	std::cout << "result is: " << arg2 << std::endl;
	return (0);
}