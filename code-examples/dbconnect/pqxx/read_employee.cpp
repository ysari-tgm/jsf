#include <iostream>
#include <pqxx/pqxx>

#include "helpers.h"

pqxx::result get_all_employees(pqxx::transaction_base &txn);
pqxx::result retrieve_employees();

int main()
{
  try
  {
    // Result objects are really just smart pointers inside, so
    // copying them around like this is very cheap.
    pqxx::result employees = retrieve_employees();

    // We'll be printing these fields:
    std::cout
      << "ID" << "\t"
      << "Name" << "\t"
      << "Dept." << std::endl;

    // Iterate over the rows in our result set.  Results objects
    // are containers similar to std::vector and such.
    for (
      pqxx::result::const_iterator row = employees.begin();
      row != employees.end();
      ++row)
    {
      // Fields within a row can be accessed by column name.
      // You can also iterate the fields in a row, or index the row
      // by column number just like an array.
      // Values are stored internally as plain strings.  You access
      // them by converting each to the desired C++ type using the
      // "as()" function template.
      std::cout
        << row["id"].as<int>() << "\t"
        << row["name"].as<std::string>() << "\t"
        << row["department"].as<int>()
        << std::endl;
    }

    // Like other C++ containers, pqxx::result has member functions
    // size() and empty().
    if (!employees.empty())
    {
      // If all we want to do is print the field values, without
      // locale formatting to make it suit local human tastes, we
      // could just read the fields as raw C strings using the
      // "c_str()" function, just like we have in std::string.
      // Results are a lot like std::vector, so we can access rows
      // through array indexing if an iterator is too much trouble.
      std::cout
        << "That first employee was:" << std::endl
        << employees[0]["id"].c_str() << "\t"
        << employees[0]["name"].c_str() << "\t"
        << employees[0]["department"].c_str()
        << std::endl;
    }

    // Our result object "employees" is local to this block, so
    // when we leave this scope without copying the object somewhere
    // else, the result's memory is freed up automatically.
  }
  catch (const std::exception &e)
  {
    // There's no need to check our database calls for errors.  If
    // any of them fails, it will throw a normal C++ exception.
    std::cerr << e.what() << std::endl;
    return 1;
  }
}

pqxx::result retrieve_employees()
{
  // Connect to the database.  Use the default database server,
  // port number, database, and password.  These can be changed
  // by passing a connection string here, or through environment
  // variables defined by libpq.
  pqxx::connection conn;
  // pqxx::connection conn("dbname=company user=accounting");

  // Start a transaction.  With libpqxx we're always working in
  // a transaction.
  pqxx::work txn(conn);

  // Query and return all employees.  Both our connection and our
  // transaction are local, so they'll be destroyed when we exit
  // this function.  That doesn't matter; the result object will
  // still be valid.
  return get_all_employees(txn);
}

pqxx::result get_all_employees(pqxx::transaction_base &txn)
{
  // Execute database query and immediately retrieve results.
  return txn.exec("SELECT id, name, department FROM Employee");
}

