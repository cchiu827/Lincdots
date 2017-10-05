integer ExcelApp;		// DispID for the Excel application
integer WorkBooks;		// DispID for the workbooks
integer WorkSheets;		// DispID for the worhSheets
integer Worksheet;		// DispID for a specific workbook
integer workbook;
integer range;
//String	SheetNames[];
string SheetNames;
long DBTblIdx_ImportExportSetup;

Constant	_EXCEL_APPLICATION_WORKBOOKS	is	572;
Constant	_EXCEL_APPLICATION_WORKSHEETS	is	494;
Constant	_EXCEL_WORKBOOKS_COUNT	is	118;
Constant	_EXCEL_WORKBOOKS_ITEM	is	170;
Constant	_EXCEL_APPLICATION_APPLICATION	is	148;
Constant	_EXCEL_WORKSHEETS_COUNT	is	118;
Constant	_EXCEL_WORKSHEETS_ITEM	is	170;

integer GetWorkBooks(integer ExcelApp);
integer FindWorkbook(string Thisworkbook, integer abortIfNotFound);
procedure GetWorksheets();
Procedure CleanupExcel();
integer SetupExcel(String ThisWorkbook);
string array_DropDownMenu[];


Procedure DeleteTableItems(String ls_SelectedTable, long li_DBTblIdx);

******************************************************************************************************************************************
// functions for excel sheet selection
******************************************************************************************************************************************
#ifdef FileName_txt
Procedure OpenBrowseFile()
{
	integer error,blankname,opened;

	if (!FileIsOpen(FileName_txt))			
	{
		if( FileName_txt == "")
		{
			blankname = 1;
		}	
		else if( FileName_txt != "" )					
		{
			blankname = 0;
			if( !fileExists(FileName_txt) )				// if file does not exist
			{
				userError("FileName_txt "+(FileName_txt)+" used in "+BlockName(MyBlockNumber())+" block number "
				+MyBlockNumber()+" does not exist or is not in the current folder. Please locate the input file.");
				FileName_txt="";
				blankname = 1;
				CleanupExcel();
				abort;
			}
		}	
		error = IPCOpenFile(FileName_txt);
		if (error == 1)
		{
			userError("FileName_txt "+(FileName_txt)+"used in Data Receive block number "+MyBlockNumber()+" could not be opened.");
			CleanupExcel();
		}
		if (!error)
		{
			if (blankname)
			{
				if (gi_DontStrip == FALSE) FileName_txt = StripPathIfLocal(IPCGetDocName());
				else if (gi_DontStrip == TRUE) FileName_txt = IPCGetDocName();
			}
		}
	}
}
#endif

Procedure ExcelSheetDropdownMenu(String ls_DialogClicked, string FileName)
{
	integer workbookItem;
	integer NumWorksheets;
	String ThisWorkbook;
	
	// Check File Name
	if(FileName == "")
	{
		UserError("You must select a workbook before you can select a worksheet. Error found in "+BlockName(MyBLockNumber())+" number " +MyBlockNumber());
		abort;
	}
		
	else if (!FileExists(FileName))
	{
		UserError("Can not find workbook, please select an existing workbook. Error found in "+BlockName(MyBLockNumber())+" number " +MyBlockNumber());
		abort;
	}
		
	else if (!FileIsOpen(FileName))
	{
		UserError("The workbook needs to be opened before a worksheet can be selected. Error found in "+BlockName(MyBLockNumber())+" number " +MyBlockNumber());
		abort;
	}

	ThisWorkbook = FileNameFromPathname(FileName);
	
	// cleanup excel
	CleanupExcel();
		// setup excel
	WorkbookItem = SetupExcel(ThisWorkbook);
	
	// setup dropdown menu
	OLEDispatchPropertyGet(worksheets, _EXCEL_WORKSHEETS_COUNT);
	NumWorksheets = OleLongResult();
		
	SetPopupLabels(ls_DialogClicked, "");
	for(i=1; i<=NumWorksheets; i++)
	{
		OLELongParam(i);
		OLEDispatchPropertyGet(worksheets, _EXCEL_WORKSHEETS_ITEM);
		worksheet  = OLEDispatchResult();
		OLEDispatchPropertyGet(worksheet, 110);
		AppendPopupLabels(ls_DialogClicked, OLEStringResult()+";");
			if(Worksheet != 0)
		{
			OLERelease(Worksheet);
			worksheet = 0;
		}
	}
		
	// cleanup excel
	CleanupExcel();
}

