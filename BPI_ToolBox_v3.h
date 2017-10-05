** This include file collects all useful tools
long gi_ReportEditorBlockNum;
long gi_TimeManagerBlockNum;
long gi_OptimizerBlockNumber;
long gi_UnitCostBlockNumber;
long gi_pHCalculatorBlockNumber;
long gi_ModuleMgrBlockNumber;
long gi_ModuleAssemblyBlockNum;
long gi_SABlockNumber;
long gi_WQInputMgrBlockNumber;
long gi_ExcelDataExBlockNum;
long gi_ModuleSetupBlockNum;
long giCapacityMgrBlockNum;
long ii;
long DBIndex_DX;
long DBIndex_UR;
long DBIndex_TS;
long DBIndex_EQ;
long DBIndex_DP;
long DBIndex_CM;
long DBIndex_TE;
long DBIndex_ODBC;



** 1. RoundDec	(Rounding Mode, Ugly Number, Round Decimal)

real RoundDec(String ls_RoundMode, real lr_UglyNum, real lr_NumDecimal)
{    
	real lr_RoundingIndex;
	real lr_PrettyNum;

	lr_RoundingIndex = 10.0^lr_NumDecimal;
	
	if (ls_RoundMode == "RU") // Round up
	{
		lr_PrettyNum = Ceil(lr_UglyNum*lr_RoundingIndex)/lr_RoundingIndex;
	}
	
	else if (ls_RoundMode == "RD") // Round down
	{
		lr_PrettyNum = Floor(lr_UglyNum*lr_RoundingIndex)/lr_RoundingIndex;
	}
	
	else if (ls_RoundMode == "R") // Normal rounding
	{
		if (lr_UglyNum*lr_RoundingIndex-int(lr_UglyNum*lr_RoundingIndex)>= 0.5)
		{
			lr_PrettyNum = Ceil(lr_UglyNum*lr_RoundingIndex)/lr_RoundingIndex;
		}
		
		else 
		{
			lr_PrettyNum = Floor(lr_UglyNum*lr_RoundingIndex);
			lr_PrettyNum = lr_PrettyNum/lr_RoundingIndex;
		}
	}
	
	return(lr_PrettyNum);
}

String NumberWithComma(String ls_Value)
{
	Real lr_Value;
	Integer li_Value;
	Integer li_NumOfDigits;
	String ls_ThousandPart;
	String ls_MillionPart;
	String ls_BillionPart;
	String ls_TrillionPart;
	String ls_DecimalPart;
	String ls_NumberWithComma;
	
	if (StrFind(ls_Value, ".", 0, 0) >= 0) ls_DecimalPart = StrPart(ls_Value, StrFind(ls_Value, ".", 0, 0), StrLen(ls_Value)-StrFind(ls_Value, ".", 0, 0));
	else ls_DecimalPart = BLANK;
	
	lr_Value = StrToReal(ls_Value);
	
	li_Value = lr_Value;
	
	li_NumOfDigits = StrLen(li_Value);
	
	ls_ThousandPart = StrPart(li_Value, li_NumOfDigits-3, 3);
	ls_MillionPart = StrPart(li_Value/1000, StrLen(li_Value/1000)-3, 3);
	ls_BillionPart = StrPart(li_Value/1000000, StrLen(li_Value/1000000)-3, 3);
	ls_TrillionPart = StrPart(li_Value/1000000000, StrLen(li_Value/1000000000)-3, 3);
	
	ls_NumberWithComma = ls_ThousandPart + ls_DecimalPart;
	if (li_NumOfDigits > 3) ls_NumberWithComma = ls_MillionPart + "," + ls_NumberWithComma;
	if (li_NumOfDigits > 6) ls_NumberWithComma = ls_BillionPart + "," + ls_NumberWithComma;
	if (li_NumOfDigits > 9) ls_NumberWithComma = ls_TrillionPart + "," + ls_NumberWithComma;
	
	
	return(ls_NumberWithComma);
}

