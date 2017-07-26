String gs_DBName;
String gs_DBTblName;
String gs_XLSheetName;

******************************************************************************************************************************************
// user messages to call import export block to work
******************************************************************************************************************************************
procedure SetupWorksheet(string worksheetName,
						 integer runNum);
#ifdef XLDBADONewName_txt
on UserMsg1
{
	// set selected excel sheet name
	DisposeArray(SheetNames);
	MakeArray(SheetNames,1);
	SheetNames[0] = gs_XLSheetName;
	XLDBADONewName_txt = gs_XLSheetName;
	
	// set selected DB name
	DisposeArray(DB_DatabaseName);
	MakeArray(DB_DatabaseName,1);
	DB_DatabaseName[0] = gs_DBName;
	SetPopupLabels("XD_DatabaseName_pop", gs_DBName);
	
	// set selected DB table name
	if (XD_TableName_prm == BLANK) XD_TableName_prm = DBTableGetName(DBIndex_prm, XD_TableIndex_prm);
	DB_TableName[0] = XD_TableName_prm;
	
	// set excel range for import/export
	XLRangeInputType_lbl = GetDialogItemLabel(myBlockNumber(), "XLRangeInputType_POP", XLRangeInputType_POP);
	OldRangeValues[0] = XLStartRow;
	OldRangeValues[1] = XLEndRow;
	OldRangeValues[2] =	XLStartCol;
	OldRangeValues[3] =	XLEndCol;
}

on UserMsg2
{
	DisposeArray(DB_DatabaseName);
	MakeArray(DB_DatabaseName,1);
	DB_DatabaseName[0] = "ODBC Exchange";
	
	SetPopupLabels("XD_DatabaseName_pop", "ODBC Exchange");
	
	DisposeArray(db_username_array);
	DisposeArray(db_password_array);
	
	MakeArray(db_username_array, 1);
	MakeArray(db_password_array, 1);
	
	db_username_array[0] = "o_dsnBlueP";
	db_password_array[0] = "d@1@f3nR3nN0w";
	
	SetDialogVariable(MyBlockNumber(), "ADO_WhichDatabase_pop", 3, 0, 0);
}
#endif


Procedure ODBCSyncStatus(long NumFields)
{
	// insert this procedure in ADO_DBFunctions v9.h, procedure ADO_exportDatabase, line 1437
	if (NumFields < 0)
	{
		UserError("SQL Server updated successfully.");
		ABORT;
	}
}
******************************************************************************************************************************************

