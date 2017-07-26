************************************
// DBEquation.h
************************************


************************************
// Version Info
************************************
// v01.00	2015/05/12	First iteration. 


************************************
// Block Developer 
************************************
// Carollo
// City, State, Zip
// Phone
// EMail
// Web


************************************
// Purpose
************************************
// The purpose of this block is to allow the user to create custom equations from the DB Equation block using modL.



************************************
// User Messages
************************************


************************************
// Used System and Global Variables
************************************


************************************
// TODO
************************************


************************************
// Constants & Static Variables
************************************
integer giDBIdx;

integer giDBEquationInputOutputsTIdx;
integer giEquationNameEqIOFIdx;
integer giInputOutputEqIOFIdx;
integer giVariableTypeEqIOFIdx;
integer giVariableNameEqIOFIdx;
integer giValueEqIOFIdx;
integer giUnitEqIOFIdx;

integer giDBEquationsTIdx;
integer giEquationNameEqFIdx;
integer giEquationRIdxEqFIdx;
integer giEquationEqFIdx;
integer giEquationEqV2FIdx;
integer giEquationPointerEqFIdx;

integer giDBEquationDescriptionsTIdx;
integer giEquationNameEqDFIdx;
integer giEquationPointerEqDFIdx;
integer giEquationDescriptionEqDFIdx;

string gsLastEquationSelected;

//string gsDialogTable[][5];
//string gsDBEquationList[];
//integer CompiledEquation_da[];

//real iV[];
//real oV[];

Constant csInputName is "Input";
Constant csOutputName is "Output";

Constant csIntegerName is "Integer";
Constant csRealName is "Real";

// DB Equation Inventory Field Constants
Constant cDBEquationNameF is 0;
Constant cNumOfInputsF is 1;
Constant cNumOfOutputsF is 2;
Constant cRenameF is 3;
Constant cDeleteF is 4;

/*
//iVar column constants
constant I_VAR_TABLE_NUM_COLS is 5;
constant I_VAR_TYPE_COL is 0;
constant I_VAR_NAME_COL is 1;
constant I_VAR_VALUE_COL is 2;
constant I_VAR_UNIT_COL is 4; // Carollo, 05/26/2015
constant I_VAR_PARENT_FIELD_COL is 3;

//oVar column constants
constant O_VAR_TABLE_NUM_COLS is 4;
constant O_VAR_TYPE_COL is 0;
constant O_VAR_NAME_COL is 1;
constant O_VAR_VALUE_COL is 2;
constant O_VAR_UNIT_COL is 3; // Carollo, 05/26/2015
constant O_VAR_NO_ITEM_COL is 3;
constant O_VAR_UNUSED_COL is 4;

constant EQ_INTEGER is 56; // Carollo, 05/26/2015
constant EQ_REAL is 57; // Carollo, 05/26/2015
constant EQ_STRING is 58; // Carollo, 05/26/2015
*/
Procedure UpdateEquationManager();

***********************************************
// This procedure delete existing equations from equation editor and populate new equation from equation editor to module tables //
Procedure PopulateEquationFromEditor()
{
	Integer i;
	Integer j;
	
	Integer NumOfDBTableRows;
	Integer DBIdx_EQ;
	Integer DBTblIdx_DBEQIOs;
	Integer DBTblIdx_DBEQs;
	Integer DBTblIdx_DBEQDescriptions;
	Integer DBIdx_Data;
	Integer DBTblIdx_ModuleInputName;
	Integer DBTblIdx_ModuleInputValue;
	Integer DBTblIdx_ModuleInputUnit;
	Integer DBTblIdx_ModuleOutputName;
	Integer DBTblIdx_ModuleOutputUnit;
	Integer DBTblIdx_ModuleEquation;
	Integer DBTableIndex;
	String DBDataValue;
	String OldEquationName;
	String NewEquationName;
	Integer li_InputCount;
	Integer li_OutputCount;
	string EQCategory;
	
	DBIdx_EQ = DBDatabaseGetIndex("DB_Equation");
	DBTblIdx_DBEQIOs = DBTableGetIndex(DBIdx_EQ, "DBEquationInputOutputs");
	DBTblIdx_DBEQs = DBTableGetIndex(DBIdx_EQ, "DBEquations");
	DBTblIdx_DBEQDescriptions = DBTableGetIndex(DBIdx_EQ, "DBEquationDescriptions");
	
	DBIdx_Data = DBDatabaseGetIndex("Data Exchange");
	DBTblIdx_ModuleInputName = DBTableGetIndex(DBIdx_Data, "Module_ParameterName");
	DBTblIdx_ModuleInputValue = DBTableGetIndex(DBIdx_Data, "Module_ParameterValue");
	DBTblIdx_ModuleInputUnit = DBTableGetIndex(DBIdx_Data, "Module_ParameterUnit");
	DBTblIdx_ModuleOutputName = DBTableGetIndex(DBIdx_Data, "Module_OutputName");
	DBTblIdx_ModuleOutputUnit = DBTableGetIndex(DBIdx_Data, "Module_OutputUnit");
	DBTblIdx_ModuleEquation = DBTableGetIndex(DBIdx_Data, "Module_Equation");
	
	//delete records in Module input name table
	DBTableIndex = DBTblIdx_ModuleInputName;
	NumOfDBTableRows = DBRecordsGetNum(DBIdx_Data, DBTableIndex);
	for (i = NumOfDBTableRows; i >= 1; i--)
	{
		DBDataValue = DBDataGetAsString(DBIdx_Data, DBTableIndex, 1, i);
		if (DBDataValue == "4-User Equations" OR DBDataValue == "3-BPI Equations")
		{
			DBRecordsDelete(DBIdx_Data, DBTableIndex, i, i);
		}
	}
	
	//delete records in Module input Value table
	DBTableIndex = DBTblIdx_ModuleInputValue;
	NumOfDBTableRows = DBRecordsGetNum(DBIdx_Data, DBTableIndex);
	for (i = NumOfDBTableRows; i >= 1; i--)
	{
		DBDataValue = DBDataGetAsString(DBIdx_Data, DBTableIndex, 1, i);
		if (DBDataValue == "4-User Equations" OR DBDataValue == "3-BPI Equations")
		{
			DBRecordsDelete(DBIdx_Data, DBTableIndex, i, i);
		}
	}
	
	//delete records in Module input Unit table
	DBTableIndex = DBTblIdx_ModuleInputUnit;
	NumOfDBTableRows = DBRecordsGetNum(DBIdx_Data, DBTableIndex);
	for (i = NumOfDBTableRows; i >= 1; i--)
	{
		DBDataValue = DBDataGetAsString(DBIdx_Data, DBTableIndex, 1, i);
		if (DBDataValue == "4-User Equations" OR DBDataValue == "3-BPI Equations")
		{
			DBRecordsDelete(DBIdx_Data, DBTableIndex, i, i);
		}
	}
	
	//delete records in Module Output Name table
	DBTableIndex = DBTblIdx_ModuleOutputName;
	NumOfDBTableRows = DBRecordsGetNum(DBIdx_Data, DBTableIndex);
	for (i = NumOfDBTableRows; i >= 1; i--)
	{
		DBDataValue = DBDataGetAsString(DBIdx_Data, DBTableIndex, 1, i);
		if (DBDataValue == "4-User Equations" OR DBDataValue == "3-BPI Equations")
		{
			DBRecordsDelete(DBIdx_Data, DBTableIndex, i, i);
		}
	}
	
	//delete records in Module Output Unit table
	DBTableIndex = DBTblIdx_ModuleOutputUnit;
	NumOfDBTableRows = DBRecordsGetNum(DBIdx_Data, DBTableIndex);
	for (i = NumOfDBTableRows; i >= 1; i--)
	{
		DBDataValue = DBDataGetAsString(DBIdx_Data, DBTableIndex, 1, i);
		if (DBDataValue == "4-User Equations" OR DBDataValue == "3-BPI Equations")
		{
			DBRecordsDelete(DBIdx_Data, DBTableIndex, i, i);
		}
	}
	
	//delete records in Module Equation table
	DBTableIndex = DBTblIdx_ModuleEquation;
	NumOfDBTableRows = DBRecordsGetNum(DBIdx_Data, DBTableIndex);
	for (i = NumOfDBTableRows; i >= 1; i--)
	{
		DBDataValue = DBDataGetAsString(DBIdx_Data, DBTableIndex, 1, i);
		if (DBDataValue == "4-User Equations" OR DBDataValue == "3-BPI Equations")
		{
			DBRecordsDelete(DBIdx_Data, DBTableIndex, i, i);
		}
	}
	
	//populate equation parameters from equation editor database table
	NumOfDBTableRows = DBRecordsGetNum(DBIdx_EQ, DBTblIdx_DBEQIOs);
	if (NumOfDBTableRows > 0)
	{
		for (i = 1; i <= NumOfDBTableRows; i++)
		{
			NewEquationName = DBDataGetAsString(DBIdx_EQ, DBTblIdx_DBEQIOs, 1, i);
			EQCategory = DBDataGetAsString(DBIdx_EQ, DBTblIdx_DBEQDescriptions, 4, DBRecordFind(DBIdx_EQ, DBTblIdx_DBEQDescriptions, 1, 1, TRUE, NewEquationName));
			
			OldEquationName = BLANK;
			if(i != 1) OldEquationName = DBDataGetAsString(DBIdx_EQ, DBTblIdx_DBEQIOs, 1, i-1);
			
			if (NewEquationName != OldEquationName)
			{
				DBRecordsInsert(DBIdx_Data, DBTblIdx_ModuleInputName, 1, 1);
				DBRecordsInsert(DBIdx_Data, DBTblIdx_ModuleInputValue, 1, 1);
				DBRecordsInsert(DBIdx_Data, DBTblIdx_ModuleInputUnit, 1, 1);
				DBRecordsInsert(DBIdx_Data, DBTblIdx_ModuleOutputName, 1, 1);
				DBRecordsInsert(DBIdx_Data, DBTblIdx_ModuleOutputUnit, 1, 1);
				DBRecordsInsert(DBIdx_Data, DBTblIdx_ModuleEquation, 1, 1);
				
				DBDataSetAsString(DBIdx_Data, DBTblIdx_ModuleInputName, 1, 1, EQCategory);
				DBDataSetAsString(DBIdx_Data, DBTblIdx_ModuleInputValue, 1, 1, EQCategory);
				DBDataSetAsString(DBIdx_Data, DBTblIdx_ModuleInputUnit, 1, 1, EQCategory);
				DBDataSetAsString(DBIdx_Data, DBTblIdx_ModuleOutputName, 1, 1, EQCategory);
				DBDataSetAsString(DBIdx_Data, DBTblIdx_ModuleOutputUnit, 1, 1, EQCategory);
				DBDataSetAsString(DBIdx_Data, DBTblIdx_ModuleEquation, 1, 1, EQCategory);
				
				DBDataSetAsString(DBIdx_Data, DBTblIdx_ModuleInputName, 2, 1, NewEquationName);
				DBDataSetAsString(DBIdx_Data, DBTblIdx_ModuleInputValue, 2, 1, NewEquationName);
				DBDataSetAsString(DBIdx_Data, DBTblIdx_ModuleInputUnit, 2, 1, NewEquationName);
				DBDataSetAsString(DBIdx_Data, DBTblIdx_ModuleOutputName, 2, 1, NewEquationName);
				DBDataSetAsString(DBIdx_Data, DBTblIdx_ModuleOutputUnit, 2, 1, NewEquationName);
				DBDataSetAsString(DBIdx_Data, DBTblIdx_ModuleEquation, 2, 1, NewEquationName);
				
				for (j = 1; j <= DBRecordsGetNum(DBIdx_EQ, DBTblIdx_DBEQDescriptions); j++)
				{
					if (DBDataGetAsString(DBIdx_EQ, DBTblIdx_DBEQDescriptions, 1, j) == NewEquationName)
					{
						DBDataSetAsString(DBIdx_Data, DBTblIdx_ModuleEquation, 4, 1, DBDataGetAsString(DBIdx_EQ, DBTblIdx_DBEQDescriptions, 3, j));
						
						BREAK;
					}
				}
				
				li_InputCount = 0;
				li_OutputCount = 0;
				
				if (DBDataGetAsString(DBIdx_EQ, DBTblIdx_DBEQIOs, 2, i) == "Input")
				{
					li_InputCount++;
					
					DBDataValue = DBDataGetAsString(DBIdx_EQ, DBTblIdx_DBEQIOs, 4, i);
					DBDataSetAsString(DBIdx_Data, DBTblIdx_ModuleInputName, 3+li_InputCount, 1, DBDataValue);
					
					DBDataValue = DBDataGetAsString(DBIdx_EQ, DBTblIdx_DBEQIOs, 5, i);
					DBDataSetAsString(DBIdx_Data, DBTblIdx_ModuleInputValue, 3+li_InputCount, 1, DBDataValue);
					
					DBDataValue = DBDataGetAsString(DBIdx_EQ, DBTblIdx_DBEQIOs, 6, i);
					DBDataSetAsString(DBIdx_Data, DBTblIdx_ModuleInputUnit, 3+li_InputCount, 1, DBDataValue);
					
					DBDataSetAsString(DBIdx_Data, DBTblIdx_ModuleInputName, 3, 1, li_InputCount);
					DBDataSetAsString(DBIdx_Data, DBTblIdx_ModuleInputValue, 3, 1, li_InputCount);
					DBDataSetAsString(DBIdx_Data, DBTblIdx_ModuleInputUnit, 3, 1, li_InputCount);
				}
			}
			
			else
			{
				if (DBDataGetAsString(DBIdx_EQ, DBTblIdx_DBEQIOs, 2, i) == "Input")
				{
					li_InputCount++;
					
					DBDataValue = DBDataGetAsString(DBIdx_EQ, DBTblIdx_DBEQIOs, 4, i);
					DBDataSetAsString(DBIdx_Data, DBTblIdx_ModuleInputName, 3+li_InputCount, 1, DBDataValue);
					
					DBDataValue = DBDataGetAsString(DBIdx_EQ, DBTblIdx_DBEQIOs, 5, i);
					DBDataSetAsString(DBIdx_Data, DBTblIdx_ModuleInputValue, 3+li_InputCount, 1, DBDataValue);
					
					DBDataValue = DBDataGetAsString(DBIdx_EQ, DBTblIdx_DBEQIOs, 6, i);
					DBDataSetAsString(DBIdx_Data, DBTblIdx_ModuleInputUnit, 3+li_InputCount, 1, DBDataValue);
					
					DBDataSetAsString(DBIdx_Data, DBTblIdx_ModuleInputName, 3, 1, li_InputCount);
					DBDataSetAsString(DBIdx_Data, DBTblIdx_ModuleInputValue, 3, 1, li_InputCount);
					DBDataSetAsString(DBIdx_Data, DBTblIdx_ModuleInputUnit, 3, 1, li_InputCount);
				}
				
				else if (DBDataGetAsString(DBIdx_EQ, DBTblIdx_DBEQIOs, 2, i) == "Output")
				{
					li_OutputCount++;
					
					DBDataValue = DBDataGetAsString(DBIdx_EQ, DBTblIdx_DBEQIOs, 4, i);
					DBDataSetAsString(DBIdx_Data, DBTblIdx_ModuleOutputName, 3+li_OutputCount, 1, DBDataValue);
					
					DBDataValue = DBDataGetAsString(DBIdx_EQ, DBTblIdx_DBEQIOs, 6, i);
					DBDataSetAsString(DBIdx_Data, DBTblIdx_ModuleOutputUnit, 3+li_OutputCount, 1, DBDataValue);
					
					DBDataSetAsString(DBIdx_Data, DBTblIdx_ModuleOutputName, 3, 1, li_OutputCount);
					DBDataSetAsString(DBIdx_Data, DBTblIdx_ModuleOutputUnit, 3, 1, li_OutputCount);
				}
			}
		}
		
		DBTableSort(DBIdx_Data, DBTblIdx_ModuleInputName, 1, TRUE, 2, TRUE, 0, 0);
		DBTableSort(DBIdx_Data, DBTblIdx_ModuleInputValue, 1, TRUE, 2, TRUE, 0, 0);
		DBTableSort(DBIdx_Data, DBTblIdx_ModuleInputUnit, 1, TRUE, 2, TRUE, 0, 0);
		DBTableSort(DBIdx_Data, DBTblIdx_ModuleOutputName, 1, TRUE, 2, TRUE, 0, 0);
		DBTableSort(DBIdx_Data, DBTblIdx_ModuleOutputUnit, 1, TRUE, 2, TRUE, 0, 0);
		DBTableSort(DBIdx_Data, DBTblIdx_ModuleEquation, 1, TRUE, 2, TRUE, 0, 0);
	}
}










