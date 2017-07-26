real RoundDec(String ls_RoundMode, real lr_UglyNum,real lr_NumDecimal);

Procedure Module_DesignHRTLtoW()
{
	Real IP_Flow, IP_HRT, IP_SWD, IP_W, IP_NumOfTrainD, IP_NumOfTrainR, IP_FB;//IP_LtoW, CHE edited
	Real OP_NumOfTrainTtl, OP_DepthTtl, OP_LengthOvl, OP_VolumeTtl, OP_LengthEach;
	
	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Design HRT to Volume")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names

	IP_NumOfTrainD	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_NumOfTrainR	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	//IP_LtoW			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]); CHE, the following moved up 1
	IP_W			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_SWD			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_FB			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_HRT			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	IP_Flow			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);

	
	// Module Equation
	OP_NumOfTrainTtl = IP_NumOfTrainD + IP_NumOfTrainR;
	OP_DepthTtl = IP_SWD + IP_FB;
	OP_LengthEach = (IP_HRT*IP_Flow/24/IP_SWD/IP_W/IP_NumOfTrainD*10^6/7.48);//CHE
	OP_LengthOvl = OP_LengthEach * OP_NumofTrainTtl;
	OP_VolumeTtl = IP_SWD*IP_W*OP_LengthEach*7.48/10^6*OP_NumOfTrainTtl;
	
	// Link Module results to output parameters
 	Module_Input_tbl[ModuleStartRowIndex+7][7] = RoundDec(R, OP_NumOfTrainTtl, 5);
	Module_Input_tbl[ModuleStartRowIndex+8][7] = RoundDec(R, OP_DepthTtl, 5);
	Module_Input_tbl[ModuleStartRowIndex+9][7] = RoundDec(R, OP_LengthOvl, 5);
	Module_Input_tbl[ModuleStartRowIndex+10][7] = RoundDec(R, OP_LengthEach, 5);
	Module_Input_tbl[ModuleStartRowIndex+11][7] = RoundDec(R, OP_VolumeTtl, 5);
}

Procedure Module_DisinfectionCT()
{
	Real IP_ChemDose, IP_ContactTime;
	Real OP_Ct;
	
	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Disinfection - Ct")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names
	IP_ChemDose		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_ContactTime	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	
	// Module Equation
	OP_Ct = IP_ChemDose*IP_ContactTime;

	// Link Module results to output parameters
	Module_Input_tbl[ModuleStartRowIndex+2][7] = RoundDec(R, OP_Ct, 5);	
}

Procedure Module_BasinCompartments()
{
	Real IP_NumOfTrainD, IP_NumOfTrainR, IP_W, IP_SWD, IP_FB, IP_AnoxPct, IP_NumOfStage, IP_Lovl; 	// IP = Input Parameter
	Real OP_Lanox, OP_LperStage, OP_VperStage, OP_Vttl; 												// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Basin Compartments")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names
	IP_NumOfTrainD	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_NumOfTrainR	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_W			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_SWD			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_FB			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_AnoxPct		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7])/100;
	IP_NumOfStage	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);
	IP_Lovl			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+7][7]);
	
	// Module Equation
	OP_Lanox = IP_Lovl*IP_AnoxPct;
	OP_LperStage = OP_Lanox/IP_NumOfStage;
	OP_VperStage = IP_W*IP_SWD*OP_LperStage*7.48/10^6;
	OP_Vttl = OP_VperStage*IP_NumOfStage*(IP_NumOfTrainD+IP_NumOfTrainR);
	
	// Link Module results to output parameters
	Module_Input_tbl[ModuleStartRowIndex+8][7] = RoundDec(R, OP_Lanox, 5);
	Module_Input_tbl[ModuleStartRowIndex+9][7] = RoundDec(R, OP_LperStage, 5);
	Module_Input_tbl[ModuleStartRowIndex+10][7] = RoundDec(R, OP_VperStage, 5);
	Module_Input_tbl[ModuleStartRowIndex+11][7] = RoundDec(R, OP_Vttl, 5);
}

