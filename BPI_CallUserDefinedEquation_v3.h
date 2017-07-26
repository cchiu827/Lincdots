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

************************************
procedure SetUpArraysForCalculation(String ls_ActivatedModuleID, String ls_SelectedEquation)
{
	integer i;
	integer liNumRecords;	
	integer liNumInputs;
	string lsValue;
	
	liNumRecords = 100;//GetDimension(gsDialogTable);
	makeArray(CompiledEquation_da, 1);
	makeArray(iV, liNumRecords);
	makeArray(oV, liNumRecords);
	for(i = 0; i < liNumRecords; i++)
	{
		iV[i] = 0;
		oV[i] = 0;
	}

	liNumInputs = 0;
	for(i = 0; i < GetDimension(Module_Input_tbl); i++)
	{
		if(Module_Input_tbl[i][0] == ls_ActivatedModuleID AND Module_Input_tbl[i][1] == ls_SelectedEquation AND Module_Input_tbl[i][2] == "I")
		{
			lsValue = Module_Input_tbl[i][7];
			iV[liNumInputs] = StrToReal(lsValue);
			liNumInputs++;
		}
	}
	
}

************************************
procedure GetResultsFromOutputArray(String ls_ActivatedModuleID, String ls_SelectedEquation)
{
	integer i;
	integer liNumRecords;
	integer liNumOutputs;
	real lrValue;
	
	liNumOutputs = 0;
	liNumRecords = 100;//GetDimension(gsDialogTable);
	for(i = 0; i < GetDimension(Module_Input_tbl); i++)
	{
		if(Module_Input_tbl[i][1] == ls_SelectedEquation AND Module_Input_tbl[i][2] == "O")
		{
			Module_Input_tbl[i][7] = oV[liNumOutputs];
			liNumOutputs++;
		}
	}	
}

************************************
// This message occurs for each step in the simulation.
Procedure ExecuteUserDefinedEquation(String ls_ActivatedModuleID, String ls_SelectedEquation)
{
	String lsEquationName;
	integer liPointerValue;
	
	GetDBIndexes();
	SetUpArraysForCalculation(ls_ActivatedModuleID, ls_SelectedEquation);
//	liEquationID = GetCurrentPopupEquationID();
	for (i = 1; i <= DBRecordsGetNum(giDBIdx, giDBEquationDescriptionsTIdx); i++)
	{
		lsEquationName = DBDataGetAsString(giDBIdx, giDBEquationDescriptionsTIdx, 1, i);
		
		if (lsEquationName == ls_SelectedEquation)
		{
			liPointerValue = DBDataGetAsNumber(giDBIdx, giDBEquationDescriptionsTIdx, 2, i);
			BREAK;
		}
	}

//	liPointerValue = DBDataGetAsNumber(giDBIdx, giDBEquationDescriptionsTIdx, giEquationPointerEqDFIdx, liEquationID);
	PointerToDynamicArray(liPointerValue, CompiledEquation_da);
	EquationCalculateDynamicVariables(iV, oV, CompiledEquation_da);

	GetResultsFromOutputArray(ls_ActivatedModuleID, ls_SelectedEquation);
	
	
	DisposeArray(CompiledEquation_da);
	DisposeArray(iV);
	DisposeArray(oV);
}