// This procedure create Database and Database tables for Equation Block, Chiu 06/29/2015 //
Procedure CreateEquationDatabase()
{
	Integer DBEQ;
	Integer DBTblIdx_DBEQIOs;
	Integer DBTblIdx_DBEQs;
	Integer DBTblIdx_DBEQDescriptions;
	
	DBEQ = DBDatabaseGetIndex("DB_Equation");
	
	if (DBEQ < 0)
	{
		DBEQ = DBDatabaseCreate("DB_Equation");
		
		DBTblIdx_DBEQIOs = DBTableCreateByIndex(DBEQ, "DBEquationInputOutputs");
		DBFieldCreateByIndex(DBEQ, DBTblIdx_DBEQIOs, "EquationName", DB_FIELDTYPE_STRING_VALUE, 0, 0, 0, 0);
		DBFieldCreateByIndex(DBEQ, DBTblIdx_DBEQIOs, "InputOutput", DB_FIELDTYPE_STRING_VALUE, 0, 0, 0, 0);
		DBFieldCreateByIndex(DBEQ, DBTblIdx_DBEQIOs, "VariableType", DB_FIELDTYPE_STRING_VALUE, 0, 0, 0, 0);
		DBFieldCreateByIndex(DBEQ, DBTblIdx_DBEQIOs, "VariableName", DB_FIELDTYPE_STRING_VALUE, 0, 0, 0, 0);
		DBFieldCreateByIndex(DBEQ, DBTblIdx_DBEQIOs, "Value", DB_FIELDTYPE_STRING_VALUE, 0, 0, 0, 0);
		DBFieldCreateByIndex(DBEQ, DBTblIdx_DBEQIOs, "Unit", DB_FIELDTYPE_STRING_VALUE, 0, 0, 0, 0);
		
		DBTblIdx_DBEQs = DBTableCreateByIndex(DBEQ, "DBEquations");
		DBFieldCreateByIndex(DBEQ, DBTblIdx_DBEQs, "EquationName", DB_FIELDTYPE_STRING_VALUE, 0, 0, 0, 0);
		DBFieldCreateByIndex(DBEQ, DBTblIdx_DBEQs, "EquationRIdx", DB_FIELDTYPE_STRING_VALUE, 0, 0, 0, 0);
		DBFieldCreateByIndex(DBEQ, DBTblIdx_DBEQs, "Equation", DB_FIELDTYPE_STRING_VALUE, 0, 0, 0, 0);
		DBFieldCreateByIndex(DBEQ, DBTblIdx_DBEQs, "EquationV2", DB_FIELDTYPE_STRING_VALUE, 0, 0, 0, 0);
		
		DBTblIdx_DBEQDescriptions = DBTableCreateByIndex(DBEQ, "DBEquationDescriptions");
		DBFieldCreateByIndex(DBEQ, DBTblIdx_DBEQDescriptions, "EquationName", DB_FIELDTYPE_STRING_VALUE, 0, 0, 0, 0);
		DBFieldCreateByIndex(DBEQ, DBTblIdx_DBEQDescriptions, "EquationPointer", DB_FIELDTYPE_STRING_VALUE, 0, 0, 0, 0);
		DBFieldCreateByIndex(DBEQ, DBTblIdx_DBEQDescriptions, "EquationDescription", DB_FIELDTYPE_STRING_VALUE, 0, 0, 0, 0);
	}
}


// This procedure gets the DB Indexes for the DB Equation block.
procedure GetDBIndexes()
{
	giDBIdx = DBDatabaseGetIndex("DB_Equation");

	// Input Outputs Table
	giDBEquationInputOutputsTIdx = DBTableGetIndex(giDBIdx, "DBEquationInputOutputs");
	giEquationNameEqIOFIdx = DBFieldGetIndex(giDBIdx, giDBEquationInputOutputsTIdx, "EquationName");
	giInputOutputEqIOFIdx = DBFieldGetIndex(giDBIdx, giDBEquationInputOutputsTIdx, "InputOutput");
	giVariableTypeEqIOFIdx = DBFieldGetIndex(giDBIdx, giDBEquationInputOutputsTIdx, "VariableType");
	giVariableNameEqIOFIdx = DBFieldGetIndex(giDBIdx, giDBEquationInputOutputsTIdx, "VariableName");
	giValueEqIOFIdx = DBFieldGetIndex(giDBIdx, giDBEquationInputOutputsTIdx, "Value");
	giUnitEqIOFIdx = DBFieldGetIndex(giDBIdx, giDBEquationInputOutputsTIdx, "Unit");
	
	// Equation Code Table
	giDBEquationsTIdx = DBTableGetIndex(giDBIdx, "DBEquations");
	giEquationNameEqFIdx = DBFieldGetIndex(giDBIdx, giDBEquationsTIdx, "EquationName");
	giEquationRIdxEqFIdx = DBFieldGetIndex(giDBIdx, giDBEquationsTIdx, "EquationRIdx");
	giEquationEqFIdx = DBFieldGetIndex(giDBIdx, giDBEquationsTIdx, "Equation");
	giEquationEqV2FIdx = DBFieldGetIndex(giDBIdx, giDBEquationsTIdx, "EquationV2");
	giEquationPointerEqFIdx = DBFieldGetIndex(giDBIdx, giDBEquationsTIdx, "Pointer");
	
	// Description Table
	giDBEquationDescriptionsTIdx = DBTableGetIndex(giDBIdx, "DBEquationDescriptions");
	giEquationNameEqDFIdx = DBFieldGetIndex(giDBIdx, giDBEquationDescriptionsTIdx, "EquationName");
	giEquationPointerEqDFIdx = DBFieldGetIndex(giDBIdx, giDBEquationDescriptionsTIdx, "EquationPointer");
	giEquationDescriptionEqDFIdx = DBFieldGetIndex(giDBIdx, giDBEquationDescriptionsTIdx, "EquationDescription");

} // procedure GetDBIndexes()

************************************************
// If this equation name is already in the database then return True.
integer IsThisEquationNameAlreadyUsed(string thisEquationName)
{
	integer i;
	integer liNumOfRecords;
	string lsValue;

	// DBEquationInputOutputs Table
	liNumOfRecords = DBRecordsGetNum(giDBIdx, giDBEquationInputOutputsTIdx);
	for(i = 1; i <= liNumOfRecords; i++)
	{
		lsValue = DBDataGetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giEquationNameEqIOFIdx, i);
		if(StringCompare(lsValue, thisEquationName, False, False) == 0)
			return True;	// A match has been found
	}
	
	// DBEquations Table
	liNumOfRecords = DBRecordsGetNum(giDBIdx, giDBEquationsTIdx);
	for(i = 1; i <= liNumOfRecords; i++)
	{
		lsValue = DBDataGetAsString(giDBIdx, giDBEquationsTIdx, giEquationNameEqFIdx, i);
		if(StringCompare(lsValue, thisEquationName, False, False) == 0)
			return True;	// A match has been found
	}
	
	// DBEquationDescriptions Table
	liNumOfRecords = DBRecordsGetNum(giDBIdx, giDBEquationDescriptionsTIdx);
	for(i = 1; i <= liNumOfRecords; i++)
	{
		lsValue = DBDataGetAsString(giDBIdx, giDBEquationDescriptionsTIdx, giEquationNameEqDFIdx, i);
		if(StringCompare(lsValue, thisEquationName, False, False) == 0)
			return True;	// A match has been found	
	}	
	return False;

} // integer IsThisEquationNameAlreadyUsed(string thisEquationName)

************************************************
// This function returns the Equation ID
integer GetEquationID(string thisEquationName)
{
	integer i;
	integer liNumOfRecords;
	string lsValue;

	liNumOfRecords = DBRecordsGetNum(giDBIdx, giDBEquationDescriptionsTIdx);
	for(i = liNumOfRecords; i >= 1; i--)
	{
		lsValue = DBDataGetAsString(giDBIdx, giDBEquationDescriptionsTIdx, giEquationNameEqDFIdx, i);
		if(StringCompare(lsValue, thisEquationName, False, False) == 0)
			return i;	// A match has been found.  
	}
	return -1;	// No match has been found

} // integer GetEquationID(string thisEquationName)

************************************************
// This procedure renames the DB Equation Name in the database tables.
procedure RenameEquationInDB(string thisNewEquationName, string thisOldEquationName)
{
	integer i;
	integer liNumOfRecords;
	string lsValue;

	// DBEquationInputOutputs Table
	liNumOfRecords = DBRecordsGetNum(giDBIdx, giDBEquationInputOutputsTIdx);
	for(i = 1; i <= liNumOfRecords; i++)
	{
		lsValue = DBDataGetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giEquationNameEqIOFIdx, i);
		if(StringCompare(lsValue, thisOldEquationName, False, False) == 0)
			// A match has been found.  Must rename the DB Equation.
			DBDataSetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giEquationNameEqIOFIdx, i, thisNewEquationName);
	}
	
	// DBEquations Table
	liNumOfRecords = DBRecordsGetNum(giDBIdx, giDBEquationsTIdx);
	for(i = 1; i <= liNumOfRecords; i++)
	{
		lsValue = DBDataGetAsString(giDBIdx, giDBEquationsTIdx, giEquationNameEqFIdx, i);
		if(StringCompare(lsValue, thisOldEquationName, False, False) == 0)
			// A match has been found.  Must rename the DB Equation.
			DBDataSetAsString(giDBIdx, giDBEquationsTIdx, giEquationNameEqFIdx, i, thisNewEquationName);
	}

	// DBEquationDescriptions Table
	liNumOfRecords = DBRecordsGetNum(giDBIdx, giDBEquationDescriptionsTIdx);
	for(i = 1; i <= liNumOfRecords; i++)
	{
		lsValue = DBDataGetAsString(giDBIdx, giDBEquationDescriptionsTIdx, giEquationNameEqDFIdx, i);
		if(StringCompare(lsValue, thisOldEquationName, False, False) == 0)
			// A match has been found.  Must rename the DB Equation.
			DBDataSetAsString(giDBIdx, giDBEquationDescriptionsTIdx, giEquationNameEqDFIdx, i, thisNewEquationName);
	}

} // procedure RenameEquationInDB(string thisNewEquationName, string thisOldEquationName)

************************************************
// This procedure will go through the two primary equation database tables and deletes the records with the given Equation name.  
procedure DeleteEquationFromDB(string thisEquationName)
{
	integer i;
	integer liNumOfRecords;
	string lsValue;

	// DBEquationInputOutputs Table
	liNumOfRecords = DBRecordsGetNum(giDBIdx, giDBEquationInputOutputsTIdx);
	for(i = liNumOfRecords; i >= 1; i--)
	{
		lsValue = DBDataGetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giEquationNameEqIOFIdx, i);
		if(StringCompare(lsValue, thisEquationName, False, False) == 0)
			// A match has been found.  Must Delete the DB Equation.
			DBRecordsDelete(giDBIdx, giDBEquationInputOutputsTIdx, i, i);
	}
	
	// DBEquations Table
	liNumOfRecords = DBRecordsGetNum(giDBIdx, giDBEquationsTIdx);
	for(i = liNumOfRecords; i >= 1; i--)
	{
		lsValue = DBDataGetAsString(giDBIdx, giDBEquationsTIdx, giEquationNameEqFIdx, i);
		if(StringCompare(lsValue, thisEquationName, False, False) == 0)
			// A match has been found.  Must Delete the DB Equation.
			DBRecordsDelete(giDBIdx, giDBEquationsTIdx, i, i);
	}
	
	// DBEquationDescriptions Table
	liNumOfRecords = DBRecordsGetNum(giDBIdx, giDBEquationDescriptionsTIdx);
	for(i = liNumOfRecords; i >= 1; i--)
	{
		lsValue = DBDataGetAsString(giDBIdx, giDBEquationDescriptionsTIdx, giEquationNameEqDFIdx, i);
		if(StringCompare(lsValue, thisEquationName, False, False) == 0)
			// A match has been found.  Must Delete the DB Equation.
			DBRecordsDelete(giDBIdx, giDBEquationDescriptionsTIdx, i, i);
	}

} // procedure DeleteEquationFromDB(string thisEquationName)

