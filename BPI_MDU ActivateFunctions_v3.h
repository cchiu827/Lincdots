
Procedure Module_pH();


**** Procedure to active module function ****
Procedure Module_ActivateFunction(Integer li_RowIdx) // general procedure to find module and activate module function
{
//	NumberOfRows_ModuleTbl = GetDimension(Module_tbl);
//
//	for (i = 0; i < NumberOfRows_ModuleTbl; i++)
//	{
	
	
	if (Module_tbl[li_RowIdx][2] == "Subtraction")        
	{
		ActivatedModule = Module_tbl[li_RowIdx][0];	Module_Subtraction();
	}
	
	else if (Module_tbl[li_RowIdx][2] == "Minimum")        
	{
		ActivatedModule = Module_tbl[li_RowIdx][0];	Module_Min();
	}
	else if (Module_tbl[li_RowIdx][2] == "Maximum")        
	{
		ActivatedModule = Module_tbl[li_RowIdx][0];	Module_Max();
	}
	
	else if (Module_tbl[li_RowIdx][2] == "Division or Ratio")    //CHE renamed to Division or Ratio                                      
	{
		ActivatedModule = Module_tbl[li_RowIdx][0];	Module_Ratio();
	}
	
	else if (Module_tbl[li_RowIdx][2] == "Empirical Relationship - DBP") 
	{
		ActivatedModule = Module_tbl[li_RowIdx][0];	Module_Empirical_DBP();
	}
	
	else if (Module_tbl[li_RowIdx][2] == "Empirical Relationship - Power") 
	{
		ActivatedModule = Module_tbl[li_RowIdx][0];	Module_Empirical_Power();
	}
	
	else if (Module_tbl[li_RowIdx][2] == "Empirical Relationship - Polymonial") 
	{
		ActivatedModule = Module_tbl[li_RowIdx][0];	Module_Empirical_Polymonial();
	}
	
	else if (Module_tbl[li_RowIdx][2] == "Empirical Relationship - Logrithmatic (10)") 
	{
		ActivatedModule = Module_tbl[li_RowIdx][0];	Module_Empirical_Logrithmatic_10();
	}
	
	else if (Module_tbl[li_RowIdx][2] == "Empirical Relationship - Logrithmatic (e)") 
	{
		ActivatedModule = Module_tbl[li_RowIdx][0];	Module_Empirical_Logrithmatic_e();
	}
	
	else if (Module_tbl[li_RowIdx][2] == "Empirical Relationship - Linear") 
	{
		ActivatedModule = Module_tbl[li_RowIdx][0];	Module_Empirical_Linear();
	}
	
	else if (Module_tbl[li_RowIdx][2] == "Empirical Relationship - Exponential") 
	{
		ActivatedModule = Module_tbl[li_RowIdx][0];	Module_Empirical_Exponential();
	}
	
	else if (Module_tbl[li_RowIdx][2] == "Perimeter of Circle") 
	{
		ActivatedModule = Module_tbl[li_RowIdx][0];	Module_PerimeterOfCircle();
	}
	
	else if (Module_tbl[li_RowIdx][2] == "Area of Circle") 
	{
		ActivatedModule = Module_tbl[li_RowIdx][0];	Module_AreaOfCircle();
	}
	
	else if (Module_tbl[li_RowIdx][2] == "Summation") 
	{
		ActivatedModule = Module_tbl[li_RowIdx][0];	Module_Summation();
	}
	
	else if (Module_tbl[li_RowIdx][2] == "Product") 
	{
		ActivatedModule = Module_tbl[li_RowIdx][0];	Module_Product();
	}
}


