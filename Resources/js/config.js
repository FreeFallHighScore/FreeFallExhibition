var VideoConfig = {};
var Tifs = {fs: Titanium.Filesystem};

VideoConfig.init = function()
{
	this.db = Titanium.Database.open("videodb");
	VideoConfig.openConfig();
}

VideoConfig.openConfig = function()
{
	Titanium.UI.createWindow({
        id: "configWindow",
        url: "app://config.html",
        title: "Exhibition Configuration",
        width: 500,
        minWidth: 500,
        maxWidth: 500,
        height: 500,
        minHeight: 500,
        maxHeight: 500,
        maximizable: false,
        minimizable: true,
        closeable: true,
        resizable: false,
        fullscreen: false,
        maximized: false,
        minimized: false,
        usingChrome: true,
        topMost: true,
        visible: true,
        transparentBackground: false,
        transparency: false
    });
}