real RoundDec(String ls_RoundMode, real lr_UglyNum,real lr_NumDecimal);

Procedure Module_Summation()
{	
	Real OP_Sum;
	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Summation")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names
	
	// Module Equation
	OP_Sum = 0;
	for (j = ModuleStartRowIndex; j <= ModuleEndRowIndex; j++)
	{
		if (Module_Input_tbl[j][2] == "I") //AND Module_Input_tbl[j][4] == TRUE) //CHE EDITED ON OCT24
		{
		 OP_Sum += StrToReal(Module_Input_tbl[j][7]);
		}
	}
	
	// Link Module results to output parameters
	for (j = ModuleStartRowIndex; j <= ModuleEndRowIndex; j++)
	{
		if (Module_Input_tbl[j][2] == "O") 	Module_Input_tbl[j][7] = RoundDec(R, OP_Sum, 5);
	}	
}

Procedure Module_Product()
{	
	Real OP_Product;
	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Product")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names
	
	// Module Equation
	OP_Product = 1;
	for (j = ModuleStartRowIndex; j <= ModuleEndRowIndex; j++)
	{
		if (Module_Input_tbl[j][2] == "I")//AND Module_Input_tbl[j][4] == TRUE) // CHE edited
		{
			OP_Product = OP_Product*StrToReal(Module_Input_tbl[j][7]);
		}
	}

	// Link Module results to output parameters
	for (j = ModuleStartRowIndex; j <= ModuleEndRowIndex; j++)
	{
		if (Module_Input_tbl[j][2] == "O") 	Module_Input_tbl[j][7] = RoundDec(R, OP_Product, 5);
	}	
}

Procedure Module_MIN()
{	
	Integer BlankIndex;
	Real OP_Min;
	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Minimum")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names
	
	// Module Equation
	OP_Min = 1000000000000;
	BlankIndex = 0;
	
	for (j = ModuleStartRowIndex; j <= ModuleEndRowIndex; j++)
	{
		if (Module_Input_tbl[j][2] == "I")//AND Module_Input_tbl[j][4] == TRUE) // CHE edited
		{
			if (StrLen(Module_Input_tbl[j][7]) == 0 OR StrLen(OP_Min) == 0) BlankIndex++;
			
			else if (StrLen(Module_Input_tbl[j][7]) != 0 AND NoValue(StrToReal(Module_Input_tbl[j][7]))) OP_Min = OP_Min;
			
			else OP_Min = Min2(OP_Min,StrToReal(Module_Input_tbl[j][7]));
		}
	}

	// Link Module results to output parameters
	for (j = ModuleStartRowIndex; j <= ModuleEndRowIndex; j++)
	{
		if (Module_Input_tbl[j][2] == "O" AND BlankIndex == 0) 	Module_Input_tbl[j][7] = RoundDec(R, OP_Min, 5);
		
		else if(Module_Input_tbl[j][2] == "O") Module_Input_tbl[j][7] = "";
	}	
}

Procedure Module_Max()
{	
	Integer BlankIndex;
	Real OP_Max;
	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Maximum")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names
	
	// Module Equation
	OP_Max = -1000000000000;
	BlankIndex = 0;
	
	for (j = ModuleStartRowIndex; j <= ModuleEndRowIndex; j++)
	{
		if (Module_Input_tbl[j][2] == "I")//AND Module_Input_tbl[j][4] == TRUE) // CHE edited
		{
			if (StrLen(Module_Input_tbl[j][7]) == 0 OR StrLen(OP_Max) == 0) BlankIndex++;
			
			else if (StrLen(Module_Input_tbl[j][7]) != 0 AND NoValue(StrToReal(Module_Input_tbl[j][7]))) OP_Max = OP_Max;
			
			else OP_Max = Max2(OP_Max,StrToReal(Module_Input_tbl[j][7]));
		}
	}

	// Link Module results to output parameters
	for (j = ModuleStartRowIndex; j <= ModuleEndRowIndex; j++)
	{
		if (Module_Input_tbl[j][2] == "O" AND BlankIndex == 0) 	Module_Input_tbl[j][7] = RoundDec(R, OP_Max, 5);
		else if(Module_Input_tbl[j][2] == "O") Module_Input_tbl[j][7] = "";
	}	
}

Procedure Module_AreaOfCircle()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Dia; 	// IP = Input Parameter
	Real OP_Area;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Area of Circle") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Dia	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Area = 3.14*IP_Dia^2/4;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+1][7] = RoundDec(R, OP_Area, 5);

}

Procedure Module_PerimeterOfCircle()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Dia; 	// IP = Input Parameter
	Real OP_Length;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Perimeter of Circle") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Dia	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Length = 3.14*IP_Dia;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+1][7] = RoundDec(R, OP_Length, 5);
}

