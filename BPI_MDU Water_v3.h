real RoundDec(String ls_RoundMode, real lr_UglyNum,real lr_NumDecimal);

Procedure Module_ImpoundmentStorage()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Capacity, IP_StorageHrReq, IP_ImpdSize; 	// IP = Input Parameter
	Real OP_NumOfImpd;			 						// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Impoundment Storage") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Capacity		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_StorageHrReq	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_ImpdSize		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);	

	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_NumOfImpd = IP_Capacity*IP_StorageHrReq/24/IP_ImpdSize;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+3][7] = RoundDec(R, OP_NumOfImpd, 5);
}

Procedure Module_RapidMix()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Capacity, IP_DsgnCap, IP_DsgnG, IP_MotorHP, IP_W, IP_L, IP_SWD; 	// IP = Input Parameter
	Real OP_NumOfMixer, OP_DetTime;			 						// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Rapid Mix") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Capacity	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_DsgnCap	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_DsgnG	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_MotorHP	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_W		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_L		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	IP_SWD		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);		
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_NumOfMixer = IP_Capacity/IP_DsgnCap;
	OP_DetTime = IP_W*IP_L*IP_SWD*60*7.48/(IP_DsgnCap*10^6/24/60);
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+7][7] = RoundDec(R, OP_NumOfMixer, 5);
	Module_Input_tbl[ModuleStartRowIndex+8][7] = RoundDec(R, OP_DetTime, 5);
}

Procedure Module_HydraulicFlocculationBasins()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Capacity, IP_NumOfTrain, IP_NumOfStage, IP_WperBasin, IP_L, IP_SWD; 	// IP = Input Parameter
	Real OP_WttlperTrain, OP_SurfaceArea, OP_Volttl, OP_DetTime;			 						// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Hydraulic Flocculation Basins") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Capacity		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_NumOfTrain	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_NumOfStage	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_WperBasin	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_L			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_SWD			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);		
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_WttlperTrain = IP_NumOfTrain*IP_WperBasin+6;
	OP_SurfaceArea = IP_L*OP_WttlperTrain;
	OP_Volttl = OP_SurfaceArea*IP_SWD*7.48/10^6;
	OP_DetTime = OP_Volttl/IP_Capacity*1440;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+6][7] = RoundDec(R, OP_WttlperTrain, 5);
	Module_Input_tbl[ModuleStartRowIndex+7][7] = RoundDec(R, OP_SurfaceArea, 5);
	Module_Input_tbl[ModuleStartRowIndex+8][7] = RoundDec(R, OP_Volttl, 5);
	Module_Input_tbl[ModuleStartRowIndex+9][7] = RoundDec(R, OP_DetTime, 5);
}

Procedure Module_SedBasinwithHydraulicScraper()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Capacity, IP_NumOfTrain, IP_SfcLR, IP_W, IP_Lbay; 	// IP = Input Parameter
	Real OP_SfcAreaReq, OP_AvailableArea;			 						// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Sed Basin with Hydraulic Scraper") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Capacity		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_NumOfTrain	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_SfcLR		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_W			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_Lbay			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);		

	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_SfcAreaReq = IP_Capacity*694/IP_SfcLR;
	OP_AvailableArea = IP_NumOfTrain*IP_W*IP_Lbay;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+5][7] = RoundDec(R, OP_SfcAreaReq, 5);
	Module_Input_tbl[ModuleStartRowIndex+6][7] = RoundDec(R, OP_AvailableArea, 5);
}

Procedure Module_RawWaterPumpStation()
{
																									**## 2.Change Parameter Name ##**
	Real IP_NumOfPump, IP_PumpCap, IP_USHL, IP_DSHL, IP_ImpdOPL, IP_PSGL; 	// IP = Input Parameter
	Real OP_PumpCapttl, OP_TDH;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Raw Water Pump Station") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_NumOfPump	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_PumpCap		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_USHL			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_DSHL			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_ImpdOPL		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_PSGL			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);		
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_PumpCapttl = IP_PumpCap*IP_NumOfPump;
	OP_TDH = IP_PSGL-IP_ImpdOPL+IP_USHL+IP_DSHL;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
		if (Module_Input_tbl[ModuleStartRowIndex+6][3] == "Total Pump Capacity") 	Module_Input_tbl[j][7] = RoundDec(R, OP_PumpCapttl, 5);
		if (Module_Input_tbl[ModuleStartRowIndex+7][3] == "Estimated TDH") 			Module_Input_tbl[j][7] = RoundDec(R, OP_TDH, 5);
}