************************************************
// This procedure will add the input variables to the database for the specified equation. 
procedure AddInputVariablesToDatabase(string thisEquationName)
{
	integer i;
	integer liNumOfRecords;

	real lrValue;
	string lsValue;

	// if there are no input variables associated with this DB Equation then no need of adding this to the table.
	iVars_NumTableRows = GetDimension(iVars_ttbl);
	
	if( iVars_NumTableRows <= 0)
		return;

	// Add the input variables
	for(i = 0; i < iVars_NumTableRows; i++)
	{
		liNumOfRecords = 1 + DBRecordsGetNum(giDBIdx, giDBEquationInputOutputsTIdx);
		DBRecordsInsert(giDBIdx, giDBEquationInputOutputsTIdx, liNumOfRecords, 1);
		
		DBDataSetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giEquationNameEqIOFIdx, liNumOfRecords, thisEquationName);
		DBDataSetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giInputOutputEqIOFIdx, liNumOfRecords, csInputName);

		lsValue = iVars_ttbl[i][I_VAR_TYPE_COL];
		DBDataSetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giVariableTypeEqIOFIdx, liNumOfRecords, lsValue);

		lsValue = iVars_ttbl[i][I_VAR_NAME_COL];
		DBDataSetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giVariableNameEqIOFIdx, liNumOfRecords, lsValue);

		lsValue = iVars_ttbl[i][I_VAR_VALUE_COL];
		DBDataSetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giValueEqIOFIdx, liNumOfRecords, lsValue);

		lsValue = iVars_ttbl[i][I_VAR_UNIT_COL];
		DBDataSetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giUnitEqIOFIdx, liNumOfRecords, lsValue);
	}

	// When finisthed, resort the table.
	DBTableSort(giDBIdx, giDBEquationInputOutputsTIdx, giEquationNameEqIOFIdx, True, giInputOutputEqIOFIdx, True, 0, 0);

} // procedure AddInputVariablesToDatabase(string thisEquationName)

************************************************
// This procedure will add the output variables to the database for the specified equation. 
procedure AddOutputVariablesToDatabase(string thisEquationName)
{
	integer i;
	integer liNumOfRecords;

	real lrValue;
	string lsValue;

	// if there are no output variables associated with this DB Equation then no need of adding this to the table.
	oVars_NumTableRows = GetDimension(oVars_ttbl);
	
	if(oVars_NumTableRows <= 0)
		return;

	// Add the output variables
	for(i = 0; i < oVars_NumTableRows; i++)
	{
		liNumOfRecords = 1 + DBRecordsGetNum(giDBIdx, giDBEquationInputOutputsTIdx);
		DBRecordsInsert(giDBIdx, giDBEquationInputOutputsTIdx, liNumOfRecords, 1);
		DBDataSetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giEquationNameEqIOFIdx, liNumOfRecords, thisEquationName);
		DBDataSetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giInputOutputEqIOFIdx, liNumOfRecords, csOutputName);

		lsValue = oVars_ttbl[i][O_VAR_TYPE_COL];
		DBDataSetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giVariableTypeEqIOFIdx, liNumOfRecords, lsValue);

		lsValue = oVars_ttbl[i][O_VAR_NAME_COL];
		DBDataSetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giVariableNameEqIOFIdx, liNumOfRecords, lsValue);

		lsValue = oVars_ttbl[i][O_VAR_VALUE_COL];
		DBDataSetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giValueEqIOFIdx, liNumOfRecords, lsValue);

		lsValue = oVars_ttbl[i][O_VAR_UNIT_COL];
		DBDataSetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giUnitEqIOFIdx, liNumOfRecords, lsValue);
	}

	// When finisthed, resort the table.
	DBTableSort(giDBIdx, giDBEquationInputOutputsTIdx, giEquationNameEqIOFIdx, True, giInputOutputEqIOFIdx, True, 0, 0);

} // procedure AddOutputVariablesToDatabase(string thisEquationName)

************************************************
procedure GeneratePointerToEquation(string thisEquationName)
{
	integer i;
	integer liNumOfRecords1;
	integer liNumOfRecords2;
	integer liNumOfRecords3;
	integer liPointer;
	integer liStringLen;
	integer liSizeEquationArray;
	integer liInputCount;
	integer liOutputCount;
	integer liStartChar;
	integer liEquationRId;
	
	string lsEquationName;
	string lsInputOutput;
	string lsVariableName;
	string lsReplaceWith;

	liNumOfRecords1 = DBRecordsGetNum(giDBIdx, giDBEquationDescriptionsTIdx);
	liNumOfRecords2 = DBRecordsGetNum(giDBIdx, giDBEquationsTIdx);
	liNumOfRecords3 = DBRecordsGetNum(giDBIdx, giDBEquationInputOutputsTIdx);

	DisposeArray(gsTempEquation);
	MakeArray(gsTempEquation, liNumOfRecords2);

	liEquationRId = 0;
	for(i = 1; i <= liNumOfRecords2; i++)
	{
		lsEquationName = DBDataGetAsString(giDBIdx, giDBEquationsTIdx, giEquationNameEqIOFIdx, i);
		if(StringCompare(lsEquationName, thisEquationName, False, False) == 0)
		{
			gsTempEquation[liEquationRId] = DBDatagetAsString(giDBIdx, giDBEquationsTIdx, giEquationEqFIdx, i);
			liEquationRId++;
		}
	}

	// Replace the input variables with iV[X]
	liInputCount = 0;
	for(i = 1; i <= liNumOfRecords3; i++)
	{
		lsEquationName = DBDataGetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giEquationNameEqIOFIdx, i);
		lsInputOutput = DBDataGetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giInputOutputEqIOFIdx, i);
		lsVariableName = DBDataGetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giVariableNameEqIOFIdx, i);
		liStringLen = StrLen(lsVariableName);
		if(StringCompare(lsEquationName, thisEquationName, False, False) == 0 and StringCompare(lsInputOutput, csInputName, False, False) == 0)
		{
			liStartChar = StrFindDynamic(gsTempEquation, lsVariableName, false, false, true);
			while (liStartChar >= 0)
			{
				lsReplaceWith = "iV[" + liInputCount + "]";
				StrReplaceDynamic(gsTempEquation, liStartChar, liStringLen, lsReplaceWith);
				liStartChar = StrFindDynamic(gsTempEquation, lsVariableName, false, false, true);
			}//END while ()
			liInputCount++;
		}
	}

	// Replace the input variables with oV[X]
	liOutputCount = 0;
	for(i = 1; i <= liNumOfRecords3; i++)
	{
		lsEquationName = DBDataGetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giEquationNameEqIOFIdx, i);
		lsInputOutput = DBDataGetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giInputOutputEqIOFIdx, i);
		lsVariableName = DBDataGetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giVariableNameEqIOFIdx, i);
		liStringLen = StrLen(lsVariableName);
		if(StringCompare(lsEquationName, thisEquationName, False, False) == 0 and StringCompare(lsInputOutput, csOutputName, False, False) == 0)
		{
			liStartChar = StrFindDynamic(gsTempEquation, lsVariableName, false, false, true);
			while (liStartChar >= 0)
			{
				lsReplaceWith = "oV[" + liOutputCount + "]";
				StrReplaceDynamic(gsTempEquation, liStartChar, liStringLen, lsReplaceWith);
				liStartChar = StrFindDynamic(gsTempEquation, lsVariableName, false, false, true);
			}//END while ()
			liOutputCount++;
		}
	}
	
	MakeArray(gsTempEquation, liNumOfRecords2);

	// Add new equation to EquationV2 field
	liEquationRId = 0;
	for(i = 1; i <= liNumOfRecords2; i++)
	{
		lsEquationName = DBDataGetAsString(giDBIdx, giDBEquationsTIdx, giEquationNameEqIOFIdx, i);
		if(StringCompare(lsEquationName, thisEquationName, False, False) == 0)
		{
			DBDatasetAsString(giDBIdx, giDBEquationsTIdx, giEquationEqV2FIdx, i, gsTempEquation[liEquationRId]);
			liEquationRId++; // just in case there are more than 1 record.
		}	
	}

	// Create Pointer
	DisposeArray(CompiledEquation_da);
	MakeArray(CompiledEquation_da, 1);	
	EquationCompileDynamicVariables("iV", "oV", gsTempEquation, CompiledEquation_da, 1);
	liPointer = PointerFromDynamicArray(CompiledEquation_da);
	DisposeArray(CompiledEquation_da);
	DisposeArray(gsTempEquation);

	for(i = 1; i <= liNumOfRecords1; i++)
	{
		lsEquationName = DBDataGetAsString(giDBIdx, giDBEquationDescriptionsTIdx, giEquationNameEqDFIdx, i);
		if(StringCompare(lsEquationName, thisEquationName, False, False) == 0)
		{
			DBDataSetAsNumber(giDBIdx, giDBEquationDescriptionsTIdx, giEquationPointerEqDFIdx, i, liPointer);
			return;
		}
	}

} // procedure GeneratePointerToEquation(string thisEquationName)

************************************************
// This procedure will add the actual equaiton code to the database for the specified equation. 
procedure AddEquationToDatabase(string thisEquationName)
{
	integer i;
	integer liSizeEquationArray;
	integer liNumOfRecords;
	integer liRecNo;

	liSizeEquationArray = GetDimension(EQ_EquationText);

	// If there are no code associated with this DB Equation then no need of adding this to the table.
	if( liSizeEquationArray <= 0)
		return;

	// Add the actual equation string to DB
	liNumOfRecords = DBRecordsGetNum(giDBIdx, giDBEquationsTIdx);
	DBRecordsInsert(giDBIdx, giDBEquationsTIdx, liNumOfRecords + 1, liSizeEquationArray);
	for (i = 1; i <= liSizeEquationArray; i++)
	{
		liRecNo = liNumOfRecords + i;
		DBDataSetAsString(giDBIdx, giDBEquationsTIdx, giEquationNameEqFIdx, liRecNo, thisEquationName);
		DBDataSetAsNumber(giDBIdx, giDBEquationsTIdx, giEquationRIdxEqFIdx, liRecNo, i-1);		
		DBDataSetAsString(giDBIdx, giDBEquationsTIdx, giEquationEqFIdx, liRecNo, EQ_EquationText[i-1]);		
	}

	// When finisthed, resort the table.
	DBTableSort(giDBIdx, giDBEquationsTIdx, giEquationNameEqFIdx, True, giEquationRIdxEqFIdx, True, False, False);

} // procedure AddEquationToDatabase(string thisEquationName)

************************************************
// This procedure will add the DB Equation description to the database for the specified equation. 
procedure AddEquationDescriptionToDatabase(string thisEquationName)
{
	integer liNumOfRecords;

	// Add the description
	liNumOfRecords = 1 + DBRecordsGetNum(giDBIdx, giDBEquationDescriptionsTIdx);
	DBRecordsInsert(giDBIdx, giDBEquationDescriptionsTIdx, liNumOfRecords, 1);
	DBDataSetAsString(giDBIdx, giDBEquationDescriptionsTIdx, giEquationNameEqDFIdx, liNumOfRecords, thisEquationName);
	DBDataSetAsString(giDBIdx, giDBEquationDescriptionsTIdx, giEquationDescriptionEqDFIdx, liNumOfRecords, dETxtEquationDescription);
	DBDataSetAsString(giDBIdx, giDBEquationDescriptionsTIdx, 4, liNumOfRecords, txt_Category);
	DBDataSetAsString(giDBIdx, giDBEquationDescriptionsTIdx, 5, liNumOfRecords, txt_subCategory);

	// When finisthed, resort the table.
	DBTableSort(giDBIdx, giDBEquationDescriptionsTIdx, giEquationNameEqDFIdx, True, False, False, False, False);

} // procedure AddEquationDescriptionToDatabase(string thisEquationName)

************************************************
// This function will return the number of Input variables for the specified DB Equation.
integer FindNumberOfRecordsForInputVariables(string thisEquationName)
{
	integer i;
	integer liNumOfRecords;
	integer liNumOfVariables;

	string lsDBEquationName;
	string lsInputOutput;

	liNumOfVariables = 0;
	liNumOfRecords = DBRecordsGetNum(giDBIdx, giDBEquationInputOutputsTIdx);
	for(i = 1; i <= liNumOfRecords; i++)
	{
		lsDBEquationName = DBDataGetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giEquationNameEqIOFIdx, i);
		lsInputOutput = DBDataGetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giInputOutputEqIOFIdx, i);
		if(StringCompare(lsDBEquationName, thisEquationName, False, False) == 0 and StringCompare(lsInputOutput, csInputName, False, False) == 0)
			liNumOfVariables++;	// Found a match.  Increment by 1.
	}

	return liNumOfVariables;

} // integer FindNumberOfRecordsForInputVariables(string thisEquationName)

