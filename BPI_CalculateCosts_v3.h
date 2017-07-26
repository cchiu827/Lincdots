Procedure CalculateCapitalCost()
{
	NumofItems_CC_UnitCost = GetDimension(C_cost_text_table_diag);
	NumofItems_CC_FixCost = GetDimension(CCost_Fixed_tbl);
	NumofItems_CC_Percent = GetDimension(CCost_Pct_tbl);
		
	Subtotal_CC_UnitCost_NBCF = 0; //Costs for not mutiplying by bracket cost factor 
	Subtotal_CC_UnitCost_BCF = 0; //Costs for mutiplying by bracket cost factor 
	Subtotal_CC_FixCost = 0;
	Subtotal_CC_Percent = 1;

	// reflect flow automatically |09/15/2014|
	for (i = 0; i < NumofItems_CC_UnitCost; i++)
	{
		if (C_cost_text_table_diag[i][4] == "Capacity") 
			C_cost_text_table_diag[i][3] = Flow_diag*1000000;
	}
		
	*** Unit Costs ***						
	for (i = 0; i < NumofItems_CC_UnitCost; i++)
	{
		if (C_cost_text_table_diag[i][4] == "Capacity" OR C_cost_text_table_diag[i][4] == "Qty" OR C_cost_text_table_diag[i][4] == "Module")
			Subtotal_CC_UnitCost_NBCF += StrToReal(C_cost_text_table_diag[i][2])*StrToReal(C_cost_text_table_diag[i][3]);
			
		if (C_cost_text_table_diag[i][4] == "Bracket") //Costs for mutiplying by bracket cost factor 
			Subtotal_CC_UnitCost_BCF += StrToReal(C_cost_text_table_diag[i][2])*StrToReal(C_cost_text_table_diag[i][3]);
	}
		
	Subtotal_CC_UnitCost = Subtotal_CC_UnitCost_NBCF + Subtotal_CC_UnitCost_BCF*CCBracketFactor;
	
	subtot_c_cost_UC_diag = Ceil(Subtotal_CC_UnitCost/1000)/1000;
		
	*** Fixed Costs ***	
	for (i = 0; i < NumofItems_CC_FixCost; i++)
	{
		Subtotal_CC_FixCost += StrToReal(CCost_Fixed_tbl[i][1]);
	}
	
	SubTotalCC = (Subtotal_CC_UnitCost + Subtotal_CC_FixCost)*CostAdjFac;
	
	subtot_c_cost_FC_diag = Ceil(Subtotal_CC_FixCost/1000)/1000;
	
	*** Percent Costs ***					
	for (i = 0; i < NumofItems_CC_Percent; i++)
	{
		Subtotal_CC_Percent = Subtotal_CC_Percent*(1+StrToReal(CCost_Pct_tbl[i][1])/100);
	}
	
	*** Total Capital Costs ***
	tot_c_cost = SubTotalCC * Subtotal_CC_Percent;
	
	tot_c_cost_diag = Ceil(tot_c_cost/1000)/1000;
}

