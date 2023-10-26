//Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D
#include "TableEntry.h"
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <getopt.h>
#include <map>

using namespace std;

class Index {
public:
    map<TableEntry, vector<int>, less<TableEntry>> bst;
    unordered_map<TableEntry, vector<int>> hash;
    int col;
    bool is_bst;
    bool valid = false;

    Index() {
        valid = false;
        col = -1;
        is_bst = false;
    }

    Index(const vector<vector<TableEntry>> &t, string type, int col_in) {
        valid = true;
        if (type == "bst") {
            is_bst = true;
        }
        else {
            is_bst = false;
        }
        col = col_in;
        if (is_bst) {
            for (int i = 0; i < static_cast<int>(t.size()); ++i) {
                bst[t[i][col]].push_back(i);
            }
        }
        else {
            for (int i = 0; i < static_cast<int>(t.size()); ++i) {
                hash[t[i][col]].push_back(i);
            }
        }
    }
    //gets row
    vector<int> operator[](const TableEntry &tb) {
        if (is_bst) {
            return bst[tb];
        }
        else {
            return hash[tb];
        }
    }

    void reset(const vector<vector<TableEntry>> &t) {
        if (is_bst) {
            bst.clear();
            for (int i = 0; i < static_cast<int>(t.size()); ++i) {
                bst[t[i][col]].push_back(i);
            }
        }
        else {
            hash.clear();
            for (int i = 0; i < static_cast<int>(t.size()); ++i) {
                hash[t[i][col]].push_back(i);
            }
        }
    }
    void insert_update(const TableEntry &t, int row) {
        if (is_bst) {
            bst[t].push_back(row);
        }
        else {
            hash[t].push_back(row);
        }
    }
};

class Table {
private:
    vector<vector<TableEntry>> table;
    Index generated_index;
    unordered_map<string, int> column_names;
    vector<string> column_types;
    string name;

    static TableEntry getTableEntry(char type) {
        //find type
        switch (type) {
        case 's':
        {
            string type_string;
            cin >> type_string;
            TableEntry value(type_string);
            return value;
        }
        case 'b':
        {
            bool type_bool;
            cin >> type_bool;
            TableEntry value(type_bool);
            return value;
        }

        case 'i':
        {
            int type_int;
            cin >> type_int;
            TableEntry value(type_int);
            return value;
        }
        case 'd':
        {
            double type_double;
            cin >> type_double;
            TableEntry value(type_double);
            return value;
        }
        default:
            return TableEntry(0);
        }
    }

    static bool getComparator(const TableEntry &l, char c, const TableEntry &value) {
        switch (c) {
        case '<':
            return l < value;
        case '>':
            return l > value;
        case '=':
            return l == value;
        default:
            return false;
        }
    }