************************************************
// This function will return the number of Output variables for the specified DB Equation.
integer FindNumberOfRecordsForOutputVariables(string thisEquationName)
{
	integer i;
	integer liNumOfRecords;
	integer liNumOfVariables;

	string lsDBEquationName;
	string lsInputOutput;

	liNumOfVariables = 0;
	liNumOfRecords = DBRecordsGetNum(giDBIdx, giDBEquationInputOutputsTIdx);
	for(i = 1; i <= liNumOfRecords; i++)
	{
		lsDBEquationName = DBDataGetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giEquationNameEqIOFIdx, i);
		lsInputOutput = DBDataGetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giInputOutputEqIOFIdx, i);
		if(StringCompare(lsDBEquationName, thisEquationName, False, False) == 0 and StringCompare(lsInputOutput, csOutputName, False, False) == 0)
			liNumOfVariables++;	// Found a match.  Increment by 1.	
	}

	return liNumOfVariables;
} // integer FindNumberOfRecordsForOutputVariables(string thisEquationName)

************************************************
// This procedure will retrieve the DB Equation Input variables and put them in the DB Equation dialog.
procedure RetrieveDBInputs(string thisEquationName)
{
	integer i, j;
	integer liNumOfRecords;

	real lrValue;

	string lsDBEquationName;
	string lsInputOutput;
	string lsVarType;
	string lsVariableName;
	string lsValue;
	string lsUnits;
	
	iVars_NumTableRows = FindNumberOfRecordsForInputVariables(thisEquationName);
//	iVars_ResizeDynamicArrays(RESIZE_ADD_SUBTRACT_FROM_END);
	liNumOfRecords = DBRecordsGetNum(giDBIdx, giDBEquationInputOutputsTIdx);
	
	DisposeArray(iVars_DA);
	DisposeArray(iVars_Names);
	DisposeArray(iVars_Units);
	DisposeArray(iVars_Types_Int);
	DisposeArray(iVars_Types_Str);
	DisposeArray(iVars_Values);
	
	MakeArray(iVars_DA, iVars_NumTableRows);
	MakeArray(iVars_Names, iVars_NumTableRows);
	MakeArray(iVars_Units, iVars_NumTableRows);
	MakeArray(iVars_Types_Int, iVars_NumTableRows);
	MakeArray(iVars_Types_Str, iVars_NumTableRows);
	MakeArray(iVars_Values, iVars_NumTableRows);
	
	j = 0;
	for(i = 1; i <= liNumOfRecords; i++)
	{
		lsDBEquationName = DBDataGetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giEquationNameEqIOFIdx, i);
		lsInputOutput = DBDataGetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giInputOutputEqIOFIdx, i);
		lsVarType = DBDataGetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giVariableTypeEqIOFIdx, i);
		lsVariableName = DBDataGetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giVariableNameEqIOFIdx, i);
		lsValue = DBDataGetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giValueEqIOFIdx, i);
		lsUnits = DBDataGetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giUnitEqIOFIdx, i);

		if(StringCompare(lsDBEquationName, thisEquationName, False, False) == 0 and StringCompare(lsInputOutput, csInputName, False, False) == 0)
		{	
			// Found a match.  Take the Input variables found in the DB and post it to the DB Equation dialog.
			iVars_DA[j][I_VAR_NAME_COL] = lsVariableName;
			iVars_DA[j][I_VAR_UNIT_COL] = lsUnits;

			iVars_Names[j] = lsVariableName;
			iVars_Units[j] = lsUnits;

			// If it is integer
			if( StringCompare(lsVarType, csIntegerName, False, False) == False )
			{
				iVars_DA[j][I_VAR_TYPE_COL] = "Integer";
				iVars_DA[j][I_VAR_VALUE_COL] = Int(StrToReal(lsValue));
				iVars_Types_Int[j] = EQ_Integer;
				iVars_Types_Str[j] = "Integer";
				iVars_Values[j] = StrToReal(lsValue);
			}

			// If it is Real
			else if( StringCompare(lsVarType, csRealName, False, False) == False )
			{
				iVars_DA[j][I_VAR_TYPE_COL] = "Real";
				iVars_DA[j][I_VAR_VALUE_COL] = lsValue;
				iVars_Types_Int[j] = EQ_Real;
				iVars_Types_Str[j] = "Real";
				iVars_Values[j] = StrToReal(lsValue);
			}

			j++;
		}		
	}
	DynamicDataTable(MyBlockNumber(), "iVars_ttbl", iVars_DA);

} // procedure RetrieveDBInputs(string thisEquationName)

************************************************
// This procedure will retrieve the DB Equation Output variables and put them in the DB Equation dialog.
procedure RetrieveDBOutputs(string thisEquationName)
{
	integer i, j;
	integer liNumOfRecords;

	real lrValue;

	string lsDBEquationName;
	string lsInputOutput;
	string lsVarType;
	string lsVariableName;
	string lsUnits;
	string lsValue;

	oVars_NumTableRows = FindNumberOfRecordsForOutputVariables(thisEquationName);
//	oVars_ResizeDynamicArrays(EQUATION_BLOCK, RESIZE_ADD_SUBTRACT_FROM_END);
	liNumOfRecords = DBRecordsGetNum(giDBIdx, giDBEquationInputOutputsTIdx);
	
	DisposeArray(oVars_DA);
	DisposeArray(oVars_Names);
	DisposeArray(oVars_Units);
	DisposeArray(oVars_Types_Int);
	DisposeArray(oVars_Types_Str);
	DisposeArray(oVars_Values);
	
	MakeArray(oVars_DA, oVars_NumTableRows);
	MakeArray(oVars_Names, oVars_NumTableRows);
	MakeArray(oVars_Units, oVars_NumTableRows);
	MakeArray(oVars_Types_Int, oVars_NumTableRows);
	MakeArray(oVars_Types_Str, oVars_NumTableRows);
	MakeArray(oVars_Values, oVars_NumTableRows);
	
	j = 0;
	for(i = 1; i <= liNumOfRecords; i++)
	{
		lsDBEquationName = DBDataGetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giEquationNameEqIOFIdx, i);
		lsInputOutput = DBDataGetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giInputOutputEqIOFIdx, i);
		lsVarType = DBDataGetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giVariableTypeEqIOFIdx, i);
		lsVariableName = DBDataGetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giVariableNameEqIOFIdx, i);
		lsValue = DBDataGetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giValueEqIOFIdx, i);
		lsUnits = DBDataGetAsString(giDBIdx, giDBEquationInputOutputsTIdx, giUnitEqIOFIdx, i);
		
		if(StringCompare(lsDBEquationName, thisEquationName, False, False) == 0 and StringCompare(lsInputOutput, csOutputName, False, False) == 0)
		{	
			// Found a match.  Take the Output variables found in the DB and post it to the DB Equation dialog.
			oVars_DA[j][O_VAR_NAME_COL] = lsVariableName;
			oVars_DA[j][O_VAR_UNIT_COL] = lsUnits;

			oVars_Names[j] = lsVariableName;
			oVars_Units[j] = lsUnits;

			// If it is integer
			if( StringCompare(lsVarType, csIntegerName, False, False) == False )
			{
				oVars_ttbl[j][O_VAR_TYPE_COL] = "Integer";
				oVars_ttbl[j][O_VAR_VALUE_COL] = Int(StrToReal(lsValue));
				oVars_Types_Int[j] = EQ_Integer;
				oVars_Types_Str[j] = "Integer";
				oVars_Values[j] = StrToReal(lsValue);
			}

			// If it is Real
			else if( StringCompare(lsVarType, csRealName, False, False) == False )
			{
				oVars_DA[j][O_VAR_TYPE_COL] = "Real";
				oVars_DA[j][O_VAR_VALUE_COL] = lsValue;
				oVars_Types_Int[j] = EQ_Real;
				oVars_Types_Str[j] = "Real";
				oVars_Values[j] =  StrToReal(lsValue);
			}
			j++;
		}		
	}
	DynamicDataTable(MyBlockNumber(), "oVars_ttbl", oVars_DA);

} // procedure RetrieveDBOutputs(string thisEquationName)

************************************************
// This procedure will retrieve the DB Equation Code and put them in the DB Equation dialog.
procedure RetrieveDBEquation(string thisEquationName)
{
	integer i;
	integer liNumOfRecords;
	integer liRIdx;
	integer li_EqArrayRowCount;

	string lsDBEquationName;
	string lsDBEquation;

	liNumOfRecords = DBRecordsGetNum(giDBIdx, giDBEquationsTIdx);
	
	li_EqArrayRowCount = 0;
	for(i = 1; i <= liNumOfRecords; i++)
	{
		lsDBEquationName = DBDataGetAsString(giDBIdx, giDBEquationsTIdx, giEquationNameEqFIdx, i);
		if(StringCompare(lsDBEquationName, thisEquationName, False, False) == 0 )
		{
			li_EqArrayRowCount++;
			MakeArray(EQ_EquationText, li_EqArrayRowCount);
			// Found a match.  Take the Code found in the DB and post it to the DB Equation dialog.
			liRIdx = DBDataGetAsNumber(giDBIdx, giDBEquationsTIdx, giEquationRIdxEqFIdx, i);
			lsDBEquation = DBDataGetAsString(giDBIdx, giDBEquationsTIdx, giEquationEqFIdx, i);
			EQ_EquationText[liRIdx] = lsDBEquation;
		}
	}

} // procedure RetrieveDBEquation(string thisEquationName)

************************************************
// This procedure will retrieve the DB Equation Description and put them in the DB Equation dialog.
procedure RetrieveDBEquationDescription(string thisEquationName)
{
	integer i;
	integer liNumOfRecords;

	string lsDBEquationName;
	string lsDBEquationDescription;
	String ls_DBEQCategory;
	string ls_DBEQsubCategory;
	
	lsDBEquationDescription = "";
	liNumOfRecords = DBRecordsGetNum(giDBIdx, giDBEquationDescriptionsTIdx);
	for(i = 1; i <= liNumOfRecords; i++)
	{
		lsDBEquationName = DBDataGetAsString(giDBIdx, giDBEquationDescriptionsTIdx, giEquationNameEqDFIdx, i);
		if(StringCompare(lsDBEquationName, thisEquationName, False, False) == 0 )
		{
			// Found a match.  Take the Description found in the DB and post it to the DB Equation dialog.
			lsDBEquationDescription = DBDataGetAsString(giDBIdx, giDBEquationDescriptionsTIdx, giEquationDescriptionEqDFIdx, i);
			ls_DBEQCategory = DBDataGetAsString(giDBIdx, giDBEquationDescriptionsTIdx, 4, i);
			ls_DBEQsubCategory = DBDataGetAsString(giDBIdx, giDBEquationDescriptionsTIdx, 5, i);
			dETxtEquationDescription = lsDBEquationDescription;
			txt_Category = ls_DBEQCategory;
			txt_subCategory = ls_DBEQsubCategory;
		}
	}

} // procedure RetrieveDBEquationDescription(string thisEquationName)

************************************************
// This procedure will first remove the past equation from the database and then add the current setup to the database.
procedure AddEquationToDB(string thisEquationName)
{
	DeleteEquationFromDB(thisEquationName);
	AddInputVariablesToDatabase(thisEquationName);
	AddOutputVariablesToDatabase(thisEquationName);
	AddEquationDescriptionToDatabase(thisEquationName);
	AddEquationToDatabase(thisEquationName);
	GeneratePointerToEquation(thisEquationName);

} // procedure AddEquationToDB(string thisEquationName)

************************************************
// The gsDBEquationList array contains the complete list of all of the DB Equations.
procedure UpdateDBEquationListArray()
{
	integer i, j;
	integer liNumOfRecords;
	integer liDBEquationCount;
	integer liThisDBEquationIsAlreadyInList;

	string lsEquationNameInDB;
	string lsEquationNameInArray;

	DisposeArray(gsDBEquationList);
	liNumOfRecords = DBRecordsGetNum(giDBIdx, giDBEquationDescriptionsTIdx);
	MakeArray(gsDBEquationList, liNumOfRecords + 1);
	for (i = 1; i <= liNumOfRecords; i++)
		gsDBEquationList[i] = "";
	
	liDBEquationCount = 0;
	for (i = 1; i <= liNumOfRecords; i++) 
	{	
		liDBEquationCount++;
		lsEquationNameInDB = DBDataGetAsString(giDBIdx, giDBEquationDescriptionsTIdx, giEquationNameEqDFIdx, i);
		gsDBEquationList[liDBEquationCount] = lsEquationNameInDB;
	}
	
} // procedure UpdateDBEquationListArray()

************************************************
// This procedure populates the DB Equation block popup for the list of DB Equations.
/*
procedure GenerateDBEqtnPop() // remove this old function, Chiu 02/22/2016
{
	integer i;
	integer liNumOfDBEquations;
	string lsPopupValue;
	
	UpdateDBEquationListArray();
	liNumOfDBEquations = DBRecordsGetNum(giDBIdx, giDBEquationDescriptionsTIdx);
	lsPopupValue = "";
	for(i = 1; i <= liNumOfDBEquations; i++)
	{
		if(i > 1)
			lsPopupValue += ";";
			
		lsPopupValue += gsDBEquationList[i];
	}

	SetPopupLabels("dPopEquationSelect", lsPopupValue);

} // procedure GenerateDBEqtnPop()
*/