Real RemoveNumberSeparator(String ls_Value)
{
	Real lr_NumberWithoutComma;
	Integer li_NumOfDecimal;
	
	li_NumOfDecimal = StrLen(StrPart(ls_Value, StrFind(ls_Value, ".", 0, 0), StrLen(ls_Value)-StrFind(ls_Value, ".", 0, 0)-1));
	
	while (StrFind(ls_Value, ",", 0, 0) >= 0)
	{
		ls_Value = StrReplace(ls_Value, StrFind(ls_Value, ",", 0, 0), 1, "");
	}
	
	lr_NumberWithoutComma = StrToReal(ls_Value);
	
	lr_NumberWithoutComma = RoundDec(R, lr_NumberWithoutComma, li_NumOfDecimal);
	
	return(lr_NumberWithoutComma);
}

String TranslateToExcelFieldHeader(Integer li_FieldNumber)
{
	Integer li_DBIdx;
	Integer li_DBTblIdx;
	String ls_FirstCharactor;
	String ls_SecondCharactor;
	String ls_TranslatedFieldHeader;
	
	li_DBIdx = DBDatabaseGetIndex("Table Editor");
	li_DBTblIdx = DBTableGetIndex(li_DBIdx, "_AToZIndex");
	
	if (Int(li_FieldNumber/26) == 0)
	{
		ls_FirstCharactor = BLANK;
		
		ls_SecondCharactor = DBDataGetAsString(li_DBIdx, li_DBTblIdx, 1, (li_FieldNumber MOD 26));
	}
	
	else if (Int(li_FieldNumber/26) > 0)
	{
		ls_FirstCharactor = DBDataGetAsString(li_DBIdx, li_DBTblIdx, 1, Int(li_FieldNumber/26));
		
		ls_SecondCharactor = DBDataGetAsString(li_DBIdx, li_DBTblIdx, 1, (li_FieldNumber MOD 26));
	}
	
	ls_TranslatedFieldHeader = ls_FirstCharactor+ls_SecondCharactor;
	
	Return(ls_TranslatedFieldHeader);
}

Integer TranslateToExtendSimFieldHeader(String ls_ColumnName)
{
	Integer li_DBIdx;
	Integer li_DBTblIdx;
	String ls_FirstCharactor;
	String ls_SecondCharactor;
	Integer li_FieldIndex;
	Integer alpha;
	
	li_DBIdx = DBDatabaseGetIndex("Table Editor");
	li_DBTblIdx = DBTableGetIndex(li_DBIdx, "_AToZIndex");
	
	if (StrLen(ls_ColumnName) == 1)
	{
		for (alpha = 1; alpha <= 26; alpha++)
		{
			if (DBDataGetAsString(li_DBIdx, li_DBTblIdx, 1, alpha) == ls_ColumnName)
			{
				li_FieldIndex = alpha;
			}
		}
	}
	
	else if (StrLen(ls_ColumnName) == 2)
	{
		ls_FirstCharactor = StrPart(ls_ColumnName, 0, 1);
		ls_SecondCharactor = StrPart(ls_ColumnName, 1, 1);
		
		for (alpha = 1; alpha <= 26; alpha++)
		{
			if (DBDataGetAsString(li_DBIdx, li_DBTblIdx, 1, alpha) == ls_FirstCharactor)
			{
				li_FieldIndex = alpha*26;
			}
		}
		
		for (alpha = 1; alpha <= 26; alpha++)
		{
			if (DBDataGetAsString(li_DBIdx, li_DBTblIdx, 1, alpha) == ls_SecondCharactor)
			{
				li_FieldIndex = li_FieldIndex + alpha;
			}
		}
	}
	
	Return(li_FieldIndex);
}