String ExcelSheetDropdownMenuInTable(String ls_DialogClicked, string FileName)
{
	integer workbookItem;
	integer NumWorksheets;
	String ThisWorkbook;
	long li_UserResponse;
	
	// Check File Name
	if(FileName == "")
	{
		UserError("You must select a workbook before you can select a worksheet. Error found in "+BlockName(MyBLockNumber())+" number " +MyBlockNumber());
		abort;
	}
		
	else if (!FileExists(FileName))
	{
		UserError("Can not find workbook, please select an existing workbook. Error found in "+BlockName(MyBLockNumber())+" number " +MyBlockNumber());
		abort;
	}
		
	else if (!FileIsOpen(FileName))
	{
		UserError("The workbook needs to be opened before a worksheet can be selected. Error found in "+BlockName(MyBLockNumber())+" number " +MyBlockNumber());
		abort;
	}

	ThisWorkbook = FileNameFromPathname(FileName);
	
	// cleanup excel
	CleanupExcel();
		// setup excel
	WorkbookItem = SetupExcel(ThisWorkbook);
	
	// setup dropdown menu
	OLEDispatchPropertyGet(worksheets, _EXCEL_WORKSHEETS_COUNT);
	NumWorksheets = OleLongResult();
		
	DisposeArray(array_DropDownMenu);
	MakeArray(array_DropDownMenu, NumWorksheets);

	for(i=1; i<=NumWorksheets; i++)
	{
		OLELongParam(i);
		OLEDispatchPropertyGet(worksheets, _EXCEL_WORKSHEETS_ITEM);
		worksheet  = OLEDispatchResult();
		OLEDispatchPropertyGet(worksheet, 110);
		
		array_DropDownMenu[i-1] = OLEStringResult();
		
//		AppendPopupLabels(ls_DialogClicked, OLEStringResult()+";");
		
		if(Worksheet != 0)
		{
			OLERelease(Worksheet);
			worksheet = 0;
		}
	}
		
	// cleanup excel
	CleanupExcel();
	
	li_UserResponse = PopupMenuArray(array_DropdownMenu, 0) - 1;
	
	if (li_UserResponse >= 0)
	{
		Return(array_DropDownMenu[li_UserResponse]);
	}
	
	else Return(BLANK);
}

#ifdef Filename_txt 
#ifdef XLDBSelectWhich_pop
Procedure AfterXLSheetWhich()
{
	integer NumWorksheets;	// number of worksheets in a workbook
	integer NumWorkbooks;
	string ThisWorkbook;
	integer workbookitem;
	string SheetName;
	long li_DBIdx;
	
	li_DBIdx = DBDatabaseGetIndex("Data Exchange");

	CleanUpExcel();												// make sure nothing is left behind

	workbookitem = SetupExcel(FileNameFromPathname(Filename_txt));			// get the DispID's for Excel
	
	OLEDispatchPropertyGet(worksheets, _EXCEL_WORKSHEETS_COUNT);	// get the numbber ofworksheets in this workbook
	NumWorksheets = OleLongResult();

	if (XLDBSelectWhich_pop <= NumWorksheets AND XLDBSelectWhich_pop > 0)
	{
		OLELongParam(XLDBSelectWhich_pop);									// specify the worksheet
		OLEDispatchPropertyGet(worksheets, _EXCEL_WORKSHEETS_ITEM);	
		worksheet  = OLEDispatchResult();
		OLEDispatchPropertyGet(worksheet, 110);						// get the name of the worksheet
//		MakeArray(SheetNames,1);
		SheetNames = OLEStringResult();

		DBTblIdx_ImportExportSetup = DBTableGetIndex(li_DBIdx, "00_ImportExportSetup");
				
		DBDataSetAsString(li_DBIdx, DBTblIdx_ImportExportSetup, 2, 1, SheetNames);
	}

	else Abort;

	CleanUpExcel();
}
#endif
#endif