// This procedure is originally used in process block to send signal to Equation Editor for processing
// This procedure is not used anymore after using include files. Chiu 04/02/2015
Procedure Module_PreDefinedEquation() // jump
{
	String ModuleOutput;
	Integer EquationEditorBlockNum;
	Integer NumOfRows_ModuleTable;
	Integer NumOfColumns_ModuleTable;
	Integer NumOfRows_ModuleInputTable;
	Integer NumOfColumns_ModuleInputTable;
	
	Integer DBTableIndex_Module;
	Integer DBTableIndex_ModuleInput;
		
	******************************************************************************************************************************
	******************* Identify Activated module parameters numbers *************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == ActivatedModuleName)
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	
	
	NumOfRows_ModuleTable = 1;
	NumOfColumns_ModuleTable = GetDimensionColumns(Module_tbl);
	NumOfRows_ModuleInputTable = ModuleEndRowIndex-ModuleStartRowIndex+1;
	NumOfColumns_ModuleInputTable = GetDimensionColumns(Module_Input_tbl);
	
	******************* Create Dynamic tables for module and module input in Equation Editor Block *******************************
	*** Safe check to delete ***
	if (DBTableExists(DBIndex, DBTableGetIndex(DBIndex, "DBTable_Module")) == TRUE)
	{
		DBTableDeleteByIndex(DBIndex, DBTableGetIndex(DBIndex, "DBTable_Module"));
	}
	
	if (DBTableExists(DBIndex, DBTableGetIndex(DBIndex, "DBTable_ModuleInput")) == TRUE)
	{
		DBTableDeleteByIndex(DBIndex, DBTableGetIndex(DBIndex, "DBTable_ModuleInput"));
	}
	
	*** Create temporary module and module input tables ***
	DBTableIndex_Module = DBTableCreateByIndex(DBIndex, "DBTable_Module");
	DBTableIndex_ModuleInput = DBTableCreateByIndex(DBIndex, "DBTable_ModuleInput");
	
	DBRecordsInsert(DBIndex, DBTableIndex_Module, 0, 1);

	for (j = 0; j < NumOfColumns_ModuleTable; j++)
	{
		DBFieldCreateByIndex(DBIndex, DBTableIndex_Module, j, DB_FIELDTYPE_STRING_VALUE, 0, 0, 0, 0);
		
		DBDataSetAsString(DBIndex, DBTableIndex_Module, j+1, 1, Module_tbl[i][j]);
	}
	
	DBRecordsInsert(DBIndex, DBTableIndex_ModuleInput, 0, NumOfRows_ModuleInputTable);
	
	for (j = 0; j < NumOfColumns_ModuleInputTable; j++)
	{
		DBFieldCreateByIndex(DBIndex, DBTableIndex_ModuleInput, j, DB_FIELDTYPE_STRING_VALUE, 0, 0, 0, 0);
		
		for (k = ModuleStartRowIndex; k <= ModuleEndRowIndex; k++)
		{
			DBDataSetAsString(DBIndex, DBTableIndex_ModuleInput, j+1, k-ModuleStartRowIndex+1, Module_Input_tbl[k][j]);
		}
	}
	
	*** populate module and module input tables to eqnation editor ***
	for (j = 0; j < NumBlocks(); j++)
	{
		if (BlockName(j) == "EQUATION EDITOR") EquationEditorBlockNum = j;
	}
	
	// Module Table
	DBDatatable(EquationEditorBlockNum, "Module_tbl", DBIndex, DBTableIndex_Module, FALSE);
	
	// Module Input Table
	DBDatatable(EquationEditorBlockNum, "Module_Input_tbl", DBIndex, DBTableIndex_ModuleInput, FALSE);
	
	
	******************************************************************************************************************************
		
	// Link Module results to output parameters
	SetDialogVariable(EquationEditorBlockNum, "PreDefinedModule_swh", TRUE, 0, 0);
	
	for (j = 0; j < NumOfRows_ModuleInputTable; j++)
	{
		if (DBDataGetAsString(DBIndex, DBTableIndex_ModuleInput, 3, j+1) == "O")
		{
			ModuleOutput = DBDataGetAsString(DBIndex, DBTableIndex_ModuleInput, 8, j+1);
			Module_Input_tbl[ModuleStartRowIndex+j][7] = ModuleOutput;
		}
	}
	SetDialogVariableNoMsg(EquationEditorBlockNum, "PreDefinedModule_swh", FALSE, 0, 0);
	
	DBTableDeleteByIndex(DBIndex, DBTableIndex_Module);
	DBTableDeleteByIndex(DBIndex, DBTableIndex_ModuleInput);
}