Procedure Module_ActualHRT_AllinService() //CHE Edited 
{
	Real IP_Flow, IP_Width, IP_SWD, IP_ActLengthEach, IP_NumofTrainsTotal; 	// IP = Input Parameter
	Real OP_ActVol, OP_HRT, OP_OvlLength; 			// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Actual HRT (All in service)")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names
	IP_Flow	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_Width= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_SWD= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_ActLengthEach= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_NumofTrainsTotal = StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	
	// Module Equation
	OP_ActVol = IP_Width * IP_SWD * IP_ActLengthEach * IP_NumofTrainsTotal *7.48 / 1000000;
	OP_HRT = OP_ActVol / IP_Flow *24;
	OP_OvlLength = IP_ActLengthEach * IP_NumofTrainsTotal;
	
	// Link Module results to output parameters
	Module_Input_tbl[ModuleStartRowIndex+5][7] = RoundDec(R, OP_ActVol, 5);
	Module_Input_tbl[ModuleStartRowIndex+6][7] = RoundDec(R, OP_HRT, 5);
	Module_Input_tbl[ModuleStartRowIndex+7][7] = RoundDec(R, OP_OvlLength,5);
}

Procedure Module_ActualHRT_DutyinService() //CHE Added
{
	Real IP_Flow, IP_Width, IP_SWD, IP_ActLengthEach, IP_NumofDutyTrains; 	// IP = Input Parameter
	Real OP_ActVol, OP_HRT, OP_OvlLengthD; 			// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Actual HRT (Duty in service)")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names
	IP_Flow	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_Width= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_SWD= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_ActLengthEach= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_NumofDutyTrains = StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	
	// Module Equation
	OP_ActVol = IP_Width * IP_SWD * IP_ActLengthEach * IP_NumofDutyTrains *7.48 / 1000000;
	OP_HRT = OP_ActVol / IP_Flow *24;
	OP_OvlLengthD = IP_ActLengthEach * IP_NumofDutyTrains;
	
	// Link Module results to output parameters
	Module_Input_tbl[ModuleStartRowIndex+5][7] = RoundDec(R, OP_ActVol, 5);
	Module_Input_tbl[ModuleStartRowIndex+6][7] = RoundDec(R, OP_HRT, 5);
	Module_Input_tbl[ModuleStartRowIndex+7][7] = RoundDec(R, OP_OvlLengthD, 5);
}

Procedure Module_BasinVolume()
{
	Real IP_NumOfTrainD, IP_NumOfTrainR, IP_LperTrain, IP_WperTrain, IP_SWD, IP_FB; 	// IP = Input Parameter
	Real OP_VperTrain, OP_Vttl; 														// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Basin Volume")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names
	IP_NumOfTrainD	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_NumOfTrainR	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_LperTrain	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_WperTrain	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_SWD			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_FB			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	
	// Module Equation
	OP_VperTrain = IP_LperTrain*IP_WperTrain*IP_SWD*7.48/10^6;
	OP_Vttl = OP_VperTrain*(IP_NumOfTrainD+IP_NumOfTrainR);
	
	// Link Module results to output parameters
	Module_Input_tbl[ModuleStartRowIndex+6][7] = RoundDec(R, OP_VperTrain, 5);
	Module_Input_tbl[ModuleStartRowIndex+7][7] = RoundDec(R, OP_Vttl, 5);
}

Procedure Module_LoadingRemoval()																	
{
																									**## 2.Change Parameter Name ##**
	Real IP_CoC, IP_BODe, IP_Conversion, IP_Flow; 			// IP = Input Parameter
	Real OP_DeltaS; 	// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Loading Removal") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_CoC			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_BODe			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_Conversion	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_Flow			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);		
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_DeltaS = (IP_CoC-IP_BODe)*IP_Conversion*IP_Flow;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+4][7] = RoundDec(R, OP_DeltaS, 5);
}