******************************************************************************************************************************************
// functions for import manager function
******************************************************************************************************************************************
Procedure SendRequestToImportExportBlock(string ls_ImportExport)
{
	Integer li_ImportExport;
	Integer li_ExDataType;
	Integer li_DataSource;
	Integer li_DataBaseIdx;
	Integer li_DBTableIdx;
	string ls_DBTableName;
	string ls_FileName;
	Integer li_XLRange_chk;
	Integer li_XLStartRow;
	Integer li_XLEndRow;
	Integer li_XLStartCol;
	Integer li_XLEndCol;
	string ls_XLTabName;
	long li_NumOfRows;
	string ls_DBTblName;
	long li_DBTblIdx;
	long li_DBIdx;
	long li_ImportExportBlockNum;
	string ls_DBName;
	
	if (ls_ImportExport == "Import") {li_ImportExport = 1; ls_DBTblName = "00_ImportManager";}
	else if (ls_ImportExport == "Export") {li_ImportExport = 2; ls_DBTblName = "00_ExportManager";}
	
	li_DBIdx = DBDatabaseGetIndex("Data Exchange");
	li_DBTblIdx = DBTableGetIndex(li_DBIdx, ls_DBTblName);
	li_NumOfRows = DBRecordsGetNum(li_DBIdx, li_DBTblIdx);
	DBTblIdx_ImportExportSetup = DBTableGetIndex(li_DBIdx, "00_ImportExportSetup");
	
	li_ImportExportBlockNum = DBDataGetAsNumber(li_DBIdx, DBTblIdx_ImportExportSetup, 2, 2);
	
	li_ExDataType = 1;
	li_DataSource = 1;
	
	SetDialogVariableNoMsg(li_ImportExportBlockNum, "ImportExport_pop", li_ImportExport, 0, 0);
	SetDialogVariableNoMsg(li_ImportExportBlockNum, "ExternalDataType_pop", li_ExDataType, 0, 0);
	SetDialogVariableNoMsg(li_ImportExportBlockNum, "DataSource_pop", li_DataSource, 0, 0);
	
	for (i = 1; i <= li_NumOfRows; i++)
	{
		if (DBDataGetAsNumber(li_DBIdx, li_DBTblIdx, 1, i) == TRUE)
		{
			ls_DBName = DBDataGetAsString(li_DBIdx, li_DBTblIdx, 2, i);
			li_DataBaseIdx = DBDataGetAsNumber(li_DBIdx, li_DBTblIdx, 3, i);
			li_DBTableIdx = DBDataGetAsNumber(li_DBIdx, li_DBTblIdx, 5, i);
			ls_DBTableName = DBDataGetAsString(li_DBIdx, li_DBTblIdx, 4, i);
			ls_FileName = DBDataGetAsString(li_DBIdx, li_DBTblIdx, 6, i);
			ls_XLTabName = DBDataGetAsString(li_DBIdx, li_DBTblIdx, 7, i);
			li_XLStartRow = DBDataGetAsNumber(li_DBIdx, li_DBTblIdx, 8, i);
			li_XLEndRow = DBDataGetAsNumber(li_DBIdx, li_DBTblIdx, 9, i);
			li_XLStartCol = DBDataGetAsNumber(li_DBIdx, li_DBTblIdx, 10, i);
			li_XLEndCol = DBDataGetAsNumber(li_DBIdx, li_DBTblIdx, 11, i);
			
			if (li_XLStartRow > 0 AND li_XLStartCol > 0)
			{
				li_XLRange_chk = TRUE;
			}
			
			else li_XLRange_chk = FALSE;
			
//			DBTblIdx_ImportExportSetup = DBTableGetIndex(li_DBIdx, "00_ImportExportSetup");
//			DBDataSetAsString(li_DBIdx, DBTblIdx_ImportExportSetup, 2, 1, ls_XLTabName);
			
			SetDialogVariableNoMsg(li_ImportExportBlockNum, "DBIndex_prm", li_DataBaseIdx, 0, 0);
			SetDialogVariableNoMsg(li_ImportExportBlockNum, "gs_DBName", ls_DBName, 1, 1);
			SetDialogVariableNoMsg(li_ImportExportBlockNum, "gs_XLSheetName", ls_XLTabName, 0, 0);
			SetDialogVariableNoMsg(li_ImportExportBlockNum, "XD_tableIndex_prm", li_DBTableIdx, 0, 0);
			SetDialogVariableNoMsg(li_ImportExportBlockNum, "XD_TableName_prm", ls_DBTableName, 0, 0);
			SetDialogVariableNoMsg(li_ImportExportBlockNum, "FileName_txt", ls_FileName, 0, 0);
			SetDialogVariableNoMsg(li_ImportExportBlockNum, "XLRangeInputType_POP", li_XLRange_chk+1, 0, 0);
			
			if (li_XLStartRow < 1) SetDialogVariableNoMsg(li_ImportExportBlockNum, "XLStartRow", BLANK, 0, 0);
			else SetDialogVariableNoMsg(li_ImportExportBlockNum, "XLStartRow", li_XLStartRow, 0, 0);
			
			if (li_XLStartCol < 1) SetDialogVariableNoMsg(li_ImportExportBlockNum, "XLStartCol", BLANk, 0, 0);
			else SetDialogVariableNoMsg(li_ImportExportBlockNum, "XLStartCol", li_XLStartCol, 0, 0);
			
			if (li_XLEndRow < 1) SetDialogVariableNoMsg(li_ImportExportBlockNum, "XLEndRow", BLANk, 0, 0);
			else SetDialogVariableNoMsg(li_ImportExportBlockNum, "XLEndRow", li_XLEndRow, 0, 0);
			
			if (li_XLEndCol < 1) SetDialogVariableNoMsg(li_ImportExportBlockNum, "XLEndCol", BLANk, 0, 0);
			else SetDialogVariableNoMsg(li_ImportExportBlockNum, "XLEndCol", li_XLEndCol, 0, 0);
			
			SetDialogVariableNoMsg(li_ImportExportBlockNum, "XLDBExisting_rdo", TRUE, 0, 0);
			
			SendMsgToBlock(li_ImportExportBlockNum, UserMsg1Msg);
			
			SetDialogVariable(li_ImportExportBlockNum, "ImportExport_btn", TRUE, 0, 0);
			
		}
	}
}

