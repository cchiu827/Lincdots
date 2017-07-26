Procedure ImportAssembly(String DBName, String AssemblyManagerName)
{
	Integer DBIdx;
	Integer TotalDBTables;
	String DBTableName;
	String AssemblyName;
	Integer DBTblIdx_AssemblyManager;
	Integer li_FindDuplicateAssemblyIndex;
	Integer ImportCaseNumber;
	Integer ChangeAssemblyName;
	Integer DBTblIdx_Assembly;
	Integer DBTblIdx_AssemblyInput;
	Integer DBTblIdx_AssemblyIO;
	Integer DBTblIdx_AssemblyCoCRR;
	Integer DBTblIdx_AssemblyCCUC;
	Integer DBTblIdx_AssemblyOMUC;
	Integer DBTblIdx_Assembly_New;
	Integer DBTblIdx_AssemblyInput_New;
	Integer DBTblIdx_AssemblyIO_New;
	Integer DBTblIdx_AssemblyCoCRR_New;
	Integer DBTblIdx_AssemblyCCUC_New;
	Integer DBTblIdx_AssemblyOMUC_New;
	Integer li_InputCount;
	Integer li_OutputCount;
	
	DBIdx = DBDatabaseGetIndex(DBName);
	
	TotalDBTables = DBTablesGetNum(DBIdx);
	DBTblIdx_AssemblyManager = DBTableGetIndex(DBIdx, AssemblyManagerName);
	
	for (i = 0; i < TotalDBTables; i++)
	{
		DBTableName = DBTableGetName(DBIdx, i);
		
		if (StrPart(DBTableName, StrLen(DBTableName)-2, 2) == "_P") *** Find primary assembly table
		{
			DBTblIdx_Assembly = i;
			
			if (DBName == "Module Assembly")
			{
				AssemblyName = StrPart(DBTableName, 7, StrLen(DBTableName)-9);
				DBTblIdx_AssemblyInput = DBTableGetIndex(DBIdx, "MDUASB_"+AssemblyName+"_Input");
				DBTblIdx_AssemblyCoCRR = DBTableGetIndex(DBIdx, "MDUASB_"+AssemblyName+"_CoCRR");
				DBTblIdx_AssemblyCCUC = DBTableGetIndex(DBIdx, "MDUASB_"+AssemblyName+"_CCUC");
				DBTblIdx_AssemblyOMUC = DBTableGetIndex(DBIdx, "MDUASB_"+AssemblyName+"_OMUC");
			}
			
			else if (DBName == "Equation Assembly")
			{
				AssemblyName = StrPart(DBTableName, 3, StrLen(DBTableName)-5);
				DBTblIdx_AssemblyInput = DBTableGetIndex(DBIdx, "EQ_"+AssemblyName+"_Input");
				DBTblIdx_AssemblyIO = DBTableGetIndex(DBIdx, "EQ_"+AssemblyName+"_I/O");
				
				li_InputCount = 0;
				li_OutputCount = 0;
				for (j = 1; j <= DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyIO); j++)
				{
					if (DBDataGetAsString(DBIdx, DBTblIdx_AssemblyIO, 3, j) == "I") li_InputCount++;
					if (DBDataGetAsString(DBIdx, DBTblIdx_AssemblyIO, 3, j) == "O") li_OutputCount++;
				}
			}
			
			li_FindDuplicateAssemblyIndex = 0;
			for (j = 1; j <= DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyManager); j++)
			{
				if (DBDataGetAsString(DBIdx, DBTblIdx_AssemblyManager, 1, j) == AssemblyName)
				{
					if (DBDataGetAsNumber(DBIdx, DBTblIdx_AssemblyManager, 2, j) == DBTblIdx_Assembly) li_FindDuplicateAssemblyIndex = -1;
					
					else if (DBDataGetAsNumber(DBIdx, DBTblIdx_AssemblyManager, 2, j) != DBTblIdx_Assembly) li_FindDuplicateAssemblyIndex++;
				}
			}
			
			if (li_FindDuplicateAssemblyIndex == -1) ImportCaseNumber = 100; *** default case: do nothing
			else if (li_FindDuplicateAssemblyIndex == 0) ImportCaseNumber = 0; *** import case 0: import 5 table into assembly manager DB table
			else if (li_FindDuplicateAssemblyIndex > 0) *** find duplicate assembly name, ask user to change name or ignore this assembly
			{
				ChangeAssemblyName = UserPrompt("Find duplicate Assembly name """+AssemblyName+""". Do you want to rename this new Assembly? (OK to rename, CANCEL to ignore)");
				
				if (ChangeAssemblyName == TRUE) ImportCaseNumber = 1; *** import case 1: rename assembly name
				
				if (ChangeAssemblyName == FALSE) ImportCaseNumber = 2; *** import case 2: ignore this new assembly
			}
			
			switch (ImportCaseNumber)
			{
				case 0: //import tables into assembly manager DB table
					DBRecordsInsert(DBIdx, DBTblIdx_AssemblyManager, 0, 1);
					DBDataSetAsString(DBIdx, DBTblIdx_AssemblyManager, 1, DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyManager), AssemblyName);
					DBDataSetAsNumber(DBIdx, DBTblIdx_AssemblyManager, 2, DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyManager), DBTblIdx_Assembly);
					DBDataSetAsNumber(DBIdx, DBTblIdx_AssemblyManager, 3, DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyManager), DBTblIdx_AssemblyInput);
					
					if (DBName == "Module Assembly")
					{
						DBDataSetAsNumber(DBIdx, DBTblIdx_AssemblyManager, 6, DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyManager), DBTblIdx_AssemblyCoCRR);
						DBDataSetAsNumber(DBIdx, DBTblIdx_AssemblyManager, 7, DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyManager), DBTblIdx_AssemblyCCUC);
						DBDataSetAsNumber(DBIdx, DBTblIdx_AssemblyManager, 8, DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyManager), DBTblIdx_AssemblyOMUC);
					}
					
					else if (DBName == "Equation Assembly")
					{
						DBDataSetAsNumber(DBIdx, DBTblIdx_AssemblyManager, 6, DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyManager), DBTblIdx_AssemblyIO);
						DBDataSetAsNumber(DBIdx, DBTblIdx_AssemblyManager, 7, DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyManager), li_InputCount);
						DBDataSetAsNumber(DBIdx, DBTblIdx_AssemblyManager, 8, DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyManager), li_OutputCount);
					}
					
					BREAK;
				
				case 1: // rename assembly name
					AssemblyName = UserParameter("Please provide a new Assembly name.", AssemblyName);
					for (j = 1; j <= DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyManager); j++)
					{
						while (DBDataGetAsString(DBIdx, DBTblIdx_AssemblyManager, 1, j) == AssemblyName)
						{
							AssemblyName = UserParameter("This Assembly name is currently used. Please use another Assembly name.", AssemblyName);
						}
					}
					
					if (AssemblyName != BLANK)
					{
						DBRecordsInsert(DBIdx, DBTblIdx_AssemblyManager, 0, 1);
						DBDataSetAsString(DBIdx, DBTblIdx_AssemblyManager, 1, DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyManager), AssemblyName);
						
						if (DBName == "Module Assembly")
						{
							*** recreate assembly primary table
							DBTblIdx_Assembly_New = DBTableCreateByIndex(DBIdx, "MDUASB_"+AssemblyName+"_P");
							
							DBRecordsInsert(DBIdx, DBTblIdx_Assembly_New, 0, DBRecordsGetNum(DBIdx, DBTblIdx_Assembly));
							for (j = 1; j <= DBFieldsGetNum(DBIdx, DBTblIdx_Assembly); j++)
							{
								DBFieldCreateByIndex(DBIdx, DBTblIdx_Assembly_New, j, DB_FIELDTYPE_STRING_VALUE, 0, 0, 0, 0);
								for (k = 1; k <= DBRecordsGetNum(DBIdx, DBTblIdx_Assembly); k++)
								{
									DBDataSetAsString(DBIdx, DBTblIdx_Assembly_New, j, k, DBDataGetAsString(DBIdx, DBTblIdx_Assembly, j, k));
								}
							}
							
							*** recreate assembly input table
							DBTblIdx_AssemblyInput_New = DBTableCreateByIndex(DBIdx, "MDUASB_"+AssemblyName+"_Input");
													
							DBRecordsInsert(DBIdx, DBTblIdx_AssemblyInput_New, 0, DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyInput));
							for (j = 1; j <= DBFieldsGetNum(DBIdx, DBTblIdx_AssemblyInput); j++)
							{
								DBFieldCreateByIndex(DBIdx, DBTblIdx_AssemblyInput_New, j, DB_FIELDTYPE_STRING_VALUE, 0, 0, 0, 0);
								for (k = 1; k <= DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyInput); k++)
								{									DBDataSetAsString(DBIdx, DBTblIdx_AssemblyInput_New, j, k, DBDataGetAsString(DBIdx, DBTblIdx_AssemblyInput, j, k));								}							}
							
							*** recreate assembly CoCRR table						
							DBTblIdx_AssemblyCoCRR_New = DBTableCreateByIndex(DBIdx, "MDUASB_"+AssemblyName+"_CoCRR");
													
							DBRecordsInsert(DBIdx, DBTblIdx_AssemblyCoCRR_New, 0, DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyCoCRR));
							for (j = 1; j <= DBFieldsGetNum(DBIdx, DBTblIdx_AssemblyCoCRR); j++)
							{
								DBFieldCreateByIndex(DBIdx, DBTblIdx_AssemblyCoCRR_New, j, DB_FIELDTYPE_STRING_VALUE, 0, 0, 0, 0);
								for (k = 1; k <= DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyCoCRR); k++)
								{
									DBDataSetAsString(DBIdx, DBTblIdx_AssemblyCoCRR_New, j, k, DBDataGetAsString(DBIdx, DBTblIdx_AssemblyCoCRR, j, k));
								}
							}
							
							*** recreate assembly CCUC table
							DBTblIdx_AssemblyCCUC_New = DBTableCreateByIndex(DBIdx, "MDUASB_"+AssemblyName+"_CCUC");
													
							DBRecordsInsert(DBIdx, DBTblIdx_AssemblyCCUC_New, 0, DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyCCUC));
							for (j = 1; j <= DBFieldsGetNum(DBIdx, DBTblIdx_AssemblyCCUC); j++)
							{
								DBFieldCreateByIndex(DBIdx, DBTblIdx_AssemblyCCUC_New, j, DB_FIELDTYPE_STRING_VALUE, 0, 0, 0, 0);
								for (k = 1; k <= DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyCCUC); k++)
								{
									DBDataSetAsString(DBIdx, DBTblIdx_AssemblyCCUC_New, j, k, DBDataGetAsString(DBIdx, DBTblIdx_AssemblyCCUC, j, k));
								}
							}
							
							*** recreate assembly OMUC table
							DBTblIdx_AssemblyOMUC_New = DBTableCreateByIndex(DBIdx, "MDUASB_"+AssemblyName+"_OMUC");
													
							DBRecordsInsert(DBIdx, DBTblIdx_AssemblyOMUC_New, 0, DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyOMUC));
							for (j = 1; j <= DBFieldsGetNum(DBIdx, DBTblIdx_AssemblyOMUC); j++)
							{
								DBFieldCreateByIndex(DBIdx, DBTblIdx_AssemblyOMUC_New, j, DB_FIELDTYPE_STRING_VALUE, 0, 0, 0, 0);
								for (k = 1; k <= DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyOMUC); k++)
								{
									DBDataSetAsString(DBIdx, DBTblIdx_AssemblyOMUC_New, j, k, DBDataGetAsString(DBIdx, DBTblIdx_AssemblyOMUC, j, k));
								}
							}
							
							*** insert record for new assembly in assembly manager
							DBDataSetAsNumber(DBIdx, DBTblIdx_AssemblyManager, 2, DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyManager), DBTblIdx_Assembly_New);
							DBDataSetAsNumber(DBIdx, DBTblIdx_AssemblyManager, 3, DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyManager), DBTblIdx_AssemblyInput_New);
							DBDataSetAsNumber(DBIdx, DBTblIdx_AssemblyManager, 6, DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyManager), DBTblIdx_AssemblyCoCRR_New);
							DBDataSetAsNumber(DBIdx, DBTblIdx_AssemblyManager, 7, DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyManager), DBTblIdx_AssemblyCCUC_New);
							DBDataSetAsNumber(DBIdx, DBTblIdx_AssemblyManager, 8, DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyManager), DBTblIdx_AssemblyOMUC_New);
							
							*** delete original assembly tables
							DBTableDeleteByIndex(DBIdx, DBTblIdx_AssemblyCoCRR);
							DBTableDeleteByIndex(DBIdx, DBTblIdx_AssemblyCCUC);
							DBTableDeleteByIndex(DBIdx, DBTblIdx_AssemblyOMUC);
						}
						
						else if (DBName == "Equation Assembly")
						{
							*** recreate assembly primary table
							DBTblIdx_Assembly_New = DBTableCreateByIndex(DBIdx, "EQ_"+AssemblyName+"_P");
							
							DBRecordsInsert(DBIdx, DBTblIdx_Assembly_New, 0, DBRecordsGetNum(DBIdx, DBTblIdx_Assembly));
							for (j = 1; j <= DBFieldsGetNum(DBIdx, DBTblIdx_Assembly); j++)
							{
								DBFieldCreateByIndex(DBIdx, DBTblIdx_Assembly_New, j, DB_FIELDTYPE_STRING_VALUE, 0, 0, 0, 0);
								for (k = 1; k <= DBRecordsGetNum(DBIdx, DBTblIdx_Assembly); k++)
								{
									DBDataSetAsString(DBIdx, DBTblIdx_Assembly_New, j, k, DBDataGetAsString(DBIdx, DBTblIdx_Assembly, j, k));
								}
							}
							
							*** recreate assembly input table
							DBTblIdx_AssemblyInput_New = DBTableCreateByIndex(DBIdx, "EQ_"+AssemblyName+"_Input");
													
							DBRecordsInsert(DBIdx, DBTblIdx_AssemblyInput_New, 0, DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyInput));
							for (j = 1; j <= DBFieldsGetNum(DBIdx, DBTblIdx_AssemblyInput); j++)
							{
								DBFieldCreateByIndex(DBIdx, DBTblIdx_AssemblyInput_New, j, DB_FIELDTYPE_STRING_VALUE, 0, 0, 0, 0);
								for (k = 1; k <= DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyInput); k++)
								{
									DBDataSetAsString(DBIdx, DBTblIdx_AssemblyInput_New, j, k, DBDataGetAsString(DBIdx, DBTblIdx_AssemblyInput, j, k));
								}
							}
							
							*** recreate assembly I/O table						
							DBTblIdx_AssemblyIO_New = DBTableCreateByIndex(DBIdx, "EQ_"+AssemblyName+"_I/O");
													
							DBRecordsInsert(DBIdx, DBTblIdx_AssemblyIO_New, 0, DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyIO));
							for (j = 1; j <= DBFieldsGetNum(DBIdx, DBTblIdx_AssemblyIO); j++)
							{
								DBFieldCreateByIndex(DBIdx, DBTblIdx_AssemblyIO_New, j, DB_FIELDTYPE_STRING_VALUE, 0, 0, 0, 0);
								for (k = 1; k <= DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyIO); k++)
								{
									DBDataSetAsString(DBIdx, DBTblIdx_AssemblyIO_New, j, k, DBDataGetAsString(DBIdx, DBTblIdx_AssemblyIO, j, k));
								}
							}
							
							*** insert record for new assembly in assembly manager
							DBDataSetAsNumber(DBIdx, DBTblIdx_AssemblyManager, 2, DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyManager), DBTblIdx_Assembly_New);
							DBDataSetAsNumber(DBIdx, DBTblIdx_AssemblyManager, 3, DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyManager), DBTblIdx_AssemblyInput_New);
							DBDataSetAsNumber(DBIdx, DBTblIdx_AssemblyManager, 6, DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyManager), DBTblIdx_AssemblyIO_New);
							DBDataSetAsNumber(DBIdx, DBTblIdx_AssemblyManager, 7, DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyManager), li_InputCount);
							DBDataSetAsNumber(DBIdx, DBTblIdx_AssemblyManager, 8, DBRecordsGetNum(DBIdx, DBTblIdx_AssemblyManager), li_OutputCount);
							
							*** delete original assembly tables
							DBTableDeleteByIndex(DBIdx, DBTblIdx_AssemblyIO);
						}
						
						DBTableDeleteByIndex(DBIdx, DBTblIdx_Assembly);
						DBTableDeleteByIndex(DBIdx, DBTblIdx_AssemblyInput);
					}
					
					BREAK;
				
				case 2:
					BREAK;
				
				default:
					BREAK;	
			}
		}
	}
	
	DBTableSort(DBIdx, DBTblIdx_AssemblyManager, 1, TRUE, 0, FALSE, 0, FALSE);
}