Procedure Module_TankSizing()
{
																									**## 2.Change Parameter Name ##**
	Real IP_NumOfTrainD, IP_NumOfTrainR, IP_LtoW, IP_SWD, IP_FB, IP_CASVol; // IP = Input Parameter
	Real OP_NumOfTrainttl, OP_Dttl, OP_Lovl, OP_Wovl; 						// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Tank Sizing") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_NumOfTrainD	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_NumOfTrainR	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_LtoW			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_SWD			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_FB			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	IP_CASVol		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);		
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_NumOfTrainttl = IP_NumOfTrainD+IP_NumOfTrainR;
	OP_Dttl = IP_SWD+IP_FB;
	OP_Wovl = (IP_CASVol/IP_SWD/IP_LtoW/IP_NumOfTrainD/7.48*10^6)^0.5;
	OP_Lovl = OP_Wovl*IP_LtoW;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+7][7] = RoundDec(R, OP_NumOfTrainttl, 5);
	Module_Input_tbl[ModuleStartRowIndex+8][7] = RoundDec(R, OP_Dttl, 5);
	Module_Input_tbl[ModuleStartRowIndex+9][7] = RoundDec(R, OP_Wovl, 5);
	Module_Input_tbl[ModuleStartRowIndex+10][7] = RoundDec(R, OP_Lovl, 5);
}

Procedure Module_MixerGValue()
{
																									**## 2.Change Parameter Name ##**
	Real IP_NumOfUnitD, IP_NumOfUnitR, IP_Vol, IP_E, IP_RunHour, IP_RunDay, IP_G, IP_Visco; // IP = Input Parameter
	Real OP_NumOfUnitttl, OP_BHPperUnit, OP_PowerConsumption; 								// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Mixer G Value") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_NumOfUnitD	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_NumOfUnitR	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_Vol			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_E			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7])/100;
	IP_RunHour		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_RunDay		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	IP_G			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);
	IP_Visco		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+7][7]);		
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_NumOfUnitttl = IP_NumOfUnitD+IP_NumOfUnitR;
	OP_BHPperUnit = IP_Visco*(IP_Vol*10^6/7.48)*IP_G^2/550/IP_E/IP_NumOfUnitD;
	OP_PowerConsumption = OP_BHPperUnit*IP_NumOfUnitD*IP_RunHour*IP_RunDay*0.7457;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+8][7] = RoundDec(R, OP_NumOfUnitttl, 5);
	Module_Input_tbl[ModuleStartRowIndex+9][7] = RoundDec(R, OP_BHPperUnit, 5);
	Module_Input_tbl[ModuleStartRowIndex+10][7] = RoundDec(R, OP_PowerConsumption, 5);
}

Procedure Module_ChemicalStorageSizing()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Capacity, IP_Density, IP_Dose, IP_StorageTime, IP_NumOFTank, IP_DiaOfTank, IP_Strength; 	// IP = Input Parameter
	Real OP_FeedRate, OP_Vol, OP_HOfTank;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Chemical Storage Sizing") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Capacity		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_Density		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_Dose			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_StorageTime	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_NumOFTank	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_DiaOfTank	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);		
	IP_Strength	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7])/100;
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_FeedRate = IP_Capacity*IP_Dose/IP_Density/IP_Strength/24*8.34/0.485;
	OP_Vol = Round(OP_FeedRate*24*IP_StorageTime/IP_NumOFTank,1);
	OP_HOfTank = OP_Vol/7.48/(3.14*IP_DiaOfTank^2/4);
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+7][7] = RoundDec(R, OP_FeedRate, 5);
	Module_Input_tbl[ModuleStartRowIndex+8][7] = RoundDec(R, OP_Vol, 5);
	Module_Input_tbl[ModuleStartRowIndex+9][7] = RoundDec(R, OP_HOfTank, 5);
}