#ifdef para_ImportExportBlockNum1
Procedure PullAllODBCTables()
{
	Integer li_ImportExport;
	Integer li_ExDataType;
	Integer li_DataSource;
	Integer li_DataBaseIdx;
	Integer li_DBTableIdx;
	string ls_DBTableName;
	string ls_ADOServerName;
	string ls_FileName;
	Integer li_XLRange_chk;
	Integer li_XLStartRow;
	Integer li_XLEndRow;
	Integer li_XLStartCol;
	Integer li_XLEndCol;
	string ls_XLTabName;
	long li_NumOfRows;
	string ls_DBTblName;
	long li_DBTblIdx;
	long li_DBIdx;
	long li_ImportExportBlockNum;
	
	
	li_ImportExportBlockNum = para_ImportExportBlockNum1;
	
	
	li_ImportExport = 1;
	li_ExDataType = 5;
	li_DataSource = 1;
	
	
	SetDialogVariableNoMsg(li_ImportExportBlockNum, "ImportExport_pop", li_ImportExport, 0, 0);
	SetDialogVariableNoMsg(li_ImportExportBlockNum, "ExternalDataType_pop", li_ExDataType, 0, 0);
	SetDialogVariableNoMsg(li_ImportExportBlockNum, "ADO_WhichDataBase_prm", "SQLServer", 0, 0);
	SetDialogVariableNoMsg(li_ImportExportBlockNum, "DataSource_pop", li_DataSource, 0, 0);
	
	li_DataBaseIdx = DBDatabaseGetIndex("ODBC Exchange");
	li_DBTableIdx = 0;
	ls_DBTableName = BLANK;
	ls_ADOServerName = "PHX-BLUEP-DB";
	ls_FileName = "CE_BLUEP";
	
	SetDialogVariableNoMsg(li_ImportExportBlockNum, "DBIndex_prm", li_DataBaseIdx, 0, 0);
	SetDialogVariableNoMsg(li_ImportExportBlockNum, "XD_tableIndex_prm", li_DBTableIdx, 0, 0);
	SetDialogVariableNoMsg(li_ImportExportBlockNum, "XD_TableName_prm", ls_DBTableName, 0, 0);
	SetDialogVariableNoMsg(li_ImportExportBlockNum, "ftpADO_ServerName_txt", ls_ADOServerName, 0, 0);
	SetDialogVariableNoMsg(li_ImportExportBlockNum, "FileName_txt", ls_FileName, 0, 0);
		
	SendMsgToBlock(li_ImportExportBlockNum, UserMsg2Msg);
	
	SetDialogVariable(li_ImportExportBlockNum, "ImportExport_btn", TRUE, 0, 0);
	
	*** renumber the user defined tables ***
	long DBTblIdx_UserDefinedTables;
	long li_NumOfRecords;
	string ls_TableName;
	
	// Admin user-Defined tables
	DBTblIdx_UserDefinedTables = DBTableGetIndex(li_DataBaseIdx, "Admin_UserTable_Index");
	li_NumOfRecords = DBRecordsGetNum(li_DataBaseIdx, DBTblIdx_UserDefinedTables);
	
	for (i = 1; i <= li_NumOfRecords; i++)
	{
		ls_TableName = DBDataGetAsString(li_DataBaseIdx, DBTblIdx_UserDefinedTables, 1, i);
		
		for (j = 1; j <= DBTablesGetNum(li_DataBaseIdx); j++)
		{
			if (DBTableGetName(li_DataBaseIdx, j) == ls_TableName)
			{
				DBDataSetAsNumber(li_DataBaseIdx, DBTblIdx_UserDefinedTables, 7, i, j);
				BREAK;
			}
		}
	}
	
	// Admin user-Defined tables
	DBTblIdx_UserDefinedTables = DBTableGetIndex(li_DataBaseIdx, "Admin_UserTable_Index");
	li_NumOfRecords = DBRecordsGetNum(li_DataBaseIdx, DBTblIdx_UserDefinedTables);
	
	for (i = 1; i <= li_NumOfRecords; i++)
	{
		ls_TableName = DBDataGetAsString(li_DataBaseIdx, DBTblIdx_UserDefinedTables, 1, i);
		
		for (j = 1; j <= DBTablesGetNum(li_DataBaseIdx); j++)
		{
			if (DBTableGetName(li_DataBaseIdx, j) == ls_TableName)
			{
				DBDataSetAsNumber(li_DataBaseIdx, DBTblIdx_UserDefinedTables, 7, i, j);
				BREAK;
			}
		}
	}
	
	// User user-Defined tables
	DBTblIdx_UserDefinedTables = DBTableGetIndex(li_DataBaseIdx, "User_UserTable_Index");
	li_NumOfRecords = DBRecordsGetNum(li_DataBaseIdx, DBTblIdx_UserDefinedTables);
	
	for (i = 1; i <= li_NumOfRecords; i++)
	{
		ls_TableName = DBDataGetAsString(li_DataBaseIdx, DBTblIdx_UserDefinedTables, 1, i);
		
		for (j = 1; j <= DBTablesGetNum(li_DataBaseIdx); j++)
		{
			if (DBTableGetName(li_DataBaseIdx, j) == ls_TableName)
			{
				DBDataSetAsNumber(li_DataBaseIdx, DBTblIdx_UserDefinedTables, 7, i, j);
				BREAK;
			}
		}
	}
	
	UserError("Your ODBC database is up-to-date.");
}
#endif

