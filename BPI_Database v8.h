******************************************************************
**	Database v7.h Include										**
**	Copyright © 2003-2010 by Imagine That, Inc.					**
**	All rights reserved.										**
**	Created by Anthony Nastasi									**
******************************************************************



******************************************************************
** Created 2003
**	Modified:
**	Date	Release		By			Description
**
******************************************************************
//v7 Database Include File


//constants
//db constants
constant PARENT_TABLE is 0;
constant PARENT_FIELD is 1;
constant PARENT_RECORD is 2;



//*****************************************************************************************************
//*****************************************************************************************************
//START DATABASE FUNCTIONS
//*****************************************************************************************************



//called in open model and checkdata.  use the chosen table name to get 
//the current table index and to verify that this table still exists.
integer DB_ValidateDatabaseName(string databaseName)
{
	
	integer databaseIndex;
	
	databaseIndex = DBDatabaseGetIndex(databaseName);
	
	if(databaseIndex == 0)
		UserError("The database " + databaseName + "that has been specified in block number " + MyBlockNumber() + " could not be found.");
	
	return(databaseIndex);

}//integer DB_ValidateDatabaseName(string63 tableName)


//WARNING!!  Make sure to call MakeArray() on tableNamesArray BEFORE calling this function!!
//This is because MakeArray() cannot be called on an array that has been passed by reference.
integer DB_GetDatabaseNames(string63 databaseNamesArray[])
{

	integer i, j;
	integer numDatabases;
	string databaseName;
	
	//build up tableNamesArray by filtering out those table indexes that are not being used
	j = 0;
	numDatabases = DBDatabasesGetNum();
	for(i=1; i<=numDatabases; i++)
		{
		databaseName = DBDatabaseGetName(i);
		if(databaseName != "")
			{
			databaseNamesArray[j] = databaseName;
			j++;
			}
		}
		
	return(numDatabases);

}//procedure DB_GetTableNames(string63 tableNamesArray[])


integer DB_GetNumDatabases()
{

	integer i;
	integer numDatabaseSlots;
	integer numDatabases;
	string63 nextName;
	
	numDatabaseSlots = DBDatabasesGetNum();
	numDatabases = 0;
	
	for(i=1; i<=numDatabaseSlots; i++)
		{
		nextName = DBDatabaseGetName(i);
		if(nextName != ""  &&  StrFind(nextName, "_", FALSE, FALSE) != 0)
			numDatabases++;
		}
	
	return(numDatabases);

}//integer DB_GetNumDatabases()




//*****************************************************************************************************
//*****************************************************************************************************
//END DATABASE FUNCTIONS
//*****************************************************************************************************






//*****************************************************************************************************
//*****************************************************************************************************
//START TABLE FUNCTIONS
//*****************************************************************************************************


//WARNING!!  Make sure to call MakeArray() on tableNamesArray BEFORE calling this function!!
//This is because MakeArray() cannot be called on an array that has been passed by reference.
integer DB_GetTableNames(integer databaseIndex, string63 tableNamesArray[])
{

	integer i, j;	integer numTables;
	string tableName;
	
	//build up tableNamesArray by filtering out those table indexes that are not being used
	j = 0;
	numTables = DBTablesGetNum(databaseIndex);
	for(i=1; i<=numTables; i++)
		{
		tableName = DBTableGetName(databaseIndex, i);
		if(tableName != "")
			{
			tableNamesArray[j] = tableName;
			j++;
			}
		}
		
	return(numTables);

}//procedure DB_GetTableNames(string63 tableNamesArray[])


//called in open model and checkdata.  use the chosen table name to get 
//the current table index and to verify that this table still exists.
integer DB_ValidateTableName(string databaseName, string tableName)
{
	
	integer databaseIndex;	
	integer tableIndex;
	
	databaseIndex = DB_ValidateDatabaseName(databaseName);
	tableIndex = DBTableGetIndex(databaseIndex, tableName);
	if(tableIndex == 0)
		UserError("The table " + tableName + "that has been specified in block number " + MyBlockNumber() + " does not exist.  Please choose a table.");
	
	return(tableIndex);

}//integer DB_ValidateTableName(string63 tableName)


