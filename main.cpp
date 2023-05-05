#include <iostream>
#include "sqlite/sqlite3.h"

using namespace std;

void addRecord(int &rc, sqlite3* &db, char* &err) {
    cout << "Enter name:";
    string name; cin >> name;
    cout << "Enter age:";
    string age; cin >> age;

    string insertSQL = "INSERT INTO users (name, age) VALUES ('" + name + "', " + age + ");";
    rc = sqlite3_exec(db, insertSQL.c_str(), nullptr, nullptr, &err);

    if (rc != SQLITE_OK) {
        cerr << "Error adding record:" << err << endl;
        sqlite3_free(err);
        sqlite3_close(db);
        return;
    }
    else cout << "Record added successfully" << endl;
}

void viewRecords(int &rc, sqlite3* &db, char* &err) {
    const char* selectSQL = "SELECT * FROM users;";

    rc = sqlite3_exec(db, selectSQL, [](void* data, int argc, char** argv, char** columnNames)
    {
        for (int i = 0; i < argc; i++)
            cout << columnNames[i] << ": " << argv[i] << endl;
        cout << endl;

        return 0;
    }, nullptr, &err);

    if (rc != SQLITE_OK) {
        cerr << "Error selecting records:" << err << endl;
        sqlite3_free(err);
        sqlite3_close(db);
        return;
    }
}

void updateRecord(int &rc, sqlite3* &db, char* &err) {
    cout << "Enter user's name to update his age:";
    string name; cin >> name;
    cout << "Enter age:";
    string age; cin >> age;

    string updateSQL = "UPDATE users SET age = " + age + " WHERE name = '" + name + "';";
    rc = sqlite3_exec(db, updateSQL.c_str(), nullptr, nullptr, &err);

    if (rc != SQLITE_OK) {
        cerr << "Error updating record:" << err << endl;
        sqlite3_free(err);
        sqlite3_close(db);
        return;
    }
    else cout << "Record updated successfully" << endl;
}

void deleteRecord(int &rc, sqlite3* &db, char* &err) {
    cout << "Enter user's name to delete the records:" << endl;
    string name; cin >> name;

    string deleteSQL = "DELETE FROM users WHERE name = '" + name + "';";
    rc = sqlite3_exec(db, deleteSQL.c_str(), nullptr, nullptr, &err);

    if (rc != SQLITE_OK) {
        cerr << "Error deleting record:" << err << endl;
        sqlite3_free(err);
        sqlite3_close(db);
        return;
    }
    else cout << "Records were deleted successfully" << endl;
}

int main()
{
    sqlite3* db;
    char* err = nullptr;
    int rc = sqlite3_open("test.db", &db);

    if (rc) {
        cerr << "Error opening database:" << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return 1;
    }

    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS users ("
                                 "id INTEGER PRIMARY KEY,"
                                 "name TEXT NOT NULL,"
                                 "age INTEGER NOT NULL);";

    rc = sqlite3_exec(db, createTableSQL, nullptr, nullptr, &err);

    if (rc != SQLITE_OK) {
        cerr << "Error creating table:" << err << endl;
        sqlite3_free(err);
        sqlite3_close(db);
        return 1;
    }

    int q = 1;
    while (q) {
        cout << "Select an option: " << endl;
        cout << "1. Add record" << endl;
        cout << "2. View records" << endl;
        cout << "3. Update record" << endl;
        cout << "4. Delete record" << endl;
        cout << "0. Quit" << endl;
        cout << "Your option:";

        cin >> q;

        if (q == 1) addRecord(rc, db, err);
        else if (q == 2) viewRecords(rc, db, err);
        else if (q == 3) updateRecord(rc, db, err);
        else if (q == 4) deleteRecord(rc, db, err);
        else break;
    }

    sqlite3_close(db);
}