#ifdef para_ImportExportBlockNum2
Procedure PushAllODBCTables()
{
	Integer li_ImportExport;
	Integer li_ExDataType;
	Integer li_DataSource;
	Integer li_DataBaseIdx;
	Integer li_DBTableIdx;
	string ls_DBTableName;
	string ls_ADOServerName;
	string ls_FileName;
	Integer li_XLRange_chk;
	Integer li_XLStartRow;
	Integer li_XLEndRow;
	Integer li_XLStartCol;
	Integer li_XLEndCol;
	string ls_XLTabName;
	long li_NumOfRows;
	string ls_DBTblName;
	long li_DBTblIdx;
	long li_DBIdx;
	long li_ImportExportBlockNum;
	
	
	li_ImportExportBlockNum = para_ImportExportBlockNum2;
	
	li_ImportExport = 2;
	li_ExDataType = 5;
	li_DataSource = 1;
	
	
	SetDialogVariableNoMsg(li_ImportExportBlockNum, "ImportExport_pop", li_ImportExport, 0, 0);
	SetDialogVariableNoMsg(li_ImportExportBlockNum, "ExternalDataType_pop", li_ExDataType, 0, 0);
	SetDialogVariableNoMsg(li_ImportExportBlockNum, "ADO_WhichDataBase_prm", "SQLServer", 0, 0);
	SetDialogVariableNoMsg(li_ImportExportBlockNum, "DataSource_pop", li_DataSource, 0, 0);
	
	li_DataBaseIdx = DBDatabaseGetIndex("ODBC Exchange");
	li_DBTableIdx = 0;
	ls_DBTableName = BLANK;
	ls_ADOServerName = "PHX-BLUEP-DB";
	ls_FileName = "CE_BlueP";
	
	SetDialogVariableNoMsg(li_ImportExportBlockNum, "DBIndex_prm", li_DataBaseIdx, 0, 0);
	SetDialogVariableNoMsg(li_ImportExportBlockNum, "XD_tableIndex_prm", li_DBTableIdx, 0, 0);
	SetDialogVariableNoMsg(li_ImportExportBlockNum, "XD_TableName_prm", ls_DBTableName, 0, 0);
	SetDialogVariableNoMsg(li_ImportExportBlockNum, "ftpADO_ServerName_txt", ls_ADOServerName, 0, 0);
	SetDialogVariableNoMsg(li_ImportExportBlockNum, "FileName_txt", ls_FileName, 0, 0);
		
	SendMsgToBlock(li_ImportExportBlockNum, UserMsg2Msg);
	
	SetDialogVariable(li_ImportExportBlockNum, "ImportExport_btn", TRUE, 0, 0);
}
#endif

#ifdef DBTblIdx_ImportMgr
Procedure ResizeImportManagerTable(string WhichTable)
{
	long li_NumOfColumn;
	long oldNumOfRows;
	String dataTableResizePop[2];
	Integer popupChoice;
	long NumOfRowsToAdd;
	long li_DBTblIdx;
	long li_DBIdx;
	
	li_DBIdx = DBDatabaseGetIndex("Data Exchange");
		
	if (whichTable == "tbl_ImportManager" OR whichTable == "tbl_ExportManager")
	{
		if (whichTable == "tbl_ImportManager") li_DBTblIdx = DBTableGetIndex(li_DBIdx, "00_ImportManager");
		else if (whichTable == "tbl_ExportManager") li_DBTblIdx = DBTableGetIndex(li_DBIdx, "00_ExportManager");
		
		li_NumOfColumn = GetDialogItemInfo(MyBlockNumber(), WhichTable, 6);
		oldNumOfRows = GetDialogItemInfo(MyBlockNumber(), WhichTable, 5);
		
		dataTableResizePop[0] = "Insert Row(s)";
		dataTableResizePop[1] = "Delete Row(s)";
		popupChoice = PopupMenuArray (dataTableResizePop, 0);
		
		if (popupChoice == 1)
		{
			NumOfRowsToAdd = NumericParameter("Number of rows to insert:", 1);
			
			if (NumOfRowsToAdd > 0)
			{
				DBRecordsInsert(li_DBIdx, li_DBTblIdx, 0, NumOfRowsToAdd);
			}
		}
		
		if (popupChoice == 2)
		{
			DeleteTableItems(whichTable, li_DBTblIdx);
		}
	}
}
#endif

