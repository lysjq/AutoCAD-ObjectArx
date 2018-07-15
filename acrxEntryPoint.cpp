// (C) Copyright 2002-2012 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- acrxEntryPoint.cpp
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
#include "CLayerUtil.h"
#include "CIOUtil.h"
#include "CViewUtil.h"
#include "CGetInputUtil.h"
#include "CJig.h"
//-----------------------------------------------------------------------------
#define szRDS _RXST("lys")
//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CSymbolTableApp : public AcRxArxApp {

public:
	CSymbolTableApp () : AcRxArxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		// TODO: Load dependencies here

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		
		// TODO: Add your initialization code here

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		// TODO: Add your code here

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;
		// TODO: Unload dependencies here

		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
	}
	
	// The ACED_ARXCOMMAND_ENTRY_AUTO macro can be applied to any static member 
	// function of the CSymbolTableApp class.
	// The function should take no arguments and return nothing.
	//
	// NOTE: ACED_ARXCOMMAND_ENTRY_AUTO has overloads where you can provide resourceid and
	// have arguments to define context and command mechanism.
	
	// ACED_ARXCOMMAND_ENTRY_AUTO(classname, group, globCmd, locCmd, cmdFlags, UIContext)
	// ACED_ARXCOMMAND_ENTRYBYID_AUTO(classname, group, globCmd, locCmdId, cmdFlags, UIContext)
	// only differs that it creates a localized name using a string in the resource file
	//   locCmdId - resource ID for localized command

	// Modal Command with localized name
	// ACED_ARXCOMMAND_ENTRY_AUTO(CSymbolTableApp, lysMyGroup, MyCommand, MyCommandLocal, ACRX_CMD_MODAL)
	static void lysMyGroupMyCommand () {
		// Put your command code here
		acedInitGet(NULL, _T("W C O"));
		TCHAR Name[40];
		int rc = acedGetString(0, _T("\n输入一个字符[W/C/O]: "), Name);
		while (rc==RTNORM||rc==RTKWORD)
		{
			if (rc == RTKWORD)
			{
				TCHAR kword[20];
				if (acedGetInput(kword)!=RTNORM)
				{
					return;
				}
				else if (_tcscmp(kword,_T("W"))==0)
				{
					acutPrintf(_T("输入了W"));
				}
				else if (_tcscmp(kword,_T("C"))==0)
				{
					acutPrintf(_T("输入了C"));
				}
				else if (_tcscmp(kword, _T("O")) == 0)
				{
					acutPrintf(_T("输入了0"));
				}
				else
				{
					acutPrintf(_T("输入了无效字符"));
				}
			}
			if (rc==RTNONE)
			{ 
				acutPrintf(_T("输入了ESC"));
				return;
			}
			if (rc==RTCAN)
			{
				acutPrintf(_T("输入了Enter"));
				return;
			}
			acedInitGet(NULL, _T("W C O"));
			rc = acedGetString(0, _T("\n输入一个字符[W/C/O]: "), Name);
		}

	}
	static void lysMyGroupHello()
	{
		AcDbDatabase *pDatebase = new AcDbDatabase(true,false);
		AcDbBlockTable *pBlockTable = NULL;
		pDatebase->getBlockTable(pBlockTable);
		AcDbBlockTableRecord *pBlockTableRec = NULL;
		pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRec, kForWrite);

		AcDbCircle *pCircle = new AcDbCircle(AcGePoint3d(10, 10, 0), AcGeVector3d(0, 0, 1), 10);
		AcDbLine *pLine = new AcDbLine(AcGePoint3d(0, 10, 0), AcGePoint3d(20, 10, 0));

		pBlockTableRec->appendAcDbEntity(pCircle);
		pBlockTableRec->appendAcDbEntity(pLine);

		pBlockTableRec->close();
		pBlockTable->close();
		pCircle->close();
		pLine->close();
		CString  path = _T("F:\\lingys.dwg");
		pDatebase->saveAs(path);

		delete pDatebase;

	}
	
	static void lysMyGroupImport()
	{
		AcGePoint3d centerpoint;
		CGetInputUtil::GetPoint(_T("\n指定中心点"), centerpoint);
		CJig jig;
		AcDbObjectId polyid;
		if (jig.doit(centerpoint, polyid))
		{
			acutPrintf(_T("\n创建成功"));
		}
		else
		{
			AcDbEntity *pEntity;
			if (acdbOpenObject(pEntity,polyid,AcDb::kForWrite)==Acad::eOk)
			{
				pEntity->erase();
				pEntity->close();
				acutPrintf(_T("\n创建取消"));
			}
		}
	}
	// Modal Command with pickfirst selection
	// ACED_ARXCOMMAND_ENTRY_AUTO(CSymbolTableApp, lysMyGroup, MyPickFirst, MyPickFirstLocal, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET)
	static void lysMyGroupMyPickFirst () {
		ads_name result ;
		int iRet =acedSSGet (ACRX_T("_I"), NULL, NULL, NULL, result) ;
		if ( iRet == RTNORM )
		{
			// There are selected entities
			// Put your command using pickfirst set code here
		}
		else
		{
			// There are no selected entities
			// Put your command code here
		}
	}

	// Application Session Command with localized name
	// ACED_ARXCOMMAND_ENTRY_AUTO(CSymbolTableApp, lysMyGroup, MySessionCmd, MySessionCmdLocal, ACRX_CMD_MODAL | ACRX_CMD_SESSION)
	static void lysMyGroupMySessionCmd () {
		// Put your command code here
	}


	// The ACED_ADSFUNCTION_ENTRY_AUTO / ACED_ADSCOMMAND_ENTRY_AUTO macros can be applied to any static member 
	// function of the CSymbolTableApp class.
	// The function may or may not take arguments and have to return RTNORM, RTERROR, RTCAN, RTFAIL, RTREJ to AutoCAD, but use
	// acedRetNil, acedRetT, acedRetVoid, acedRetInt, acedRetReal, acedRetStr, acedRetPoint, acedRetName, acedRetList, acedRetVal to return
	// a value to the Lisp interpreter.
	//
	// NOTE: ACED_ADSFUNCTION_ENTRY_AUTO / ACED_ADSCOMMAND_ENTRY_AUTO has overloads where you can provide resourceid.
	
	//- ACED_ADSFUNCTION_ENTRY_AUTO(classname, name, regFunc) - this example
	//- ACED_ADSSYMBOL_ENTRYBYID_AUTO(classname, name, nameId, regFunc) - only differs that it creates a localized name using a string in the resource file
	//- ACED_ADSCOMMAND_ENTRY_AUTO(classname, name, regFunc) - a Lisp command (prefix C:)
	//- ACED_ADSCOMMAND_ENTRYBYID_AUTO(classname, name, nameId, regFunc) - only differs that it creates a localized name using a string in the resource file

	// Lisp Function is similar to ARX Command but it creates a lisp 
	// callable function. Many return types are supported not just string
	// or integer.
	// ACED_ADSFUNCTION_ENTRY_AUTO(CSymbolTableApp, MyLispFunction, false)
	static int ads_MyLispFunction () {
		//struct resbuf *args =acedGetArgs () ;
		
		// Put your command code here

		//acutRelRb (args) ;
		
		// Return a value to the AutoCAD Lisp Interpreter
		// acedRetNil, acedRetT, acedRetVoid, acedRetInt, acedRetReal, acedRetStr, acedRetPoint, acedRetName, acedRetList, acedRetVal

		return (RTNORM) ;
	}
	
} ;
//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CSymbolTableApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CSymbolTableApp, lysMyGroup, MyCommand, lingys, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CSymbolTableApp, lysMyGroup, Hello, Hello, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CSymbolTableApp, lysMyGroup, Import, MyImport,ACRX_CMD_MODAL,NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CSymbolTableApp, lysMyGroup, MyPickFirst, MyPickFirstLocal, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CSymbolTableApp, lysMyGroup, MySessionCmd, MySessionCmdLocal, ACRX_CMD_MODAL | ACRX_CMD_SESSION, NULL)
ACED_ADSSYMBOL_ENTRY_AUTO(CSymbolTableApp, MyLispFunction, false)

 