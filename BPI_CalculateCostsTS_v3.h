Procedure CalculateCapitalCost(Real lr_Capacity)
{
	double lr_PV, lr_IR, lr_NumPayment, lr_Payment, lr_AmortizedCC, lr_Qty;
	long li_ThisYear, li_YearBegin;
	string ls_ThisYear;
	
	NumofItems_CC_UnitCost = GetDimension(C_cost_text_table_diag);
	NumofItems_CC_FixCost = GetDimension(CCost_Fixed_tbl);
	NumofItems_CC_Percent = GetDimension(CCost_Pct_tbl);
		
	Subtotal_CC_UnitCost_NBCF = 0; //Costs for not mutiplying by bracket cost factor 
	Subtotal_CC_UnitCost_BCF = 0; //Costs for mutiplying by bracket cost factor 
	Subtotal_CC_FixCost = 0;
	Subtotal_CC_Percent = 1;

	*** Unit Costs ***						
	for (i = 0; i < NumofItems_CC_UnitCost; i++)
	{
		if (C_cost_text_table_diag[i][4] == "Capacity") 
		{
			C_cost_text_table_diag[i][3] = lr_Capacity*1000000;
			Subtotal_CC_UnitCost_NBCF += StrToReal(C_cost_text_table_diag[i][2])*StrToReal(C_cost_text_table_diag[i][3]);
		}			
		
		else if (C_cost_text_table_diag[i][4] == "Qty" OR C_cost_text_table_diag[i][4] == "Module" OR C_cost_text_table_diag[i][4] == "Phase")
		{	
			if (C_cost_text_table_diag[i][4] == "Phase")
			{
				lr_PV = StrToReal(C_cost_text_table_diag[i][9]);
				lr_IR = StrToReal(C_cost_text_table_diag[i][10])/100.0;
				lr_NumPayment = StrToReal(C_cost_text_table_diag[i][11]);
				li_YearBegin = StrToReal(C_cost_text_table_diag[i][12]);
				ls_ThisYear = tbl_TS_FlowManager[CurrentSim+1][0];
				li_ThisYear = StrToReal(StrPart(ls_ThisYear, StrLen(ls_ThisYear)-4, 4));
			}
			
			lr_Qty = StrToReal(C_cost_text_table_diag[i][3]);
			
			if (C_cost_text_table_diag[i][8] == TRUE AND GlobalStr0 == "TS") // PMT
			{
				if (li_ThisYear >= li_YearBegin AND li_ThisYear < li_YearBegin+lr_NumPayment) lr_Payment = -CalcPMT(lr_IR, lr_NumPayment, lr_PV*10^6, 0, 0); //(lr_PV*1000000*lr_IR/100/(1-(1+lr_IR/100)^-lr_NumPayment));
				else lr_Payment = 0.0;
				
				lr_AmortizedCC = Ceil(lr_Payment/lr_Qty);
				if (lr_Qty == 0) lr_AmortizedCC = 0.0;
				
				C_cost_text_table_diag[i][2] = lr_AmortizedCC;
				Subtotal_CC_UnitCost_NBCF += StrToReal(C_cost_text_table_diag[i][2])*lr_Qty;
			}
			
			else if (lr_Capacity > 0 OR chx_ForceCalcCC == TRUE) // if PMT is false or under steady-state, only calculate when capacity change for the rest of the items
			{
				if (C_cost_text_table_diag[i][4] == "Phase" AND GlobalStr0 == "TS")
				{
					if (li_ThisYear == li_YearBegin) C_cost_text_table_diag[i][2] = lr_PV*1000000/lr_Qty;
					else C_cost_text_table_diag[i][2] = 0.0;
				}
				
				Subtotal_CC_UnitCost_NBCF += StrToReal(C_cost_text_table_diag[i][2])*lr_Qty;
			}
		}
			
		else if (C_cost_text_table_diag[i][4] == "Bracket") //Costs for mutiplying by bracket cost factor 
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
	long li_ThisYear, li_YearBegin;
	string ls_ThisYear;
	
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
		if (OM_cost_text_table_diag[i][5] == "Flow" OR OM_cost_text_table_diag[i][5] == "Qty" OR OM_cost_text_table_diag[i][5] == "Module" OR OM_cost_text_table_diag[i][5] == "Phase")
		{
			if (OM_cost_text_table_diag[i][4] == "Day")
			{Subtotal_OM_UnitCost_NBCF_D += StrToReal(OM_cost_text_table_diag[i][2])*StrToReal(OM_cost_text_table_diag[i][3]);}
			
			else if (OM_cost_text_table_diag[i][4] == "Week")
			{Subtotal_OM_UnitCost_NBCF_W += StrToReal(OM_cost_text_table_diag[i][2])*StrToReal(OM_cost_text_table_diag[i][3]);}
			
			else if (OM_cost_text_table_diag[i][4] == "Month")
			{Subtotal_OM_UnitCost_NBCF_M += StrToReal(OM_cost_text_table_diag[i][2])*StrToReal(OM_cost_text_table_diag[i][3]);}
			
			else if (OM_cost_text_table_diag[i][4] == "Year")
			{
				if (OM_cost_text_table_diag[i][8] != BLANK)
				{
					li_YearBegin = StrToReal(OM_cost_text_table_diag[i][8]);
					ls_ThisYear = tbl_TS_FlowManager[CurrentSim+1][0];
					li_ThisYear = StrToReal(StrPart(ls_ThisYear, StrLen(ls_ThisYear)-4, 4));
					
					if (li_ThisYear >= li_YearBegin)
					{
						Subtotal_OM_UnitCost_NBCF_Y += StrToReal(OM_cost_text_table_diag[i][2])*StrToReal(OM_cost_text_table_diag[i][3]);
					}
				}
				
				else Subtotal_OM_UnitCost_NBCF_Y += StrToReal(OM_cost_text_table_diag[i][2])*StrToReal(OM_cost_text_table_diag[i][3]);
			}
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