procedure GenerateDBEqtnPop()
{
	integer i;
	integer liNumOfDBEquations;
	long li_count;
	long DBTblIdx_subCategory;
	string ls_subCategory;
	long li_StartReocrdIdx;
	string ls_ModuleName;
	
	UpdateDBEquationListArray();
	liNumOfDBEquations = DBRecordsGetNum(giDBIdx, giDBEquationDescriptionsTIdx);
	DBTblIdx_subCategory = DBTableGetIndex(giDBIdx, "Module_subCategory");
	
	DisposeArray(array_Equationlist);
//	MakeArray(array_Equationlist, liNumOfDBEquations);

	if (txt_Category == "4-User Equations")
	{
		li_count = 0;
		for(i = 1; i <= liNumOfDBEquations; i++)
		{
			if (DBDataGetAsString(giDBIdx, giDBEquationDescriptionsTIdx, 4, i) == txt_Category)
			{
				li_count++;
				MakeArray(array_Equationlist, li_count);
				array_Equationlist[li_count-1] = DBDataGetAsString(giDBIdx, giDBEquationDescriptionsTIdx, 1, i);
			}
		}
	}
	
	else if (txt_Category == "3-BPI Equations")
	{
		li_count = 0;
		for (i = 1; i <= DBRecordsGetNum(giDBIdx, DBTblIdx_subCategory); i++)
		{
			li_count +=1;
			MakeArray(array_Equationlist, li_count);
			
			ls_subCategory = DBDataGetAsString(giDBIdx, DBTblIdx_subCategory, 1, i);
			
			array_Equationlist[li_count-1] = "<b>"+ls_subCategory;
			
			li_StartReocrdIdx = 1;
			while (li_StartReocrdIdx > 0 AND li_StartReocrdIdx <= DBRecordsGetNum(giDBIdx, giDBEquationDescriptionsTIdx))
			{
				li_StartReocrdIdx = DBRecordFind(giDBIdx, giDBEquationDescriptionsTIdx, 5, li_StartReocrdIdx, TRUE, ls_subCategory);
				
				if (li_StartReocrdIdx > 0 AND DBDataGetAsString(giDBIdx, giDBEquationDescriptionsTIdx, 4, li_StartReocrdIdx) == txt_Category)
				{
					ls_ModuleName = DBDataGetAsString(giDBIdx, giDBEquationDescriptionsTIdx, 1, li_StartReocrdIdx);
					
					li_count +=1;
					MakeArray(array_Equationlist, li_count);
					array_Equationlist[li_count-1] = ls_ModuleName;
					
					li_StartReocrdIdx++;
				}
			}
		}
	}
}

************************************************
// This procedure sets the popup value based on the specified equation name.
procedure SelectThisDBEquationPop(string thisEquationName)
{
	integer i;
	integer liNumOfDBEquations;
	string lsDBEquation;

	liNumOfDBEquations = DBRecordsGetNum(giDBIdx, giDBEquationDescriptionsTIdx);
	for(i = 1; i <= liNumOfDBEquations; i++)
	{
		lsDBEquation = gsDBEquationList[i];
		if(StringCompare(thisEquationName, lsDBEquation, False, False) == 0)
		{
			// I found a match.  This is the DB Equation Popup
			dPopEquationSelect = i;
			dETxtEquationName_1 = thisEquationName;
			return;
		}
	}

} // procedure SelectThisDBEquationPop(string thisEquationName)


************************************************
procedure doCarolloOpenModel()
{
	integer i;
	integer liNumRecords;
	string liDBEquationName;

	GetDBIndexes();	

	liNumRecords = DBRecordsGetNum(giDBIdx, giDBEquationDescriptionsTIdx);
	for(i = 1; i <= liNumRecords; i++)
	{
		liDBEquationName = DBDataGetAsString(giDBIdx, giDBEquationDescriptionsTIdx, giEquationNameEqDFIdx, i);
		GeneratePointerToEquation(liDBEquationName);
	}
}


************************************************
** Message Handlers
************************************************

// This message handler is called when the user clicks the Update button.  It will take the current specified DB Equation and add it to the 
//	database if it does not already exists.  If it does exists it will delete the current database data related to that DB Equation
//	and then add the current dialog data to the database.
on dBtnUpdate
{
	integer liEquationID;
	integer liPointer;
	string lsLastDBEquationSelected;
	string lsEquation;

	EQ_Compile(FALSE);
	GetDBIndexes();	
	lsLastDBEquationSelected = dETxtEquationName;
	AddEquationToDB(dETxtEquationName);	
	GenerateDBEqtnPop();
	SelectThisDBEquationPop(lsLastDBEquationSelected);
	UpdateEquationManager();

} // on dBtnUpdate

***********************************************
// This message handler is called when the user selects a specific DB Equation.  It will then popuplate the DB Equation block dialog
//	with the data found in the database.
on dPopEquationSelect
{
	integer liDimensions;
	integer liNumOfDBEquations;
	string lsEquationName;
	Integer li_UserResponse;
	
	GetDBIndexes();	
	liDimensions = GetDimension(gsDBEquationList);
	if (liDimensions == 0)
		UpdateDBEquationListArray();

	liDimensions = GetDimension(gsDBEquationList);
	if (liDimensions == 0)
		return;

	liNumOfDBEquations = DBRecordsGetNum(giDBIdx, giDBEquationDescriptionsTIdx);

	GenerateDBEqtnPop();
	
	li_UserResponse = PopupMenuArray(array_EquationList, 0) - 1;
	
	for (i = 0; i < GetDimension(array_EquationList); i++)
	{
		if (li_UserResponse == i AND StrFind(array_EquationList[i], "<b>", 0, 0) < 0)
		{
			dETxtEquationName = array_EquationList[i];
			dETxtEquationName_1 = array_EquationList[i];
			
			DIPopupButton(MyBlockNumber(), "dPopEquationSelect", TRUE);
			
			BREAK;
		}
	}
	
	RetrieveDBInputs(dETxtEquationName);	
	RetrieveDBOutputs(dETxtEquationName);
	RetrieveDBEquation(dETxtEquationName);
	RetrieveDBEquationDescription(dETxtEquationName);
	
	/*
	if (dPopEquationSelect > 0 and dPopEquationSelect <= liNumOfDBEquations)
	{
		dETxtEquationName = gsDBEquationList[dPopEquationSelect];
		RetrieveDBInputs(dETxtEquationName);	
		RetrieveDBOutputs(dETxtEquationName);
		RetrieveDBEquation(dETxtEquationName);
		RetrieveDBEquationDescription(dETxtEquationName);
	}
	*/
	
	equation_dtxt = DynamicTextArrayNumber(EQ_EquationText);

} // on dPopEquationSelect

************************************************
// This message handler will delete the selected DB Equation.
on dBtnDelete
{
	GetDBIndexes();	
	DeleteEquationFromDB(dETxtEquationName);
	dETxtEquationName = "";
	dETxtEquationDescription = "";
	UpdateDBEquationListArray();
	GenerateDBEqtnPop();

	DisposeArray(EQ_EquationText);
	MakeArray(EQ_EquationText, 1);
	EQ_EquationText[0] = "";
	equation_dtxt = DynamicTextArrayNumber(EQ_EquationText);

	iVars_NumTableRows = 0;
	MakeArray(iVars_DA, iVars_NumTableRows);
	DynamicDataTable(MyBlockNumber(), "iVars_ttbl", iVars_DA);
//	iVars_ResizeDynamicArrays(RESIZE_ADD_SUBTRACT_FROM_END);

	oVars_NumTableRows = 0;
	MakeArray(oVars_DA, oVars_NumTableRows);
	DynamicDataTable(MyBlockNumber(), "oVars_ttbl", oVars_DA);
//	oVars_ResizeDynamicArrays(EQUATION_BLOCK, RESIZE_ADD_SUBTRACT_FROM_END);

} // on dBtnDelete

