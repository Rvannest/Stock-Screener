#include <stdio.h>
#include <sqlite3.h>

//Robert Vannest, Number: 110039175

static int callback(void* data, int argc, char** argv, char** ColName){
   
   for(int i = 0; i<argc; i++){
      printf("%s = %s\n", ColName[i], argv[i]);
   }
   
   return 0;
}

int main(int argc, char* argv[]) {
	
	sqlite3* db;
	int c;
	int question;
	
	c = sqlite3_open_v2("/home/vannestr/Desktop/StockTable1.db", &db, SQLITE_OPEN_READWRITE, NULL);
	
	if(c != SQLITE_OK) {
		printf("Can't open database! %s\n", sqlite3_errmsg(db));
		return(0);
		} else {
		printf("Connect to database successfully.\n");
		}		
	
	// code to open database goes here
	char* errMsg = 0;
	
	//create SQL statement
	char* sql = "CREATE TABLE Stock("\
	"Id INTEGER PRIMARY KEY AUTOINCREMENT,"\
	"CompanyName VARCHAR(255) NOT NULL,"\
	"MarketCap INT NULL,"\
	"ExDivDate VARCHAR(255) NULL,"\
	"CurrAssets INT NULL,"\
	"EnterpriseValue INT NULL,"\
	"Cash INT NULL,"\
	"CurrLiabilities INT NULL,"\
	"Revenue INT NULL,"\
	"GrossProfit INT NULL,"\
	"DivDate VARCHAR(255) NULL,"\
	"NetIncome INT NULL,"\
	"TotLiabilities INT NULL,"\
	"TotAssets INT NULL"\
");"\

	"CREATE TABLE NormalHolders("\
	"Id INTEGER PRIMARY KEY AUTOINCREMENT,"\
	"Name VARCHAR(255) NOT NULL"\
");"\

	"CREATE TABLE OutsideControl("\
	"Id INTEGER PRIMARY KEY AUTOINCREMENT,"\
	"QtrDivAmt INT NULL,"\
	"StockId INT NOT NULL,"\
	"NormalHoldersId INT NOT NULL,"\
	"CONSTRAINT FK_OutsideControl_StockId_2_Stock_Id FOREIGN KEY(StockId)"\
	"REFERENCES Stock(Id)"\
	"CONSTRAINT FK_OutsideControl_NormalHoldersId_2_NormalHolders_Id FOREIGN KEY(NormalHoldersId)"\
	"REFERENCES NormalHolders(Id)"\
");"\

	"CREATE TABLE CEO("\
	"Id INTEGER PRIMARY KEY AUTOINCREMENT,"\
	"Name VARCHAR(255) NOT NULL,"\
	"Salary INT NULL,"\
	"CONSTRAINT UK_Name UNIQUE(Name)"\
");"\

	"CREATE TABLE ExecManagement("\
	"Id INTEGER PRIMARY KEY AUTOINCREMENT,"\
	"Name VARCHAR(255) NOT NULL,"\
	"Position VARCHAR(255) NULL,"\
	"Salary INT NULL,"\
	"CEOId INT NOT NULL,"\
	"CONSTRAINT FK_ExecManagement_CEOId_2_CEO_Id FOREIGN KEY(CEOId)"\
	"REFERENCES CEO(Id)"\
");"\

	"CREATE TABLE InternalControl("\
	"Id INTEGER PRIMARY KEY AUTOINCREMENT,"\
	"Payment INT NULL,"\
	"StockId INT NOT NULL,"\
	"ExecManagementId INT NOT NULL,"\
	"CONSTRAINT FK_InternalControl_StockId_2_Stock_Id FOREIGN KEY(StockId)"\
	"REFERENCES Stock(Id)"\
	"CONSTRAINT FK_InternalControl_ExecManagementId_2_ExecManagement_Id FOREIGN KEY(ExecManagementId)"\
	"REFERENCES ExecManagement(Id)"\
");"\

	"CREATE TABLE BoardDirectors("\
	"Id INTEGER PRIMARY KEY AUTOINCREMENT,"\
	"Name VARCHAR(255) NOT NULL,"\
	"Salary INT NULL,"\
	"CEOId INT NOT NULL,"\
	"CONSTRAINT FK_BoardDirectors_CEOId_2_CEO_Id FOREIGN KEY(CEOId)"\
	"REFERENCES CEO(Id)"\
");"\

	"CREATE TABLE MajorityHolders("\
	"Id INTEGER PRIMARY KEY AUTOINCREMENT,"\
	"Name VARCHAR(255) NOT NULL,"\
	"ShareAmt INT NULL"\
");"\

	"CREATE TABLE MajorityControl("\
	"Id INTEGER PRIMARY KEY AUTOINCREMENT,"\
	"QtrDivAmt INT NULL,"\
	"MajorityHoldersId INT NOT NULL,"\
	"BoardDirectorsId INT NOT NULL,"\
	"CONSTRAINT FK_MajorityControl_MajorityHoldersId_2_MajorityHolders_Id FOREIGN KEY(MajorityHoldersId) REFERENCES MajorityHolders(Id)"\
	"CONSTRAINT FK_MajorityControl_BoardDirectorsId_2_BoardDirectors_Id FOREIGN KEY(BoardDirectorsId) REFERENCES BoardDirectors(Id)"\
");";

//(below create) execute sql statement
int r = sqlite3_exec(db, sql, NULL, 0, &errMsg);

if(r != SQLITE_OK ){
	printf("SQL error: %s\n", errMsg);
	sqlite3_free(errMsg);
}
else {
	printf("Table created successfully\n");
	}
	
sql = "INSERT INTO Stock(Id, CompanyName, CurrAssets, Cash, CurrLiabilities, Revenue, GrossProfit, NetIncome, TotLiabilities, TotAssets) VALUES (1, 'Apple Inc', 135405000, 48304000, 153982000, 90146000, 38095000, 20721000, 302083000, 352755000);"\
"INSERT INTO Stock(Id, CompanyName, CurrAssets, Cash, CurrLiabilities, Revenue, GrossProfit, NetIncome, TotLiabilities, TotAssets) VALUES (2, 'Microsoft Corporation', 160812000, 107244000, 87389000, 50122000, 34670000, 17556000, 186218000, 359784000);"\
"INSERT INTO Stock(Id, CompanyName, CurrAssets, Cash, CurrLiabilities, Revenue, GrossProfit, NetIncome, TotLiabilities, TotAssets) VALUES (3, 'Amazon.com Inc', 131463000, 58662000, 142266000, 469822000, 66315000, 33364000, 282304000, 420549000);"\
"INSERT INTO Stock(Id, CompanyName, CurrAssets, Cash, CurrLiabilities, Revenue, GrossProfit, NetIncome, TotLiabilities, TotAssets) VALUES (4, 'Alphabet Inc', 166109000, 116259000, 65979000, 257637000, 146698000, 76033000, 104629000, 358255000);"\
"INSERT INTO Stock(Id, CompanyName, CurrAssets, Cash, CurrLiabilities, Revenue, GrossProfit, NetIncome, TotLiabilities, TotAssets) VALUES (5, 'Tesla Inc', 35990000, 21107000, 24611000, 21454000, 5382000, 3292000, 33302000, 74426000);"\


"INSERT INTO NormalHolders(Id, Name) VALUES (1, 'jane');"\
"INSERT INTO NormalHolders(Id, Name) VALUES (2, 'joe');"\
"INSERT INTO NormalHolders(Id, Name) VALUES (3, 'rob');"\
"INSERT INTO NormalHolders(Id, Name) VALUES (4, 'chris');"\
"INSERT INTO NormalHolders(Id, Name) VALUES (5, 'james');"\

"INSERT INTO OutsideControl(Id, QtrDivAmt, StockId, NormalHoldersId) VALUES (1, 0.23, 1, 1);"\
"INSERT INTO OutsideControl(Id, QtrDivAmt, StockId, NormalHoldersId) VALUES (2, 0.68, 2, 2);"\
"INSERT INTO OutsideControl(Id, QtrDivAmt, StockId, NormalHoldersId) VALUES (3, NULL, 3, 3);"\
"INSERT INTO OutsideControl(Id, QtrDivAmt, StockId, NormalHoldersId) VALUES (4, NULL, 4, 4);"\
"INSERT INTO OutsideControl(Id, QtrDivAmt, StockId, NormalHoldersId) VALUES (5, NULL, 5, 5);"\

"INSERT INTO CEO(Id, Name) VALUES (1, 'Tim Cook');"\
"INSERT INTO CEO(Id, Name) VALUES (2, 'Satya Nadella');"\
"INSERT INTO CEO(Id, Name) VALUES (3, 'Andrew Jassy');"\
"INSERT INTO CEO(Id, Name) VALUES (4, 'Sundar Pichai');"\
"INSERT INTO CEO(Id, Name) VALUES (5, 'Elon Musk');"\

"INSERT INTO ExecManagement(Id, Name, Position, CEOId) VALUES (1, 'Luca Maestri', 'CFO', 1);"\
"INSERT INTO ExecManagement(Id, Name, Position, CEOId) VALUES (2, 'James Wilson', 'CTO', 1);"\
"INSERT INTO ExecManagement(Id, Name, Position, CEOId) VALUES (3, 'Mary Demby', 'CIO', 1);"\

"INSERT INTO ExecManagement(Id, Name, Position, CEOId) VALUES (4, 'Amy Hood', 'CFO', 2);"\
"INSERT INTO ExecManagement(Id, Name, Position, CEOId) VALUES (5, 'Bradford Smith', 'Vice Chairman', 2);"\
"INSERT INTO ExecManagement(Id, Name, Position, CEOId) VALUES (6, 'Judson Althoff', 'CCO', 2);"\

"INSERT INTO ExecManagement(Id, Name, Position, CEOId) VALUES (7, 'Brian Olsavsky', 'CFO', 3);"\
"INSERT INTO ExecManagement(Id, Name, Position, CEOId) VALUES (8, 'Werner Vogels', 'CTO', 3);"\
"INSERT INTO ExecManagement(Id, Name, Position, CEOId) VALUES (9, 'Adam Selipsky', 'CEO of AWS', 3);"\

"INSERT INTO ExecManagement(Id, Name, Position, CEOId) VALUES (10, 'Ruth Porat', 'CFO', 4);"\
"INSERT INTO ExecManagement(Id, Name, Position, CEOId) VALUES (11, 'Lawrence Page', 'Co-Founder/Director', 4);"\
"INSERT INTO ExecManagement(Id, Name, Position, CEOId) VALUES (12, 'Sergey Brin', 'Co-Founder/Director', 4);"\

"INSERT INTO ExecManagement(Id, Name, Position, CEOId) VALUES (13, 'Zachary Kirkhorn', 'CFO', 5);"\
"INSERT INTO ExecManagement(Id, Name, Position, CEOId) VALUES (14, 'Andrew Baglino', 'VP of Engineering', 5);"\
"INSERT INTO ExecManagement(Id, Name, Position, CEOId) VALUES (15, 'Vaibhav Taneja', 'CAO', 5);"\

"INSERT INTO InternalControl(Id, Payment, StockId, ExecManagementId) VALUES (1, 5020000, 1, 1);"\
"INSERT INTO InternalControl(Id, Payment, StockId, ExecManagementId) VALUES (2, 4000000, 1, 2);"\
"INSERT INTO InternalControl(Id, Payment, StockId, ExecManagementId) VALUES (3, 3000000, 1, 3);"\

"INSERT INTO InternalControl(Id, Payment, StockId, ExecManagementId) VALUES (4, 4640000, 2, 4);"\
"INSERT INTO InternalControl(Id, Payment, StockId, ExecManagementId) VALUES (5, 4660000, 2, 5);"\
"INSERT INTO InternalControl(Id, Payment, StockId, ExecManagementId) VALUES (6, 4430000, 2, 6);"\

"INSERT INTO InternalControl(Id, Payment, StockId, ExecManagementId) VALUES (7, 163000, 3, 7);"\
"INSERT INTO InternalControl(Id, Payment, StockId, ExecManagementId) VALUES (8, 150000, 3, 8);"\
"INSERT INTO InternalControl(Id, Payment, StockId, ExecManagementId) VALUES (9, 158000, 3, 9);"\

"INSERT INTO InternalControl(Id, Payment, StockId, ExecManagementId) VALUES (10, 667000, 4, 10);"\
"INSERT INTO InternalControl(Id, Payment, StockId, ExecManagementId) VALUES (11, 1, 4, 11);"\
"INSERT INTO InternalControl(Id, Payment, StockId, ExecManagementId) VALUES (12, 1, 4, 12);"\

"INSERT INTO InternalControl(Id, Payment, StockId, ExecManagementId) VALUES (13, 301000, 5, 13);"\
"INSERT INTO InternalControl(Id, Payment, StockId, ExecManagementId) VALUES (14, 301000, 5, 14);"\
"INSERT INTO InternalControl(Id, Payment, StockId, ExecManagementId) VALUES (15, 200000, 5, 15);"\

"INSERT INTO BoardDirectors(Id, Name, CEOId) VALUES (1, 'James Bell', 1);"\
"INSERT INTO BoardDirectors(Id, Name, CEOId) VALUES (2, 'Dina Dublon', 2);"\
"INSERT INTO BoardDirectors(Id, Name, CEOId) VALUES (3, 'Keith Alexander', 3);"\
"INSERT INTO BoardDirectors(Id, Name, CEOId) VALUES (4, 'Frances Arnold', 4);"\
"INSERT INTO BoardDirectors(Id, Name, CEOId) VALUES (5, 'Kimbal Musk', 5);"\

"INSERT INTO MajorityHolders(Id, Name) VALUES (1, 'Vanguard Group');"\
"INSERT INTO MajorityHolders(Id, Name) VALUES (2, 'Vanguard Group');"\
"INSERT INTO MajorityHolders(Id, Name) VALUES (3, 'Vanguard Group');"\
"INSERT INTO MajorityHolders(Id, Name) VALUES (4, 'Vanguard Group');"\
"INSERT INTO MajorityHolders(Id, Name) VALUES (5, 'Vanguard Group');"\

"INSERT INTO MajorityControl(Id, QtrDivAmt, MajorityHoldersId, BoardDirectorsId) VALUES (1, 0.23, 1, 1);"\
"INSERT INTO MajorityControl(Id, QtrDivAmt, MajorityHoldersId, BoardDirectorsId) VALUES (2, 0.68, 2, 2);"\
"INSERT INTO MajorityControl(Id, QtrDivAmt, MajorityHoldersId, BoardDirectorsId) VALUES (3, NULL, 3, 3);"\
"INSERT INTO MajorityControl(Id, QtrDivAmt, MajorityHoldersId, BoardDirectorsId) VALUES (4, NULL, 4, 4);"\
"INSERT INTO MajorityControl(Id, QtrDivAmt, MajorityHoldersId, BoardDirectorsId) VALUES (5, NULL, 5, 5);";

//(below insert) execute sql statement
r = sqlite3_exec(db, sql, NULL, 0, &errMsg);

if( r != SQLITE_OK ){
	printf("SQL error: %s\n", errMsg);
	sqlite3_free(errMsg);
	}
	else {
	printf("Stock inserted successfully\n");
	}

  sql = "SELECT * from Stock";

  //(below select)
  r = sqlite3_exec(db, sql, callback, 0, &errMsg);
 
  if( r != SQLITE_OK ){
    printf("SQL error: %s\n", errMsg);
    sqlite3_free(errMsg);
  }
  else {
    printf("Stocks are retrieved successfully\n");
    sqlite3_free(errMsg);
  }
  
  //questions
  printf("\n");
  printf("Welcome to the Stock Screener application\n");
  printf("0) Exit\n");
  printf("1) List of Stock/Company Names\n");
  printf("2) List of CEOs\n");
  printf("3) List of Executives Managers\n");
  printf("4) List of Board of Directors\n");
  printf("5) Find the executives for Apple Inc\n");
  printf("6) Executives pay for Apple Inc\n");
  printf("7) Quarterly Dividend Amount for Apple Inc\n");
  printf("8) Current Maximum pay for all executives\n");
  printf("9) Average pay for Microsoft Corporation executives\n");
  printf("10) Delete a Stock from the database (Identify it by its Stock/Company Names)\n");
  
  //accept the number
  scanf("%d", &question);
  
  //case switch
  switch (question){
	default:
	printf("Pick a valid number again\n");
	break;
  
	case 0:
	sqlite3_close(db);
	return 0;
	break;
  
	case 1:
	sql = "SELECT CompanyName from Stock";

	r = sqlite3_exec(db, sql, callback, 0, &errMsg);
	 
	if( r != SQLITE_OK ){
	printf("SQL error: %s\n", errMsg);
	sqlite3_free(errMsg);
	}
	else {
	printf("Stocks/Company Names are retrieved successfully\n");
	sqlite3_free(errMsg);
	}
	break;
	  
	case 2:
	sql = "SELECT Name from CEO";

	r = sqlite3_exec(db, sql, callback, 0, &errMsg);
	 
	if( r != SQLITE_OK ){
	printf("SQL error: %s\n", errMsg);
	sqlite3_free(errMsg);
	}
	else {
	printf("CEOs retrieved successfully\n");
	sqlite3_free(errMsg);
	}
	break;
	  
	case 3:
	sql = "SELECT Name from ExecManagement";

	r = sqlite3_exec(db, sql, callback, 0, &errMsg);
	 
	if( r != SQLITE_OK ){
	printf("SQL error: %s\n", errMsg);
	sqlite3_free(errMsg);
	}
	else {
	printf("Executive Managers retrieved successfully\n");
	sqlite3_free(errMsg);
	}
	break;
	  
	case 4:
	sql = "SELECT Name from BoardDirectors";

	r = sqlite3_exec(db, sql, callback, 0, &errMsg);
	 
	if( r != SQLITE_OK ){
	printf("SQL error: %s\n", errMsg);
	sqlite3_free(errMsg);
	}
	else {
	printf("Board of directors retrieved successfully\n");
	sqlite3_free(errMsg);
	}
	break;
	  
	case 5:
	sql = "SELECT Name FROM ExecManagement WHERE CEOId = 1";

	r = sqlite3_exec(db, sql, callback, 0, &errMsg);
	 
	if( r != SQLITE_OK ){
	printf("SQL error: %s\n", errMsg);
	sqlite3_free(errMsg);
	}
	else {
	printf("Apple Inc Executives\n");
	sqlite3_free(errMsg);
	}
	break;
	  
	case 6:
	sql = "SELECT Payment FROM InternalControl WHERE StockId = 1";

	r = sqlite3_exec(db, sql, callback, 0, &errMsg);
	 
	if( r != SQLITE_OK ){
	printf("SQL error: %s\n", errMsg);
	sqlite3_free(errMsg);
	}
	else {
	printf("Apple Inc Executives Salary\n");
	sqlite3_free(errMsg);
	}
	break;
	  
	case 7:
	sql = "SELECT QtrDivAmt FROM OutsideControl WHERE StockId = 1";

	r = sqlite3_exec(db, sql, callback, 0, &errMsg);
	 
	if( r != SQLITE_OK ){
	printf("SQL error: %s\n", errMsg);
	sqlite3_free(errMsg);
	}
	else {
	printf("Apple Inc Quarterly Dividend\n");
	sqlite3_free(errMsg);
	}
	break;
	  
	case 8:
	sql = "SELECT MAX(Payment) FROM InternalControl";

	r = sqlite3_exec(db, sql, callback, 0, &errMsg);
	 
	if( r != SQLITE_OK ){
	printf("SQL error: %s\n", errMsg);
	sqlite3_free(errMsg);
	}
	else {
	printf("Current maximum pay from all executives\n");
	sqlite3_free(errMsg);
	}
	break;
	  
	case 9:
	sql = "SELECT AVG(Payment) FROM InternalControl WHERE StockId = 2";

	r = sqlite3_exec(db, sql, callback, 0, &errMsg);
	 
	if( r != SQLITE_OK ){
	printf("SQL error: %s\n", errMsg);
	sqlite3_free(errMsg);
	}
	else {
	printf("Average pay for Microsoft Executives\n");
	sqlite3_free(errMsg);
	}
	break;
	  
	case 10:
	char sql[500];
	char name[40];

	printf("\n");
	printf("Name of the Stock to delete\n");
	scanf(" %[^\n]s",name);
	
	sprintf(sql, "DELETE FROM Stock WHERE CompanyName = '%s';",name) ;

      	r = sqlite3_exec(db, sql, callback, 0, &errMsg);
 
      	if( r != SQLITE_OK ){
        printf("SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
      	} 
      	else {
        printf("\n");
        printf("Here's the new Stock list\n");
        printf("--------------------------------------\n");
        sqlite3_free(errMsg);
  	}
  	//Create SQL statement SELECT
      	sprintf (sql, "SELECT CompanyName from Stock");

      	//execute SQL statement SELECT
      	r = sqlite3_exec(db, sql, callback, 0, &errMsg);
 
     	if( r != SQLITE_OK ){
        printf("SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
      	} 
      	else {
        printf("Retrieved\n");
        sqlite3_free(errMsg);
      	}

    	break;
  	
  //bracket for case switch
  }
  
  }
  
