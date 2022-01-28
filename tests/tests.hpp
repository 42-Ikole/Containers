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

#ifndef VERY_GOOD_TESTS_HPP
# define VERY_GOOD_TESTS_HPP

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

void	map_test();
void	map_iterator_test();

void	set_test();
void	set_iterator_test();

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
		std::cout << con[i] << " ";
	std::cout << "\n";
}

template < class Con, class Itr >
	static void whats_in_this_map_yo(Con &con, Itr i, std::string test)
{
	std::cout << "\n--[ " << test << " ]--" << std::endl;
	std::cout << "\nsize = " << con.size() << std::endl;
	std::cout << (int)(con.begin() == con.end()) << std::endl;
	for (; i != con.end(); i++)
		std::cout << "[" << (*i).first << "]-[" << (*i).second << "] ";
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


/////////////////
// test struct //
/////////////////

struct test {
	private: 
		int			_val;
		std::string	_name;
	public:
		test(int val = 0, std::string name = "unknown") : _val(val), _name(name) {}
		~test() {}

	void	print_test() const {
		std::cout << "val = " << _val << " name = " << _name << std::endl;
	}

	bool	operator == (const test& x) const {
		return (this->_val == x._val);
	}

	bool	operator != (const test& x) const {
		return (this->_val != x._val);
	}

	bool	operator < (const test& x) const {
		return (this->_val < x._val);
	}

	bool	operator <= (const test& x) const {
		return (this->_val <= x._val);
	}

	bool	operator > (const test& x) const {
		return (this->_val > x._val);
	}
	
	bool	operator >= (const test& x) const {
		return (this->_val >= x._val);
	}
};


#endif