Procedure Module_SolidsLoading()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Capacity, IP_NTU, IP_CoagF, IP_PolyF, IP_SStoNTUR, IP_PACF, IP_CoagDose, IP_PolyDose, IP_PACDose, IP_Recycle; 	// IP = Input Parameter
	Real OP_SolidsLoadingAvg;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Solids Production") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Capacity	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_NTU		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_CoagF	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_PolyF	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_SStoNTUR	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_PACF		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	IP_CoagDose	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);
	IP_PolyDose	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+7][7]);
	IP_PACDose	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+8][7]);
	IP_Recycle	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+9][7]);	
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_SolidsLoadingAvg = (1+IP_Recycle/100)*IP_Capacity*8.34*(IP_NTU*IP_SStoNTUR+IP_CoagF*IP_CoagDose+IP_PolyF*IP_PolyDose+IP_PACF*IP_PACDose);
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+10][7] = RoundDec(R, OP_SolidsLoadingAvg, 5);
}

Procedure Module_RemovalEff() // Use Naming Convention: Module_CC000XXXXXX... CC = Category Abbreviation, 000 = Numeric ID, XXXX... are descriptive name of the moduel.
{
																									**## 2.Change Parameter Name ##**
	Real IP_InfCon, IP_EffCon; 	// IP = Input Parameter
	Real OP_RemovalEff;			 			// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Removal Efficiency") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_InfCon	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_EffCon	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_RemovalEff = (IP_InfCon-IP_EffCon)/IP_InfCon * 100;
		
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+2][7] = RoundDec(R, OP_RemovalEff, 2);
}

Procedure Module_HLR()//CHE Added)
{
																									**## 2.Change Parameter Name ##**
	Real IP_Capacity, IP_NumOfTank, IP_NumofStandby, IP_Width, IP_SWD, IP_TgtHyL, IP_LengthActual, IP_FB; 	// IP = Input Parameter
	Real OP_LengthEach, OP_LengthOvl, OP_HyLoadingActualAll,OP_HyLoadingActualDuty,OP_TotalNumofTrains, OP_TotalDepth;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "HLR") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
		IP_Capacity		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
		IP_NumOfTank	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
		IP_NumOfStandby	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
		IP_Width		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
		IP_SWD			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
		IP_TgtHyL		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
		IP_LengthActual	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);
		IP_FB =StrToReal(Module_Input_tbl[ModuleStartRowIndex+7][7]);

	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_LengthEach = IP_Capacity * 1000000 / IP_TgtHyL / IP_Width / IP_NumOfTank;
	OP_TotalNumofTrains = IP_NumofTank + IP_NumofStandby;
	OP_LengthOvl = OP_LengthEach * OP_TotalNumofTrains;
	OP_HyLoadingActualAll = IP_Capacity * 1000000 / IP_Width / IP_LengthActual ;
	OP_HyLoadingActualDuty = IP_Capacity * 1000000 / IP_Width / IP_LengthActual/(IP_NumOfTank/OP_TotalNumofTrains);
	OP_TotalDepth = IP_SWD + IP_FB;
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+8][7] = RoundDec(R, OP_LengthEach, 2);
	Module_Input_tbl[ModuleStartRowIndex+9][7] = RoundDec(R, OP_LengthOvl, 2);
	Module_Input_tbl[ModuleStartRowIndex+10][7] = RoundDec(R, OP_HyLoadingActualAll, 2);
	Module_Input_tbl[ModuleStartRowIndex+11][7] = RoundDec(R, OP_HyLoadingActualDuty, 2);
	Module_Input_tbl[ModuleStartRowIndex+12][7] = RoundDec(R, OP_TotalNumofTrains, 2);
	Module_Input_tbl[ModuleStartRowIndex+13][7] = RoundDec(R, OP_TotalDepth, 2);
}