    class compare_functor {
    private:
        TableEntry value;
        int index;
        char comp;
    public:
        compare_functor(TableEntry v_in, int index_in, char c_in) :
            value(v_in), index(index_in), comp(c_in) {}
        bool operator()(const vector<TableEntry> &l) {
            return getComparator(l[index], comp, value);
        }
    };

public:
    Table(string name_in, int n) {
        name = name_in;
        column_types.resize(n);
        string in;
        for (int i = 0; i < n; ++i) {
            cin >> in;
            column_types[i] = in;
        }
        for (int i = 0; i < n; ++i) {
            cin >> in;
            column_names[in] = i;
            cout << in << " ";
        }
    }
    //INSERT INTO <tablename> <N> ROWS 
    //<value11> <value12> ... <value1M>
    //<value21> <value22> ... <value2M>
    //...
    //<valueN1> <valueN2> ... <valueNM>
    void insert() {
        int n;
        string trash;
        cin >> n >> trash;
        size_t start_index = table.size();
        table.resize(start_index + n);
        for (size_t i = start_index; i < table.size(); ++i) {
            table[i].reserve(column_types.size());
            for (int j = 0; j < static_cast<int>(column_types.size()); ++j) {
                char type = column_types[j][0];
                string type_string;
                bool type_bool;
                int type_int;
                double type_double;
                switch (type) {
                case 's':
                    cin >> type_string;
                    table[i].emplace_back(type_string);
                    if (generated_index.valid && j == generated_index.col) {
                        generated_index.insert_update(table[i][j], static_cast<int>(i));
                    }
                    break;
                case 'b':
                    cin >> type_bool;
                    table[i].emplace_back(type_bool);
                    if (generated_index.valid && j == generated_index.col) {
                        generated_index.insert_update(table[i][j], static_cast<int>(i));
                    }
                    break;
                case 'i':
                    cin >> type_int;
                    table[i].emplace_back(type_int);
                    if (generated_index.valid && j == generated_index.col) {
                        generated_index.insert_update(table[i][j], static_cast<int>(i));
                    }
                    break;
                case 'd':
                    cin >> type_double;
                    table[i].emplace_back(type_double);
                    if (generated_index.valid && j == generated_index.col) {
                        generated_index.insert_update(table[i][j], static_cast<int>(i));
                    }
                    break;
                }
            }
        }
        cout << "Added " << n << " rows to " << name << " from position "
            << start_index << " to " << table.size() - 1 << "\n";
    }
    //PRINT FROM <tablename> <N> <print_colname1> <print_colname2> ... <print_colnameN> 
    //                                             {WHERE <colname> <OP> <value> | ALL}
    void print() {
        int n;
        cin >> n;
        string in;
        vector<string> printed_col_names(n);
        for (int i = 0; i < n; ++i) {
            cin >> in;
            if (column_names.find(in) == column_names.end()) {
                cout << "Error during PRINT: " << in << " does not name a column in " << name << "\n";
                string trash;
                getline(cin, trash);
                return;
            }
            printed_col_names[i] = in;
        }
        cin >> in;
        //ALL
        if (in == "ALL") {
            for (string s : printed_col_names) {
                cout << s << " ";
            }
            cout << "\n";
            for (size_t i = 0; i < table.size(); ++i) {
                for (string s : printed_col_names) {
                    cout << table[i][column_names[s]] << " ";
                }
                cout << "\n";
            }
            cout << "Printed " << table.size() << " matching rows from " << name << "\n";
        }
        //WHERE
        else {
            string col_name;
            char op;
            cin >> col_name >> op;
            if (column_names.find(col_name) == column_names.end()) {
                cout << "Error during PRINT: " << col_name << " does not name a column in " << name << "\n";
                string trash;
                getline(cin, trash);
                return;
            }
            int col_idx = column_names[col_name];
            char type = column_types[col_idx][0];
            TableEntry value = getTableEntry(type);
            for (string s : printed_col_names) {
                cout << s << " ";
            }
            cout << "\n";
            int num_printed = 0;
            //edit for bst/index stuff
            if (generated_index.valid && generated_index.is_bst && generated_index.col == col_idx) {
                switch (op) {
                case '<':
                {
                    auto fit = generated_index.bst.begin();
                    auto it = generated_index.bst.lower_bound(value);
                    while (fit != it) {
                        //print row of each match
                        for (int row : fit->second) {
                            //print the row
                            for (string s : printed_col_names) {
                                    cout << table[row][column_names[s]] << " ";
                            }
                            ++num_printed;
                            cout << "\n";
                        }
                        ++fit;
                    }
                    break;
                }
                case '>':
                {
                    auto it = generated_index.bst.upper_bound(value);
                    while (it != generated_index.bst.end()) {
                        //print row of each match
                        for (int row : it->second) {
                            //print the row
                            for (string s : printed_col_names) {
                                    cout << table[row][column_names[s]] << " ";
                            }
                            ++num_printed;
                            cout << "\n";
                        }
                        ++it;
                    }
                    break;
                }
                case '=':
                    auto it = generated_index.bst.find(value);
                    if (it == generated_index.bst.end()) {
                        break;
                    }
                    else {
                        for (int row : it->second) {
                            //print the row
                            for (string s : printed_col_names) {
                                cout << table[row][column_names[s]] << " ";
                            }
                            ++num_printed;
                            cout << "\n";
                        }
                        break;
                    }
                }
            }
            else {
                for (size_t i = 0; i < table.size(); ++i) {
                    if (getComparator(table[i][col_idx], op, value)) {
                        for (string s : printed_col_names) {
                            cout << table[i][column_names[s]] << " ";
                        }
                        ++num_printed;
                        cout << "\n";
                    }
                }
            }
            cout << "Printed " << num_printed << " matching rows from " << name << "\n";
        }
    }

