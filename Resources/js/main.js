var createMenuItem = Titanium.UI.createMenuItem;
var createMenu = Titanium.UI.createMenu;

var mainMenu = createMenu();
	mainMenu.appendItem(createMenuItem("Configuration"));

var menu = createMenu();
	menu.appendItem(createMenuItem("Open Config", function() {
	    VideoConfig.init();
	}));
	mainMenu.getItemAt(0).setSubmenu(menu);
	
Titanium.UI.currentWindow.menu = mainMenu;