Procedure Module_SLR()//CHE Added)
{
																									**## 2.Change Parameter Name ##**
	Real IP_Capacity, IP_NumOfTank, IP_NumofStandby, IP_Width, IP_SWD, IP_TgtSldL, IP_LengthActual, IP_TSSCon, IP_FB; 	// IP = Input Parameter
	Real OP_TSSLoad, OP_LengthEach, OP_LengthOvl, OP_HyLoadingActualAll,OP_HyLoadingActualDuty,OP_TotalNumofTrains,OP_TotalDepth;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "SLR") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
		IP_Capacity		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
		IP_NumOfTank	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
		IP_NumOfStandby	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
		IP_Width		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
		IP_SWD			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
		IP_TgtSldL		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
		IP_LengthActual	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);
		IP_TSSCon	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+7][7]);
		IP_FB	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+8][7]);
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_TSSLoad = IP_TSSCon * IP_Capacity * 8.34;
	OP_LengthEach = OP_TSSLoad / IP_TgtSldL / IP_Width / IP_NumOfTank;
	OP_TotalNumofTrains = IP_NumofTank + IP_NumofStandby;
	OP_LengthOvl = OP_LengthEach * OP_TotalNumofTrains;
	OP_HyLoadingActualAll = OP_TSSLoad / IP_Width / IP_LengthActual ;
	OP_HyLoadingActualDuty = OP_TSSLoad / IP_Width / IP_LengthActual/(IP_NumOfTank/OP_TotalNumofTrains);
	OP_TotalDepth = IP_FB + IP_SWD;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+9][7] = RoundDec(R, OP_TSSLoad, 2);
	Module_Input_tbl[ModuleStartRowIndex+10][7] = RoundDec(R, OP_LengthEach, 2);
	Module_Input_tbl[ModuleStartRowIndex+11][7] = RoundDec(R, OP_LengthOvl, 2);
	Module_Input_tbl[ModuleStartRowIndex+12][7] = RoundDec(R, OP_HyLoadingActualAll, 2);
	Module_Input_tbl[ModuleStartRowIndex+13][7] = RoundDec(R, OP_HyLoadingActualDuty, 2);
	Module_Input_tbl[ModuleStartRowIndex+14][7] = RoundDec(R, OP_TotalNumofTrains, 2);
	Module_Input_tbl[ModuleStartRowIndex+15][7] = RoundDec(R, OP_TotalDepth, 2);
}

Procedure Module_DesignHRTLtoWCircular() // New Module by Chiu
{
	Real IP_Flow, IP_HRT, IP_SWD, IP_Dia, IP_NumOfTrainD, IP_NumOfTrainR, IP_FB;//IP_LtoW, CHE edited
	Real OP_NumOfTrainTtl, OP_DepthTtl, OP_VolumeTtl, OP_PerimeterEach, OP_PerimeterOvl; // Chiu Edited
	
	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Design HRT to Volume - Circular")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names

	IP_NumOfTrainD	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_NumOfTrainR	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	//IP_LtoW			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]); CHE, the following moved up 1
	IP_Dia			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_SWD			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_FB			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_HRT			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	IP_Flow			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);

	
	// Module Equation
	OP_NumOfTrainTtl = IP_NumOfTrainD + IP_NumOfTrainR;
	OP_DepthTtl = IP_SWD + IP_FB;
	OP_PerimeterEach = sqrt((IP_HRT*IP_Flow/24/IP_SWD/(3.14/4)/IP_NumOfTrainD*10^6/7.48));//CHE
	OP_PerimeterOvl = OP_PerimeterEach * OP_NumofTrainTtl;
	OP_VolumeTtl = IP_SWD*(3.14*IP_Dia^2/4)*7.48/10^6*OP_NumOfTrainTtl; // Chiu
	
	// Link Module results to output parameters
 	Module_Input_tbl[ModuleStartRowIndex+7][7] = RoundDec(R, OP_NumOfTrainTtl, 5);
	Module_Input_tbl[ModuleStartRowIndex+8][7] = RoundDec(R, OP_DepthTtl, 5);
	Module_Input_tbl[ModuleStartRowIndex+9][7] = RoundDec(R, OP_PerimeterOvl, 5);
	Module_Input_tbl[ModuleStartRowIndex+10][7] = RoundDec(R, OP_PerimeterEach, 5);
	Module_Input_tbl[ModuleStartRowIndex+11][7] = RoundDec(R, OP_VolumeTtl, 5);
}