************************************************
// This message handler will rename the selected DB Equation.
on dBtnRename
{
	integer liAlreadyInUse;
	string lsOldName;
	string lsNewName;

	GetDBIndexes();	
	lsOldName = dETxtEquationName;
	lsNewName = UserParameter("Please provide a new DB Equation Name", "");
	liAlreadyInUse = IsThisEquationNameAlreadyUsed(lsNewName);
	if(liAlreadyInUse == True)
	{
		// If the name is already in use then simply let the user know and exit out.
		UserError("This name is arealy in use.");
		return;
	}

	RenameEquationInDB(lsNewName, lsOldName);
	dETxtEquationName = lsNewName;
	GenerateDBEqtnPop();
	SelectThisDBEquationPop(lsNewName);

} // on dBtnRename
*************************************************
*************************************************
*************************************************
on EQ_TestEquation_btn
{

	integer i, j;
	integer me;
	integer numChars;
	string15 attribName;
	integer found;
	integer fieldType;
	integer legitField;
	integer parentInfo[3];
	integer currRecord;
	integer numRecords;
	integer PT_CurrBestRecordRank;
	integer S_CurrBestRecordRank;
	integer PT_NumNonBlankRankedRecords;
	integer S_NumNonBlankRankedRecords;
	integer parentArray[3];
	integer parentRecordIndex;
	integer parentParentRecordIndex;
	
	me = MyBlockNumber();
		
	EQ_Compile(FALSE);
	
//	oVarsOut_VarIsWhichConUpdate();	//make sure we know which output variables are connector variables before we calc
//	oVarsOut_ConIsWhichVarUpdate();
/*	
	//get the column IDs for the input varibles
	for(i=0; i<iVars_NumTableRows; i++)
		{
		if(iVars_Types_Int[i] == EQ_ITEM_ATTRIBUTE  ||  iVars_Types_Int[i] == EQ_DB_READ_VAL_USING_ATTRIB  ||  iVars_Types_Int[i] == EQ_DB_READ_PRI_USING_ATTRIB)
			{
			#ifdef EQ_IsItemBlock
				{
				iVars_AttribColumnIndexes[i] = Attrib_GetColumnIndex(iVars_Names[i]);
				}
			#endif
			}
		else
			iVars_AttribColumnIndexes[i] = PROPERTY_TYPE_NO_PROPERTY;
		}
	
	//get the column IDs for the output varibles
	for(i=0; i<oVars_NumTableRows; i++)
		{
		//if(StrFind(oVars_Types_str[i], "attrib", FALSE, FALSE) >= 0)	//AJN, 7.0.5, 10/24/08
		if(oVars_Types_Int[i] == EQ_ITEM_ATTRIBUTE  ||  oVars_Types_Int[i] == EQ_DB_WRITE_VAL_USING_ATTRIB  ||  oVars_Types_Int[i] == EQ_DB_WRITE_PRI_USING_ATTRIB)
			{
			#ifdef EQ_IsItemBlock
				{
				oVars_AttribColumnIndexes[i] = Attrib_GetColumnIndex(oVars_Names[i]);
				}
			#endif
			}
		else
			//oVars_AttribColumnIndexes[i] = EQ_VarTypeGet(oVars_Types_str[i]);	//6/19/09
			oVars_AttribColumnIndexes[i] = PROPERTY_TYPE_NO_PROPERTY;
		}
*/
	//update the input variable values
	for(i=0; i<iVars_NumTableRows; i++)
		{
/*		
		if(iVars_Types_Int[i] == EQ_DB_READ_VAL)
			{
			if(EQ_DBAddressLocationExists(iVars_DBCoords[i], DB_ADDRESS_TYPE_RECORD))		//8/17/10
				{
				legitField = iVars_CheckChosenField(i, iVars_DBCoords[i]);
				if(!legitField)
					AbortAllSims();
				
				iVars_Values[i] = DBDataGetAsNumberUsingAddress(iVars_DBCoords[i]);
				
				//if targeted field is of type "Date Time", then convert the number being read from Julian format to simTime.
				//why?  because all time numbers calculated in an equation are ALWAYS in simTime time units.
				fieldType = DBFieldGetPropertiesUsingAddress(iVars_DBCoords[i], 1) ;	//where 1 = fieldType
				if(fieldType == DB_FIELDTYPE_REAL_DATE_TIME  &&  convertDateTimeData_chk)
					{
					iVars_Values[i] = EDDateToSimTime(iVars_Values[i],0);
					}
	
				iVars_ValueWasFound[i] = TRUE;
				}
			else	
				{
				UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
						  "'DB read value', but the specified location does not exist.");
				AbortAllSims();
				}
			}
		
		else if(iVars_Types_Int[i] == EQ_DB_READ_PRI)
			{
			if(EQ_DBAddressLocationExists(iVars_DBCoords[i], DB_ADDRESS_TYPE_RECORD))		//8/17/10
				{
				legitField = iVars_CheckChosenField(i, iVars_DBCoords[i]);
				if(!legitField)
					AbortAllSims();
				
				DBDataGetParentUsingAddress(iVars_DBCoords[i], parentInfo);
				iVars_Values[i] = parentInfo[PARENT_RECORD];
	
				iVars_ValueWasFound[i] = TRUE;
				}
			else	
				{
				UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
						  "'DB read PRI', but the specified location does not exist.");
				AbortAllSims();
				}
			}
		
		else if(iVars_Types_Int[i] == EQ_DB_ADDRESS)
			{
			iVars_Values[i] = iVars_DBCoords[i];
			iVars_ValueWasFound[i] = TRUE;
			}

		#ifdef EQ_IsQueryEquationTypeBlock
			
			else if(iVars_Types_Int[i] == EQ_DBQ_QUERY_FIELD_VALUE)
				{
				//if a direct query field has been specified
				if(DBQF_OptionsChosen[i] != DBQ_NOT_DEFINED)
					{
					if(DBFieldExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i]))		//8/17/10
						{
						if( DBRecordExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i], DBQ_CurrRecordInQueryCycle) )		//8/17/10
							{
							fieldType = DBFieldGetProperties(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i], 1) ;	//where 1 = fieldType
							
							//if query field is a string field, we know we have a problem
							if(fieldType == DB_FIELDTYPE_STRING_VALUE)
								{
								parentRecordIndex = DBDataGetParent(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i], DBQ_CurrRecordInQueryCycle, parentInfo);
								
								//if direct query field is a string field that is also child field
								if(parentRecordIndex >= 0)	
									{
									//NOTE:  if parentRecordIndex = 0, then field is a child field, but no PRI has been selected yet.
									
									UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
											  "'DBQ read value', but the query field is a string child field. Either change the query field or change " +
											  "the variable type to 'DBQ read PRI'.");
									AbortAllSims();
									}
								
								//if direct query field is a string field
								else	
									{
									UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
											  "'DBQ read value', but the query field is a string field.");
									AbortAllSims();
									}
								}
							
							//if query field not a string field
							else
								{
								iVars_Values[i] = DBDataGetAsNumber(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i], DBQ_CurrRecordInQueryCycle);

								//if targeted field is of type "Date Time", then convert the number being read from Julian format to simTime.
								//why?  because all time numbers calculated in an equation are ALWAYS in simTime time units.
								if(fieldType == DB_FIELDTYPE_REAL_DATE_TIME  &&  convertDateTimeData_chk)
									{
									iVars_Values[i] = EDDateToSimTime(iVars_Values[i],0);
									}
								}
									
							iVars_ValueWasFound[i] = TRUE;
							}
						else
							{
							UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
									  "'DBQ read value', but the current record, " + DBQ_CurrRecordInQueryCycle + " is out of bounds.");
							AbortAllSims();
							}
						}
					else
						{
						if(!DBDatabaseExists(DBQ_DatabaseIndex_prm))
							{
							UserError("There is a problem in " + BlockName(me) + " " + me + ". The chosen database with index = " + DBQ_DatabaseIndex_prm + " does not exist.");
							AbortAllSims();
							}
						if(!DBTableExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm))
							{
							UserError("There is a problem in " + BlockName(me) + " " + me + ". The chosen query table with index = " + DBQ_TableIndex_prm + " does not exist.");
							AbortAllSims();
							}
						if(!DBFieldExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i]))
							{
							UserError("There is a problem in " + BlockName(me) + " " + me + ". The chosen query field for input variable " + (i+1) + " does not exist.");
							AbortAllSims();
							}
						}
					}
				}
	
			else if(iVars_Types_Int[i] == EQ_DBQ_QUERY_FIELD_PRI)
				{
				//if an indirect parent query field has been specified
				if(DBQFP_OptionsChosen[i] != DBQ_NOT_DEFINED)
					{
					if(	
						DBFieldExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i])  &&  
						DBFieldExists(DBQ_DatabaseIndex_prm, DBQFP_TableIndex[i], DBQFP_FieldIndex[i])
					  )
						{
						if( DBRecordExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i], DBQ_CurrRecordInQueryCycle) )		//8/17/10
							{
							parentRecordIndex = DBDataGetParent(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i], DBQ_CurrRecordInQueryCycle, parentInfo);
							
							//if the direct query field is a child field and a PRI has been specified in the direct field's db cell
							if(parentRecordIndex >= 1)
								{
								if( DBRecordExists(DBQ_DatabaseIndex_prm, DBQFP_TableIndex[i], DBQFP_FieldIndex[i], parentRecordIndex) )		//8/17/10
									{
									parentParentRecordIndex = DBDataGetParent(DBQ_DatabaseIndex_prm, DBQFP_TableIndex[i], DBQFP_FieldIndex[i], parentRecordIndex, parentInfo);
								
									//if the indirect query field is a child AND a PRI has been specified in the indirect field's db cell,...
									if(parentParentRecordIndex >= 1)
										{
										//...then by default grab the PRI found in the parent table- the "parentParent"
										iVars_Values[i] = parentParentRecordIndex;
										}
					
									//if the indirect query field is a child BUT a PRI has not been specified in the indirect field's db cell
									else if(parentParentRecordIndex == 0)	
										{
										iVars_Values[i] = blank;
										}
									
									//if indirect query field is NOT a child
									else
										{
										iVars_Values[i] = DBDataGetAsNumber(DBQ_DatabaseIndex_prm, DBQFP_TableIndex[i], DBQFP_FieldIndex[i], parentRecordIndex);
										
										//if targeted field is of type "Date Time", then convert the number being read from Julian format to simTime.
										//why?  because all time numbers calculated in an equation are ALWAYS in simTime time units.
										fieldType = DBFieldGetProperties(DBQ_DatabaseIndex_prm, DBQFP_TableIndex[i], DBQFP_FieldIndex[i], 1) ;	//where 1 = fieldType
										if(fieldType == DB_FIELDTYPE_REAL_DATE_TIME  &&  convertDateTimeData_chk)
											{
											iVars_Values[i] = EDDateToSimTime(iVars_Values[i],0);
											}
										}
									}
								else
									{
									UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
											  "'DBQ read PRI', but parent record " + parentRecordIndex  + " does not exist.");
									AbortAllSims();
									}
								}
							
							//if the direct query field is a child field and a PRI has not been specified in the direct field's db cell
							else if(parentRecordIndex == 0)	
								{
								iVars_Values[i] = blank;
								}
							
							//if the direct query field not a child field
							else 
								{
								UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
										  "'DBQ read PRI', but the query field is not a child field. Either change the query field or change " +
										  "the variable type to 'DBQ read value'.");
								AbortAllSims();
								}
								
							iVars_ValueWasFound[i] = TRUE;
							}
						else
							{
							UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
									  "'DBQ read PRI', and the current record " + DBQ_CurrRecordInQueryCycle  + " does not exist.");
							AbortAllSims();
							}
						}
					else
						{
						if(!DBDatabaseExists(DBQ_DatabaseIndex_prm))
							{
							UserError("There is a problem in " + BlockName(me) + " " + me + ". The chosen database with index = " + DBQ_DatabaseIndex_prm + " does not exist.");
							}
						if(!DBTableExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm))
							{
							UserError("There is a problem in " + BlockName(me) + " " + me + ". The chosen query table with index = " + DBQ_TableIndex_prm + " does not exist.");
							}
						if(!DBFieldExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i]))
							{
							UserError("There is a problem in " + BlockName(me) + " " + me + ". The chosen query field for input variable " + (i+1) + " does not exist.");
							}
						if(!DBTableExists(DBQ_DatabaseIndex_prm, DBQFP_TableIndex[i]))
							{
							UserError("There is a problem in " + BlockName(me) + " " + me + ". The parent table with index = " + DBQFP_TableIndex[i] + " for input variable " + (i+1) + "does not exist.");
							}
						if(!DBFieldExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQFP_FieldIndex[i]))
							{
							UserError("There is a problem in " + BlockName(me) + " " + me + ". The parent table with index = " + DBQFP_FieldIndex[i] + " for input variable " + (i+1) + "does not exist.");
							}
						AbortAllSims();
						}
					}
					
				//else if a direct query field has been specified
				else if(DBQF_OptionsChosen[i] != DBQ_NOT_DEFINED)
					{
					if(DBFieldExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i]))		//8/17/10
						{
						if( DBRecordExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i], DBQ_CurrRecordInQueryCycle) )		//8/17/10
							{
							parentRecordIndex = DBDataGetParent(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i], DBQ_CurrRecordInQueryCycle, parentInfo);
							
							//if direct query field is a child AND a PRI has been specified in the direct field's db cell
							if(parentRecordIndex >= 1)
								{
								iVars_Values[i] = parentRecordIndex;	//note if parentRecordIndex = 0, then child cell has nothing selected yet
								}
				
							//if direct query field is a child BUT a PRI has not yet been specified in the direct field's db cell
							else if(parentRecordIndex == 0)	
								{
								iVars_Values[i] = blank;
								}
							
							//else if direct query field is NOT a child field
							else if(parentRecordIndex < 0)
								{
								UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
										  "'DBQ read PRI', but the query field is not a child field. Either change the query field or change " +
										  "the variable type to 'DBQ read value'.");
								AbortAllSims();
								}
							
							iVars_ValueWasFound[i] = TRUE;
							}
						else
							{
							UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
									  "'DBQ read PRI', and current record " + DBQ_CurrRecordInQueryCycle  + " does not exist.");
							AbortAllSims();
							}
						}
					else
						{
						if(!DBDatabaseExists(DBQ_DatabaseIndex_prm))
							{
							UserError("There is a problem in " + BlockName(me) + " " + me + ". The chosen database with index = " + DBQ_DatabaseIndex_prm + " does not exist.");
							}
						if(!DBTableExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm))
							{
							UserError("There is a problem in " + BlockName(me) + " " + me + ". The chosen query table with index = " + DBQ_TableIndex_prm + " does not exist.");
							}
						if(!DBFieldExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i]))
							{
							UserError("There is a problem in " + BlockName(me) + " " + me + ". The chosen query field for input variable " + (i+1) + " does not exist.");
							}
						AbortAllSims();
						}
					}
				}
			
			else if(iVars_Types_Int[i] == EQ_DBQ_CURRENT_RECORD)
				{
				//iVars_Values[i] = DBQ_CurrRecordInQueryCycle;
				currRecord = NumericParameter("Enter the current record.", 1);
				iVars_Values[i] = currRecord;
				iVars_ValueWasFound[i] = TRUE;
				}
		
			else if(iVars_Types_Int[i] == EQ_DBQ_NUM_RECORDS)
				{
				if(DBQ_DatabaseIndex_prm >=1  &&  DBQ_TableIndex_prm >= 1)
					numRecords = DBRecordsGetNum(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm);
				else
					numRecords = 1;
				iVars_Values[i] = numRecords;
				iVars_ValueWasFound[i] = TRUE;
				}
				
			else if(iVars_Types_Int[i] == EQ_DBQ_CURR_BEST_RANK_RESULT)
				{
				//iVars_Values[i] = DBQPT_CurrBestRankResult;
				PT_CurrBestRecordRank = NumericParameter("Enter the current best pass-through record rank.", 1);
				iVars_Values[i] = PT_CurrBestRecordRank;
				iVars_ValueWasFound[i] = TRUE;
				}
		
			else if(iVars_Types_Int[i] == EQ_DBQS_CURR_BEST_RANK_RESULT)
				{
				//iVars_Values[i] = DBQS_CurrBestRankResult;
				S_CurrBestRecordRank = NumericParameter("Enter the current best spawn record rank.", 1);
				iVars_Values[i] = S_CurrBestRecordRank;
				iVars_ValueWasFound[i] = TRUE;
				}
		
			else if(iVars_Types_Int[i] == EQ_DBQ_NUM_NON_BLANK_RANKED_RECORDS)
				{
				PT_NumNonBlankRankedRecords = NumericParameter("Enter the number of non-blank pass-through record ranks.", 1);
				iVars_Values[i] = PT_NumNonBlankRankedRecords;
				iVars_ValueWasFound[i] = TRUE;
				}
		
			else if(iVars_Types_Int[i] == EQ_DBQS_NUM_NON_BLANK_RANKED_RECORDS)
				{
				S_NumNonBlankRankedRecords = NumericParameter("Enter the number of non-blank spawn record ranks.", 1);
				iVars_Values[i] = S_NumNonBlankRankedRecords;
				iVars_ValueWasFound[i] = TRUE;
				}
		
			else if(iVars_Types_Int[i] == EQ_DBQ_STATIC_QUERY_INIT)
				{
				//do nothing- static query vars were initialized at the start of the query in DBQ_DoQuery() and updated during EquationCalculateDynamicVariables()
				iVars_ValueWasFound[i] = TRUE;
				}
				
		#endif //EQ_IsQueryEquationTypeBlock
	
		else if(iVars_Types_Int[i] == EQ_STATIC_FRI  ||  iVars_Types_Int[i] == EQ_STATIC_MRI  ||  iVars_Types_Int[i] == EQ_STATIC_OPEN_MODEL)
			{
			//do nothing to preserve the static
			}

		//5/24/11
		else if(iVars_Types_Int[i] == EQ_ITEM_ATTRIBUTE  &&  iVars_AttribTypes[i] == ATTRIB_TYPE_STRING)
			{
			//if the ivar is pointing to a string attrib, we need to convert the string val into a string index
			iVars_Values[i] = SLStringGetIndex(iVars_Names[i], iVars_ttbl[i][I_VAR_VALUE_COL]);
			
			if(iVars_Values[i] < 0)
				{
				UserError("There is a problem with the value of input variable number " + (i+1) + ". " + 
						  "The string value """ + iVars_ttbl[i][I_VAR_VALUE_COL] + """ for the attribute """ + iVars_Names[i] + """ does not exist.");
				AbortAllSims();
				}
			}
*/		
		if(iVars_Types_Int[i] == EQ_STRING ) // Carollo
		{
			iVars_ValuesStr[i] = iVars_ttbl[i][I_VAR_VALUE_COL];
//			iVars_ValueWasFound[i] = TRUE;
		}
		else
			{
			iVars_Values[i] = StrToReal(iVars_ttbl[i][I_VAR_VALUE_COL]);
//			iVars_ValueWasFound[i] = TRUE;
			}
		
		}//for(i=0; i<iVars_NumTableRows; i++)

	//get initial values for output variables
//	oVars_InitVals();

	if(dbg_chk == TRUE)
		EquationDebugCalculate(dbg_HiddenBlock, iVars_Values, oVars_Values);
	else
		EquationCalculateDynamicVariables(iVars_Values, oVars_Values, EQ_CompiledEquation);
/*
	//update the database
	for(i=0; i<oVars_NumTableRows; i++)
		{
		if(oVars_Types_Int[i] == EQ_DB_WRITE_VAL  ||  oVars_Types_Int[i] == EQ_DB_WRITE_PRI)
			{
			legitField = oVars_CheckChosenField(i, oVars_DBCoords[i]);
			if(!legitField)
				AbortAllSims();

			//if targeted field is of type "Date Time", then convert the number being written to Julian format.
			//why?  because all time numbers calculated in an equation are ALWAYS in simTime time units.
			fieldType = DBFieldGetPropertiesUsingAddress(oVars_DBCoords[i], 1) ;	//where 1 = fieldType
			if(fieldType == DB_FIELDTYPE_REAL_DATE_TIME  &&  convertDateTimeData_chk)
				{
				oVars_Values[i] = EDSimTimeToDate(oVars_Values[i], 0);
				}

			//	8/25/09
			//DBDataSetAsNumberUsingAddress(oVars_DBCoords[i], oVars_Values[i]);

			if(EQ_DBAddressLocationExists(oVars_DBCoords[i], DB_ADDRESS_TYPE_RECORD))		//8/17/10
				{
				if(oVars_Types_Int[i] == EQ_DB_WRITE_VAL)
					DBDataSetAsNumberUsingAddress(oVars_DBCoords[i], oVars_Values[i]);
				
				else //if(oVars_Types_Int[i] == EQ_DB_WRITE_PRI)
					//with this option user wants to set a parent index in a child
					DBDataSetAsParentIndexUsingAddress(oVars_DBCoords[i], oVars_Values[i]);
				}
			else
				{
				UserError("There is a problem in " + BlockName(me) + " " + me + ". Output variable " + (i+1) + " is of type " +
						  "'DB write value', but the specified location does not exist.");
				AbortAllSims();
				}
			}
		}
*/
	//update output connectors
//	#ifdef oVarsOut
//		for(i=0; i<oVars_NumTableRows; i++)
//			{
//			if(oVars_VarIsWhichCon[i] != -1)
//				ConArraySetValue(oVarsOut, oVars_VarIsWhichCon[i], oVars_Values[i]);
//			}
//	#endif

	//if have static variables, update the input table
	for(i=0; i<iVars_NumTableRows; i++)
		{
		if(iVars_Types_Int[i] == EQ_STATIC_FRI  ||  iVars_Types_Int[i] == EQ_STATIC_MRI  ||  iVars_Types_Int[i] == EQ_STATIC_OPEN_MODEL)
			iVars_ttbl[i][I_VAR_VALUE_COL] = iVars_StaticInitValues[i] + " : " + iVars_Values[i];
		}

	//if the output variable is an attrib variable, get result from iVars_Values
	#ifdef EQ_IsItemBlock
			
		for(i=0; i<oVars_NumTableRows; i++)
			{
				
			if(oVars_Types_Int[i] >= EQ_ITEM_ATTRIBUTE)		//ie, it's an attribute variable
				{
				
				for(j=0; j<iVars_NumTableRows; j++)
					{
					if(oVars_Names[i] == iVars_Names[j])
						{	
						oVars_Values[i] = iVars_Values[j];
						break;
						}
					}

				}
					
			}//for(i=0; i<oVars_NumTableRows; i++)
				
	#endif

	//update the output table
	for(i=0; i<oVars_NumTableRows; i++)
	{
		// Carollo
		if (oVars_Types_Int[i] == EQ_Integer)
		{
			oVars_Values[i] = Int(oVars_Values[i]);
			oVars_ttbl[i][O_VAR_VALUE_COL] = oVars_Values[i];
		}
		else if (oVars_Types_Int[i] == EQ_String)
			oVars_ttbl[i][O_VAR_VALUE_COL] = oVars_ValuesStr[i];
		else
			oVars_ttbl[i][O_VAR_VALUE_COL] = oVars_Values[i];
	}
	
}

