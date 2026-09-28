#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"
using namespace std;

Clothing::Clothing(std::string name, double price, int qty, std::string size, std::string brand)
    :Product("clothing", name, price, qty) {
      size_ = size;
      brand_ = brand;
    }

std::set<std::string> Clothing::keywords() const {
  set<string> nameToWords = parseStringToWords(name_);
  set<string> brandToWords = parseStringToWords(brand_);

  return setUnion(nameToWords, brandToWords);
}

std::string Clothing::displayString() const {
  stringstream ss;
  ss << name_ << "\n";
  ss << "Size: " << size_ << " Brand: " << brand_ << "\n";
  ss << fixed << setprecision(2) << price_ << " " << qty_ << " left.";
  return ss.str();
}

void Clothing::dump(std::ostream& os) const {
  os << "clothing" << "\n";
  os << name_ << "\n";
  os << fixed << setprecision(2) << price_ << "\n";
  os << qty_ << "\n";
  os << size_ << "\n";
  os << brand_ << "\n";
}