#include "TList.h"

int main()
{
	UTIL::TList<int> mylist({ 0, 1, 2, 3, 4, 5, 6 }); 

	mylist.set_display_fn([&mylist]() {

		size_t list_size = mylist.size();

		if (list_size == 0)
		{
			std::cout << "TList have not elements!" << std::endl;
		}
		else
		{
			for (int i = 0; i < list_size; i++)
			{
				std::cout << mylist[i] << (i == (list_size - 1) ? "\n" : " ");
			}
		}
		});

	mylist.display();
	mylist.pop_front();
	mylist.display();

	return EXIT_SUCCES;
}