Procedure DeleteTableItems(String ls_SelectedTable, long li_DBTblIdx)
{
	Integer li_TopRow;
	Integer li_BottomRow;
	Integer li_LeftCol;
	Integer li_RightCol;
	Integer array_TableSelection[4];
	long li_DBIdx;
	
	li_DBIdx = DBDatabaseGetIndex("Data Exchange");
	
	GetDataTableSelection(ls_SelectedTable, array_TableSelection);
	li_TopRow = array_TableSelection[0];
	li_BottomRow = array_TableSelection[1];
	li_LeftCol = array_TableSelection[2];
	StopDataTableEditing();				//for some reason this is needed in order for this procedure to work properly.
	
	if (li_TopRow >= 0 AND li_BottomRow >= 0 AND li_LeftCol == 0)
	{
		DBRecordsDelete(li_DBIdx, li_DBTblIdx, li_TopRow+1, li_BottomRow+1);
	}
	
	SetDataTableSelection(ls_SelectedTable, -1, -1, -1, -1, FALSE);
}

Procedure SetupImportManagerTable(string ls_ImportManagerTblName)
{
	DTHideLinkButton(MyblockNumber(), ls_ImportManagerTblName, TRUE);
	DTGrowButton(MyblockNumber(), ls_ImportManagerTblName, TRUE);
	SetDTRowStart(MyBlockNumber(),ls_ImportManagerTblName,1);
	SetDTColumnWidth(MyBlockNumber(), ls_ImportManagerTblName, 0, 25, TRUE);
	SetDTColumnWidth(MyBlockNumber(), ls_ImportManagerTblName, 1, 25, TRUE);
	SetDTColumnWidth(MyBlockNumber(), ls_ImportManagerTblName, 2, 100, TRUE);
	SetDTColumnWidth(MyBlockNumber(), ls_ImportManagerTblName, 3, 25, TRUE);
	SetDTColumnWidth(MyBlockNumber(), ls_ImportManagerTblName, 4, 250, TRUE);
	SetDTColumnWidth(MyBlockNumber(), ls_ImportManagerTblName, 5, 30, TRUE);
	SetDTColumnWidth(MyBlockNumber(), ls_ImportManagerTblName, 6, 174, TRUE);
	SetDTColumnWidth(MyBlockNumber(), ls_ImportManagerTblName, 7, 100, TRUE);
	SetDTColumnWidth(MyBlockNumber(), ls_ImportManagerTblName, 8, 35, TRUE);
	SetDTColumnWidth(MyBlockNumber(), ls_ImportManagerTblName, 9, 35, TRUE);
	SetDTColumnWidth(MyBlockNumber(), ls_ImportManagerTblName, 10, 35, TRUE);
	SetDTColumnWidth(MyBlockNumber(), ls_ImportManagerTblName, 11, 35, TRUE);
	SetDTColumnWidth(MyBlockNumber(), ls_ImportManagerTblName, 12, 1, TRUE);
	SetDTColumnWidth(MyBlockNumber(), ls_ImportManagerTblName, 13, 1, TRUE);
	SetDTColumnWidth(MyBlockNumber(), ls_ImportManagerTblName, 14, 1, TRUE);
	SetDTColumnWidth(MyBlockNumber(), ls_ImportManagerTblName, 15, 1, TRUE);
	DTColumnTagSet(MyBlockNumber(), ls_ImportManagerTblName, 0, 20, 0, "", "");
	DTColumnTagSet(MyBlockNumber(), ls_ImportManagerTblName, 1, 40, 0, "", "");
	DTColumnTagSet(MyBlockNumber(), ls_ImportManagerTblName, 3, 40, 0, "", "");
	DTColumnTagSet(MyBlockNumber(), ls_ImportManagerTblName, 6, 40, 0, "", "");
}