Procedure FindGlobalBlockNumber()
{
	for (ii = 0; ii < NumBlocks(); ii++)
	{
		if (BlockName(ii) == "TS_Simulated Time Controller") gi_TimeManagerBlockNum = ii;
		
		else if (BlockName(ii) == "Report Editor_v2") gi_ReportEditorBlockNum = ii;
		
		else if (BlockName(ii) == "BluePlanit_Optimizer") gi_OptimizerBlockNumber = ii;
		
		else if (BlockName(ii) == "Unit_Cost_Controller") gi_UnitCostBlockNumber = ii;
		
		else if (BlockName(ii) == "pH Calculator") gi_pHCalculatorBlockNumber = ii;
		
		else if (BlockName(ii) == "MODULE MANAGER") gi_ModuleMgrBlockNumber = ii;
		
		else if (BlockName(ii) == "Module Assembly") gi_ModuleAssemblyBlockNum = ii;
		
		else if (BlockName(ii) == "Excel Data Exchange") gi_ExcelDataExBlockNum = ii;
		
		else if (BlockName(ii) == "MODEL SETUP") gi_ModuleSetupBlockNum = ii;
		
		else if (BlockName(ii) == "Capacity Manager") giCapacityMgrBlockNum = ii;
		
		#ifdef GroupTag_diag
		else if (BlockName(ii) == "Sensitivity Analysis" AND GetBlockLabel(ii) == GroupTag_diag) gi_SABlockNumber = ii;
		
		else if (BlockName(ii) == "Constituents Of Concern" AND GetBlockLabel(ii) == GroupTag_diag) gi_WQInputMgrBlockNumber = ii;
		#endif
	}
}

Procedure GetDatabaseNumber()
{
	DBIndex_DX = DBDatabaseGetIndex("Data Exchange");
	DBIndex_UR = DBDatabaseGetIndex("User Database");
	DBIndex_TS = DBDatabaseGetIndex("TimeStep DB");
	DBIndex_EQ = DBDatabaseGetIndex("DB_Equation");
	DBIndex_DP = DBDatabaseGetIndex("Demand Projections");
	DBIndex_CM = DBDatabaseGetIndex("Capacity Manager");
	DBIndex_TE = DBDatabaseGetIndex("Table Editor");
	DBIndex_ODBC = DBDatabaseGetIndex("ODBC Exchange");
}

Procedure DeleteDBTableItems(String ls_SelectedTable, long li_DBTblIdx)
{
	Integer li_TopRow;
	Integer li_BottomRow;
	Integer li_LeftCol;
	Integer li_RightCol;
	Integer array_TableSelection[4];
	
	GetDataTableSelection(ls_SelectedTable, array_TableSelection);
	li_TopRow = array_TableSelection[0];
	li_BottomRow = array_TableSelection[1];
	li_LeftCol = array_TableSelection[2];
	StopDataTableEditing();				//for some reason this is needed in order for this procedure to work properly.
	
	if (li_TopRow >= 0 AND li_BottomRow >= 0 AND li_LeftCol == 0)
	{
		DBRecordsDelete(DBIndex_TE, li_DBTblIdx, li_TopRow+1, li_BottomRow+1);
	}
	
	SetDataTableSelection(ls_SelectedTable, -1, -1, -1, -1, FALSE);
}

Procedure ResizeDataTable(string WhichTable, long li_DBTblIdx)
{
	long li_NumOfColumn;
	long oldNumOfRows;
	String dataTableResizePop[2];
	Integer popupChoice;
	long NumOfRowsToAdd;
		
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
			DBRecordsInsert(DBIndex_TE, li_DBTblIdx, 0, NumOfRowsToAdd);
		}
	}
	
	if (popupChoice == 2)
	{
		DeleteDBTableItems(whichTable, li_DBTblIdx);
	}
}

