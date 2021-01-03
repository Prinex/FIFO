#include <iostream>
#include <algorithm>
#include <vector>

// ANSI codes for setting and resetting the text colors
#define RESET	"\033[0m"
#define RED		"\033[1;31m"
#define PURPLE	"\033[1;35m"

void print(std::vector<std::vector<int>> tbl, std::vector<int> pages, int pageFaults)
{
	/*	This function prints the will print the initial sequence 
	 * 	and then the page table after using fifo algorithm
	**/

	// printing the sequence first
	std::cout << std::endl;
	std::cout << " \tThe paging sequence" << std::endl;
	std::cout << PURPLE << "               ";
	for (std::vector<int>::iterator it = pages.begin(); it != pages.end(); it = std::next(it))
	{
		std::cout << *it << "  ";
	}
	std::cout << RESET << std:: endl;

	/*	Print the page table after fifo algorithm was used
	 *  In order to print a normal page table I've transposed the 
	 *	no of rows with the no of columns
	**/
	size_t cols = tbl.size();
	// find the number of rows
	size_t rows = 0;
	for (auto& col : tbl)
		if (col.size() > rows)
			rows = col.size();

	for (size_t row = 0; row < rows; ++row)
	{
		std::cout << "Page frame " << row << " : ";
		for (size_t col = 0; col < cols; ++col)
		{
			// check if the element exists
			if (row < tbl[col].size())
				// it exists, print it
				std::cout << tbl[col][row];
			else
				// it does not exist, print a space
				std::cout << " ";

			// separating space
			std::cout << "  ";
		}
		std::cout << '\n' << std::endl;
	}

	// Print the no of page faults
	// Set red color of the output using ansi codes if there are page faults or not
	std::cout << RED;
	if (pageFaults == 0)
	{
		std::cout << "No page faults" << std::endl;
	}
	else
	{
		
		std::cout << "Page fault score is " << pageFaults << std::endl;
	}
	std::cout << RESET;
}

bool search(std::vector<int> pageEntries, int page)
{
	// a function for searching a value in a range 
	if (std::find(pageEntries.begin(), pageEntries.end(), page) != pageEntries.end())
	{
		return true;
	}
	return false;
}

void fifo(std::vector<int> pages, int noFrames)
{
	// pageEntries will be used to store the no of frames with its entries
	std::vector<int> pageEntries;
	// pageFrames will be the page table 
	std::vector<std::vector<int>> pageFrames;
	int pageFaults = 0;
	// page is a counter for the current page
	int page = 0;
	// pageCounter will store the no of pages inserted
	int pageCounter;

	/* The firs part of the algorithm will fill the given entries
	 * till the given size is met
	 */
	for (auto it = pages.begin(); it != pages.end(); it = std::next(it))
	{
		if (pageEntries.size() == noFrames)
		{
			break;
		}
		// Add the first page when there is nothing in the current frame
		if (pageEntries.empty())
		{
			pageEntries.push_back(*it);
			pageFaults++;
		}
		// We only add other pages if the current page from the seqeunce is not in pageEntries
		if (search(pageEntries, *it) == false)
		{
			pageEntries.push_back(*it);
			pageFaults++;
		}
		page++;
		pageCounter = page;
		pageFrames.push_back(pageEntries);
	}
	/* Now, the second part of the algorithm will actually use fifo but not like an actual queue
	 * We start the loop from the last element that was inserted in the first part of the algorithm
	 * using the pageCounter variable that holds the no of pages inserted so far
	 */
	for (auto it = pages.begin() + page; it != pages.end(); it = std::next(it))
	{
		if (page == pageCounter)
		{
			page = 0;
		}
		// If the current page is already in the pageEntry add a duplicate (hint)
		if (std::find(pageEntries.begin(), pageEntries.end(), *it) != pageEntries.end())
		{
			pageFrames.push_back(pageEntries);
			continue;
		}
		// Replace the first page inserted with the new page if there's not space
		std::replace(pageEntries.begin(), pageEntries.end(), pageEntries.at(page), *it);
		// Push the entries in the table
		pageFrames.push_back(pageEntries);

		pageFaults++;
		page++;
	}
	print(pageFrames, pages, pageFaults);
}

int main()
{
	std::vector<int> pages;
	int noFrames;
	// read some values and push them into the sequence it could be less or greater than 11 values
	// read the no of frames
	std::cout << "Enter a sequence : ";
	while (true)
	{
		int value;
		std::cin >> value;
		pages.push_back(value);
		// when enter is pressed the loop ends
		if (std::cin.get() == '\n')
			break;
	}
	std::cout << "Enter the number of frames : ";
	std::cin >> noFrames;
	// start the algorithm
	fifo(pages, noFrames);

	return 0;
}