Procedure Module_Empirical_Exponential()
{
																									**## 2.Change Parameter Name ##**
	Real IP_X, IP_a, IP_b; 	// IP = Input Parameter
	Real OP_Y;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Empirical Relationship - Exponential") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_X	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_a	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_b	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Y = IP_a*Exp(IP_X*IP_b);
		
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+3][7] = RoundDec(R, OP_Y, 5);
}

Procedure Module_Empirical_Linear()
{
																									**## 2.Change Parameter Name ##**
	Real IP_X, IP_a, IP_b; 	// IP = Input Parameter
	Real OP_Y;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Empirical Relationship - Linear") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_X	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_a	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_b	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Y = IP_a*IP_X+IP_b;
		
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+3][7] = RoundDec(R, OP_Y, 5);
}

Procedure Module_Empirical_Logrithmatic_e()
{
																									**## 2.Change Parameter Name ##**
	Real IP_X, IP_a, IP_b; 	// IP = Input Parameter
	Real OP_Y;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Empirical Relationship - Logrithmatic (e)") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_X	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_a	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_b	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Y = IP_a*LOG(IP_X)+IP_b;
		
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+3][7] = RoundDec(R, OP_Y, 5);
}

Procedure Module_Empirical_Logrithmatic_10()
{
																									**## 2.Change Parameter Name ##**
	Real IP_X, IP_a, IP_b; 	// IP = Input Parameter
	Real OP_Y;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Empirical Relationship - Logrithmatic (10)") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_X	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_a	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_b	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Y = IP_a*LOG10(IP_X)+IP_b;
		
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+3][7] = RoundDec(R, OP_Y, 5);
}

Procedure Module_Empirical_Polymonial()
{
																									**## 2.Change Parameter Name ##**
	Real IP_X, IP_a, IP_b, IP_c, IP_d, IP_e, IP_f; 	// IP = Input Parameter
	Real OP_Y;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Empirical Relationship - Polymonial") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_X	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_a	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_b	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_c	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_d	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_e	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	IP_f	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Y = IP_a*IP_X^5+IP_b*IP_X^4+IP_c*IP_X^3+IP_d*IP_X^2+IP_e*IP_X^1+IP_f;
		
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+7][7] = RoundDec(R, OP_Y, 5);
}

Procedure Module_Empirical_Power()
{
																									**## 2.Change Parameter Name ##**
	Real IP_X, IP_a, IP_b; 	// IP = Input Parameter
	Real OP_Y;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Empirical Relationship - Power") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_X	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_a	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_b	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Y = IP_a*IP_X^IP_b;
		
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+3][7] = RoundDec(R, OP_Y, 5);
}

Procedure Module_Empirical_DBP()
{
																									**## 2.Change Parameter Name ##**
	Real IP_pH, IP_TOC, IP_SUVA, IP_Cl2, IP_Time, IP_Temp, IP_a, IP_b, IP_c, IP_d, IP_e, IP_f, IP_g; 	// IP = Input Parameter
	Real OP_THM;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Empirical Relationship - DBP") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_pH	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_TOC	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_SUVA	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_Cl2	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_Time	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_Temp	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	IP_a	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);
	IP_b	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+7][7]);
	IP_c	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+8][7]);
	IP_d	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+9][7]);
	IP_e	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+10][7]);
	IP_f	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+11][7]);
	IP_g	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+12][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_THM = IP_a*IP_pH^IP_b*IP_TOC^IP_c*IP_SUVA^IP_d*IP_Cl2^IP_e*IP_Time^IP_f*IP_Temp^IP_g;
		
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+13][7] = RoundDec(R, OP_THM, 5);
}

Procedure Module_Ratio() // Use Naming Convention: Module_CC000XXXXXX... CC = Category Abbreviation, 000 = Numeric ID, XXXX... are descriptive name of the moduel.
{
																									**## 2.Change Parameter Name ##**
	Real IP_Numerator, IP_Denominator; 	// IP = Input Parameter
	Real OP_Ratio;			 			// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Ratio") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Numerator	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_Denominator	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	if (IP_Denominator == 0) OP_Ratio = 0;
	
	else OP_Ratio = IP_Numerator/IP_Denominator;
		
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+2][7] = RoundDec(R, OP_Ratio, 5);
}

Procedure Module_Subtraction()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Minuend, IP_Subtrahend; 		// IP = Input Parameter
	Real OP_Difference;			 			// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Subtraction") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Minuend	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_Subtrahend	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Difference = IP_Minuend-IP_Subtrahend;
		
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+2][7] = RoundDec(R, OP_Difference, 5);	
}