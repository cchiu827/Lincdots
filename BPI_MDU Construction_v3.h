
real RoundDec(String ls_RoundMode, real lr_UglyNum,real lr_NumDecimal);

Procedure Module_ExcavationVolume()
{
																									**## 2.Change Parameter Name ##**
	Real IP_L, IP_AL, IP_W, IP_AW, IP_D, IP_AD, IP_F; 	// IP = Input Parameter
	Real OP_Vol;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Excavation Volume") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_L	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_AL	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_W	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_AW	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_D	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_AD	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	IP_F	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Vol = (IP_L+IP_AL)*(IP_W+IP_AW)*(IP_D+IP_AD)*IP_F/27;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+7][7] = RoundDec(R, OP_Vol, 5);
}

Procedure Module_ConcreteVolume_SlabOnGrade()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Number, IP_L, IP_W, IP_T; 	// IP = Input Parameter
	Real OP_Vol;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Concrete Volume - Slab on Grade") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Number	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_L		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_W		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_T		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Vol = IP_Number*(IP_L*IP_W*IP_T/12)/27;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+4][7] = RoundDec(R, OP_Vol, 5);
}

Procedure Module_ConcreteVolume_Wall()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Number, IP_L, IP_H, IP_T; 	// IP = Input Parameter
	Real OP_Vol;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Concrete Volume - Wall") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Number	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_L		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_H		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_T		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Vol = IP_Number*(IP_L*IP_H*IP_T/12)/27;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+4][7] = RoundDec(R, OP_Vol, 5);
}

Procedure Module_ConcreteVolume_ElevatedSlab()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Number, IP_L, IP_W, IP_T; 	// IP = Input Parameter
	Real OP_Vol;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Concrete Volume - Elevated Slab") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Number	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_L		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_W		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_T		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Vol = IP_Number*(IP_L*IP_W*IP_T/12)/27;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+4][7] = RoundDec(R, OP_Vol, 5);
}

Procedure Module_ConcreteVolume_CircularSlabOnGrade()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Number, IP_Area, IP_T; 	// IP = Input Parameter
	Real OP_Vol;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Concrete Volume - Circular Slab on Grade") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Number	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_Area		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_T		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Vol = IP_Number*(IP_Area*IP_T/12)/27;
		
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+3][7] = RoundDec(R, OP_Vol, 5);
}

Procedure Module_ConcreteVolume_CircularWall()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Number, IP_L, IP_H, IP_T; 	// IP = Input Parameter
	Real OP_Vol;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Concrete Volume - Circular Slab on Grade") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Number	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_L		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_H		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_T		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Vol = IP_Number*(IP_L*IP_H*IP_T/12)/27;
		
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+4][7] = RoundDec(R, OP_Vol, 5);
}

Procedure Module_ConcreteVolume_CircularElevatedSlab()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Number, IP_Area, IP_T; 	// IP = Input Parameter
	Real OP_Vol;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Concrete Volume - Circular Elevated Slab") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Number	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_Area		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_T		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Vol = IP_Number*(IP_Area*IP_T/12)/27;
		
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+3][7] = RoundDec(R, OP_Vol, 5);
}