#include "ProductRepository.h"
#include <fstream>

using namespace dao;

TxtProductRepository::TxtProductRepository(std::string sourcepath) {
	this->sourcepath = sourcepath;
}

Product* TxtProductRepository::get(std::string name)
{
	Product* res = nullptr;
	std::ifstream in;
	in.open(sourcepath, std::ios::in);

	if (!in) {
		throw 404;
	}

	Product* prodread = new Product();
	while (!in.eof())
	{
		in >> prodread->name >> prodread->amountBought >> prodread->amountSold >> prodread->primaryCost >> prodread->marketCost;
		if (prodread->name == name)
		{
			res = prodread;
			break;
		}
	}

	if (res != prodread)
	{
		delete prodread;
	}

	in.close();

	return res;
}

std::list<Product*> TxtProductRepository::get()
{
	std::list<Product*> products;

	std::ifstream in;
	in.open(sourcepath, std::ios::in);

	if (!in) {
		throw 404;
	}


	while (!in.eof())
	{
		Product* prodread = new Product();
		in >> prodread->name >> prodread->amountBought >> prodread->amountSold >> prodread->primaryCost >> prodread->marketCost;
		products.push_back(prodread);
	}

	in.close();
	
	return products;
}

Product* TxtProductRepository::save(Product* prod)
{
	std::list<Product*> products = get();

	bool shouldInsert = true;
	for (std::list<Product*>::iterator it = products.begin(); it != products.end(); ++it)
	{
		auto i = *it;
		if (i->name == prod->name) {
			i->amountBought = prod->amountBought;
			i->amountSold = prod->amountSold;
			i->marketCost = prod->marketCost;
			i->primaryCost = prod->primaryCost;

			shouldInsert = false;
			break;
		}
	}

	if (shouldInsert)
	{
		products.push_back(prod);
	}

	std::ofstream out;
	out.open("db.txt", std::ios::out | std::ios::trunc);

	if (!out) {
		throw 404;
	}

	for (std::list<Product*>::iterator it = products.begin(); it != products.end(); ++it)
	{
		auto i = *it;
		out << i->name << '\t' << i->amountBought << '\t' << i->amountSold << '\t' << i->primaryCost << '\t' << i->marketCost;
	}

	out.close();

	return prod;
}

void TxtProductRepository::del(std::string name)
{
	std::list<Product*> products = get();

	for (std::list<Product*>::iterator it = products.begin(); it != products.end(); )
	{
		auto i = *it;
		if (i->name == name) {
			it = products.erase(it);
			break;
		}
		else
		{
			++it;
		}
	}

	std::ofstream out;
	out.open("db.txt", std::ios::out | std::ios::trunc);

	if (!out) {
		throw 404;
	}

	for (std::list<Product*>::iterator it = products.begin(); it != products.end(); ++it)
	{
		auto i = *it;
		out << i->name << '\t' << i->amountBought << '\t' << i->amountSold << '\t' << i->primaryCost << '\t' << i->marketCost;
	}

	out.close();
}

ProductRepository* ProductRepository::of(RepositoryType type)
{
	ProductRepository* repo = nullptr;
	switch (type)
	{
	case TXT:
		repo = new TxtProductRepository("db.txt");
		break;
	default:
		break;
	}

	return repo;
}