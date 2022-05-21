 


#include <memory>
#include "List.h"
#include "Element.h"
#include "Utilities.h"

using namespace std;

namespace sdds
{
	List<Product> mergeRaw(const List<Description>& desc, const List<Price>& price) {
		List<Product> priceList;
		for (size_t i = 0; i < desc.size(); i++) {
			for (size_t j = 0; j < price.size(); j++) {
				if (desc[i].prod_code == price[j].prod_code) {
					Product* Prot = new Product(desc[i].desc, price[j].price);
					Prot->validate();
					priceList += Prot;
					delete Prot;
					Prot = nullptr;
				}
			}
		}
		return priceList;
	}

	List<Product> mergeSmart(const List<Description>& desc, const List<Price>& price) {
		List<Product> priceList;
		for (size_t i = 0; i < desc.size(); ++i) {
			for (size_t x = 0; x < price.size(); ++x) {
				if (desc[i].prod_code == price[x].prod_code) {
					std::unique_ptr<Product> Prot{ new Product(desc[i].desc, price[x].price) };
					Prot->validate();
					priceList += Prot;
				}
			}
		}
		return priceList;
	}
}