Procedure Module_Flocculation()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Capacity, IP_NumOfTrainD, IP_NumOfTrainR, IP_DsgnCap, IP_W, IP_L, IP_SWD; 	// IP = Input Parameter
	Real OP_VolPerTrain, OP_DetTime, OP_DetTimemax;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Flocculation") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Capacity		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_NumOfTrainD	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_NumOfTrainR	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_DsgnCap		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_W			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_L			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	IP_SWD			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);		
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_VolPerTrain = IP_W*IP_L*IP_SWD;
	OP_DetTime = OP_VolPerTrain*7.48/10^6/(IP_DsgnCap/24/60);
	OP_DetTimemax = OP_DetTime/IP_NumOfTrainD*(IP_NumOfTrainD-IP_NumOfTrainR);
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+7][7] = RoundDec(R, OP_VolPerTrain, 5);
	Module_Input_tbl[ModuleStartRowIndex+8][7] = RoundDec(R, OP_DetTime, 5);
	Module_Input_tbl[ModuleStartRowIndex+9][7] = RoundDec(R, OP_DetTimemax, 5);
}

Procedure Module_Sedimentation()
{
																									**## 2.Change Parameter Name ##**
	Real IP_NumOfTrainD, IP_DsgnCap, IP_LtoW, IP_W, IP_SWD, IP_DsgnSfcLR, IP_DsgnWeirLR; 	// IP = Input Parameter
	Real OP_SfcLR, OP_WeirLperBasin;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Sedimentation") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_NumOfTrainD	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_DsgnCap		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_LtoW			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_W			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_SWD			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_DsgnSfcLR	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	IP_DsgnWeirLR	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);		
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_SfcLR = IP_DsgnCap*694/(IP_W*IP_W*IP_LtoW);
	OP_WeirLperBasin = IP_DsgnCap*10^6/IP_DsgnWeirLR;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+7][7] = RoundDec(R, OP_SfcLR, 5);
	Module_Input_tbl[ModuleStartRowIndex+8][7] = RoundDec(R, OP_WeirLperBasin, 5);
}

Procedure Module_Clarifier()
{
																									**## 2.Change Parameter Name ##**
	Real IP_SolidsLAvg, IP_FeedSolidConc, IP_SolidCapture, IP_NumOfClarifier, IP_DiaOfClarifier, IP_SWD, IP_TgtSL, IP_TgtHyL; 	// IP = Input Parameter
	Real OP_SludgeFeed, OP_SolidsLActual, OP_HyLoadingActual;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Clarifier") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_SolidsLAvg		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_FeedSolidConc	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_SolidCapture		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_NumOfClarifier	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_DiaOfClarifier	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_SWD				= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	IP_TgtSL			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);
	IP_TgtHyL			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+7][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_SludgeFeed = IP_SolidsLAvg*IP_SolidCapture/100/(IP_FeedSolidConc/100)/8.34;
	OP_SolidsLActual = IP_SolidsLAvg/(3.14*IP_DiaOfClarifier^2/4)*IP_NumOfClarifier;
	OP_HyLoadingActual = OP_SludgeFeed/(3.14*IP_DiaOfClarifier^2/4);
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+8][7] = RoundDec(R, OP_SludgeFeed, 5);
	Module_Input_tbl[ModuleStartRowIndex+9][7] = RoundDec(R, OP_SolidsLActual, 5);
	Module_Input_tbl[ModuleStartRowIndex+10][7] = RoundDec(R, OP_HyLoadingActual, 5);
}

Procedure Module_DryingBeds()
{
																									**## 2.Change Parameter Name ##**
	Real IP_SolidsLAvg, IP_NumOfBed, IP_L, IP_W, IP_DsgnSfcLR; 	// IP = Input Parameter
	Real OP_Areattl, OP_SolidsLActual, OP_NumOfBeds;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Drying Beds") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_SolidsLAvg	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_NumOfBed		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_L			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_W			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_DsgnSfcLR	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Areattl = IP_L*IP_W*0.9683*IP_NumOfBed/43560;
	OP_SolidsLActual = IP_SolidsLAvg/(OP_Areattl*43560)*365;
	OP_NumOfBeds = IP_SolidsLAvg/(IP_DsgnSfcLR/365)/(IP_L*IP_W*0.9683);
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+5][7] = RoundDec(R, OP_Areattl, 5);
	Module_Input_tbl[ModuleStartRowIndex+6][7] = RoundDec(R, OP_SolidsLActual, 5);
	Module_Input_tbl[ModuleStartRowIndex+7][7] = RoundDec(R, OP_NumOfBeds, 5);
}