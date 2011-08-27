var VideoDL = {};
var Tifs = {fs: Titanium.Filesystem};
var videos = [];

VideoDL.init = function()
{
	var vidapp = this;
	this.db = Titanium.Database.open("videodb");

	this.contentArea = $('#ytid');
	//VideoDL.prototype.hide();
	// Load all the topics
	VideoDL.loadVideos();

}

VideoDL.loadVideos = function()
{

	var xhr = Titanium.Network.createHTTPClient();
	xhr.onload = function() {
		VideoDL.startTimer();
		var vidjson = JSON.parse(this.responseData);
		$.each(vidjson, function(i) {
			if (vidjson[i].disabled === false) {
				if($.inArray(vidjson[i].youtube_id,videos)) {
					videos[i] = vidjson[i].youtube_id;
				};
				
			};
		});
		
		$.each(videos, function(i) {
			$('#ytid').append(VideoDL.Video(videos[i]));
		});
    };
	xhr.open("GET", "http://freefallhighscore.heroku.com/videos.json");
	xhr.send();
	
	/*topicDir.getDirectoryListing().forEach(function(videoFile)
	{
		var video = new VideoDL.Video(videoFile);
		vidapp.contentArea.append(video.contentDiv);
		vidapp.videos.push(topic);
	});*/

	//this.currentVideo = this.videos[0];
	//this.currentVideo.show();
}


VideoDL.Video = function(youtube_id)
{
	// Load topic content text
	this.contentDiv = $('<div class="video_content" id="yt_'+ youtube_id +'">');
	this.ytIframe = $('<iframe frameborder="0">');
	this.ytIframe.attr('src','http://www.youtube.com/embed/' + youtube_id + '?version=3&loop=1&autoplay=1&theme=dark&autohide=2&controls=0&modestbranding=1&showinfo=0');
	//this.ytIframe.attr('src','http://www.youtube.com/embed/' + youtube_id);
	this.contentDiv.append(this.ytIframe);
	//this.contentDiv.hide();
	
	return this.contentDiv;

}

VideoDL.startTimer = function()
{
	setTimeout(function() {
		alert(videos[4]);
	}, 2000);
	
	setInterval(function() {
		VideoDL.loadVideos();
	},300000);
}

VideoDL.Video.prototype.show = function()
{
	this.contentArea.fadeIn(1000);
}

VideoDL.Video.prototype.hide = function()
{
	this.contentArea.fadeOut(1000);
}