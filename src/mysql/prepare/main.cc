/* Copyright 2008, 2010, Oracle and/or its affiliates.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; version 2 of the License.

There are special exceptions to the terms and conditions of the GPL
as it is applied to this software. View the full text of the
exception in file EXCEPTIONS-CONNECTOR-C++ in the directory of this
software distribution.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

/* Standard C++ includes */
#include <cstdlib>
#include <iostream>

/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

int main() {
    cout << endl;
    cout << "Let's have MySQL count from 10 to 1..." << endl;

    try {
        sql::Driver *driver;

        /* Create a connection */
        driver = get_driver_instance();
        std::unique_ptr<sql::Connection> con(driver->connect("tcp://127.0.0.1:3306", "root", "123"));
        /* Connect to the MySQL test database */
        con->setSchema("menagerie");

        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        stmt->execute("DROP TABLE IF EXISTS test");
        stmt->execute("CREATE TABLE test(id INT)");

        /* '?' is the supported placeholder syntax */
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO test(id) VALUES (?)"));
        for (int i = 1; i <= 10; i++) {
            pstmt->setInt(1, i);
            pstmt->executeUpdate();
        }

        /* Select in ascending order */
        pstmt.reset(con->prepareStatement("SELECT id FROM test ORDER BY id ASC"));
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        /* Fetch in reverse = descending order! */
        res->afterLast();
        while (res->previous())
            cout << "\t... MySQL counts: " << res->getInt("id") << endl;


    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

    cout << endl;

    return EXIT_SUCCESS;
}