Procedure CalculateOMCost()
{
	// reflect flow automatically |09/15/2014|
	for (i = 0; i < NumofItems_OM_UnitCost; i++)
	{
		if (OM_cost_text_table_diag[i][5] == "Flow") 
			OM_cost_text_table_diag[i][3] = Flow_diag*1000;
	}
	
	//chemical unit cost is ($/m-gal) *** Here, chemical unit cost is actually chemical daily cost, 12/05/2014 ***
	Total_Chemical_UnitCost = 0; 
	for (i = 0; i <= NumberofChemicals-1; i++)
	{				
		if (ChemicalCost_tbl[i][3] == "Feed") FlowFactor = StrToReal(SS_Flow_Tbl[0][2]);
		if (ChemicalCost_tbl[i][3] == "Product") FlowFactor = StrToReal(SS_Flow_Tbl[0][3]);
		if (ChemicalCost_tbl[i][3] == "Waste") FlowFactor = StrToReal(SS_Flow_Tbl[0][4]);
		
		Total_Chemical_UnitCost += StrToReal(ChemicalCost_tbl[i][1])*StrToReal(ChemicalCost_tbl[i][2])*8.34*FlowFactor; //*StrToReal(ChemicalCost_tbl[i][3])*8.34;
	}
	
	Chemical_cost = Total_Chemical_UnitCost*30.4; //in $/month 
	
	**** Chiu Add O&M Cost Calculation, 05/28/2014 ****
	NumofItems_OM_UnitCost = GetDimension(OM_cost_text_table_diag);
	NumofItems_OM_FixCost = GetDimension(OM_Fixed_tbl);
	NumofItems_OM_Percent = GetDimension(OM_Pct_tbl);
			
	Subtotal_OM_UnitCost_NBCF_D = 0; // non-bracket cost factor, daily
	Subtotal_OM_UnitCost_NBCF_W = 0; // non-bracket cost factor, weekly
	Subtotal_OM_UnitCost_NBCF_M = 0; // non-bracket cost factor, monthly
	Subtotal_OM_UnitCost_NBCF_Y = 0; // non-bracket cost factor, yearly
	Subtotal_OM_UnitCost_BCF_D = 0; // bracket cost factor, daily
	Subtotal_OM_UnitCost_BCF_W = 0; // bracket cost factor, weekly
	Subtotal_OM_UnitCost_BCF_M = 0; // bracket cost factor, monthly
	Subtotal_OM_UnitCost_BCF_Y = 0; // bracket cost factor, yearly
	Subtotal_OM_UnitCost = 0;
	Subtotal_OM_FixCost_Year = 0;
	Subtotal_OM_FixCost_Month = 0;
	Subtotal_OM_FixCost_Week = 0;
	Subtotal_OM_FixCost_Day = 0;
	Subtotal_OM_FixCost = 0;
	Subtotal_OM_Percent = 1;
	
	*** Unit Costs ***			|09/15/2014|			
	for (i = 0; i < NumofItems_OM_UnitCost; i++)
	{
		if (OM_cost_text_table_diag[i][5] == "Flow" OR OM_cost_text_table_diag[i][5] == "Qty" OR OM_cost_text_table_diag[i][5] == "Module")
		{
			if (OM_cost_text_table_diag[i][4] == "Day")
			{Subtotal_OM_UnitCost_NBCF_D += StrToReal(OM_cost_text_table_diag[i][2])*StrToReal(OM_cost_text_table_diag[i][3]);}
			
			if (OM_cost_text_table_diag[i][4] == "Week")
			{Subtotal_OM_UnitCost_NBCF_W += StrToReal(OM_cost_text_table_diag[i][2])*StrToReal(OM_cost_text_table_diag[i][3]);}
			
			if (OM_cost_text_table_diag[i][4] == "Month")
			{Subtotal_OM_UnitCost_NBCF_M += StrToReal(OM_cost_text_table_diag[i][2])*StrToReal(OM_cost_text_table_diag[i][3]);}
			
			if (OM_cost_text_table_diag[i][4] == "Year")
			{Subtotal_OM_UnitCost_NBCF_Y += StrToReal(OM_cost_text_table_diag[i][2])*StrToReal(OM_cost_text_table_diag[i][3]);}
		}
						
		else if (OM_cost_text_table_diag[i][5] == "Bracket") //Costs for mutiplying by bracket cost factor 
		{
			if (OM_cost_text_table_diag[i][4] == "Day")
			{Subtotal_OM_UnitCost_BCF_D += StrToReal(OM_cost_text_table_diag[i][2])*StrToReal(OM_cost_text_table_diag[i][3]);}
			
			if (OM_cost_text_table_diag[i][4] == "Week")
			{Subtotal_OM_UnitCost_BCF_W += StrToReal(OM_cost_text_table_diag[i][2])*StrToReal(OM_cost_text_table_diag[i][3]);}
		
			if (OM_cost_text_table_diag[i][4] == "Month")
			{Subtotal_OM_UnitCost_BCF_M += StrToReal(OM_cost_text_table_diag[i][2])*StrToReal(OM_cost_text_table_diag[i][3]);}
			
			if (OM_cost_text_table_diag[i][4] == "Year")
			{Subtotal_OM_UnitCost_BCF_Y += StrToReal(OM_cost_text_table_diag[i][2])*StrToReal(OM_cost_text_table_diag[i][3]);}
		}
	}
	
	Subtotal_OM_UnitCost_NBCF = Subtotal_OM_UnitCost_NBCF_D + Subtotal_OM_UnitCost_NBCF_W/7 + Subtotal_OM_UnitCost_NBCF_M/30.4 + Subtotal_OM_UnitCost_NBCF_Y/365.25;
		
	Subtotal_OM_UnitCost_BCF = Subtotal_OM_UnitCost_BCF_D + Subtotal_OM_UnitCost_BCF_W/7 + Subtotal_OM_UnitCost_BCF_M/30.4 + Subtotal_OM_UnitCost_BCF_Y/365.25;
	
	Subtotal_OM_UnitCost = (Subtotal_OM_UnitCost_NBCF + Subtotal_OM_UnitCost_BCF*OMBracketFactor); // Daily O&M Cost in $
	
	daily_om_Subtotal_UC_diag = Ceil(Subtotal_OM_UnitCost/10)/100;

	*** Fixed Costs ***	
	for (i = 0; i < NumofItems_OM_FixCost; i++)
	{
		if (OM_Fixed_tbl[i][2] == "/Year") Subtotal_OM_FixCost_Year += StrToReal(OM_Fixed_tbl[i][1]);
		if (OM_Fixed_tbl[i][2] == "/Month") Subtotal_OM_FixCost_Month += StrToReal(OM_Fixed_tbl[i][1]);
		if (OM_Fixed_tbl[i][2] == "/Week") Subtotal_OM_FixCost_Week += StrToReal(OM_Fixed_tbl[i][1]);
		if (OM_Fixed_tbl[i][2] == "/Day") Subtotal_OM_FixCost_Day += StrToReal(OM_Fixed_tbl[i][1]);
	}
	
	Subtotal_OM_FixCost = Subtotal_OM_FixCost_Year/365.25 + Subtotal_OM_FixCost_Month/30.4 + Subtotal_OM_FixCost_Week/7 + Subtotal_OM_FixCost_Day; // Daily O&M Cost
		
	daily_om_Subtotal_FC_diag = Ceil(Subtotal_OM_FixCost/10)/100;
	
	subtot_om_cost = (Subtotal_OM_UnitCost + Subtotal_OM_FixCost)*CostAdjFac; // Daily O&M Cost, $ |09/15/2014|
	
	*** Percent Costs ***					
	for (i = 0; i < NumofItems_OM_Percent; i++)
	{
		Subtotal_OM_Percent = Subtotal_OM_Percent*(1+StrToReal(OM_Pct_tbl[i][1])/100);
	}
}