Integer FindRecord(string ls_FindValue, string ls_TableName, integer li_ColumnIndex, integer li_StartRow) // return -1 if not found
{
	long li_NumOfRows;
	long ri;
	long li_RecordIndex;
	string li_value;
	long li_FindIndex;
	
	li_NumOfRows = GetDialogItemInfo(MyBlockNumber(), ls_TableName, 5);
	
	li_RecordIndex = 0;
	for (ri = li_StartRow; ri < li_NumOfRows; ri++)
	{
		li_value = GetDialogVariable(MyBlockNumber(), ls_TableName, ri, li_ColumnIndex);
		if (li_value != ls_FindValue)
		{
			li_RecordIndex++;
			li_FindIndex = -1;
		}
		
		else 
		{
			li_FindIndex = ri;
			BREAK;
		}
	}
	
	return(li_FindIndex);
}

Procedure CopyAndPasteDBTableContent(long li_FromDBIndex, long li_FromDBTblIdx, long li_ToDBIndex, long li_ToDBTblIdx, 
									 long li_StartRecordIdx, long li_EndRecordIdx, long li_StartFieldIdx, long li_EndFieldIdx, long li_TopRecord, long li_LeftFieldIdx)
{
	long li_Record;
	long li_Field;
	string ls_Value;
	long li_TargetRecordIdx;
	long li_TargetFieldIdx;
	
	if (li_EndFieldIdx == 0) // if input of end field index is 0, use the last field index as end field index
	{
		li_EndFieldIdx = DBFieldsGetNum(li_FromDBIndex, li_FromDBTblIdx);
	}
	
	if (li_EndRecordIdx == 0) // if input of end record index is 0, use the last record index as end record index
	{
		li_EndRecordIdx = DBRecordsGetNum(li_FromDBIndex, li_FromDBTblIdx);
	}
	
	// start copy-and-paste	
	for (li_Record = li_StartRecordIdx; li_Record <= li_EndRecordIdx; li_Record++)
	{
		for (li_Field = li_StartFieldIdx; li_Field <= li_EndFieldIdx; li_Field++)
		{
			ls_Value = DBDataGetAsString(li_FromDBIndex, li_FromDBTblIdx, li_Field, li_Record);
			
			li_TargetRecordIdx = li_Record - li_StartRecordIdx + li_TopRecord;
			li_TargetFieldIdx = li_Field - li_StartFieldIdx + li_LeftFieldIdx;
			
			DBDataSetAsString(li_ToDBIndex, li_ToDBTblIdx, li_TargetFieldIdx, li_TargetRecordIdx, ls_Value);
		}
	}
}

Procedure CopyAndPasteDBTableToDT(long li_FromDBIndex, long li_FromDBTblIdx, long li_BlockNumber, string ls_ToDTName, 
									 long li_StartRecordIdx, long li_EndRecordIdx, long li_StartFieldIdx, long li_EndFieldIdx, long li_TopRowIdx, long li_LeftColIdx)
{
	long li_Record;
	long li_Field;
	string ls_Value;
	long li_TargetRowIdx;
	long li_TargetColIdx;
	
	if (li_EndFieldIdx == 0) // if input of end field index is 0, use the last field index as end field index
	{
		li_EndFieldIdx = DBFieldsGetNum(li_FromDBIndex, li_FromDBTblIdx);
	}
	
	if (li_EndRecordIdx == 0) // if input of end record index is 0, use the last record index as end record index
	{
		li_EndRecordIdx = DBRecordsGetNum(li_FromDBIndex, li_FromDBTblIdx);
	}
	
	// start copy-and-paste	
	for (li_Record = li_StartRecordIdx; li_Record <= li_EndRecordIdx; li_Record++)
	{
		for (li_Field = li_StartFieldIdx; li_Field <= li_EndFieldIdx; li_Field++)
		{
			ls_Value = DBDataGetAsString(li_FromDBIndex, li_FromDBTblIdx, li_Field, li_Record);
			
			li_TargetRowIdx = li_Record - li_StartRecordIdx + li_TopRowIdx;
			li_TargetColIdx = li_Field - li_StartFieldIdx + li_LeftColIdx;
			
			SetDialogVariableNoMsg(li_BlockNumber, ls_ToDTName, ls_Value, li_TargetRowIdx, li_TargetColIdx);
		}
	}
}

*********************************************************************************************

