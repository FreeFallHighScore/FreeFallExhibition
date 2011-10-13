// 
//  main.js
//  FreeFallExhibition
//  
//  Created by Logan Best on 2011-08-27.
//  Copyright 2011 Logan Best. All rights reserved.
//
//  Description: Creates all application menus, namely the config menu.
// 

var createMenuItem = Titanium.UI.createMenuItem;
var createMenu = Titanium.UI.createMenu;

var configMenu = createMenu();
	configMenu.appendItem(createMenuItem("Configuration"));

var configSubMenu = createMenu();
	configSubMenu.appendItem(createMenuItem("Open Config", function(e) {
	    FFFramework.openConfig();
	}));
	configMenu.getItemAt(0).setSubmenu(configSubMenu);
	
Titanium.UI.currentWindow.menu = configMenu;