#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <sstream>
#include <iomanip>
#include <map>
#include "datastore.h"

class MyDataStore : public DataStore {
public:
  MyDataStore();
  ~MyDataStore();

  void addProduct(Product* p);
  void addUser(User* u);
  std::vector<Product*> search(std::vector<std::string>& terms, int type);
  void dump(std::ostream& ofile);
  bool addToCart(std::string username, Product* p);
  bool viewCart(std::string username);
  bool buyCart(std::string username);

private:
  User* findUser(std::string username);
  std::vector<Product*> products_;
  std::vector<User*> users_;
  std::map<std::string, std::set<Product*> > keywordMap_;
  std::map<std::string, std::vector<Product*> > carts_;
};
#endif