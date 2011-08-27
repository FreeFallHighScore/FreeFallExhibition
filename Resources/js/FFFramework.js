var FFFramework = {
	
	db: Titanium.Database.open("videodb"),
	contentArea: $('#ytid'),
	videos: [],
	vidHeight: 333,
	vidWidth: 540,
	TimerLength: 300000,
	
	init: function() {
		FFFramework.loadVideos();
	},
	
	loadVideos: function() {
		var xhr = Titanium.Network.createHTTPClient();
		xhr.onload = function() {
			FFFramework.startTimer();
			var vidjson = JSON.parse(this.responseData);
			$.each(vidjson, function(i) {
				//alert(i);
				if (vidjson[i].disabled === false) {
					if($.inArray(vidjson[i].youtube_id,FFFramework.videos)) {
						FFFramework.videos[i] = vidjson[i].youtube_id;
					};
					
				};
			});
			
			$.each(FFFramework.videos, function(i) {
				$('#ytid').append(FFFramework.Video(FFFramework.videos[i]));
			});
	    };
		xhr.open("GET", "http://freefallhighscore.heroku.com/videos.json");
		xhr.send();
	},
	
	Video: function(youtube_id) {
		var contentDiv = $('<div class="video_content" id="yt_'+ youtube_id +'">');
		var ytIframe = $('<iframe frameborder="0">');
		
		ytIframe.attr('src','http://www.youtube.com/embed/' + youtube_id + '?version=3&loop=1&autoplay=1&theme=dark&autohide=2&controls=0&modestbranding=1&showinfo=0');
		contentDiv.append(ytIframe);
		
		
		return contentDiv;
	},
	
	startTimer: function() {
		setTimeout(function() {
			alert(FFFramework.videos[4]);
		}, 2000);
		
		var vidTimer = setInterval(function() {
							FFFramework.loadVideos();
						},FFFramework.TimerLength);
	},
	
	restartTimer: function() {
		clearInterval(vidTimer);
		FFFramework.startTimer();
	},
	
	openConfig: function() {
		var configWindow = Titanium.UI.createWindow({
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
	    
	    configWindow.open();
	}
	
};