    void quiet_print() {
        int n;
        cin >> n;
        string in;
        for (int i = 0; i < n; ++i) {
            cin >> in;
            if (column_names.find(in) == column_names.end()) {
                cout << "Error during PRINT: " << in << " does not name a column in " << name << "\n";
                string trash;
                getline(cin, trash);
                return;
            }
        }
        cin >> in;
        //ALL
        if (in == "ALL") {
            cout << "Printed " << table.size() << " matching rows from " << name << "\n";
        }
        //WHERE
        else {
            string col_name;
            char op;
            cin >> col_name >> op;
            if (column_names.find(col_name) == column_names.end()) {
                cout << "Error during PRINT: " << col_name << " does not name a column in " << name << "\n";
                string trash;
                getline(cin, trash);
                return;
            }
            int col_idx = column_names[col_name];
            char type = column_types[col_idx][0];
            TableEntry value = getTableEntry(type);
            int num_printed = 0;
            if (generated_index.valid && generated_index.is_bst && generated_index.col == col_idx) {
                switch (op) {
                case '<':
                {
                    auto fit = generated_index.bst.begin();
                    auto it = generated_index.bst.lower_bound(value);
                    while (fit != it) {
                        num_printed += static_cast<int>(fit->second.size());
                        ++fit;
                    }
                    break;
                }
                case '>':
                {
                    auto it = generated_index.bst.upper_bound(value);
                    while (it != generated_index.bst.end()) {
                        num_printed += static_cast<int>(it->second.size());
                        ++it;
                    }
                    break;
                }
                case '=':
                {
                    auto it = generated_index.bst.find(value);
                    if (it != generated_index.bst.end()) {
                        num_printed += static_cast<int>(it->second.size());
                    }
                    break;
                }
                }
            }
            //non bst index
            else {
                for (vector<TableEntry> row : table) {
                    if (getComparator(row[col_idx], op, value)) {
                        ++num_printed;
                    }
                }
            }
            cout << "Printed " << num_printed << " matching rows from " << name << "\n";
        }
    }
    //bst?
    //DELETE FROM <tablename> WHERE <colname> <OP> <value>
    void delete_table() {
        string name_in;
        char comparator;
        char type;
        cin >> name_in >> name_in;
        auto col_index = column_names.find(name_in);
        if (col_index == column_names.end()) {
            cout << "Error during DELETE: " << name_in << " does not name a column in " << name << "\n";
            string trash;
            getline(cin, trash);
            return;
        }
        size_t old_size = table.size();
        type = column_types[col_index->second][0];
        cin >> comparator;
        TableEntry value = getTableEntry(type);
        compare_functor func(value, col_index->second, comparator);
        auto it = remove_if(table.begin(), table.end(), func);
        //UPDATE INDEX
        table.resize(it - table.begin());
        if (generated_index.valid) {
            generated_index.reset(table);
        }
        cout << "Deleted " <<  old_size - table.size() << " rows from " << name << "\n";
    }
    //JOIN <tablename1> AND <tablename2> WHERE <colname1> = <colname2> AND PRINT 
    // <N> <print_colname1> <1|2> <print_colname2> <1|2> ... <print_colnameN> <1|2>
    void join(bool q, Table* t2) {
        string col_name_1;
        string col_name_2;
        string trash;
        int n;
        char op;
        cin >> col_name_1 >> col_name_1 >> op >> col_name_2;
        cin >> trash >> trash >> n;
        if (column_names.find(col_name_1) == column_names.end()) {
            cout << "Error during JOIN: " << col_name_1 << " does not name a column in " << name << "\n";
            string trash;
            getline(cin, trash);
            return;
        }
        if (t2->column_names.find(col_name_2) == t2->column_names.end()) {
            cout << "Error during JOIN: " << col_name_2 << " does not name a column in " << t2->name << "\n";
            string trash;
            getline(cin, trash);
            return;
        }
        vector<pair<string, int>> joined_cols;
        joined_cols.resize(n);
        string print_name;
        int which_table;
        for (int i = 0; i < n; ++i) {
            cin >> print_name >> which_table;
            switch (which_table) {
            case 1:
                if (column_names.find(print_name) == column_names.end()) {
                    cout << "Error during JOIN: " << print_name << " does not name a column in " << name << "\n";
                    string trash;
                    getline(cin, trash);
                    return;
                }
                break;
            case 2:
                if (t2->column_names.find(print_name) == t2->column_names.end()) {
                    cout << "Error during JOIN: " << print_name << " does not name a column in " << t2->name << "\n";
                    string trash;
                    getline(cin, trash);
                    return;
                }
                break;
            }
            joined_cols[i] = make_pair(print_name, which_table);
            //error check
        }
        int t1_col_num = column_names[col_name_1];
        int t2_col_num = t2->column_names[col_name_2];
        int num_rows = 0;
        if (!q) {
            for (pair<string, int> p : joined_cols) {
                cout << p.first << " ";
            }
            cout << "\n";
        }
        //use hash
        if (t2->generated_index.valid && !t2->generated_index.is_bst && t2->generated_index.col == t2_col_num) {
            if (q) {
                for (vector<TableEntry> row : table) {
                    auto match = t2->generated_index.hash.find(row[t1_col_num]);
                    //found
                    if (match != t2->generated_index.hash.end()) {
                        num_rows += static_cast<int>(match->second.size());
                    }
                }
            }
            else {
                for (vector<TableEntry> row : table) {
                    auto match = t2->generated_index.hash.find(row[t1_col_num]);
                    //found
                    if (match != t2->generated_index.hash.end()) {
                        //iterate through each match
                        for (int t2_row : match->second) {
                            //printing the row
                            for (pair<string, int> p : joined_cols) {
                                switch (p.second) {
                                case 1:
                                    cout << row[column_names[p.first]] << " ";
                                    break;
                                case 2:
                                    cout << t2->table[t2_row][t2->column_names[p.first]] << " ";
                                    break;
                                }
                            }
                            ++num_rows;
                            cout << "\n";
                        }
                    }
                }
            }
        }
        else {
            unordered_map<TableEntry, vector<int>> hash_helper;
            for (int i = 0; i < static_cast<int>(t2->table.size()); ++i) {
                hash_helper[t2->table[i][t2_col_num]].push_back(i);
            }
            if (q) {
                for (vector<TableEntry> row : table) {
                    auto match = hash_helper.find(row[t1_col_num]);
                    //found
                    if (match != hash_helper.end()) {
                        num_rows += static_cast<int>(match->second.size());
                    }
                }
            }
            else {
                for (vector<TableEntry> row : table) {
                    auto match = hash_helper.find(row[t1_col_num]);
                    //found
                    if (match != hash_helper.end()) {
                        //iterate through each match
                        for (int t2_row : match->second) {
                            //printing the row
                            for (pair<string, int> p : joined_cols) {
                                switch (p.second) {
                                case 1:
                                    cout << row[column_names[p.first]] << " ";
                                    break;
                                case 2:
                                    cout << t2->table[t2_row][t2->column_names[p.first]] << " ";
                                    break;
                                }
                            }
                            ++num_rows;
                            cout << "\n";
                        }
                    }
                }
            }
        }
        cout << "Printed " << num_rows << " rows from joining " << name << " to " << t2->name << "\n";
    }
    //GENERATE FOR <tablename> <indextype> INDEX ON <colname>
    void generate() {
        //column value -> row
        string idx_type;
        string col_name;
        cin >> idx_type >> col_name >> col_name >> col_name;
        if (column_names.find(col_name) == column_names.end()) {
            cout << "Error during GENERATE: " << col_name << " does not name a column in " << name << "\n";
            string trash;
            getline(cin, trash);
            return;
        }
        generated_index = Index(table, idx_type, column_names[col_name]);
        cout << "Created " << idx_type << " index for table " << name << " on column " << col_name << "\n";
    }
};