Procedure Module_ActualHRT_AllinServiceCircular() //Chiu Edited 
{
	Real IP_Flow, IP_Dia, IP_SWD, IP_NumofTrainsTotal; 	// IP = Input Parameter
	Real OP_ActVol, OP_HRT, OP_OvlPerimeter; 			// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Actual HRT (All in service) - Circular")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names
	IP_Flow	= 				StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_Dia= 				StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_SWD= 				StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
//	IP_ActLengthEach= 		StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_NumofTrainsTotal = 	StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	
	// Module Equation
	OP_ActVol = IP_SWD * (3.14*IP_Dia^2/4) * IP_NumofTrainsTotal *7.48 / 1000000;
	OP_HRT = OP_ActVol / IP_Flow *24;
	OP_OvlPerimeter = (3.14*IP_Dia) * IP_NumofTrainsTotal;
	
	// Link Module results to output parameters
	Module_Input_tbl[ModuleStartRowIndex+4][7] = RoundDec(R, OP_ActVol, 5);
	Module_Input_tbl[ModuleStartRowIndex+5][7] = RoundDec(R, OP_HRT, 5);
	Module_Input_tbl[ModuleStartRowIndex+6][7] = RoundDec(R, OP_OvlPerimeter, 5);
}

Procedure Module_ActualHRT_DutyinServiceCircular() //Chiu Added
{
	Real IP_Flow, IP_Dia, IP_SWD, IP_NumofDutyTrains; 	// IP = Input Parameter
	Real OP_ActVol, OP_HRT, OP_OvlPerimeterD; 			// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Actual HRT (Duty in service) - Circular")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names
	IP_Flow	= 				StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_Dia= 				StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_SWD= 				StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
//	IP_ActLengthEach= 		StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_NumofDutyTrains = 	StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	
	// Module Equation
	OP_ActVol = IP_SWD * (3.14*IP_Dia^2/4) * IP_NumofDutyTrains *7.48 / 1000000;
	OP_HRT = OP_ActVol / IP_Flow *24;
	OP_OvlPerimeterD = (3.14*IP_Dia) * IP_NumofDutyTrains;
	
	// Link Module results to output parameters
	Module_Input_tbl[ModuleStartRowIndex+4][7] = RoundDec(R, OP_ActVol, 5);
	Module_Input_tbl[ModuleStartRowIndex+5][7] = RoundDec(R, OP_HRT, 5);
	Module_Input_tbl[ModuleStartRowIndex+6][7] = RoundDec(R, OP_OvlPerimeterD, 5);
}


Procedure Module_HLRCircular()//CHE Added)
{
																									**## 2.Change Parameter Name ##**
	Real IP_Capacity, IP_NumOfTankD, IP_NumofStandby, IP_DiaActual, IP_SWD, IP_TgtHyL, IP_FB; 	// IP = Input Parameter
	Real OP_Diameter, OP_HyLoadingActualAll,OP_HyLoadingActualDuty,OP_TotalNumofTrains, OP_TotalDepth;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "HLR - Circular") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
		IP_Capacity		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
		IP_NumOfTankD	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
		IP_NumOfStandby	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
		IP_DiaActual	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
		IP_SWD			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
		IP_TgtHyL		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
		IP_FB 			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);

	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Diameter = sqrt(IP_Capacity * 1000000 / IP_TgtHyL / (3.14/4) / IP_NumOfTankD);
	OP_TotalNumofTrains = IP_NumofTankD + IP_NumofStandby;
	OP_HyLoadingActualAll = IP_Capacity * 1000000 / (3.14*IP_DiaActual^2/4) / OP_TotalNumofTrains;
	OP_HyLoadingActualDuty = IP_Capacity * 1000000 / (3.14*IP_DiaActual^2/4)/(IP_NumOfTankD);
	OP_TotalDepth = IP_SWD + IP_FB;
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+7][7] = RoundDec(R, OP_Diameter, 0);
	Module_Input_tbl[ModuleStartRowIndex+8][7] = RoundDec(R, OP_HyLoadingActualAll, 2);
	Module_Input_tbl[ModuleStartRowIndex+9][7] = RoundDec(R, OP_HyLoadingActualDuty, 2);
	Module_Input_tbl[ModuleStartRowIndex+10][7] = RoundDec(R, OP_TotalNumofTrains, 0);
	Module_Input_tbl[ModuleStartRowIndex+11][7] = RoundDec(R, OP_TotalDepth, 0);
}

