integer ExcelApp;		// DispID for the Excel application
integer WorkBooks;		// DispID for the workbooks
integer WorkSheets;		// DispID for the worhSheets
integer Worksheet;		// DispID for a specific workbook
integer workbook;
integer range;
//String	SheetNames[];
string SheetNames;

Constant	_EXCEL_APPLICATION_WORKBOOKS	is	572;
Constant	_EXCEL_APPLICATION_WORKSHEETS	is	494;
Constant	_EXCEL_WORKBOOKS_COUNT	is	118;
Constant	_EXCEL_WORKBOOKS_ITEM	is	170;
Constant	_EXCEL_APPLICATION_APPLICATION	is	148;
Constant	_EXCEL_WORKSHEETS_COUNT	is	118;
Constant	_EXCEL_WORKSHEETS_ITEM	is	170;

integer GetWorkBooks(integer ExcelApp);
integer FindWorkbook(string Thisworkbook);
procedure GetWorksheets();
Procedure CleanupExcel();
integer SetupExcel(String ThisWorkbook);
Procedure DeleteTableItems(String ls_SelectedTable);

******************************************************************************************************************************************
// functions for excel sheet selection
******************************************************************************************************************************************
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
				FileName_txt = StripPathIfLocal(IPCGetDocName());
			}
		}
	}
}

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

#ifdef XLDBSelectWhich_pop
Procedure AfterXLSheetWhich()
{
	integer NumWorksheets;	// number of worksheets in a workbook
	integer NumWorkbooks;
	string ThisWorkbook;
	integer workbookitem;
	long DBIdx_DataEx, DBTblIdx_ImportExportSetup;
	string SheetName;

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
		
		DBIdx_DataEx = DBDatabaseGetIndex("Data Exchange");
		DBTblIdx_ImportExportSetup = DBTableGetIndex(DBIdx_DataEx, "00_ImportExportSetup");
				
		DBDataSetAsString(DBIdx_DataEx, DBTblIdx_ImportExportSetup, 2, 1, SheetNames);
	}

	else Abort;

	CleanUpExcel();
}
#endif

******************************************************************************************************************************************
// functions for import manager function
******************************************************************************************************************************************

#ifdef tbl_ImportManager
Procedure SendRequestToImportExportBlock(string ls_ImportExport)
{
	Integer li_ImportExport;
	Integer li_ExDataType;
	Integer li_DataSource;
	Integer li_DataBaseIdx;
	Integer li_DBTableIdx;
	string ls_FileName;
	Integer li_XLRange_chk;
	Integer li_XLStartRow;
	Integer li_XLEndRow;
	Integer li_XLStartCol;
	Integer li_XLEndCol;
	string ls_XLTabName;
		
	if (ls_ImportExport == "Import") li_ImportExport = 1;
	else if (ls_ImportExport == "Export") li_ImportExport = 2;
	li_ExDataType = 1;
	li_DataSource = 1;
	
	SetDialogVariableNoMsg(para_ExportBlockNum, "ImportExport_pop", li_ImportExport, 0, 0);
	SetDialogVariableNoMsg(para_ExportBlockNum, "ExternalDataType_pop", li_ExDataType, 0, 0);
	SetDialogVariableNoMsg(para_ExportBlockNum, "DataSource_pop", li_DataSource, 0, 0);
	
	for (i = 0; i < GetDimension(tbl_ImportManager); i++)
	{
		if (gi_ImportAllClicked == TRUE OR (gi_ImportAllClicked == FALSE AND tbl_ImportManager[i][0] == TRUE))
		{
			li_DataBaseIdx = StrToReal(tbl_ImportManager[i][2]);
			li_DBTableIdx = StrToReal(tbl_ImportManager[i][4]);
			ls_FileName = tbl_ImportManager[i][5];
			ls_XLTabName = tbl_ImportManager[i][6];
			li_XLStartRow = StrToReal(tbl_ImportManager[i][7]);
			li_XLEndRow = StrToReal(tbl_ImportManager[i][8]);
			li_XLStartCol = StrToReal(tbl_ImportManager[i][9]);
			li_XLEndCol = StrToReal(tbl_ImportManager[i][10]);
			
			if (tbl_ImportManager[i][7] != BLANK AND tbl_ImportManager[i][8] != BLANK AND tbl_ImportManager[i][9] != BLANK AND tbl_ImportManager[i][10] != BLANK)
			{
				li_XLRange_chk = TRUE;
			}
			
			else li_XLRange_chk = FALSE;
			
			DBTblIdx_ImportExportSetup = DBTableGetIndex(DBIndex, "00_ImportExportSetup");
			DBDataSetAsString(DBIndex, DBTblIdx_ImportExportSetup, 2, 1, ls_XLTabName);
			
			SetDialogVariableNoMsg(para_ExportBlockNum, "DBIndex_prm", li_DataBaseIdx, 0, 0);
			SetDialogVariableNoMsg(para_ExportBlockNum, "XD_tableIndex_prm", li_DBTableIdx, 0, 0);
			SetDialogVariableNoMsg(para_ExportBlockNum, "FileName_txt", ls_FileName, 0, 0);
			SetDialogVariableNoMsg(para_ExportBlockNum, "XLRange_chk", li_XLRange_chk, 0, 0);
			SetDialogVariableNoMsg(para_ExportBlockNum, "XLStartRow", li_XLStartRow, 0, 0);
			SetDialogVariableNoMsg(para_ExportBlockNum, "XLStartCol", li_XLStartCol, 0, 0);
			SetDialogVariableNoMsg(para_ExportBlockNum, "XLEndRow", li_XLEndRow, 0, 0);
			SetDialogVariableNoMsg(para_ExportBlockNum, "XLDBExisting_rdo", TRUE, 0, 0);
			SetDialogVariableNoMsg(para_ExportBlockNum, "XLEndCol", li_XLEndCol, 0, 0);
			
			SendMsgToBlock(para_ExportBlockNum, UserMsg1Msg);
			
			SetDialogVariable(para_ExportBlockNum, "ImportExport_btn", TRUE, 0, 0);
			
		}
	}
}

