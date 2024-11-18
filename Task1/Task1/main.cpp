#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<map>

using namespace std;

class SqlSelectQueryBilder 
{
private:
	vector<string> colums;
	string from_table;
	map<string, string>where_condition;
public:
	SqlSelectQueryBilder& AddColumns(const string& column) 
	{
		colums.push_back(column);
		return *this;
	}
	SqlSelectQueryBilder& AddColums(const vector<string>&cols)noexcept 
	{
		colums.insert(colums.end(), cols.begin(),cols.end());
		return *this;
	
	}
	SqlSelectQueryBilder& AddFrom(const string& table) {
		from_table = table;
		return *this;
	}
	SqlSelectQueryBilder& AddWhere(const string& column, const string& value) 
	{
		where_condition[column] = value;
		return *this;
	}

	SqlSelectQueryBilder& AddWhere(const map<string, string>& kv)noexcept 
	{
		where_condition.insert(kv.begin(), kv.end());
		return *this;
	}

	string BuildQuery()const {
		ostringstream query;
		query << "SELECT";
		if (colums.empty()) {
			query << "*";	
		}
		else {
			for (size_t i = 0; i < colums.size(); ++i) {
				query<< colums[i];
				if (i < colums.size() - 1) query << ", ";
			}
		}
		query << " FROM " << from_table<<endl;

		if (!where_condition.empty()) {
			query << "WHERE";
			bool first = true;
			for (const auto& condition : where_condition) {
			
				query << condition.first << " = " << condition.second;
				first = false;
			}
		}
		query << "; "<<endl;
		return query.str();
	}

};


int main() 
{
	SqlSelectQueryBilder query_builder;

	query_builder.AddColumns(" name ").AddColumns(" phone ").AddColumns("email");
	query_builder.AddFrom(" students ");
	query_builder.AddWhere(" id ", " 42 ").AddWhere(" name ", " John ").AddWhere("age","21");

	cout << query_builder.BuildQuery() << endl;


	return 0;
}