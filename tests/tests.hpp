/* ************************************************************************** */
/*                                                                            */
/*              ,---------.     .-''-.      .-'''-.  ,---------.              */
/*              \          \  .'_ _   \    / _     \ \          \             */
/*               `--.  ,---' / ( ` )   '  (`' )/`--'  `--.  ,---'             */
/*                  |   \   . (_ o _)  | (_ o _).        |   \                */
/*                  :_ _:   |  (_,_)___|  (_,_). '.      :_ _:                */
/*                  (_I_)   '  \   .---. .---.  \  :     (_I_)                */
/*                 (_(=)_)   \  `-'    / \    `-'  |    (_(=)_)               */
/*                  (_I_)     \       /   \       /      (_I_)                */
/*                  '---'      `'-..-'     `-...-'       '---'                */
/*																			  */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*																			  */
/* ************************************************************************** */

#ifndef TESTS_HPP
# define TESTS_HPP

# include <exception>
# include <string>
# include <exception>

///////////////////
// COLOR DEFINES //
///////////////////

# define COLOR_RED		"\033[31m"
# define COLOR_GREEN	"\033[32m"
# define COLOR_RESET	"\033[0m"
# define COLOR_YELLOW	"\033[33m"
# define COLOR_BLUE		"\033[27m"

///////////
// TESTS //
///////////

void	vector_test();
void	vector_iterator_test();

void	deque_test();

/////////////
// HELPERS //
/////////////
void	print_header(std::string);

template < class Con >
	static void whats_in_this_container_yo(Con &con, std::string test)
{
	std::cout << "\n--[ " << test << " ]--" << std::endl;
	std::cout << "\nsize = " << con.size() << std::endl;
	for (size_t i = 0; i < con.size(); i++)
		std::cout << con[i] << " " << std::endl;
}

/////////////////////
// Exception class //
/////////////////////

class conception : public std::exception
{
	private:
		std::string _msg;

	public:
		conception(std::string msg, std::string type, std::string val)
		{
			_msg = std::string("[") + COLOR_GREEN + type + COLOR_RESET + std::string("] ") + 
				COLOR_RED + std::string("Error: ") + COLOR_RESET + msg + 
				std::string(" <") + COLOR_YELLOW + val + COLOR_RESET + std::string(">"); 
		}

		const char* what() const throw()
		{
			return (_msg.c_str());
		}

		~conception() throw() {};
};

#endif
