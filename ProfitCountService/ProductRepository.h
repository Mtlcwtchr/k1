#pragma once
#include "Product.h"
#include "RepositoryType.h"
#include <list>
namespace dao
{
	class ProductRepository
	{
	public:
		virtual Product* get(std::string name) = 0;
		virtual std::list<Product*> get() = 0;
		virtual Product* save(Product* product) = 0;
		virtual void del(std::string name) = 0;

		static ProductRepository* of(RepositoryType);

	};

	class TxtProductRepository : public ProductRepository
	{
	private:
		std::string sourcepath;

	public:
		TxtProductRepository(std::string);

		virtual Product* get(std::string name);
		virtual std::list<Product*> get();
		virtual Product* save(Product* product);
		virtual void del(std::string name);
	};
};