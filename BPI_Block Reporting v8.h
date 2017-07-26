******************************************************************
**	Block Reporting.h Include									**
**	Copyright © 2003-2010 by Imagine That, Inc.					**
**	All rights reserved.										**
**	Created by Anthony Nastasi									**
******************************************************************



******************************************************************
** Created 2003
**	Modified:
**	Date	Release		By			Description
**
******************************************************************

constant REPORT_DIALOGS is 0;
constant REPORT_STATISTICS is 1;

constant INDENTATION_DI_TITLE  is 4;
constant COLUMN_WIDTH is 15;
constant INDENTATION_COLUMN_TITLE is 9;




//on createReport_btn
on BlockReport
{

	integer i, j, k, m;
	integer numRows;
	integer numCols;
	string str;
	string strVal;
	integer thisBlockNumber;
	string31 thisBlockLabel;
	string31 thisBlockName;
	string31 thisBlockType;
	integer numDialogItems;
	integer titleLength;
	integer cellContentsLength;
	string31 cellContents;
	integer columnNameWidth;
	integer unusedColumnWidth;
	integer underlineStart;
	integer columnTitleWidth;
	integer reportType;
	integer NumReportingArrays;
	integer NumReportingRows;
	integer NumReportingColumns;
	real	ReportValue;
	integer CloneInitSent;
	integer PopupValue;
	String31 PopupLabel;
	
	
//	integer j;
//	integer k;//	integer NumRows;
	
	integer NumReportingDialogs;
	integer i1;


	if( sysGlobal1 != 0.0 ) ** 0 is error, check for open file for REPORT
		{
	
		//get the block's title info
		thisBlockNumber = MyBlockNumber();
		thisBlockName = BlockName(thisBlockNumber);
		thisBlockLabel = GetBlockLabel(thisBlockNumber);
		thisBlockType = GetBlockType(thisBlockNumber);
		
	
		if(GetReportType() == 1) ** 0 for dialogs, 1 is statistics
			{
			#ifdef ReportingDialogs
				GetReportingDialogs();
				NumReportingDialogs = GetDimension(ReportingDialogs);
				if(IsFirstReport())						// this is the first report for this type of block
					{
					// header for all blocks of same type
					
					// make type name uppercase for report (1=lowercase)
					str = GetBlockType(thisBlockNumber);
					str = StringCase(str,0);
					fileWrite(sysGlobal1,"","",True); 
					fileWrite(sysGlobal1,"","",True); 
					i1 = StrLen(str);
					for(;(i1<15);i1++)
						str=str+"_";  
					fileWrite(sysGlobal1,str,"",True); 
	
					str = FormatString(3,"%-30s %-6s %-12s ","Block Label","Number","Name","","","","","");
					for(i=0;i<NumReportingDialogs;i++)
						str += FormatString(1,"%-7s ",ReportingDialogs[i],"","","","","","","");
					fileWrite(sysGlobal1,str,"",True);
	
					str=FormatString(2,"%-34s %-7s ","------------------------------ ------ ------------","-------"
						,"","","","","","");
					for(i=0;i<NumReportingDialogs;i++)
						str += FormatString(1,"%-7s ","-------","","","","","","","");
					fileWrite(sysGlobal1,str,"",True);
					}
				str=FormatString(3,"%-30s %-6.6s %-12.12s ",thisBlockLabel,NumToFormat(thisBlockNumber,6,6,0),ThisBlockName,"","","","","");
				for(i=0;i<NumReportingDialogs;i++)
					{
					str += FormatString(1, "%-7s ", NumToFormat(ReportingValues[i],7,7,0),0.,0.,0.,0.,0.,0.,0.);
					}				fileWrite(sysGlobal1,str,"",True); 
			#endif
				
				
							#ifdef GetReportValue
				NumReportingArrays = GetNumReportingArrays();
				for(i=0;i<NumReportingArrays;i++)
					{			
					Str = "";
					GetReportingLabels(i);
					for(i=0;i<GetDimension(ReportingLabels);i++)
						Str += FormatString(1, "%-7s ", ReportingLabels[i], "", "", "", "", "", "", "");
					fileWrite(sysGlobal1,str,"",True); 
					NumReportingRows = GetReportingRows(i);
					NumReportingColumns = GetReportingColumns(i);
					for(j=0;j<NumReportingRows;j++)
						{
						str = "";
						for(k=0;k<NumReportingColumns;k++)
							{
							ReportValue = GetReportValue(i,j,k);
							str = FormatString(1, "%-7s ", NumToFormat(ReportValue,7,7,0),0.,0.,0.,0.,0.,0.,0.);
							fileWrite(sysGlobal1,str,"",FALSE); 
							}
						fileWrite(sysGlobal1,"","",TRUE); 					// new line
						}
					}
			#endif
	//			fileWrite(sysGlobal1,str,"",True); 
		
			
			}
		else
			{
			//write out the title for the block
			str = "Block Name: " + thisBlockName + "     " + "Block Number: " + thisBlockNumber + "     " + "Block Label: " + thisBlockLabel;
			FileWrite(sysGlobal1, str, "", TRUE); 
			
			//underline the title
			titleLength = StrLen(str);
			str = "";
			for(i=0; i<titleLength; i++)
				str += "-";
			FileWrite(sysGlobal1, str, "", TRUE); 
			
			//write out the block's statistics
			numDialogItems = GetDialogNames(thisBlockNumber, BR_DINames, BR_DITypes);
			CloneInitSent = FALSE;
			
			for(i=0; i<numDialogItems; i++)
				{
				
				reportType = GetReportType();
				
				if(reportType == REPORT_DIALOGS  ||reportType == REPORT_STATISTICS)
					{
				
					if(BR_DITypes[i] == DI_PARAMETER)
						{
						str = "";
						
						//add indentation to str
						for(j=0; j<INDENTATION_DI_TITLE; j++)
							str += " ";
						
						//add name and value to str
						str += BR_DINames[i] + " = " + GetDialogVariable(thisBlockNumber, BR_DINames[i], 0, 0);
						
						//write str
						FileWrite(sysGlobal1, str, "", TRUE); 
						
						//add carriage return
		//				FileWrite(sysGlobal1, "", "", TRUE);
						}
					else if(BR_DITypes[i] == DI_POPUP_MENU)
						{
						str = "";
						
						//add indentation to str
						for(j=0; j<INDENTATION_DI_TITLE; j++)
							str += " ";
						
						if(!CloneInitSent)
							{
							CloneInitSent = TRUE;
							SendMsgToBlock(MyBlockNumber(),CloneInitMsg);
							}
							
						PopupValue = StrToReal(GetDialogVariable(thisBlockNumber, BR_DINames[i], 0, 0));
//						PopupLabel = GetDialogItemLabel(thisBlockNumber, BR_DINames[i], PopupValue);
						//add name and value to str
						str += BR_DINames[i] + " = " + GetDialogItemLabel(thisBlockNumber, BR_DINames[i], PopupValue);
						
						//write str
						FileWrite(sysGlobal1, str, "", TRUE); 
						
						//add carriage return
		//				FileWrite(sysGlobal1, "", "", TRUE);
						}
						
					else if(BR_DITypes[i] == DI_DATA_TABLE  ||  BR_DITypes[i] == DI_TEXT_TABLE)
						{
						numRows = GetDialogItemInfo(thisBlockNumber, BR_DINames[i], 5);
						numCols = GetDialogItemInfo(thisBlockNumber, BR_DINames[i], 6);
						
						//write the table name header
						str = "";
						for(j=0; j<INDENTATION_DI_TITLE; j++)
							str += " ";
						str += "Table: " + BR_DINames[i];
						FileWrite(sysGlobal1, str, "", TRUE); 
						
						//write the column names
						str = "";
						for(j=0; j<numCols; j++)
							{
							if(j == 0)
								unusedColumnWidth = INDENTATION_COLUMN_TITLE;
							else
								{
								columnNameWidth = StrLen("Column" + j);
								unusedColumnWidth = COLUMN_WIDTH - columnNameWidth;
								}
			
							//add spaces
							for(k=0; k<unusedColumnWidth; k++)
								str += " ";
			
							//add column title
							str += "Column" + j;
							}
						FileWrite(sysGlobal1, str, "", TRUE);
						
						//underline the column names
						titleLength = StrLen(str) - INDENTATION_COLUMN_TITLE;
						underlineStart = INDENTATION_COLUMN_TITLE;
						str = "";
						for(j=0; j<underlineStart; j++)
							str += " ";
						for(j=0; j<titleLength; j++)
							str += "-";
						FileWrite(sysGlobal1, str, "", TRUE);
						
						//write the contents of the next table row 
						for(j=0; j<numRows; j++)
							{
							str = "";
							
							for(k=0; k<numCols; k++)
								{
								cellContents = GetDialogVariable(MyBlockNumber(), BR_DINames[i], j, k);
								
								if(cellContents != "")
									{
									cellContentsLength = StrLen(cellContents);
									
									//add spaces before adding cell contents so that cell contents appear right justified
									if(k == 0)
										{
										columnTitleWidth = StrLen("Column1");
										for(m=cellContentsLength; m<INDENTATION_COLUMN_TITLE+columnTitleWidth; m++)
											str += " ";	
										}
									else
										{
										for(m=cellContentsLength; m<COLUMN_WIDTH; m++)
											str += " ";	
										}
									}
								
								//add cell contents
								str += cellContents;
								}
						
							if(str != "")
								FileWrite(sysGlobal1, str, "", TRUE);
							}//for(j=0; j<numRows; j++)
			
						//add a carriage return
		//				FileWrite(sysGlobal1, "", "", TRUE);
						
						}//else if(BR_DITypes[i] == DI_DATA_TABLE  ||  BR_DITypes[i] == DI_TEXT_TABLE)
						
					}//if(reportType == REPORT_DIALOGS  ||reportType == REPORT_STATISTICS)
					
				if(reportType == REPORT_DIALOGS)
					{
		
					if(BR_DITypes[i] == DI_CHECK_BOX)
						{
						str = "";
						
						//add indentation to str
						for(j=0; j<INDENTATION_DI_TITLE; j++)
							str += " ";
						
						//add name and value to str
						strVal = GetDialogVariable(thisBlockNumber, BR_DINames[i], 0, 0);
						if(strVal == "0")
							str += BR_DINames[i] + " = UnChecked";
						else
							str += BR_DINames[i] + " = Checked";
						
						//write str
						FileWrite(sysGlobal1, str, "", TRUE); 
						
						//add carriage return
		//				FileWrite(sysGlobal1, "", "", TRUE);
						}
					
					else if(BR_DITypes[i] == DI_RADIO_BUTTON)
						{
						str = "";
						
						//add indentation to str
						for(j=0; j<INDENTATION_DI_TITLE; j++)
							str += " ";
						
						//add name and value to str
						strVal = GetDialogVariable(thisBlockNumber, BR_DINames[i], 0, 0);
						if(strVal == "0")
							str += BR_DINames[i] + " = Unselected";
						else
							str += BR_DINames[i] + " = Selected";
						
						//write str
						FileWrite(sysGlobal1, str, "", TRUE); 
						
						//add carriage return
		//				FileWrite(sysGlobal1, "", "", TRUE);
						}
					
					else if(BR_DITypes[i] == DI_SWITCH)
						{
						str = "";
						
						//add indentation to str
						for(j=0; j<INDENTATION_DI_TITLE; j++)
							str += " ";
						
						//add name and value to str
						strVal = GetDialogVariable(thisBlockNumber, BR_DINames[i], 0, 0);
						if(strVal == "0")
							str += BR_DINames[i] + " = Off";
						else
							str += BR_DINames[i] + " = On";
						
						//write str
						FileWrite(sysGlobal1, str, "", TRUE); 
						
						//add carriage return
		//				FileWrite(sysGlobal1, "", "", TRUE);
						}
					
					else if(BR_DITypes[i] == DI_SLIDER)
						{
						str = "";
						
						//add indentation to str
						for(j=0; j<INDENTATION_DI_TITLE; j++)
							str += " ";
						
						//add name and value to str
						str += BR_DINames[i] + " = ";
						str += GetDialogVariable(thisBlockNumber, BR_DINames[i], 0, 0) + ", ";
						str += GetDialogVariable(thisBlockNumber, BR_DINames[i], 0, 1) + ", ";
						str += GetDialogVariable(thisBlockNumber, BR_DINames[i], 0, 2);
						
						//write str
						FileWrite(sysGlobal1, str, "", TRUE); 
						
						//add carriage return
		//				FileWrite(sysGlobal1, "", "", TRUE);
						}
					
					else if(BR_DITypes[i] == DI_METER  ||  BR_DITypes[i] == DI_EDITABLE_TEXT  ||  BR_DITypes[i] == DI_DYNAMIC_TEXT  ||  BR_DITypes[i] == DI_TEXT_31)
						{
						str = "";
						
						//add indentation to str
						for(j=0; j<INDENTATION_DI_TITLE; j++)
							str += " ";
						
						//add name and value to str
						str += BR_DINames[i] + " = " + GetDialogVariable(thisBlockNumber, BR_DINames[i], 0, 0);
						
						//write str
						FileWrite(sysGlobal1, str, "", TRUE); 
						
						//add carriage return
		//				FileWrite(sysGlobal1, "", "", TRUE);
						}
					
					}//if(reportType == REPORT_DIALOGS)
					
				}//for(i=0; i<numDialogItems; i++)
				
			//add two carriage returns to create some distance in the report for the next block's info
			FileWrite(sysGlobal1, "", "", TRUE); 
			FileWrite(sysGlobal1, "", "", TRUE); 
			
			DisposeArray(BR_DINames);
			DisposeArray(BR_DITypes);
			}
		}
	
}//on BlockReport









