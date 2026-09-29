#include <iostream>
#include "mydatastore.h"
#include "util.h"
using namespace std;

MyDataStore::MyDataStore()
{

}

MyDataStore::~MyDataStore() {
  for (size_t i = 0; i < products_.size(); i++) {
    delete products_[i];
  }
  for (size_t i = 0; i < users_.size(); i++) {
    delete users_[i];
  }
}

void MyDataStore::addUser(User* u) {
  users_.push_back(u);
}

User* MyDataStore::findUser(string username) {
  for (size_t i = 0; i < users_.size(); i++) {
    if (convToLower(users_[i]->getName()) == convToLower(username)) {
      return users_[i];
    }
  }
  return NULL;
}

void MyDataStore::addProduct(Product* p) {
  products_.push_back(p);
  set<string> words = p->keywords();
  for (set<string>::iterator it = words.begin(); it != words.end(); ++it) {
    string word = *it;
    keywordMap_[word].insert(p);
  }
}