on dbg_OpenBreakpointsWindow_btn
{

	integer successfullCompile;
	
	if(EQE_EditorIsOpen == TRUE)
		{
		UserError("Please close the equation editor window first.");
		abort;
		}

	successfullCompile = EQ_Compile(FALSE);

	if(successfullCompile == TRUE)
		EquationDebugSetBreakpoints(dbg_HiddenBlock);
	
}//on dbg_OpenBreakpointsWindow_btn


on dbg_chk
{

	if(dbg_chk == TRUE)
		{
		if(EQE_EditorIsOpen == TRUE)
			{
			UserError("Please close the equation editor window first.");
			dbg_chk = FALSE;
			abort;
			}
	
		EQ_Compile(TRUE);
		}
	else
		{
		EquationDebugDispose(dbg_HiddenBlock);
		dbg_HiddenBlock = -1;
			//NOTE:  any time the hidden debug block is destroyed, must set dbg_HiddenBlock = -1 
			//so that when EquationDebugCompile() is called, a new hidden debug block is created.
		}
	
	//show breakpoint dialog items
	if(dbg_chk == TRUE)
		DisableDialogItem("dbg_OpenBreakpointsWindow_btn", FALSE);
	else
		DisableDialogItem("dbg_OpenBreakpointsWindow_btn", TRUE);
	
}//on dbg_chk

procedure EQE_CreateEditorFile()
{

	integer me;
	integer i;
	integer fileNumber;
	integer fileDoesExist;
	integer numRowsInEquation;
	string arrayText;
	integer arrayTextLength;
	string nextRowArrayText;
	string lineString;
	integer lineLength;
	string CR;						//Carriage Return
	string LF;						//Line Feed
	string HT;						//Horizontal Tab
	integer crPosi;
	integer lfPosi;
	integer numChars;
	integer tabStart;

	me = MyBlockNumber();
	
	if(EQE_EditorIsOpen == FALSE)
		{
	
		//create editorName
		MakeArray(EQE_Name, 1);
		EQE_Name[0] = "Equation Editor [" + me + "].h";
		
		//create a pathName for the editor file
		MakeArray(EQE_PathName, 1);
		if(PlatformWindows)
			EQE_PathName[0] = GetUserPath() + "Extensions\" + EQE_Name[0];
		else
			EQE_PathName[0] = GetUserPath() + "Extensions:" + EQE_Name[0];
		
		//if file already exists, delete it so that we can create a blank one from scratch
		fileDoesExist = FileExists(EQE_PathName[0]);
		if(fileDoesExist == TRUE)
			{
			FileDelete(EQE_PathName[0]);
			}
		
		//create the equation editor file
		fileNumber = FileNew(EQE_PathName[0], FALSE);
		
		numRowsInEquation = GetDimension(EQ_EquationText);

		//remove all occurrences of line feed characters from the equation
		LF = StrPutAscii(10);		//line feed
		for(i=0; i<numRowsInEquation; i++)
			{
			do
				{
				lfPosi = StrFind(EQ_EquationText[i], LF, FALSE, FALSE);
				if(lfPosi >= 0)
					{
					EQ_EquationText[i] = StrReplace(EQ_EquationText[i], lfPosi, 1, "");
					}
				}while (lfPosi >= 0);
			}
		
		//map text from the equation array into equation editor
		CR = StrPutAscii(13);		//carriage return
		HT = StrPutAscii(9);		//horizontal tab
		for(i=0; i<numRowsInEquation; i++)
			{
			
			arrayText = EQ_EquationText[i];								//the next chunk of text from the equation array
			arrayTextLength = StrLen(arrayText);
			while(arrayTextLength > 0)
				{
				
				crPosi = StrFind(arrayText, CR, FALSE, FALSE);
				if(crPosi >= 0)
					{
					numChars = crPosi;									//leave off the CR
					lineString = StrPart(arrayText, 0, numChars);		//the next line of text to add to the equation editor

					//set up for next pass through while
					arrayText = StrPart(arrayText, numChars+1, 255);	//remove lineString + CR from arrayText.  note: 255 used to ensure we get everything
					arrayTextLength = StrLen(arrayText);
					}
					
				else //if no CR,...
					{
					//...,then grab remaning text from current row
					lineString = arrayText;
					
					//force exit out of while loop
					arrayTextLength = 0;													

					//if there is another row in equation array,...
					if(i < numRowsInEquation - 1)
						{
						//...then define how many chars we want to remove from the next row of equation array...
						crPosi = StrFind(EQ_EquationText[i+1], CR, FALSE, FALSE);
						if(crPosi >= 0)
							numChars = crPosi;							//leave off the CR
						else
							numChars = StrLen(EQ_EquationText[i+1]);
						
						//...and add text from next row of equation array to lineString
						lineString += StrPart(EQ_EquationText[i+1], 0, numChars);

						//remove the chunk of text that we're using from next row in equation array
						EQ_EquationText[i+1] = StrPart(EQ_EquationText[i+1], numChars+1, 255);		//"numChars+1":  leave out the CR if one exists.
						}
					}
					
				//replace every instance of "5 spaces" with a tab character
				do
					{
					tabStart = StrFind(lineString, "     ", FALSE, FALSE);
					if(tabStart >= 0)
						{
						lineString = StrReplace(lineString, tabStart, 5, HT);
						}
					}
				while(tabStart >= 0);
				
				//write lineString to the equation editor file	
				FileWrite(fileNumber, lineString, "@", TRUE);		//"@" to write CR at the end of the text we're writing
									
				}//while(arrayTextLength > 0)
			
			}//for(i=0; i<numRowsInEquation; i++)
		
		//close the file after having created it.
		FileClose(fileNumber);
		
		}//if(EQE_EditorIsOpen == FALSE)

}//procedure EQE_CreateEditorFile()


procedure EQE_DeleteEditorFile()
{

	FileDelete(EQE_PathName[0]);
	
	DisposeArray(EQE_Name);
	DisposeArray(EQE_PathName);
	
}//procedure EQE_DeleteEditorFile()



procedure EQE_CloseEditor()
{
	
	integer me;
	integer fileNumber;
	integer endOfFile;
	string lineString;
	integer lineLength;
	integer currPosi;
	string HT;				//Horizontal Return
	integer htPosi;
	
	me = MyBlockNumber();
	
	//save and close the equation editor
	SaveTopDocAs(EQE_PathName[0], FALSE);	//FALSE = close synchronously
	ExecuteMenuCommand(4);
	
	//************************************************************************
	//START: open the editor file and copy contents over into the equation
	
		HT = StrPutAscii(9);			//get the Horizontal Tab symbol;

		//blank out the dynamic text dialog
		MakeArray(EQ_EquationText, 1);
		StrReplaceDynamic(EQ_EquationText, 0, 255, "");
		
		//open the equation editor file
		fileNumber = FileOpen(EQE_PathName[0], FALSE);
		
		//copy text from the equation editor file to the equation dynamic text
		endOfFile = FileEndOfFile(fileNumber);
		currPosi = 0;
		while(endOfFile == FALSE)
			{
			lineString = FileRead(fileNumber, "@") + StrPutAscii(13);		//"@" unused character to force grab to end of line character
			
			//replace every instance of a tab character with 5 spaces
			do
				{
				htPosi = StrFind(lineString, HT, FALSE, FALSE);
				if(htPosi >= 0)
					{
					lineString = StrReplace(lineString, htPosi, 1, "     ");
					}
				}
			while(htPosi >= 0);
			
			lineLength = StrLen(lineString);
			StrReplaceDynamic(EQ_EquationText, currPosi, lineLength, lineString);
			currPosi = currPosi + lineLength;
			endOfFile = FileEndOfFile(fileNumber);
			}//while(endOfFile == FALSE)
			
		//close the equation editor file
		FileClose(fileNumber);
		
	//END:  open the equation editor and copy contents over into the equation
	//************************************************************************
	
	//update settings
	EQE_EditorIsOpen = FALSE;
	DITitleSet(me, "EQE_btn", "Open / Close Equation Editor");
	DisableDialogItem("equation_dtxt", FALSE);

	EQE_DeleteEditorFile();

}//procedure EQE_CloseEditor()



on EQE_btn
{
	
	integer me;
	integer openSuccess;
	
	me = MyBlockNumber();
	
	if(EQE_EditorIsOpen == FALSE)
		{
		//create the editor file
		EQE_CreateEditorFile();
		
		//open the editor file
		openSuccess = OpenExtendFile(EQE_PathName[0]);
		if(openSuccess == 0)
			{
			EQE_EditorIsOpen = TRUE;
			//DITitleSet(me, "EQE_btn", "Close equation editor");
			}
		else
			{
			EQE_EditorIsOpen = FALSE;
			//DITitleSet(me, "EQE_btn", "Open Equation Editor");
			}
			
		//tell ExtendSim that we want to receive an "IncludeFileClose" message when user closes this window
		IncludeFileEditor(EQE_Name[0], me);
		DisposeArray(EQE_Name);
		
		DisableDialogItem("equation_dtxt", TRUE);
		}
		
	else if(EQE_EditorIsOpen == TRUE)
		{
		OpenExtendFile(EQE_PathName[0]);	//bring the editor to the front
		EQE_CloseEditor();
		}

}//on EQE_btn

