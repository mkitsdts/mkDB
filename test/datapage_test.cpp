#include "../include/page/datapage.h"
#include <iostream>

int main()
{
    auto page = DataPage::create(1);
    page->add_column(INT, "id", KEY, NOT_NULL);
    page->add_column(VARCHAR, "name", NOT_KEY, NOT_NULL);
    page->add_column(DATE, "birthday", NOT_KEY, NOT_NULL);
    page->add_column(FLOAT, "salary", NOT_KEY, NOT_NULL);
    if(!page->write())
	    std::cout << "write success" << std::endl;

    return 0;
}