Procedure Module_SLRCircular()//CHE Added)
{
																									**## 2.Change Parameter Name ##**
	Real IP_Capacity, IP_NumOfTankD, IP_NumofStandby, IP_DiaActual, IP_SWD, IP_TgtSldL, IP_TSSCon, IP_FB; 	// IP = Input Parameter
	Real OP_Diameter, OP_TSSLoad, OP_HyLoadingActualAll,OP_HyLoadingActualDuty,OP_TotalNumofTrains,OP_TotalDepth;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "SLR - Circular") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
		IP_Capacity		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
		IP_NumOfTankD	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
		IP_NumOfStandby	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
		IP_DiaActual	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
		IP_SWD			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
		IP_TgtSldL		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
		IP_TSSCon		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);
		IP_FB			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+7][7]);
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_TSSLoad = IP_TSSCon * IP_Capacity * 8.34;
	OP_Diameter = sqrt(OP_TSSLoad / IP_TgtSldL / (3.14/4) / IP_NumOfTankD);
	OP_TotalNumofTrains = IP_NumofTankD + IP_NumofStandby;
	OP_HyLoadingActualAll = OP_TSSLoad / (3.14*IP_DiaActual^2/4)/OP_TotalNumofTrains;
	OP_HyLoadingActualDuty = OP_TSSLoad / (3.14*IP_DiaActual^2/4) / (IP_NumOfTankD);
	OP_TotalDepth = IP_FB + IP_SWD;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
//	Module_Input_tbl[ModuleStartRowIndex+8][7] = RoundDec(R, OP_TSSLoad, 2);
	Module_Input_tbl[ModuleStartRowIndex+8][7] = RoundDec(R, OP_Diameter, 0);
	Module_Input_tbl[ModuleStartRowIndex+9][7] = RoundDec(R, OP_HyLoadingActualAll, 2);
	Module_Input_tbl[ModuleStartRowIndex+10][7] = RoundDec(R, OP_HyLoadingActualDuty, 2);
	Module_Input_tbl[ModuleStartRowIndex+11][7] = RoundDec(R, OP_TotalNumofTrains, 0);
	Module_Input_tbl[ModuleStartRowIndex+12][7] = RoundDec(R, OP_TotalDepth, 0);
}

