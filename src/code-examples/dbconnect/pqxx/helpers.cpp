#include <pqxx/pqxx>

pqxx::result get_all_employees(pqxx::transaction_base &txn)
{
  // Execute database query and immediately retrieve results.
  return txn.exec("SELECT id, name, department FROM Employee");
}

void add_employee(pqxx::transaction_base &txn, std::string name, int department)
{
  // Use quote() to escape and quote a value safely for use in a
  // query.  Avoid bugs and security holes when strings contain
  // backslashes, quotes, or other "weird" characters.
  // That's not very useful for department (an integer), but it
  // also represents the value as a string.  We don't want to add
  // an int to the query, we want to add a string that represents
  // the int value.
  txn.exec(
    "INSERT INTO Employee(name, department) "
    "VALUES (" +
    txn.quote(name) + ", " +
    txn.quote(department) +
    ")");
}