#ifdef FileName_txt
Procedure ImportManagerTableClicked()
{
	string ls_Value;
	long li_DBIdx;
	string ls_SheetName;
	long li_Value;
	string ls_DialogClicked;
	long li_RowClicked, li_ColClicked, li_NumOfRows;

	ls_DialogClicked = WhichDialogItemClicked();
	li_RowClicked = WhichDTCellClicked(0);
	li_ColClicked = WhichDTCellClicked(1);
	li_NumOfRows = GetDialogItemInfo(MyBlockNumber(), ls_DialogClicked, 5);
	
	if ((ls_DialogClicked == "tbl_ImportManager" OR ls_DialogClicked == "tbl_ExportManager") AND li_RowClicked >= 0 AND li_RowClicked < li_NumOfRows)
	{
		if (li_ColClicked == 5 AND GetModifierKey(2) == TRUE)
		{
			ls_Value = GetDialogVariable(MyBlockNumber(), ls_DialogClicked, li_RowClicked, li_ColClicked);
			
			FileName_txt = ls_Value;
			
			OpenBrowseFile();
			SetDialogVariableNoMsg(MyBlockNumber(), ls_DialogClicked, FileName_txt, li_RowClicked, li_ColClicked);
		}
		
		else if (li_ColClicked == 6 AND GetDialogVariable(MyBlockNumber(), ls_DialogClicked, li_RowClicked, 5) != BLANK)
		{
			ls_Value = GetDialogVariable(MyBlockNumber(), ls_DialogClicked, li_RowClicked, 5);
			
			ls_SheetName = ExcelSheetDropdownMenuInTable(ls_DialogClicked, ls_Value);
			SetDialogVariableNoMsg(MyBlockNumber(), ls_DialogClicked, ls_SheetName, li_RowClicked, li_ColClicked);
		}
		
		else if (li_ColClicked == 1)
		{
			li_Value = StrToReal(GetDialogVariable(MyBlockNumber(), ls_DialogClicked, li_RowClicked, 2));
			li_Value = DBDatabasePopupSelector(li_Value);
			SetDialogVariableNoMsg(MyBlockNumber(), ls_DialogClicked, DBDatabaseGetName(li_Value), li_RowClicked, li_ColClicked);
			SetDialogVariableNoMsg(MyBlockNumber(), ls_DialogClicked, li_Value, li_RowClicked, 2);
		}
		
		else if (li_ColClicked == 3)
		{
			li_DBIdx = StrToReal(GetDialogVariable(MyBlockNumber(), ls_DialogClicked, li_RowClicked, 2));
						if (!NoValue(li_DBIdx))
			{
				li_Value = StrToReal(GetDialogVariable(MyBlockNumber(), ls_DialogClicked, li_RowClicked, 4));
				li_Value = DBTablePopupSelector(li_DBIdx, li_Value);
				SetDialogVariableNoMsg(MyBlockNumber(), ls_DialogClicked, DBTableGetName(li_DBIdx, li_Value), li_RowClicked, li_ColClicked);
				SetDialogVariableNoMsg(MyBlockNumber(), ls_DialogClicked, li_Value, li_RowClicked, 4);
				
				DBDatabaseOpenViewer(li_DBIdx, DBTableGetName(li_DBIdx, li_Value));
			}
		}
	}
}
#endif
******************************************************************************************************************************************

******************************************************************************************************************************************
// tool functions for excel sheet selection
******************************************************************************************************************************************
integer GetWorkBooks(integer ExcelApp)
{
	integer fail;
	OleDispatchPropertyGet(ExcelApp, _EXCEL_APPLICATION_WORKBOOKS);				// get the DispID of the workbooks object
	return(OleDispatchResult());
}

//integer FindWorkbook(string Thisworkbook, 
//					 integer embeddedNum, 
//					 integer embedded,
//					 integer abortIfNotFound)	//	5/9/16		9.2.1		PHT

