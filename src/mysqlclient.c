#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <mysql.h>

int main(void)
{
  if (mysql_library_init(0, NULL, NULL))
    {
      fprintf(stderr, "could not initialize MySQL client library\n");
      exit(1);
    }
  else
    fprintf(stdout, "MySQL client library initialized!\n");

  MYSQL mysql_hdl;
  mysql_init(&mysql_hdl);
  if (!mysql_real_connect(&mysql_hdl,
                          "localhost", /* host */
                          "rcoscali", "password",  /* user & pwd */
                          "dst",       /* database */
                          0,           /* port */
                          NULL,        /* unix socket */
                          0            /* client flag */
                          ))
    {
      fprintf(stderr,
              "Failed to connect to database: Error: %s\n",
              mysql_error(&mysql_hdl));
    }
  else
    fprintf(stdout, "Connection successful!\n");

  /*
   * First statement: count rows in customer table
   */
  MYSQL_STMT *stmt = mysql_stmt_init(&mysql_hdl);
  MYSQL_BIND bind;
  unsigned long rows;
  my_bool error;

  char* stmtstr = "select COUNT(*) from customer";
  mysql_stmt_prepare(stmt, stmtstr, strlen(stmtstr));
  mysql_stmt_execute(stmt);

  memset(&bind, 0, sizeof(bind));
  bind.buffer_type = MYSQL_TYPE_LONG;
  bind.buffer = (unsigned long*)&rows;
  bind.error = &error; 
  
  mysql_stmt_bind_result(stmt, &bind);
  
  mysql_stmt_fetch(stmt);
  
  fprintf(stdout, "Number of lines in customer table = %ld\n", rows);

  mysql_stmt_close(stmt);
  
  char* stmt2str = "SELECT lastname, firstname, city, zipcode, active FROM customer WHERE firstname='Lisa' ORDER BY zipcode";
  mysql_query(&mysql_hdl, stmt2str);
  MYSQL_RES* query_result = mysql_store_result(&mysql_hdl);
  int column_count = mysql_num_fields(query_result);
 
  fprintf(stdout,
          "total columns in SELECT statement: %d\n",
          column_count);
  
  if (column_count != 5) /* validate column count */
    {
      fprintf(stderr, " invalid column count returned by MySQL\n");
      exit(0);
    }

  fprintf(stdout,   "+===============================+================================+==============+==========+\n");
  fprintf(stdout,   "| %s\n", stmt2str);
  fprintf(stdout,   "+===============================+================================+==============+==========+\n");
  MYSQL_ROW row;
  while((row = mysql_fetch_row(query_result)))
    fprintf(stdout, "|name:%-5s %-12s\t|city:%-27s|zipcode:%5d\t|active:%s|\n", row[1], row[0], row[2], atoi(row[3]), atoi(row[4]) ? "YES" : "NO");
  fprintf(stdout,   "+===============================+================================+==============+==========+\n");
  
  /*
   * Disconnect & terminate
   */
  mysql_close(&mysql_hdl);
  fprintf(stdout, "Connection closed!\n");
  mysql_library_end();
  fprintf(stdout, "Library terminated!\n");

  return EXIT_SUCCESS;
