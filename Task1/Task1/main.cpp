#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>

class SqlSelectQueryBuilder {
    std::vector<std::string> columns;
    std::string from_table;
    std::vector<std::string> where_conditions;

public:
    
    SqlSelectQueryBuilder& AddColumns(const std::string& column) {
        columns.push_back(column);
        return *this;
    }

    
    SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& cols) noexcept {
        columns.insert(columns.end(), cols.begin(), cols.end());
        return *this;
    }

    
    SqlSelectQueryBuilder& AddFrom(const std::string& table) {
        from_table = table;  
        return *this;
    }

  
    SqlSelectQueryBuilder& AddWhere(const std::string& key, const std::string& value) {
        where_conditions.push_back(key + "=" + value);
        return *this;
    }

   
    SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept {
        for (const auto& [key, value] : kv) {
            where_conditions.push_back(key + "=" + value);
        }
        return *this;
    }

    std::string BuildQuery() const {
        std::ostringstream query;

        query << "SELECT ";
        if (columns.empty()) {
            query << "*";
        }
        else {
            for (size_t i = 0; i < columns.size(); ++i) {
                query << columns[i];
                if (i < columns.size() - 1) query << ", ";
            }
        }

        query << " FROM " << from_table;  

        if (!where_conditions.empty()) {
            query << " WHERE ";
            for (size_t i = 0; i < where_conditions.size(); ++i) {
                query << where_conditions[i];
                if (i < where_conditions.size() - 1) query << " AND ";
            }
        }

        query << ";";
        return query.str();
    }
};

int main() {
   
    SqlSelectQueryBuilder query_builder;

    
    query_builder.AddColumns(std::vector<std::string>{"name", "phone"});

   
    query_builder.AddFrom("students");


    query_builder.AddWhere("id", "42").AddWhere("name", "John");


    std::cout << query_builder.BuildQuery() << std::endl;

    
    query_builder.AddFrom("teachers");
    std::cout << query_builder.BuildQuery() << std::endl;

    return 0;
}