integer DB_GetNumTables(integer dbIndex)
{

	integer i;
	integer numTableSlots;
	integer numTables;
	string63 nextName;
	
	numTableSlots = DBTablesGetNum(dbIndex);
	numTables = 0;
	
	for(i=1; i<=numTableSlots; i++)
		{
		nextName = DBTableGetName(dbIndex, i);
		if(nextName != "")
			numTables++;
		}
	
	return(numTables);

}//integer DB_GetNumTables()



//*****************************************************************************************************
//END TABLE FUNCTIONS
//*****************************************************************************************************
//*****************************************************************************************************





//*****************************************************************************************************
//START FIELD FUNCTIONS
//*****************************************************************************************************
//*****************************************************************************************************


//WARNING!!  Make sure to call MakeArray() on fieldNamesArray BEFORE calling this function!!
//This is because MakeArray() cannot be called on an array that has been passed by reference.
integer DB_GetFieldNames(integer databaseIndex, integer tableIndex, string63 fieldNamesArray[])
{

	integer i, j;
	integer numFields;
	string fieldName;
	
	//build up fieldNamesArray by filtering out those table indexes that are not being used
	j = 0;
	numFields = DBFieldsGetNum(databaseIndex, tableIndex);
	for(i=1; i<=numFields; i++)
		{
		fieldName = DBFieldGetName(databaseIndex, tableIndex, i);
		if(fieldName != "")
			{
			fieldNamesArray[j] = fieldName;
			j++;
			}
		}
		
	return(numFields);

}//procedure DB_GetFieldNames(integer tableIndex, string63 fieldNamesArray[])



//called in open model and checkdata.  use the chosen field name to get 
//the current field index and to verify that this field still exists.
integer DB_ValidateFieldName(string databaseName, string tableName, string fieldName)
{

	integer databaseIndex;
	integer tableIndex;
	integer fieldIndex;
	
	databaseIndex = DB_ValidateDatabaseName(databaseName);
	tableIndex = DB_ValidateTableName(databaseName, tableName);
	fieldIndex = DBFieldGetIndex(databaseIndex, tableIndex, fieldName);

	if(fieldIndex == 0)
		UserError("The field " + fieldName + "that has been specified in block number " + MyBlockNumber() + " does not exist.  Please choose a field.");

	return(fieldIndex);

}//integer DB_ValidateFieldName(string63 tableName, string63 fieldName)



//*****************************************************************************************************
//END FIELD FUNCTIONS
//*****************************************************************************************************
//*****************************************************************************************************






//*****************************************************************************************************
//*****************************************************************************************************
//START RECORD FUNCTIONS
//*****************************************************************************************************



//WARNING!!  Make sure to call MakeArray() on cellContentsArray BEFORE calling this function!!
//This is because MakeArray() cannot be called on an array that has been passed by reference.
integer DB_GetCellContents(integer databaseIndex, integer tableIndex, integer fieldIndex, string cellContentsArray[])
{

	integer i;
	integer numRecords;
	string recordName;
	
	//build up fieldNamesArray by filtering out those table indexes that are not being used
	numRecords = DBRecordsGetNum(databaseIndex, tableIndex);
	for(i=1; i<=numRecords; i++)
		{
		recordName = DBDataGetAsString(databaseIndex, tableIndex, fieldIndex, i);
		cellContentsArray[i-1] = i + " : " + recordName;
		}
		
	return(numRecords);

}//procedure DB_GetCellContents(integer tableIndex, string fieldNamesArray[])



//called in open model and checkdata to verify that the chosen record index is 
//not greater than the total number of records in the selected table.
integer DB_ValidateRecordIndex(string databaseName, string tableName, integer whichRecord)
{

	integer databaseIndex;
	integer tableIndex;
	integer totalRecords;
	integer recordIsInBounds;
	
	databaseIndex = DB_ValidateDatabaseName(databaseName);
	tableIndex = DB_ValidateTableName(databaseName, tableName);
	totalRecords = DBRecordsGetNum(databaseIndex, tableIndex);
	if(totalRecords < whichRecord)
		{
		recordIsInBounds = FALSE;
		UserError("The record that has been chosen in block number " + MyBlockNumber() + " does not exist.  Please choose a record.");
		}
	else
		recordIsInBounds = TRUE;
		
	return(recordIsInBounds);

}//procedure DB_ValidateRecordIndex(string63 tableName, integer whichRecord)



//*****************************************************************************************************
//END RECORD FUNCTIONS
//*****************************************************************************************************
//*****************************************************************************************************










