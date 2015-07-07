program MicroBoot;
//***************************************************************************************
// Project Name: MicroBoot for Borland Delphi
//  Description: Contains the main program entry
//    File Name: MicroBoot.dpr
//
//---------------------------------------------------------------------------------------
//                          C O P Y R I G H T
//---------------------------------------------------------------------------------------
//   Copyright (c) 2011 by Feaser    http://www.feaser.com    All rights reserved
//
//   This software has been carefully tested, but is not guaranteed for any particular
// purpose. The author does not offer any warranties and does not guarantee the accuracy,
//   adequacy, or completeness of the software and is not responsible for any errors or
//              omissions or the results obtained from use of the software.
//
//---------------------------------------------------------------------------------------
//                            L I C E N S E
//---------------------------------------------------------------------------------------
// This file is part of OpenBLT. OpenBLT is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// OpenBLT is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with OpenBLT.
// If not, see <http://www.gnu.org/licenses/>.
//
// A special exception to the GPL is included to allow you to distribute a combined work
// that includes OpenBLT without being obliged to provide the source code for any
// proprietary components. The exception text is included at the bottom of the license
// file <license.html>.
//
//***************************************************************************************

uses
  Forms,
  MainUnit in 'MainUnit.pas' {mainForm},
  SettingsUnit in 'SettingsUnit.pas' {settingsForm},
  StopWatch in 'StopWatch.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.Title := 'MicroBoot';
  Application.CreateForm(TmainForm, mainForm);
  Application.CreateForm(TsettingsForm, settingsForm);
  Application.Run;
end.
//******************************** end of MicroBoot.dpr *********************************