class Shell {
private:
    unordered_map<string, Table*> tables;
    bool quiet;
    //CREATE <tablename> <N> <coltype1> <coltype2> ... <coltypeN> 
    //                       <colname1> <colname2> ... <colnameN>
    void CREATE() {
        string table_name;
        cin >> table_name;
        if (tables.find(table_name) != tables.end()) {
            cout << "Error during CREATE: Cannot create already existing table <tablename>\n";
            string trash;
            getline(cin, trash);
            return;
        }
        else {
            int num_columns;
            cin >> num_columns;
            cout << "New table " << table_name << " with column(s) ";
            Table* new_table = new Table(table_name, num_columns);
            cout << "created\n";
            tables[table_name] = new_table;
        }
    }
    //#
    void COMMENT() {
        string trash;
        getline(cin, trash);
    }
    //REMOVE <tablename>
    void REMOVE() {
        string name;
        cin >> name;
        auto it = tables.find(name);
        if (it == tables.end()) {
            cout << "Error during REMOVE: " << name << " does not name a table in the database\n";
            string trash;
            getline(cin, trash);
            return;
        }
        else {
            //LEAK
            delete it->second;
            tables.erase(name);
            cout << "Table " << name << " deleted\n";
        }
    }
    //INSERT INTO <tablename> <N> ROWS 
    //<value11> <value12> ... <value1M>
    //<value21> <value22> ... <value2M>
    //...
    //<valueN1> <valueN2> ... <valueNM>
    void INSERT() {
        string name;
        cin >> name >> name;
        if (tables.find(name) == tables.end()) {
            cout << "Error during INSERT: " << name << " does not name a table in the database\n";
            string trash;
            getline(cin, trash);
            return;
        }
        else {
            tables[name]->insert();
        }
    }
    //PRINT FROM <tablename> <N> <print_colname1> <print_colname2> ... <print_colnameN> 
    //                                             {WHERE <colname> <OP> <value> | ALL}
    void PRINT() {
        string name;
        cin >> name >> name;
        if (tables.find(name) == tables.end()) {
            cout << "Error during PRINT: " << name << " does not name a table in the database\n";
            string trash;
            getline(cin, trash);
            return;
        }
        else {
            if (!quiet) {
                tables[name]->print();
            }
            else {
                tables[name]->quiet_print();
            }
        }
    }
    //DELETE FROM <tablename> WHERE <colname> <OP> <value>
    void DELETE() {
        string name;
        cin >> name >> name;
        if (tables.find(name) == tables.end()) {
            cout << "Error during DELETE: " << name << " does not name a table in the database\n";
            string trash;
            getline(cin, trash);
            return;
        }
        else {
            tables[name]->delete_table();
        }
    }
    //JOIN <tablename1> AND <tablename2> WHERE <colname1> = <colname2> AND PRINT 
    // <N> <print_colname1> <1|2> <print_colname2> <1|2> ... <print_colnameN> <1|2>
    void JOIN() {
        string name1;
        string name2;
        cin >> name1 >> name2 >> name2;
        if (tables.find(name1) == tables.end()) {
            cout << "Error during DELETE: " << name1 << " does not name a table in the database\n";
            string trash;
            getline(cin, trash);
            return;
        }
        else if (tables.find(name2) == tables.end()) {
            cout << "Error during DELETE: " << name2 << " does not name a table in the database\n";
            string trash;
            getline(cin, trash);
            return;
        }
        else {
            tables[name1]->join(quiet, tables[name2]);
        }
    }
    //GENERATE FOR <tablename> <indextype> INDEX ON <colname>
    void GENERATE() {
        string name;
        cin >> name >> name;
        if (tables.find(name) == tables.end()) {
            cout << "Error during GENERATE: " << name << " does not name a table in the database\n";
            string trash;
            getline(cin, trash);
            return;
        }
        else {
            tables[name]->generate();
        }
    }

public:
    Shell(bool q) {
        quiet = q;
    }
    void read_input(string s) {
        switch (s[0]) {
        case 'C': //CREATE
            CREATE();
            break;
        case 'Q': //QUIT
            break;
        case '#': //# COMMENT
            COMMENT();
            break;
        case 'R': //REMOVE
            REMOVE();
            break;
        case 'I': //INSERT
            INSERT();
            break;
        case 'P': //PRINT
            PRINT();
            break;
        case 'D': //DELETE
            DELETE();
            break;
        case 'J': //JOIN
            JOIN();
            break;
        case 'G': //GENERATE
            GENERATE();
            break;
        default:
            cout << "Error: unrecognized command\n";
            string trash;
            getline(cin, trash);
            break;
        }
    }
};

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(false);
    cin >> std::boolalpha;
    cout << std::boolalpha;
    bool quiet_mode = false;
    //GETOPT
    int option_index = 0;
    int choice;
    option long_options[] = {
        { "quiet",  no_argument, nullptr, 'q'},
        { "help",  no_argument,       nullptr, 'h'},
        { nullptr, 0,                 nullptr, '\0' }
    };
    while ((choice = getopt_long(argc, argv, "qh", long_options, &option_index)) != -1) {
        switch (choice) {
        case 'q':
            quiet_mode = true;
            break;
        case 'h':
            cout << "This programs take in a castle layout and outputs a path from Marco to the Countess. \n"
                << "Command Line Arguments: \n"
                << "You must select routing scheme using either --stack or --queue. YOU CANNOT ENTER BOTH!\n"
                << "You can indicate output file format using --output 'M' or 'L' (Program defaults to M outpt)\n";
            exit(0);
        default:
            cerr << "Unknown command line option\n" << endl;
            exit(1);
        }
    }
    //shell
    string read;
    Shell shell(quiet_mode);
    do {
        cout << "% ";
        cin >> read;
        shell.read_input(read);
    } while (read != "QUIT");
    cout << "Thanks for being silly!\n";
}