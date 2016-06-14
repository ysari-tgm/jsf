#include <iostream>
#include <pqxx/pqxx>

void add_employee(pqxx::transaction_base &txn, std::string name, int department);

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    std::cerr
      << "Give me an employee name and a department id.  No more, no less."
      << std::endl;
    return 2;
  }

  try
  {
    int department;

    // Use a libpqxx helper to interpret our department id string as an int.
    pqxx::from_string(argv[2], department);

    pqxx::connection conn;
    pqxx:: work txn(conn);
    add_employee(txn, argv[1], department);

    // Commit.  If we neglect to do this (e.g. because the program crashed)
    // then our changes will be rolled back.
    txn.commit();
  }
  catch (const std::exception &e)
  {
    // Our transaction's destructor has already been called, so our change
    // is implicitly rolled back before we get here.

    std::cerr << e.what() << std::endl;
    return 1;
  }
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