/*
Procedure Module_pH2()//Chiu Added 11/19/2014
{
																									**## 2.Change Parameter Name ##**
	Real IP_TDS, IP_Temp, IP_pH, IP_Alk, IP_Ca, IP_Cl, IP_SO4; 	// IP = Input Parameter
	Real OP_pH, OP_CCPP, OP_LSI, OP_Ca, OP_Alk, OP_Cl, OP_SO4;			 									// OP = Output Parameter
	Integer pHCalculatorBlockNumber;
	Integer DBTableIndex_ChemicalDB;
	Integer ChemicalIndex;
	Integer NumOfBlocks;

	
	DBTableIndex_ChemicalDB = DBTableGetIndex(DBIndex, "Chemicals_DB");
	pHIndex ++;
	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "pH Calculator") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_TDS	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_Temp	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_pH	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_Alk	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_Ca	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_Cl	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	IP_SO4	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);

	// Module Equation 																				**## 5.Change Module Equation ##**
	NumOfBlocks = NumBlocks();
	
	for (k = 0; k < NumOfBlocks; k++)
	{
		if (BlockName(k) == "pH Calculator") pHCalculatorBlockNumber = k;
	}
	
	*** Chemical Input ***
	for (k = 0 ; k < GetDialogItemInfo(pHCalculatorBlockNumber, "ChemicalAddition_tbl", 5); k++)
	{
		for (j = 0 ; j < GetDialogItemInfo(pHCalculatorBlockNumber, "ChemicalAddition_tbl", 6); j++)
		{
			SetDialogVariableNoMsg(pHCalculatorBlockNumber, "ChemicalAddition_tbl", BLANK, k, j);
		}
	}
	
	ChemicalIndex = 0;
	for (k = 0; k < GetDimension(ChemicalCost_tbl); k++)
	{
		for (j = 1; j < DBRecordsGetNum(DBIndex, DBTableIndex_ChemicalDB); j++)
		{
			if (ChemicalCost_tbl[k][0] == DBDataGetAsString(DBIndex, DBTableIndex_ChemicalDB, 1, j))
			{
				SetDialogVariableNoMsg(pHCalculatorBlockNumber, "ChemicalAddition_tbl", ChemicalCost_tbl[k][0], ChemicalIndex, 0);
				SetDialogVariableNoMsg(pHCalculatorBlockNumber, "ChemicalAddition_tbl", ChemicalCost_tbl[k][1], ChemicalIndex, 1);
				ChemicalIndex++;
			}
		}
	}
	
	*** WQ input ***
	SetDialogVariableNoMsg(pHCalculatorBlockNumber, "ChemicalAddition_rbtn",	TRUE, 0, 0);
	SetDialogVariableNoMsg(pHCalculatorBlockNumber, "measured_TDS",	IP_TDS, 0, 0);
	SetDialogVariableNoMsg(pHCalculatorBlockNumber, "measured_T",	IP_Temp, 0, 0);
	SetDialogVariableNoMsg(pHCalculatorBlockNumber, "measured_pH",	IP_pH, 0, 0);
	SetDialogVariableNoMsg(pHCalculatorBlockNumber, "measured_ALK",	IP_Alk, 0, 0);
	SetDialogVariableNoMsg(pHCalculatorBlockNumber, "measured_Ca",	IP_Ca, 0, 0);
	SetDialogVariableNoMsg(pHCalculatorBlockNumber, "measured_Cl",	IP_Cl, 0, 0);
	SetDialogVariableNoMsg(pHCalculatorBlockNumber, "measured_SO4",	IP_SO4, 0, 0);
	
	*** Retrive result back ***
	OP_pH 		= StrToReal(GetDialogVariable(pHCalculatorBlockNumber, "pH_Final_diag", 0, 0));
	OP_CCPP 	= StrToReal(GetDialogVariable(pHCalculatorBlockNumber, "CCPP_diag", 0, 0));
	OP_LSI 		= StrToReal(GetDialogVariable(pHCalculatorBlockNumber, "LSI_diag", 0, 0));
	OP_Ca 		= StrToReal(GetDialogVariable(pHCalculatorBlockNumber, "Ca_Final_diag", 0, 0));
	OP_Alk 		= StrToReal(GetDialogVariable(pHCalculatorBlockNumber, "Alk_Final_diag", 0, 0));
	OP_Cl 		= StrToReal(GetDialogVariable(pHCalculatorBlockNumber, "Cl_Final_diag", 0, 0));
	OP_SO4 		= StrToReal(GetDialogVariable(pHCalculatorBlockNumber, "SO4_Final_diag", 0, 0));
	OP_Acidity	= StrToReal(GetDialogVariable(pHCalculatorBlockNumber, "Acidity_Final_diag", 0, 0));
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+7][7] = RoundDec(R, OP_pH, 5);
	Module_Input_tbl[ModuleStartRowIndex+8][7] = RoundDec(R, OP_CCPP, 5);
	Module_Input_tbl[ModuleStartRowIndex+9][7] = RoundDec(R, OP_LSI, 5);
	Module_Input_tbl[ModuleStartRowIndex+10][7] = RoundDec(R, OP_Ca, 5);
	Module_Input_tbl[ModuleStartRowIndex+11][7] = RoundDec(R, OP_Alk, 5);
	Module_Input_tbl[ModuleStartRowIndex+12][7] = RoundDec(R, OP_Cl, 5);
	Module_Input_tbl[ModuleStartRowIndex+13][7] = RoundDec(R, OP_SO4, 5);
}
*/