Procedure ResizeImportManagerTable(string WhichTable)
{
	long li_NumOfColumn;
	long oldNumOfRows;
	String dataTableResizePop[2];
	Integer popupChoice;
	long NumOfRowsToAdd;
		
	if (whichTable == "tbl_ImportManager")
	{
		li_NumOfColumn = GetDialogItemInfo(MyBlockNumber(), WhichTable, 6);
		oldNumOfRows = GetDialogItemInfo(MyBlockNumber(), WhichTable, 5);
		
		dataTableResizePop[0] = "Insert Row(s)";
		dataTableResizePop[1] = "Delete Row(s)";
		popupChoice = PopupMenuArray (dataTableResizePop, 0);
		
		if (popupChoice == 1)
		{
			NumOfRowsToAdd = NumericParameter("Number of rows to insert:", 1);
			
			if (oldNumOfRows+NumOfRowsToAdd > 0)
			{
				DynamicDataTableVariableColumns(MyblockNumber(), WhichTable, array_ImportManager, oldNumOfRows+NumOfRowsToAdd, li_NumOfColumn);
			}	
			
			else if (oldNumOfRows+NumOfRowsToAdd <= 0 AND oldNumOfRows+NumOfRowsToAdd >= -100)
			{
				DynamicDataTableVariableColumns(MyblockNumber(), WhichTable, array_ImportManager, 0, li_NumOfColumn);
			}
		}
		
		if (popupChoice == 2)
		{
			DeleteTableItems(whichTable);
		}
	}
}