procedure EQ_OnCellAccept()
{

	string dName;		// name of the dialog item clicked
	integer caRow;
	integer caCol;
	integer SA_ValIndex;
	String ls_VariableName;

	caRow = WhichDTCellClicked(0);		//which row did the user just exit
	caCol = WhichDTCellClicked(1);		//which col did the user just exit
	dName = WhichDialogItemClicked();
	
	iVars_NumTableRows = GetDimension(iVars_ttbl);
	oVars_NumTableRows = GetDimension(oVars_ttbl);
	
	if(dName == "iVars_ttbl"  &&  caRow >= 0  &&  caRow < iVars_NumTableRows  )
	{
	
		//store user's inputs in the individual arrays
		//!!NOTE:  need this here.  if not, when user types in test values, they disappear
		if(caCol == I_VAR_VALUE_COL)
		{
			if(
				iVars_Types_str[caRow] != "Static first run init"  &&  
				iVars_Types_str[caRow] != "Static multi run init"  &&  
				iVars_Types_str[caRow] != "Static open model init"  &&  
				iVars_Types_str[caRow] != "DBQ static query init"
			  )
				{
				if(iVars_Types_str[caRow] == "Attribute"  &&  iVars_AttribTypes[caRow] == ATTRIB_TYPE_STRING) 
					{
					SA_ValIndex = SLStringGetIndex(iVars_Names[caRow], iVars_ttbl[caRow][I_VAR_VALUE_COL]);
					iVars_Values[caRow] = SA_ValIndex;
					}
				else
					{
					iVars_Values[caRow] = StrToReal(iVars_ttbl[caRow][I_VAR_VALUE_COL]);
					}
				}
			
			StopDataTableEditing();
		}
		
		else if(caCol == I_VAR_NAME_COL)
		{
			iVars_Names[caRow] = iVars_ttbl[caRow][I_VAR_NAME_COL];
		}
			
		// checek variable naming fashion
		for (i = 0; i < iVars_NumTableRows; i++)
		{
			ls_VariableName = iVars_ttbl[i][1];
			
			if (StrFind(ls_VariableName, "/", 0, 0) > 0 OR StrFind(ls_VariableName, "\", 0, 0) > 0 OR StrFind(ls_VariableName, "-", 0, 0) > 0 OR 
				StrFind(ls_VariableName, " ", 0, 0) > 0 OR !NoValue(StrToReal(ls_VariableName)))
			{
				UserError("Input Variable Name: ["+ls_VariableName+"] contains ""/"", ""\"", ""-"", SPACE or start with a number. Please provide a new name.");
			}
		}
			
	}//if(dName == "iVars_ttbl")
		
	if(dName == "oVars_ttbl"  &&  caRow >= 0  &&  caRow < oVars_NumTableRows)
	{

		//store user's inputs in the individual arrays
		if(caCol == O_VAR_NAME_COL)
			oVars_Names[caRow] = oVars_ttbl[caRow][O_VAR_NAME_COL];
			
		// checek variable naming fashion
		for (i = 0; i < oVars_NumTableRows; i++)
		{
			ls_VariableName = oVars_ttbl[i][1];
			
			if (StrFind(ls_VariableName, "/", 0, 0) > 0 OR StrFind(ls_VariableName, "\", 0, 0) > 0 OR StrFind(ls_VariableName, "-", 0, 0) > 0 OR 
				StrFind(ls_VariableName, " ", 0, 0) > 0 OR !NoValue(StrToReal(ls_VariableName)))
			{
				UserError("Output Variable Name: ["+ls_VariableName+"] contains ""/"", ""\"", ""-"", SPACE or start with a number. Please provide a new name.");
			}
		}

	}//if(dName == "oVars_ttbl")
	
	for (i = 0; i < iVars_NumTableRows; i++)
	{
		ls_VariableName = iVars_ttbl[i][1];
		
		for (j = 0; j < oVars_NumTableRows; j++)
		{
			if (oVars_ttbl[j][1] == ls_VariableName AND ls_VariableName != BLANK)
			{
				UserError("Variable Name ["+ls_VariableName+"] is used for both input and output variable. Please provide a new name.");
			}
		}
	}

}//procedure EQ_OnCellAccept()

procedure EQ_OnCreateBlock(integer calledFrom)
{

	integer i, j;
	integer me;
	integer iVars_DBNameTrackingListIndex;
	integer oVars_DBNameTrackingListIndex;
	integer numBlocksInModel;
	integer blockTypeArray[4];
	string nameOfBlock;
	integer execCheckBoxVal;
	
	me = MyBlockNumber();

	rowClicked = -1;
	colClicked = -1;
	
	dbg_HiddenBlock = -1;
	
	EQE_EditorIsOpen = FALSE;
	
	inLinkStructure = FALSE;

	#ifdef respondToLinkAlerts_chk
		respondToLinkAlerts_chk = FALSE;
	#endif
	
	//random seed stuff
	MySeed = randomGetSeed() + MyBlockNumber() + 1;
	previousSeed = MySeed;

	//set up input variable stuff
	iVars_NumTableRows = 1;
	iVars_OldNumTableRows = iVars_NumTableRows;
//	iVars_ResizeDynamicArrays(RESIZE_ADD_SUBTRACT_FROM_END);
	
	//setup iVarsIn connectors
	iVarsIn_NumCons = iVars_NumTableRows;
	iVarsIn_NumConsOld = iVarsIn_NumCons;
	MakeArray(iVarsIn_NumBlocksConnected, iVarsIn_NumCons);
	MakeArray(iVarsIn_ConNums, iVarsIn_NumCons);
	ConArraySetNumCons(MyBlockNumber(), "iVarsIn", iVarsIn_NumCons, TRUE);
	for(i=0; i<iVarsIn_NumCons; i++)									// Look through the connector array
		iVarsIn_ConNums[i] = ConArrayGetConNumber(MyBlockNumber(), "iVarsIn", i);
//	iVarsIn_ConnectorsSetup();

	//setup output variable stuff
	oVars_NumTableRows = 1;
	oVars_OldNumTableRows = oVars_NumTableRows;
//	oVars_ResizeDynamicArrays(calledFrom, RESIZE_ADD_SUBTRACT_FROM_END);

	#ifdef oVars_Initialize_prm
		oVars_Initialize_prm = 0.0;
	#endif
	
	#ifdef oVarsOut
		//setup oVarsOut connectors
		oVarsOut_NumCons = oVars_NumTableRows;
		oVarsOut_NumConsOld = oVarsOut_NumCons;
		MakeArray(oVarsOut_NumBlocksConnected, oVarsOut_NumCons);
		MakeArray(oVarsOut_ConNums, oVarsOut_NumCons);
		ConArraySetNumCons(MyBlockNumber(), "oVarsOut", oVarsOut_NumCons, TRUE);
		for(i=0; i<oVarsOut_NumCons; i++)									// Look through the connector array
			oVarsOut_ConNums[i] = ConArrayGetConNumber(MyBlockNumber(), "oVarsOut", i);
//		oVarsOut_ConnectorsSetup();
	#endif
			
	equation_DTxt = DynamicTextArrayNumber(EQ_EquationText);	//points "equation_dtxt" to "EQ_EquationText".
	MakeArray(EQ_EquationText, 1);
	if(calledFrom == EQUATION_QUEUE_BLOCK)
		EQ_EquationText[0] = "iRank_0 = inCon0;";
	else if(calledFrom == EQUATION_QUERY_BLOCK_VALUE)
		{
		EQ_EquationText[0] = "rRank_0 = inCon0;";
		}
	else if(calledFrom == EQUATION_QUERY_BLOCK_ITEM)
		{
		EQ_EquationText[0] = "prRank_0 = inCon0;";
		}
	else
		EQ_EquationText[0] = "outCon0 = inCon0;";
		
	//set up db name tracking
	iVars_DBNameTrackingListIndex = ListCreate(me, 2, 0, 0, 0, 0, 2, DBNT_WHICH_ROW_IN_TABLE_FIELD);	//2 sets sort type as integer
	ListLocked(me, iVars_DBNameTrackingListIndex, TRUE);
	ListAddString63s(me, iVars_DBNameTrackingListIndex, 4);
	ListSetName(me, iVars_DBNameTrackingListIndex, DBNT_IVARS_LIST_NAME);
	oVars_DBNameTrackingListIndex = ListCreate(me, 1, 0, 0, 0, 0, 2, DBNT_WHICH_ROW_IN_TABLE_FIELD);	//2 sets sort type as integer
	ListLocked(me, oVars_DBNameTrackingListIndex, TRUE);
	ListAddString63s(me, oVars_DBNameTrackingListIndex, 4);
	ListSetName(me, oVars_DBNameTrackingListIndex, DBNT_OVARS_LIST_NAME);

	//10/13/08, AJN:  check Executive to see if this block should show property names on connector labels
	numBlocksInModel = NumBlocks();
	for(i=0; i<numBlocksInModel; i ++)									//look through all of the blocks in the model
		{
		if(i != me && GetBlockTypePosition(i,blockTypeArray) == 3)		//if this is a block from a library
			{
			nameOfBlock = BlockName(i);
			
			if(nameOfBlock == "Executive")
				{
				execCheckBoxVal = StrToReal(GetDialogVariable(i, "ShowPropertyName_chk", 0, 0));
				if(execCheckBoxVal == TRUE)
					{
					iVars_ShowConNames_chk = TRUE;
					oVars_ShowConNames_chk = TRUE;
					}
				else
					{
					iVars_ShowConNames_chk = FALSE;
					oVars_ShowConNames_chk = FALSE;
					}
				}
			}
		}
		
	//4/20/11
	convertDateTimeData_chk = FALSE;
	modelIs_802_OrOlder = TRUE;		//ensures convertDateTimeData_chk wont get alteredin OpenModel 

}//procedure EQ_OnCreateBlock()

procedure EQ_TranslateEquation()
{

	integer i, j;
	integer sizeEquationArray;
	integer placeFound;
	integer stringLength;
	string15 stringToFind;
	string15 previousChar;
	string15 subsequentChar;
	integer startPoint;

	//fill EQ_TranslatedEquationText with the current contents of EQ_EquationText
	sizeEquationArray = GetDimension(EQ_EquationText);
	MakeArray(EQ_TranslatedEquationText, sizeEquationArray);
	for(i=0; i<sizeEquationArray; i++)
		EQ_TranslatedEquationText[i] = EQ_EquationText[i];
	
	//**********************
	//Start: Input Variables

	//replace every instance of the input variable name with iVars_Values[i]
	for(i=0; i<iVars_NumTableRows; i++)
		{
		stringToFind = iVars_Names[i];
		stringLength = strLen(stringToFind);
		startPoint = 0;
		
		do
			{
			placeFound = StrFindDynamicStartPoint(EQ_TranslatedEquationText, stringToFind, 0, 0, 1, startPoint);  //returns the place where the string was found or -1 if not found.
			if(placeFound > -1)
				{
				if(placeFound == 0)
					StrReplaceDynamic(EQ_TranslatedEquationText, placeFound, stringLength, "iVars_Values[" + i + "]");
				
				else if(placeFound > 0)
					{
					//before replacing, check to make sure user did not put the input variable in quotes.
					previousChar = StrPartDynamic(EQ_TranslatedEquationText, (placeFound-1), 1);
					subsequentChar = StrPartDynamic(EQ_TranslatedEquationText, (placeFound+stringLength), 1);		//6/24/10
					//if(previousChar != """")	//6/24/10
					if(previousChar != """"  &&  subsequentChar != """")
						//weird syntax, but that's actually what you write to check for the presence of a " (ie a single double quote character)
						//replace only if "stringToFind" is not surrounded by quotes
						{
						StrReplaceDynamic(EQ_TranslatedEquationText, placeFound, stringLength, "iVars_Values[" + i + "]");
						}
					}
				
				startPoint = placeFound + stringLength;
				}
			}while(placeFound > -1);  //keep replacing occurrences of the current variable until none are left.
		}

	//End: Input Variables
	//********************

	//***********************
	//Start: Output Variables

	//replace every instance of the output variable name with oVars_Values[i]
	for(i=0; i<oVars_NumTableRows; i++)
		{
		stringToFind = oVars_Names[i];
		stringLength = strLen(stringToFind);
		startPoint = 0;
		
		do
			{
			placeFound = StrFindDynamicStartPoint(EQ_TranslatedEquationText, stringToFind, 0, 0, 1, startPoint);  //returns the place where the string was found or -1 if not found.
			if(placeFound > -1)
				{
				if(placeFound == 0)
					StrReplaceDynamic(EQ_TranslatedEquationText, placeFound, stringLength, "oVars_Values[" + i + "]");
				
				else if(placeFound > 0)
					{
					//before replacing, check to make sure user did not put the output variable in quotes.
					previousChar = StrPartDynamic(EQ_TranslatedEquationText, (placeFound-1), 1);
					subsequentChar = StrPartDynamic(EQ_TranslatedEquationText, (placeFound+stringLength), 1);
					//if(previousChar != """")	//6/24/10
					if(previousChar != """"  &&  subsequentChar != """")
						//weird syntax, but that's actually what you write to check for the presence of a " (ie a single double quote character)
						//replace only if "stringToFind" is not surrounded by quotes
						{
						StrReplaceDynamic(EQ_TranslatedEquationText, placeFound, stringLength, "oVars_Values[" + i + "]");
						}
					}
				
				startPoint = placeFound + stringLength;
				}
			}while(placeFound > -1);  //keep replacing occurrences of the current variable until none are left.
		}

	//End: Output Variables
	//*********************

}//procedure EQ_TranslateEquation()

integer EQ_Compile(integer destroyRemoteBlock)
{
	
	integer i;
	integer error;
	integer outputsSize;
	integer numIncludes;
	string includeName;
	integer successfullCompile;
	
	//copy user's result names from the output table to the associated individual array
	oVars_NumTableRows = GetDimension(oVars_ttbl);
	DisposeArray(oVars_Names);
	DisposeArray(oVars_Units);
	DisposeArray(oVars_Values);
	MakeArray(oVars_Names, oVars_NumTableRows);
	MakeArray(oVars_Units, oVars_NumTableRows);
	MakeArray(oVars_Values, oVars_NumTableRows);
	
	for(i=0; i<oVars_NumTableRows; i++)
		{
		oVars_Names[i] = oVars_ttbl[i][O_VAR_NAME_COL];
		}

	EQ_TranslateEquation();

	//add any include files
	if(Incl_chk)
		{
		numIncludes = GetDimension(Incl_FileNames_ttbl);
		for(i=0; i<numIncludes; i++)
			{
			includeName = incl_FileNames_DA[i][INCL_NAME_COL];
			if(includeName != "")
				EquationIncludeSet(includeName);
			}
		}

	EquationCompileSetStaticArray(staticIncludeVars);			//1/19/11
	
	error = EquationCompileDynamicVariables("iVars_Values", 			//array containing the input values
									   		"oVars_Values", 			//array containing the output values
									    	EQ_TranslatedEquationText,	//array containing the dialog's equation_dtxt
									    	EQ_CompiledEquation,		//the compiled equation_dtxt in machine code- what this function returns
									    	EQUATION_TAB_ORDER);		//identifier for the "equation_dtxt" dialog item
										  
	if(error)
		{
		successfullCompile = FALSE;
		AbortAllSims();			// don't close the dialog box
		}
	
	else //good compile
		{
		successfullCompile = TRUE;
		
		DynamicTextSetDirty(MyBlockNumber(), "equation_dtxt", FALSE);

		if(dbg_chk == TRUE)
			{
			//after successful compile above, have to add includes again
			if(Incl_chk)
				{
				numIncludes = GetDimension(Incl_FileNames_ttbl);
				for(i=0; i<numIncludes; i++)
					{
					includeName = incl_FileNames_DA[i][INCL_NAME_COL];
					if(includeName != "")
						EquationIncludeSet(includeName);
					}
				}

			//first destroy the hidden debugger block
			if(destroyRemoteBlock == TRUE)
				{
				EquationDebugDispose(dbg_HiddenBlock);		
				dbg_HiddenBlock = -1;
					//NOTE:  any time the hidden debug block is destroyed, must set dbg_HiddenBlock = -1 
					//so that when EquationDebugCompile() is called, a new hidden debug block is created.
				}
			
			//second, create a new hidden debugger block
			dbg_HiddenBlock = EquationDebugCompile(dbg_HiddenBlock, 
												   iVars_Names, 
												   oVars_Names, 
												   EQ_EquationText, 
												   EQUATION_TAB_ORDER);					//1 for tab order.  isn't used for anything right now
			}
		}

	DisposeArray(iVars_NamesNoSpaces);
	DisposeArray(EQ_TranslatedEquationText);
	
	return(successfullCompile);

}//procedure EQ_Compile(integer disposeRemoteBlock)

on IncludeFileClose
{
	
	EQE_CloseEditor();
	
}