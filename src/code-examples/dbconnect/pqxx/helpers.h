void add_employee(pqxx::transaction_base &txn, std::string name, int department);
pqxx::result get_all_employees(pqxx::transaction_base &txn);