integer FindWorkbook(string Thisworkbook, integer abortIfNotFound)	// ExtendSim Version 9 new code 11/14/2016
{
integer NumWorkbooks;
integer i;
string testWorkbook;
string useWorkbook;
integer BlockPosition[4];

	OLEDispatchPropertyGet(WorkBooks, _EXCEL_WORKBOOKS_COUNT);
	NumWorkbooks = OleLongResult();

//		5/8/03   6.0.3  DJK added additional checks for NumWorkbooks because Excel sometimes reports that there are none even when some are there
// Sometimes Excel reports 0 workbooks. Wait up to 10 seconds to see if any show up

	i = 0;
	While(NumWorkbooks == 0 && i < 5)
		{
		WaitNTicks(60);		// wait 1 second
		OLEDispatchPropertyGet(WorkBooks, _EXCEL_WORKBOOKS_COUNT);
		NumWorkbooks = OleLongResult();
		i++;
		}
//	for(i=1;i<=NumWorkbooks;i++)
/*	
	if(embedded)
		{
	
		OLEDispatchPropertyGet(WorkBooks, _EXCEL_WORKBOOKS_COUNT);
		NumWorkbooks = OleLongResult();

		if(embeddedNum < 0)
			{
//		7/15/04  6.0.6  DJK added block number to error messages
			UserError("Embedded workbook not specified. Error found in "+BlockName(MyBLockNumber())+" number " +MyBlockNumber());
			XL_cleanupExcel(True, False);
			abort;
			}
//		else if(EmbeddedNum == 1 || EmbeddedNum == 0)
//			{
//			UseWorkbook = "worksheet in "+GetModelName();
//			}
//		else
//			{
//			UseWorkbook = "worksheet in "+GetModelName() + " "+embeddedNum;
//			}
**	5/15/13	8.0.3		DJK			Revised how name of embedded worksheet is calculated. This fixes a problem when the worksheet is embedded inside of a hierarchical block
		UseWorkbook = FileName_txt;	
		}
	else
		UseWorkbook = ThisWorkbook;
*/		
	UseWorkbook = ThisWorkbook;
	
	i = 1;
	TestWorkbook = "";
	while(i<= NumWorkbooks && UseWorkbook != TestWorkbook)
		{
		OLELongParam(i);
		OLEDispatchPropertyGet(WorkBooks, _EXCEL_WORKBOOKS_ITEM);
		workbook = OLEDispatchResult();
		OLEDispatchPropertyGet(workbook, 110);
		testworkbook = OLEStringResult();
		if(UseWorkbook != TestWorkbook)
			{
			OLERelease(workbook);
			workbook = 0;
			i++;
			}
		}
	if(UseWorkBook != testWorkbook)
		{
		if (!abortIfNotFound)
			return(-1);		//	5/9/16		9.2.1		PHT
//		7/15/04  6.0.6  DJK added block number to error messages
		UserError("Workbook "+UseWorkbook+" could not be found. Select a different workbook. Error found in "+BlockName(MyBLockNumber())+" number " +MyBlockNumber());
		CleanupExcel();
		if(GetSimulationPhase() != 0)
			abort;
		}
		
			
//	XL_minimizeWorkbookWindow(workbook);	//	7/8/15		9.2.1		PHT
	return(i);
}


/*
integer FindWorkbook(string Thisworkbook)
{
	integer NumWorkbooks;
	string testWorkbook;
	string useWorkbook;
	integer BlockPosition[4];

	OLEDispatchPropertyGet(workbooks, _EXCEL_WORKBOOKS_COUNT);
	NumWorkbooks = OleLongResult();

	// Sometimes Excel reports 0 workbooks. Wait up to 10 seconds to see if any show up

	i = 0;
	While(NumWorkbooks == 0 && i < 5)
	{
		WaitNTicks(60);		// wait 1 second
		OLEDispatchPropertyGet(workbooks, _EXCEL_WORKBOOKS_COUNT);
		NumWorkbooks = OleLongResult();
		i++;
	}

	UseWorkbook = ThisWorkbook;

	i = 1;
	TestWorkbook = "";
	while(i<= NumWorkbooks && UseWorkbook != TestWorkbook)
	{
		OLELongParam(i);
		OLEDispatchPropertyGet(workbooks, _EXCEL_WORKBOOKS_ITEM);
		workbook  = OLEDispatchResult();
		OLEDispatchPropertyGet(workbook, 110);
		testworkbook = OLEStringResult();
		if(UseWorkbook != TestWorkbook)
		{
			OLERelease(workbook);
			workbook = 0;
			i++;
		}
	}

	if(UseWorkBook != testWorkbook)
	{
		UserError("Worksheet "+UseWorkbook+" could not be found. Select a different workbook. Error found in "+BlockName(MyBLockNumber())+" number " +MyBlockNumber());
		CleanupExcel();
		abort;
	}
	return(i);
}
*/

procedure GetWorksheets()
{
	OleDispatchPropertyGet(workbook,_EXCEL_APPLICATION_WORKSHEETS);				// get the DispID for the worksheets
	Worksheets = OleDispatchResult();

	if(Worksheets == 0)
	{
		usererror("error getting worksheets. Error found in "+BlockName(MyBLockNumber())+" number " +MyBlockNumber());
		CleanupExcel();
	}

}

Procedure CleanupExcel()
{
	if(ExcelApp != 0)
		{
		OLERelease(ExcelApp);
		ExcelApp = 0;
		}
	if(Workbooks != 0)
		{
		OLERelease(WorkBooks);
		WorkBooks = 0;
		}
	if(Worksheets != 0)
		{
		OLERelease(WorkSheets);
		WorkSheets = 0;
		}
	if(Worksheet != 0)
		{
		OLERelease(Worksheet);
		Worksheet = 0;
		}
}

integer SetupExcel(String ThisWorkbook)
{
	long WorkbookItem;
	
	ExcelApp = OLECreateObject("excel.application");

	WaitNTicks(10);
	WorkBooks = GetWorkbooks(ExcelApp);
	WorkbookItem = FindWorkbook(ThisWorkbook, TRUE);

	GetWorksheets();

	return(workbookItem);
}