// Chiu, 03/20/2015 //
// This is the first include file tested to generate popup menu when select icon popup menu is clicked in Time Manager Block //

String array_SelectIcon[];
String gs_SelectIconLabel;



Procedure SelectIconPopupMenu() // create module assembly dropdown menu
{
	String ls_DialogName;
	Integer DBTableIndex_IconView;
	Integer li_UserResponse;
	Integer li_StringPosition;
	String li_TempIconLabel;
	
		
	DBIndex = DBDatabaseGetIndex("Data Exchange");
	DBTableIndex_IconView = DBTableGetIndex(DBIndex, gs_DBTableName_IconView);
		
	ls_DialogName = WhichDialogItemClicked();
	
	if (ls_DialogName == "pop_SelectIcon")
	{
		*** Generate Module Assembly dropdown menu ***
		MakeArray(array_SelectIcon, DBRecordsGetNum(DBIndex, DBTableIndex_IconView));
		
		for (i = 0; i < DBRecordsGetNum(DBIndex, DBTableIndex_IconView); i++)
		{
			array_SelectIcon[i] = DBDataGetAsString(DBIndex, DBTableIndex_IconView, 2, i+1);
			
			if (array_SelectIcon[i] == gs_SelectIconLabel) array_SelectIcon[i] = "<b>" + array_SelectIcon[i];
		}
		
		*** popup dropdown menu when "ImportAssembledModule_pop" button is clicked ***
		li_UserResponse = PopupMenuArray(array_SelectIcon, 0) - 1;
		
		for (i = 0; i < DBRecordsGetNum(DBIndex, DBTableIndex_IconView); i++)
		{
			if (li_UserResponse == i)
			{
				gs_SelectIconLabel = array_SelectIcon[i];
				
				li_StringPosition = StrFind(gs_SelectIconLabel, "<b>", 0, 0);
				if (li_StringPosition >= 0)
				{
					li_TempIconLabel = StrPart(gs_SelectIconLabel, StrLen("<b>"), StrLen(gs_SelectIconLabel)-StrLen("<b>"));
					gs_SelectIconLabel = li_TempIconLabel;
				}
				
				
				SetPopupLabels("pop_SelectIcon", array_SelectIcon[i]);
				#ifdef txt_IconViewLabel
				txt_IconViewLabel = gs_SelectIconLabel;
				#endif
				DIPopupButton(myblocknumber(), "pop_SelectIcon", TRUE);
			}
		}
		
		if (li_UserResponse < 0) ABORT;
		
		else
		{
			gs_IconName = DBDataGetAsString(DBIndex, DBTableIndex_IconView, 1, li_UserResponse+1);
			
			dialogPicture("lbl_IconPreview", gs_IconName, TRUE);
		}
		
		DisposeArray(array_SelectIcon);
	}
}