Procedure DeleteTableItems(String ls_SelectedTable)
{
	Integer TempDBTableIndex;
	Integer NumOfSelectedTableColumns;
	Integer NumOfSelectedTableRows;
	String ls_SelectedTableArrayName;
	String VariableCloneTitle;
	String VariableCloneValue;
	integer whatGotSelected[4];
	Integer TableItemDeleteStartRow;
	Integer TableItemDeleteEndRow;
	Integer numDeletableRows;
	Integer leftCol;
	String ls_Value;
	Integer li_NewRowIndex;
	Integer li_NumOfDeletedRows;
	Integer li_NumOfFinalRows;
	
	*********************************************************************************************************************
	GetDataTableSelection(ls_SelectedTable, whatGotSelected);
	TableItemDeleteStartRow = whatGotSelected[0];
	TableItemDeleteEndRow = whatGotSelected[1];
	leftCol = whatGotSelected[2];
	StopDataTableEditing();				//for some reason this is needed in order for this procedure to work properly.
	
	NumOfSelectedTableColumns = GetDialogItemInfo(MyBlockNumber(), ls_SelectedTable, 6);
	NumOfSelectedTableRows = GetDialogItemInfo(MyBlockNumber(), ls_SelectedTable, 5);
	
	li_NumOfDeletedRows = TableItemDeleteEndRow - TableItemDeleteStartRow + 1;
	li_NumOfFinalRows = NumOfSelectedTableRows - li_NumOfDeletedRows;
	*********************************************************************************************************************
	
	if (leftCol == 0 AND TableItemDeleteEndRow >= 0 AND TableItemDeleteStartRow < NumOfSelectedTableRows AND TableItemDeleteEndRow < NumOfSelectedTableRows)
	{
		*** Create temporary  DB table to save un-selected rows ***
		for (i = 0; i <= DBTablesGetNum(DBIndex); i++) // safe check to delete "Temp_" DB table
		{
			if (DBTableGetName(DBIndex, i) == "Temp_SelectedTable") DBTableDeleteByIndex(DBIndex, i);
		}
		
		TempDBTableIndex = DBTableCreateByIndex(DBIndex, "Temp_SelectedTable");
		
		for (i = 0; i < NumOfSelectedTableColumns; i++)
		{
			DBFieldCreateByIndex(DBIndex, TempDBTableIndex, i+1, DB_FIELDTYPE_STRING_VALUE, 0, 0, 0, 0);
		}
		
		for (i = 0; i < NumOfSelectedTableRows; i++)
		{
			DBRecordsInsert(DBIndex, TempDBTableIndex, 0, 1);
			
			for (j = 0; j < NumOfSelectedTableColumns; j++)
			{
				ls_Value = GetDialogVariable(MyBlockNumber(), ls_SelectedTable, i, j);
				
				DBDataSetAsString(DBIndex, TempDBTableIndex, j+1, DBRecordsGetNum(DBIndex, TempDBTableIndex), ls_Value);
			}
		}
		
		*** resize table
		DynamicDataTableVariableColumns(MyblockNumber(), ls_SelectedTable, array_ImportManager, li_NumOfFinalRows, NumOfSelectedTableColumns);
			
		DisableDialogItem("btn_UndoDeleteCC", FALSE);
		
		*** populate data
		for (i = 1; i <= TableItemDeleteStartRow; i++)
		{
			for (j = 1; j <= NumOfSelectedTableColumns; j++)
			{
				ls_Value = DBDataGetAsString(DBIndex, TempDBTableIndex, j, i);
				
				SetDialogVariableNoMsg(MyBlockNumber(), ls_SelectedTable, ls_Value, i-1, j-1);
			}
		}
		
		li_NewRowIndex = TableItemDeleteStartRow;
		for (i = TableItemDeleteEndRow+2; i <= NumOfSelectedTableRows; i++)
		{
			for (j = 1; j <= NumOfSelectedTableColumns; j++)
			{
				ls_Value = DBDataGetAsString(DBIndex, TempDBTableIndex, j, i);
				
				SetDialogVariableNoMsg(MyBlockNumber(), ls_SelectedTable, ls_Value, li_NewRowIndex, j-1);
			}
			
			li_NewRowIndex++;
		}
		
		*** delete temp_DBtable
		DBTableDeleteByIndex(DBIndex, TempDBTableIndex);
		
//		ls_SelectedTable = BLANK;
		TableItemDeleteStartRow = BLANK;
		TableItemDeleteEndRow = BLANK;
	}
}

Procedure SetupImportManagerTable(string ls_ImportManagerTblName)
{
	DTHideLinkButton(MyblockNumber(), ls_ImportManagerTblName, TRUE);
	DTGrowButton(MyblockNumber(), ls_ImportManagerTblName, TRUE);
	SetDTRowStart(MyBlockNumber(),ls_ImportManagerTblName,1);
	SetDTColumnWidth(MyBlockNumber(), ls_ImportManagerTblName, 0, 25, TRUE);
	SetDTColumnWidth(MyBlockNumber(), ls_ImportManagerTblName, 1, 25, TRUE);
	SetDTColumnWidth(MyBlockNumber(), ls_ImportManagerTblName, 2, 120, TRUE);
	SetDTColumnWidth(MyBlockNumber(), ls_ImportManagerTblName, 3, 25, TRUE);
	SetDTColumnWidth(MyBlockNumber(), ls_ImportManagerTblName, 4, 150, TRUE);
	SetDTColumnWidth(MyBlockNumber(), ls_ImportManagerTblName, 5, 30, TRUE);
	SetDTColumnWidth(MyBlockNumber(), ls_ImportManagerTblName, 6, 150, TRUE);
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
	
	if (ls_DialogClicked == "tbl_ImportManager" AND li_RowClicked >= 0 AND li_RowClicked < li_NumOfRows)
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
			}
		}
	}
}
#endif
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
	WorkbookItem = FindWorkbook(ThisWorkbook);

	GetWorksheets();

	return(workbookItem);
}